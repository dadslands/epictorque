#****************************************************************************************
# \file         CMakeLists.txt
# \brief        CMake descriptor file for the OpenBLT host library.
# \internal
#----------------------------------------------------------------------------------------
#                          C O P Y R I G H T
#----------------------------------------------------------------------------------------
#   Copyright (c) 2017  by Feaser    http://www.feaser.com    All rights reserved
#
#----------------------------------------------------------------------------------------
#                            L I C E N S E
#----------------------------------------------------------------------------------------
# This file is part of OpenBLT. OpenBLT is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# OpenBLT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE. See the GNU General Public License for more details.
#
# You have received a copy of the GNU General Public License along with OpenBLT. It 
# should be located in ".\Doc\license.html". If not, contact Feaser to obtain a copy.
# 
# \endinternal
#****************************************************************************************
# Specify the version being used aswell as the language
cmake_minimum_required(VERSION 3.10)


#****************************************************************************************
# Project configuration
#****************************************************************************************
# Specify the project name
project(LibOpenBLT)

# Build debug version by default
set(CMAKE_BUILD_TYPE "Debug")


#****************************************************************************************
# Options
#****************************************************************************************
# Add option with default value to enable the generation and building of the shared
# library. By default it is turned on. It can be overridden on the command line when 
# CMake is called using the following parameter: -DBUILD_SHARED=OFF
option(BUILD_SHARED "Configurable to enable/disable building of the shared library" ON)

# Add option with default value to enable the generation and building of the static
# library. By default it is turned off. It can be overridden on the command line when 
# CMake is called using the following parameter: -DBUILD_STATIC=ON
option(BUILD_STATIC "Configurable to enable/disable building of the static library" OFF)

# Add option with default value to disable the generation of the PC-lint target. It can 
# be overridden on the command line when CMake is called using the following parameter:
# -DLINT_ENABLED=ON  
option(LINT_ENABLED "Configurable to enable/disable the PC-lint target" OFF)


#****************************************************************************************
# Directories
#****************************************************************************************
# Set the port directory, which is platform specific
if(WIN32)
  set(PROJECT_PORT_DIR ${PROJECT_SOURCE_DIR}/port/windows)
elseif(UNIX)
  set(PROJECT_PORT_DIR ${PROJECT_SOURCE_DIR}/port/linux)
endif(WIN32)

# Set the output directory
set (PROJECT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../..)

# Set the output directory for the generic no-config case (e.g. with mingw)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY} )
# Set the output directory for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_OUTPUT_DIRECTORY} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_OUTPUT_DIRECTORY} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_OUTPUT_DIRECTORY} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

