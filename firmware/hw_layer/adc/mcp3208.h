/*
*
 * @date 2024-12-16
 *
 * @author gurov
 */

#ifdef EFI_MCP_3208

#pragma once

#include "global.h"
#include "efifeatures.h"
#include <hal.h>

#define MCP3208_ADCCH 8

#ifndef BOARD_MCP3208_COUNT
#define BOARD_MCP3208_COUNT 1
#endif

#if EFI_MCP_3208 && !EFI_SIMULATOR

#ifndef MAX31855KASAT_COUNT
#define MAX31855KASAT_COUNT 8
#endif

struct mcp3208_config {
#if HAL_USE_SPI
	SPIDriver		*spi_bus;
	SPIConfig	spi_config;
    Gpio cs;
#endif
	struct {
		ioportid_t		port;
		uint_fast8_t	pad;
	} reset;
};


int mcp3208_add(brain_pin_e base, unsigned int index, const struct mcp3208_config *cfg);


#define LIS3DH_DI_MASK                     0xFF
#define LIS3DH_DI(n)                       (1 << n)
#define LIS3DH_AD_MASK                     0x3F
#define LIS3DH_AD(n)                       (1 << n)
#define LIS3DH_MS                          (1 << 6)
#define LIS3DH_RW                          (1 << 7)

#define  LIS3DH_AD_OUT_T                   0x0C
#define  LIS3DH_AD_INFO1                   0x0D
#define  LIS3DH_AD_INFO2                   0x0E
#define  LIS3DH_AD_OFF_X                   0x10
#define  LIS3DH_AD_OFF_Y                   0x11
#define  LIS3DH_AD_OFF_Z                   0x12
#define  LIS3DH_AD_CS_X                    0x13
#define  LIS3DH_AD_CS_Y                    0x14
#define  LIS3DH_AD_CS_Z                    0x15
#define  LIS3DH_AD_LC_L                    0x16
#define  LIS3DH_AD_LC_H                    0x17
#define  LIS3DH_AD_STAT                    0x18
#define  LIS3DH_AD_PEAK1                   0x19
#define  LIS3DH_AD_PEAK2                   0x1A
#define  LIS3DH_AD_VFC_1                   0x1B
#define  LIS3DH_AD_VFC_2                   0x1C
#define  LIS3DH_AD_VFC_3                   0x1D
#define  LIS3DH_AD_VFC_4                   0x1E
#define  LIS3DH_AD_THRS3                   0x1F


#define  LIS3DH_AD_WHO_AM_I                0x0F
#define  LIS3DH_AD_CTRL_REG1               0x20
#define  LIS3DH_AD_CTRL_REG2               0x21
#define  LIS3DH_AD_CTRL_REG3               0x22
#define  LIS3DH_AD_CTRL_REG4               0x23
#define  LIS3DH_AD_CTRL_REG5               0x24
#define  LIS3DH_AD_CTRL_REG6               0x25
#define  LIS3DH_AD_STATUS                  0x27
#define  LIS3DH_AD_OUT_X_L                 0x28
#define  LIS3DH_AD_OUT_X_H                 0x29
#define  LIS3DH_AD_OUT_Y_L                 0x2A
#define  LIS3DH_AD_OUT_Y_H                 0x2B
#define  LIS3DH_AD_OUT_Z_L                 0x2C
#define  LIS3DH_AD_OUT_Z_H                 0x2D


#define  LIS3DH_AD_REF                     0x26

