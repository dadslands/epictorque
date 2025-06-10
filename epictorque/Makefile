# EpicTorque Build System
# Makefile for building and testing the torque control system

PROJECT_NAME = epictorque
VERSION = 1.0.0

# Directories
SRC_DIR = src
TEST_DIR = tests
DOCS_DIR = docs
BUILD_DIR = build
DIST_DIR = dist

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(SRC_DIR)/*.h)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
INCLUDES = -I$(SRC_DIR) -Iinclude
DEFINES = -DEFI_TORQUE_CONTROL=1 -DTORQUE_CONTROL_VERSION=1

# Test settings
TEST_CXXFLAGS = $(CXXFLAGS) -DEFI_UNIT_TEST=1
TEST_LIBS = -lgtest -lgtest_main -lpthread

# Default target
all: build

# Build the library
build: $(BUILD_DIR)/lib$(PROJECT_NAME).a

$(BUILD_DIR)/lib$(PROJECT_NAME).a: $(SOURCES) $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $(SOURCES)
	ar rcs $@ *.o
	@rm -f *.o
	@echo "Built $(PROJECT_NAME) library"

# Build tests
test: $(BUILD_DIR)/test_$(PROJECT_NAME)
	@echo "Running tests..."
	$(BUILD_DIR)/test_$(PROJECT_NAME)

$(BUILD_DIR)/test_$(PROJECT_NAME): $(TEST_SOURCES) $(SOURCES) $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(TEST_CXXFLAGS) $(INCLUDES) $(DEFINES) -o $@ $(TEST_SOURCES) $(SOURCES) $(TEST_LIBS)

# Performance benchmark
benchmark: $(BUILD_DIR)/benchmark_$(PROJECT_NAME)
	@echo "Running performance benchmark..."
	$(BUILD_DIR)/benchmark_$(PROJECT_NAME)

$(BUILD_DIR)/benchmark_$(PROJECT_NAME): $(TEST_DIR)/benchmark.cpp $(SOURCES) $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -DBENCHMARK_MODE=1 -o $@ $< $(SOURCES)

# Documentation
docs:
	@mkdir -p $(DOCS_DIR)/html
	doxygen Doxyfile
	@echo "Documentation generated in $(DOCS_DIR)/html"

# Package for distribution
package: clean build test
	@mkdir -p $(DIST_DIR)
	tar -czf $(DIST_DIR)/$(PROJECT_NAME)-$(VERSION).tar.gz \
		$(SRC_DIR) $(TEST_DIR) $(DOCS_DIR) \
		Makefile README.md LICENSE CHANGELOG.md \
		examples/ tunerstudio/
	@echo "Package created: $(DIST_DIR)/$(PROJECT_NAME)-$(VERSION).tar.gz"

# Install to rusEFI firmware directory
install: build
	@if [ -z "$(RUSEFI_DIR)" ]; then \
		echo "Error: RUSEFI_DIR not set. Use: make install RUSEFI_DIR=/path/to/rusefi"; \
		exit 1; \
	fi
	@echo "Installing to $(RUSEFI_DIR)/firmware/"
	cp -r $(SRC_DIR)/* $(RUSEFI_DIR)/firmware/
	cp tunerstudio/torque_control.ini $(RUSEFI_DIR)/tunerstudio/
	@echo "Installation complete. Add 'include firmware/torque_control.mk' to your Makefile"

# Development setup
dev-setup:
	@echo "Setting up development environment..."
	sudo apt-get update
	sudo apt-get install -y build-essential cmake git
	sudo apt-get install -y libgtest-dev doxygen graphviz
	@echo "Development environment ready"

# Code formatting
format:
	find $(SRC_DIR) $(TEST_DIR) -name "*.cpp" -o -name "*.h" | xargs clang-format -i
	@echo "Code formatted"

# Static analysis
analyze:
	cppcheck --enable=all --std=c++17 $(SRC_DIR)
	@echo "Static analysis complete"

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)
	rm -f *.o
	@echo "Cleaned build artifacts"

# Clean everything including docs
clean-all: clean
	rm -rf $(DOCS_DIR)/html
	@echo "Cleaned all generated files"

# Help
help:
	@echo "EpicTorque Build System"
	@echo "======================"
	@echo ""
	@echo "Targets:"
	@echo "  build      - Build the torque control library"
	@echo "  test       - Build and run unit tests"
	@echo "  benchmark  - Run performance benchmarks"
	@echo "  docs       - Generate documentation"
	@echo "  package    - Create distribution package"
	@echo "  install    - Install to rusEFI (requires RUSEFI_DIR)"
	@echo "  dev-setup  - Setup development environment"
	@echo "  format     - Format code with clang-format"
	@echo "  analyze    - Run static analysis"
	@echo "  clean      - Clean build artifacts"
	@echo "  clean-all  - Clean everything including docs"
	@echo "  help       - Show this help"
	@echo ""
	@echo "Examples:"
	@echo "  make build"
	@echo "  make test"
	@echo "  make install RUSEFI_DIR=/path/to/rusefi"

.PHONY: all build test benchmark docs package install dev-setup format analyze clean clean-all help