#****************************************************************************************
# Compiler flags
#****************************************************************************************
# Set platform specific compiler macro PLATFORM_XXX
if(WIN32)
  if(CMAKE_C_COMPILER_ID MATCHES GNU)  
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPLATFORM_WIN32 -D_CRT_SECURE_NO_WARNINGS -std=gnu99")
  elseif(CMAKE_C_COMPILER_ID MATCHES MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPLATFORM_WIN32 -D_CRT_SECURE_NO_WARNINGS")
  endif()
elseif(UNIX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPLATFORM_LINUX -pthread -std=gnu99")
endif(WIN32)

# Configure a statically linked run-time library for msvc
if(WIN32)
  if(CMAKE_C_COMPILER_ID MATCHES MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()
endif(WIN32)


#***************************************************************************************
# Includes
#****************************************************************************************
# Source: http://www.vtk.org/Wiki/CMake/Examples
macro (header_directories return_list dir)
  file(GLOB_RECURSE new_list ${dir}/*.h)
  set(dir_list "")
  foreach(file_path ${new_list})
    get_filename_component(dir_path ${file_path} PATH)
    set(dir_list ${dir_list} ${dir_path})
  endforeach()
  list(REMOVE_DUPLICATES dir_list)
  set(${return_list} ${dir_list})
endmacro()

# Set include directories
header_directories(PROJECT_PORT_INC_DIRS "${PROJECT_PORT_DIR}")
include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_PORT_INC_DIRS}")


#***************************************************************************************
# Files
#****************************************************************************************
# Get header files from the root directory and the port directory.
file(GLOB INCS_ROOT "*.h")
file(GLOB_RECURSE INCS_PORT "${PROJECT_PORT_DIR}/*.h")
set(INCS ${INCS_ROOT} ${INCS_PORT})

# Get source files from the root directory and the port directory.
file(GLOB SRCS_ROOT "*.c")
file(GLOB_RECURSE SRCS_PORT "${PROJECT_PORT_DIR}/*.c")
set(SRCS ${SRCS_ROOT} ${SRCS_PORT})

# Add sources
set(
  LIB_SRCS 
  ${SRCS}
  ${INCS}
)


#***************************************************************************************
# Targets
#****************************************************************************************
# Only generate the static library taget if the option is enabled. Use 
# "make openblt_static" to individually build the static library. 
# Note that when you link your own application to the static library of LibOpenBLT under
# Unix, you need to also link the LibUsb and LibDL libraries by adding usb-1.0 and dl to
# the linker library dependencies. Under Windows, you need to also link the Winsock
# library by adding ws2_32 to the linker library dependencies. 
if(BUILD_STATIC)
  add_library(openblt_static STATIC ${LIB_SRCS})
  SET_TARGET_PROPERTIES(openblt_static PROPERTIES OUTPUT_NAME openblt CLEAN_DIRECT_OUTPUT 1)
endif(BUILD_STATIC)

# Only generate the shared library taget if the option is enabled. Use 
# "make openblt_shared" to build individually  shared library.
if(BUILD_SHARED)
  add_library(openblt_shared SHARED ${LIB_SRCS})
  if(UNIX)
    # Under Unix the LibUsb library (http://libusb.info/) is needed for the USB support.
    # Make sure the libusb-1.0-0 and  libusb-1.0-0-dev packages are installed to be able to
    # build LibOpenBLT. Example under Debian/Ubuntu:
    #   sudo apt-get install libusb-1.0-0 libusb-1.0-0-dev
    # Additionally, the LibDL is needed for dynamic library loading.
    # According to the CMake docs, item names starting with '-', but not '-l' or 
    # '-framework', are treated as linker flags. This means "-Wl" type linker flags can be
    # specified here. Use this to add the path of the shared library to the library search 
    # path. This way an (optional) seed and key shared library file can simply be in the
    # same directory as the LibOpenBLT shared library.
    target_link_libraries(openblt_shared usb-1.0 dl "-Wl,-rpath,.")
  elseif(WIN32)
    # Link the Winsock library
    target_link_libraries(openblt_shared ws2_32)
  endif(UNIX)  
  if(CMAKE_C_COMPILER_ID MATCHES MSVC)
    # Microsoft Visual Studio does not add "lib" to the name of the DLL, whereas GCC
    # (including MinGW) does. Correct this here.
    SET_TARGET_PROPERTIES(openblt_shared PROPERTIES OUTPUT_NAME libopenblt CLEAN_DIRECT_OUTPUT 1)
  else()
    SET_TARGET_PROPERTIES(openblt_shared PROPERTIES OUTPUT_NAME openblt CLEAN_DIRECT_OUTPUT 1)
  endif()
endif(BUILD_SHARED)

# Only generate the PC-lint taget if the option is enabled. Use "make openblt_LINT" to 
# lint the project sources
if(LINT_ENABLED)
  # Include PC-lint configuration file for the correct compiler. Currently GNU GCC and
  # Microsoft Visual Studio are supported.
  if(CMAKE_C_COMPILER_ID MATCHES GNU)  
    include(${PROJECT_SOURCE_DIR}/lint/gnu/pc_lint.cmake)
  elseif(CMAKE_C_COMPILER_ID MATCHES MSVC)
    include(${PROJECT_SOURCE_DIR}/lint/msvc/pc_lint.cmake)
  endif()

  # Generate the PC-lint target.  
  if(COMMAND add_pc_lint)
    add_pc_lint(openblt ${LIB_SRCS})
  endif(COMMAND add_pc_lint)
endif(LINT_ENABLED)


#*********************************** end of CMakeLists.txt ****************************** 