#define  LIS3DH_AD_FIFO_CTRL               0x2E
#define  LIS3DH_AD_FIFO_SRC                0x2F
#define  LIS3DH_AD_ST1_0                   0x40
#define  LIS3DH_AD_ST1_1                   0x41
#define  LIS3DH_AD_ST1_2                   0x42
#define  LIS3DH_AD_ST1_3                   0x43
#define  LIS3DH_AD_ST1_4                   0x44
#define  LIS3DH_AD_ST1_5                   0x45
#define  LIS3DH_AD_ST1_6                   0x46
#define  LIS3DH_AD_ST1_7                   0x47
#define  LIS3DH_AD_ST1_8                   0x48
#define  LIS3DH_AD_ST1_9                   0x49
#define  LIS3DH_AD_ST1_A                   0x4A
#define  LIS3DH_AD_ST1_B                   0x4B
#define  LIS3DH_AD_ST1_C                   0x4C
#define  LIS3DH_AD_ST1_D                   0x4D
#define  LIS3DH_AD_ST1_E                   0x4E
#define  LIS3DH_AD_ST1_F                   0x4F
#define  LIS3DH_AD_TIM4_1                  0x50
#define  LIS3DH_AD_TIM3_1                  0x51
#define  LIS3DH_AD_TIM2_1_L                0x52
#define  LIS3DH_AD_TIM2_1_H                0x53
#define  LIS3DH_AD_TIM1_1_L                0x54
#define  LIS3DH_AD_TIM1_1_H                0x55
#define  LIS3DH_AD_THRS2_1                 0x56
#define  LIS3DH_AD_THRS1_1                 0x57
#define  LIS3DH_AD_MASK1_B                 0x59
#define  LIS3DH_AD_MASK1_A                 0x5A
#define  LIS3DH_AD_SETT1                   0x5B
#define  LIS3DH_AD_PR1                     0x5C
#define  LIS3DH_AD_TC1_L                   0x5D
#define  LIS3DH_AD_TC1_H                   0x5E
#define  LIS3DH_AD_OUTS1                   0x5F
#define  LIS3DH_AD_ST2_0                   0x60
#define  LIS3DH_AD_ST2_1                   0x61
#define  LIS3DH_AD_ST2_2                   0x62
#define  LIS3DH_AD_ST2_3                   0x63
#define  LIS3DH_AD_ST2_4                   0x64
#define  LIS3DH_AD_ST2_5                   0x65
#define  LIS3DH_AD_ST2_6                   0x66
#define  LIS3DH_AD_ST2_7                   0x67
#define  LIS3DH_AD_ST2_8                   0x68
#define  LIS3DH_AD_ST2_9                   0x69
#define  LIS3DH_AD_ST2_A                   0x6A
#define  LIS3DH_AD_ST2_B                   0x6B
#define  LIS3DH_AD_ST2_C                   0x6C
#define  LIS3DH_AD_ST2_D                   0x6D
#define  LIS3DH_AD_ST2_E                   0x6E
#define  LIS3DH_AD_ST2_F                   0x6F
#define  LIS3DH_AD_TIM4_2                  0x70
#define  LIS3DH_AD_TIM3_2                  0x71
#define  LIS3DH_AD_TIM2_2_L                0x72
#define  LIS3DH_AD_TIM2_2_H                0x73
#define  LIS3DH_AD_TIM1_2_L                0x74
#define  LIS3DH_AD_TIM1_2_H                0x75
#define  LIS3DH_AD_THRS2_2                 0x76
#define  LIS3DH_AD_THRS1_2                 0x77
#define  LIS3DH_AD_DES2                    0x78
#define  LIS3DH_AD_MASK2_B                 0x79
#define  LIS3DH_AD_MASK2_A                 0x7A
#define  LIS3DH_AD_SETT2                   0x7B
#define  LIS3DH_AD_PR2                     0x7C
#define  LIS3DH_AD_TC2_L                   0x7D
#define  LIS3DH_AD_TC2_H                   0x7E
#define  LIS3DH_AD_OUTS2                   0x7F



/**
 * @brief   LIS3DH full scale.
 */
typedef enum {
  LIS3DH_ACC_FS_2G = 0x00,         /**< Full scale �2g.                    */
  LIS3DH_ACC_FS_4G = 0x08,         /**< Full scale �4g.                    */
  LIS3DH_ACC_FS_6G = 0x10,         /**< Full scale �6g.                    */
  LIS3DH_ACC_FS_8G = 0x18,         /**< Full scale �8g.                    */
  LIS3DH_ACC_FS_16G = 0x20         /**< Full scale �16g.                   */
}lis3dh_acc_fs_t;

/**
 * @brief   LIS3DH output data rate.
 */
typedef enum {
  LIS3DH_ACC_ODR_PD = 0x00,        /**< ODR 100 Hz.                        */
  LIS3DH_ACC_ODR_3_125HZ = 0x10,   /**< ODR 3.125 Hz.                      */
  LIS3DH_ACC_ODR_6_25HZ = 0x20,    /**< ODR 6.25 Hz.                       */
  LIS3DH_ACC_ODR_12_5HZ = 0x30,    /**< ODR 12.5 Hz.                       */
  LIS3DH_ACC_ODR_25HZ = 0x40,      /**< ODR 25 Hz.                         */
  LIS3DH_ACC_ODR_50HZ = 0x50,      /**< ODR 50 Hz.                         */
  LIS3DH_ACC_ODR_100HZ = 0x60,     /**< ODR 100 Hz.                        */
  LIS3DH_ACC_ODR_400HZ = 0x70,     /**< ODR 400 Hz.                        */
  LIS3DH_ACC_ODR_800HZ = 0x80,     /**< ODR 800 Hz.                        */
  LIS3DH_ACC_ODR_1600HZ = 0x90     /**< ODR 1600 Hz.                       */
}lis3dh_acc_odr_t;

/**
 * @brief   LIS3DH anti-aliasing bandwidth.
 */
typedef enum {
  LIS3DH_ACC_BW_800HZ = 0x00,      /**< AA filter BW 800Hz.                */
  LIS3DH_ACC_BW_200HZ = 0x40,      /**< AA filter BW 200Hz.                */
  LIS3DH_ACC_BW_400HZ = 0x80,      /**< AA filter BW 400Hz.                */
  LIS3DH_ACC_BW_50HZ = 0xC0        /**< AA filter BW 50Hz.                 */
}lis3dh_acc_bw_t;

/**
 * @brief   LIS3DH block data update.
 */
typedef enum {
  LIS3DH_ACC_BDU_CONTINUOUS = 0x00,/**< Block data continuously updated.   */
  LIS3DH_ACC_BDU_BLOCKED = 0x80    /**< Block data updated after reading.  */
} lis3dh_acc_bdu_t;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
  LIS3DH_UNINIT = 0,               /**< Not initialized.                   */
  LIS3DH_STOP = 1,                 /**< Stopped.                           */
  LIS3DH_READY = 2,                /**< Ready.                             */
} lis3dh_state_t;


struct lis3dh_config {
  SPIDriver                 *spi_bus;
  SPIConfig           spi_config;
  Gpio cs;
};


//struct MAX31855KASAT_config {
//  SPIDriver                 *spi_bus;
//  SPIConfig           spi_config;
//  Gpio cs;
//};

#endif

#endif