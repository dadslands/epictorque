/*
    ChibiOS - Copyright (C) 2006..2020 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for STMicroelectronics STM32 Nucleo144-F429ZI board.
 */

/*
 * Board identifier.
 */
#define BOARD_AT_START_F435
#define BOARD_NAME                  "Artery AT-START-F435 board"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

// AT-START-F435 has crystal/ceramic resonator
//#define STM32_HSE_BYPASS

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the AT header.
 */
#define AT32F435xx

/*
 * IO pins assignments.
 */
/* TODO: */
#define GPIOA_BUTTON                0U
#define GPIOA_TIM2_CH1              0U
#define GPIOA_RMII_REF_CLK          1U
#define GPIOA_RMII_MDIO             2U
#define GPIOA_ARD_A0                3U
#define GPIOA_ADC123_IN3            3U
#define GPIOA_ZIO_D24               4U
#define GPIOA_SPI3_NSS              4U
#define GPIOA_ARD_D13               5U
#define GPIOA_SPI1_SCK              5U
#define GPIOA_ARD_D12               6U
#define GPIOA_SPI1_MISO             6U
#define GPIOA_ARD_D11               7U
#define GPIOA_SPI1_MOSI             7U
#define GPIOA_ZIO_D71               7U
#define GPIOA_RMII_RX_DV            7U
#define GPIOA_USB_SOF               8U
#define GPIOA_USART1_TX             9U
#define GPIOA_USART1_RX             10U
#define GPIOA_OTG1_DM               11U
#define GPIOA_OTG2_DP               12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_ZIO_D20               15U
#define GPIOA_I2S3_WS               15U

#define GPIOB_ZIO_D33               0U
#define GPIOB_TIM3_CH3              0U
#define GPIOB_LED1                  0U
#define GPIOB_ZIO_A6                1U
#define GPIOB_ADC12_IN9             1U
#define GPIOB_ZIO_D27               2U
#define GPIOB_ZIO_D23               3U
#define GPIOB_I2S3_CK               3U
#define GPIOB_ZIO_D25               4U
#define GPIOB_SPI3_MISO             4U
#define GPIOB_ZIO_D22               5U
#define GPIOB_I2S3_SD               5U
#define GPIOB_ZIO_D26               6U
#define GPIOB_LED2                  7U
#define GPIOB_ARD_D15               8U
#define GPIOB_I2C1_SCL              8U
#define GPIOB_ARD_D14               9U
#define GPIOB_I2C1_SDA              9U
#define GPIOB_ZIO_D36               10U
#define GPIOB_TIM2_CH3              10U
#define GPIOB_ZIO_D35               11U
#define GPIOB_TIM2_CH4              11U
#define GPIOB_OTG2_ID               12U
#define GPIOB_OTG2_VBUS             13U
#define GPIOB_OTG2_DP               14U
#define GPIOB_OTG2_DM               15U

#define GPIOC_ARD_A1                0U
#define GPIOC_ADC123_IN10           0U
#define GPIOC_RMII_MDC              1U
#define GPIOC_ZIO_A7                2U
#define GPIOC_ADC123_IN12           2U
#define GPIOC_ARD_A2                3U
#define GPIOC_ADC123_IN13           3U
#define GPIOC_RMII_RXD0             4U
#define GPIOC_RMII_RXD1             5U
#define GPIOC_ZIO_D16               6U
#define GPIOC_I2S2_MCK              6U
#define GPIOC_ZIO_D21               7U
#define GPIOC_I2S3_MCK              7U
#define GPIOC_ZIO_D43               8U
#define GPIOC_SDMMC_D0              8U
#define GPIOC_ZIO_D44               9U
#define GPIOC_SDMMC_D1              9U
#define GPIOC_ZIO_D45               10U
#define GPIOC_SDMMC_D2              10U
#define GPIOC_ZIO_D46               11U
#define GPIOC_SDMMC_D3              11U
#define GPIOC_ZIO_D47               12U
#define GPIOC_SDMMC_CK              12U
#define GPIOC_BUTTON                13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOD_ZIO_D67               0U
#define GPIOD_CAN1_RX               0U
#define GPIOD_ZIO_D66               1U
#define GPIOD_CAN1_TX               1U
#define GPIOD_ZIO_D48               2U
#define GPIOD_SDMMC_CMD             2U
#define GPIOD_ZIO_D55               3U
#define GPIOD_USART2_CTS            3U
#define GPIOD_ZIO_D54               4U
#define GPIOD_USART2_RTS            4U
#define GPIOD_ZIO_D53               5U
#define GPIOD_USART2_TX             5U
#define GPIOD_ZIO_D52               6U
#define GPIOD_USART2_RX             6U
#define GPIOD_ZIO_D51               7U
#define GPIOD_USART2_SCLK           7U
#define GPIOD_USART3_RX             8U
#define GPIOD_STLK_RX               8U
#define GPIOD_USART3_TX             9U
#define GPIOD_STLK_TX               9U
#define GPIOD_PIN10                 10U
#define GPIOD_ZIO_D30               11U
#define GPIOD_ZIO_D29               12U
#define GPIOD_LED0                  13U
#define GPIOD_LED1                  14U
#define GPIOD_LED2                  15U

#define GPIOE_ZIO_D34               0U
#define GPIOE_TIM4_ETR              0U
#define GPIOE_PIN1                  1U
#define GPIOE_ZIO_D31               2U
#define GPIOE_ZIO_D56               2U
#define GPIOE_SAI1_MCLK_A           2U
#define GPIOE_ZIO_D60               3U
#define GPIOE_SAI1_SD_B             3U
#define GPIOE_ZIO_D57               4U
#define GPIOE_SAI1_FS_A             4U
#define GPIOE_ZIO_D58               5U
#define GPIOE_SAI1_SCK_A            5U
#define GPIOE_ZIO_D59               6U
#define GPIOE_SAI1_SD_A             6U
#define GPIOE_ZIO_D41               7U
#define GPIOE_TIM1_ETR              7U
#define GPIOE_ZIO_D42               8U
#define GPIOE_TIM1_CH1N             8U
#define GPIOE_ARD_D6                9U
#define GPIOE_TIM1_CH1              9U
#define GPIOE_ZIO_D40               10U
#define GPIOE_TIM1_CH2N             10U
#define GPIOE_ARD_D5                11U
#define GPIOE_TIM1_CH2              11U
#define GPIOE_ZIO_D39               12U
#define GPIOE_TIM1_CH3N             12U
#define GPIOE_ARD_D3                13U
#define GPIOE_TIM1_CH3              13U
#define GPIOE_ZIO_D38               14U
#define GPIOE_ZIO_D37               15U
#define GPIOE_TIM1_BKIN1            15U

#define GPIOF_ZIO_D68               0U
#define GPIOF_I2C2_SDA              0U
#define GPIOF_ZIO_D69               1U
#define GPIOF_I2C2_SCL              1U
#define GPIOF_ZIO_D70               2U
#define GPIOF_I2C2_SMBA             2U
#define GPIOF_ARD_A3                3U
#define GPIOF_ADC3_IN9              3U
#define GPIOF_ZIO_A8                4U
#define GPIOF_ADC3_IN14             4U
#define GPIOF_ARD_A4                5U
#define GPIOF_ADC3_IN15             5U
#define GPIOF_PIN6                  6U
#define GPIOF_ZIO_D62               7U
#define GPIOF_SAI1_MCLK_B           7U
#define GPIOF_ZIO_D61               8U
#define GPIOF_SAI1_SCK_B            8U
#define GPIOF_ZIO_D63               9U
#define GPIOF_SAI1_FS_B             9U
#define GPIOF_ARD_A5                10U
#define GPIOF_ADC3_IN8              10U
#define GPIOF_PIN11                 11U
#define GPIOF_ARD_D8                12U
#define GPIOF_ARD_D7                13U
#define GPIOF_ARD_D4                14U
#define GPIOF_ARD_D2                15U

#define GPIOG_ZIO_D65               0U
#define GPIOG_ZIO_D64               1U
#define GPIOG_ZIO_D49               2U
#define GPIOG_ZIO_D50               3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_USB_GPIO_OUT          6U
#define GPIOG_USB_GPIO_IN           7U
#define GPIOG_PIN8                  8U
#define GPIOG_ARD_D0                9U
#define GPIOG_USART6_RX             9U
#define GPIOG_PIN10                 10U
#define GPIOG_RMII_TX_EN            11U
#define GPIOG_PIN12                 12U
#define GPIOG_RMII_TXD0             13U
#define GPIOG_ARD_D1                14U
#define GPIOG_USART6_TX             14U
#define GPIOG_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

#define GPIOJ_PIN0                  0U
#define GPIOJ_PIN1                  1U
#define GPIOJ_PIN2                  2U
#define GPIOJ_PIN3                  3U
#define GPIOJ_PIN4                  4U
#define GPIOJ_PIN5                  5U
#define GPIOJ_PIN6                  6U
#define GPIOJ_PIN7                  7U
#define GPIOJ_PIN8                  8U
#define GPIOJ_PIN9                  9U
#define GPIOJ_PIN10                 10U
#define GPIOJ_PIN11                 11U
#define GPIOJ_PIN12                 12U
#define GPIOJ_PIN13                 13U
#define GPIOJ_PIN14                 14U
#define GPIOJ_PIN15                 15U

#define GPIOK_PIN0                  0U
#define GPIOK_PIN1                  1U
#define GPIOK_PIN2                  2U
#define GPIOK_PIN3                  3U
#define GPIOK_PIN4                  4U
#define GPIOK_PIN5                  5U
#define GPIOK_PIN6                  6U
#define GPIOK_PIN7                  7U
#define GPIOK_PIN8                  8U
#define GPIOK_PIN9                  9U
#define GPIOK_PIN10                 10U
#define GPIOK_PIN11                 11U
#define GPIOK_PIN12                 12U
#define GPIOK_PIN13                 13U
#define GPIOK_PIN14                 14U
#define GPIOK_PIN15                 15U

/*
 * IO lines assignments.
 */

#define LINE_LED1                   PAL_LINE(GPIOD, 13U)
#define LINE_LED_RED                LINE_LED1
#define LINE_LED2                   PAL_LINE(GPIOD, 14U)
#define LINE_LED_YELLOW             LINE_LED2
#define LINE_LED3                   PAL_LINE(GPIOD, 15U)
#define LINE_LED_GREEN              LINE_LED3

#define LINE_BUTTON                 PAL_LINE(GPIOA, 0U)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
/* Normal */
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
/* Normal */
#define PIN_OSPEED_MEDIUM(n)        (3U << ((n) * 2U))
/* Large */
#define PIN_OSPEED_HIGH(n)          (1U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - ZIO_D32 TIM2_CH1          (input pullup).
 * PA1  - RMII_REF_CLK              (alternate 11).
 * PA2  - RMII_MDIO                 (alternate 11).
 * PA3  - ARD_A0 ADC123_IN3         (input pullup).
 * PA4  - ZIO_D24 SPI3_NSS          (input pullup).
 * PA5  - ARD_D13 SPI1_SCK          (input pullup).
 * PA6  - ARD_D12 SPI1_MISO         (input pullup).
 * PA7  - ARD_D11 SPI1_MOSI ZIO_D71 RMII_RX_DV(alternate 11).
 * PA8  - USB_SOF                   (alternate 10).
 * PA9  - USB_VBUS                  (analog).
 * PA10 - USB_ID                    (alternate 10).
 * PA11 - USB_DM                    (alternate 10).
 * PA12 - USB_DP                    (alternate 10).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - ZIO_D20 I2S3_WS           (input pullup).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_BUTTON) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_RMII_REF_CLK) |\
                                     PIN_MODE_ALTERNATE(GPIOA_RMII_MDIO) |  \
                                     PIN_MODE_INPUT(GPIOA_ARD_A0) |         \
                                     PIN_MODE_INPUT(GPIOA_ZIO_D24) |        \
                                     PIN_MODE_INPUT(GPIOA_ARD_D13) |        \
                                     PIN_MODE_INPUT(GPIOA_ARD_D12) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_ARD_D11) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_SOF) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_USART1_TX) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_USART1_RX) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG1_DM) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG2_DP) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_ZIO_D20))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_BUTTON) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RMII_REF_CLK) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_RMII_MDIO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ARD_A0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ZIO_D24) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ARD_D13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ARD_D12) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ARD_D11) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_SOF) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART1_TX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USART1_RX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG1_DM) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG2_DP) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ZIO_D20))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_BUTTON) |        \
                                     PIN_OSPEED_HIGH(GPIOA_RMII_REF_CLK) |  \
                                     PIN_OSPEED_HIGH(GPIOA_RMII_MDIO) |     \
                                     PIN_OSPEED_HIGH(GPIOA_ARD_A0) |        \
                                     PIN_OSPEED_HIGH(GPIOA_ZIO_D24) |       \
                                     PIN_OSPEED_HIGH(GPIOA_ARD_D13) |       \
                                     PIN_OSPEED_HIGH(GPIOA_ARD_D12) |       \
                                     PIN_OSPEED_HIGH(GPIOA_ARD_D11) |       \
                                     PIN_OSPEED_HIGH(GPIOA_USB_SOF) |       \
                                     PIN_OSPEED_HIGH(GPIOA_USART1_TX) |     \
                                     PIN_OSPEED_HIGH(GPIOA_USART1_RX) |     \
                                     PIN_OSPEED_HIGH(GPIOA_OTG1_DM) |       \
                                     PIN_OSPEED_HIGH(GPIOA_OTG2_DP) |       \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_ZIO_D20))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_BUTTON) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_RMII_REF_CLK) |\
                                     PIN_PUPDR_PULLUP(GPIOA_RMII_MDIO) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_ARD_A0) |       \
                                     PIN_PUPDR_PULLUP(GPIOA_ZIO_D24) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_ARD_D13) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_ARD_D12) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_ARD_D11) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_SOF) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_USART1_TX) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_USART1_RX) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG1_DM) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG2_DP) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_SWDIO) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_ZIO_D20))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_BUTTON) |           \
                                     PIN_ODR_HIGH(GPIOA_RMII_REF_CLK) |     \
                                     PIN_ODR_HIGH(GPIOA_RMII_MDIO) |        \
                                     PIN_ODR_HIGH(GPIOA_ARD_A0) |           \
                                     PIN_ODR_HIGH(GPIOA_ZIO_D24) |          \
                                     PIN_ODR_HIGH(GPIOA_ARD_D13) |          \
                                     PIN_ODR_HIGH(GPIOA_ARD_D12) |          \
                                     PIN_ODR_HIGH(GPIOA_ARD_D11) |          \
                                     PIN_ODR_HIGH(GPIOA_USB_SOF) |          \
                                     PIN_ODR_HIGH(GPIOA_USART1_TX) |        \
                                     PIN_ODR_HIGH(GPIOA_USART1_RX) |        \
                                     PIN_ODR_HIGH(GPIOA_OTG1_DM) |          \
                                     PIN_ODR_HIGH(GPIOA_OTG2_DP) |          \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_ZIO_D20))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_BUTTON, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_RMII_REF_CLK, 11U) | \
                                     PIN_AFIO_AF(GPIOA_RMII_MDIO, 11U) |    \
                                     PIN_AFIO_AF(GPIOA_ARD_A0, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_ZIO_D24, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_ARD_D13, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_ARD_D12, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_ARD_D11, 11U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_USB_SOF, 10U) |      \
                                     PIN_AFIO_AF(GPIOA_USART1_TX, 7U) |     \
                                     PIN_AFIO_AF(GPIOA_USART1_RX, 7U) |     \
                                     PIN_AFIO_AF(GPIOA_OTG1_DM, 10U) |      \
                                     PIN_AFIO_AF(GPIOA_OTG2_DP, 10U) |      \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_ZIO_D20, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - ZIO_D33 TIM3_CH3 LED1     (output pushpull maximum).
 * PB1  - ZIO_A6 ADC12_IN9          (input pullup).
 * PB2  - ZIO_D27                   (input pullup).
 * PB3  - ZIO_D23 I2S3_CK           (input pullup).
 * PB4  - ZIO_D25 SPI3_MISO         (input pullup).
 * PB5  - ZIO_D22 I2S3_SD           (input pullup).
 * PB6  - ZIO_D26                   (input pullup).
 * PB7  - LED2                      (output pushpull maximum).
 * PB8  - ARD_D15 I2C1_SCL          (input pullup).
 * PB9  - ARD_D14 I2C1_SDA          (input pullup).
 * PB10 - ZIO_D36 TIM2_CH3          (input pullup).
 * PB11 - ZIO_D35 TIM2_CH4          (input pullup).
 * PB12 - ZIO_D19 I2S2_WS           (input pullup).
 * PB13 - ZIO_D18 I2S2_CK RMII_TXD1 (alternate 11).
 * PB14 - LED3                      (output pushpull maximum).
 * PB15 - ZIO_D17 I2S2_SD           (input pullup).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_OUTPUT(GPIOB_ZIO_D33) |       \
                                     PIN_MODE_INPUT(GPIOB_ZIO_A6) |         \
                                     PIN_MODE_INPUT(GPIOB_ZIO_D27) |        \
                                     PIN_MODE_INPUT(GPIOB_ZIO_D23) |        \
                                     PIN_MODE_INPUT(GPIOB_ZIO_D25) |        \
                                     PIN_MODE_INPUT(GPIOB_ZIO_D22) |        \
                                     PIN_MODE_INPUT(GPIOB_ZIO_D26) |        \
                                     PIN_MODE_OUTPUT(GPIOB_LED2) |          \
                                     PIN_MODE_INPUT(GPIOB_ARD_D15) |        \
                                     PIN_MODE_INPUT(GPIOB_ARD_D14) |        \
                                     PIN_MODE_INPUT(GPIOB_ZIO_D36) |        \
                                     PIN_MODE_INPUT(GPIOB_ZIO_D35) |        \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG2_ID) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG2_VBUS) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG2_DP) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_OTG2_DM))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_ZIO_D33) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ZIO_A6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ZIO_D27) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ZIO_D23) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ZIO_D25) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ZIO_D22) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ZIO_D26) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LED2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ARD_D15) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ARD_D14) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ZIO_D36) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ZIO_D35) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG2_ID) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG2_VBUS) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG2_DP) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_OTG2_DM))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_ZIO_D33) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ZIO_A6) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ZIO_D27) |    \
                                     PIN_OSPEED_HIGH(GPIOB_ZIO_D23) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ZIO_D25) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ZIO_D22) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_ZIO_D26) |    \
                                     PIN_OSPEED_HIGH(GPIOB_LED2) |          \
                                     PIN_OSPEED_HIGH(GPIOB_ARD_D15) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ARD_D14) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ZIO_D36) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ZIO_D35) |       \
                                     PIN_OSPEED_HIGH(GPIOB_OTG2_ID) |       \
                                     PIN_OSPEED_HIGH(GPIOB_OTG2_VBUS) |     \
                                     PIN_OSPEED_HIGH(GPIOB_OTG2_DP) |       \
                                     PIN_OSPEED_HIGH(GPIOB_OTG2_DM))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_ZIO_D33) |    \
                                     PIN_PUPDR_PULLUP(GPIOB_ZIO_A6) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_ZIO_D27) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_ZIO_D23) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_ZIO_D25) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_ZIO_D22) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_ZIO_D26) |      \
                                     PIN_PUPDR_FLOATING(GPIOB_LED2) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_ARD_D15) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_ARD_D14) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_ZIO_D36) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_ZIO_D35) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOB_OTG2_ID) |    \
                                     PIN_PUPDR_PULLDOWN(GPIOB_OTG2_VBUS) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_OTG2_DP) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_OTG2_DM))
#define VAL_GPIOB_ODR               (PIN_ODR_LOW(GPIOB_ZIO_D33) |           \
                                     PIN_ODR_HIGH(GPIOB_ZIO_A6) |           \
                                     PIN_ODR_HIGH(GPIOB_ZIO_D27) |          \
                                     PIN_ODR_HIGH(GPIOB_ZIO_D23) |          \
                                     PIN_ODR_HIGH(GPIOB_ZIO_D25) |          \
                                     PIN_ODR_HIGH(GPIOB_ZIO_D22) |          \
                                     PIN_ODR_HIGH(GPIOB_ZIO_D26) |          \
                                     PIN_ODR_LOW(GPIOB_LED2) |              \
                                     PIN_ODR_HIGH(GPIOB_ARD_D15) |          \
                                     PIN_ODR_HIGH(GPIOB_ARD_D14) |          \
                                     PIN_ODR_HIGH(GPIOB_ZIO_D36) |          \
                                     PIN_ODR_HIGH(GPIOB_ZIO_D35) |          \
                                     PIN_ODR_HIGH(GPIOB_OTG2_ID) |          \
                                     PIN_ODR_HIGH(GPIOB_OTG2_VBUS) |        \
                                     PIN_ODR_HIGH(GPIOB_OTG2_DP) |          \
                                     PIN_ODR_HIGH(GPIOB_OTG2_DM))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_ZIO_D33, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ZIO_A6, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_ZIO_D27, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ZIO_D23, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ZIO_D25, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ZIO_D22, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ZIO_D26, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_LED2, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_ARD_D15, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ARD_D14, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ZIO_D36, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_ZIO_D35, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_OTG2_ID, 12U) |      \
                                     PIN_AFIO_AF(GPIOB_OTG2_VBUS, 12U) |    \
                                     PIN_AFIO_AF(GPIOB_OTG2_DP, 12U) |      \
                                     PIN_AFIO_AF(GPIOB_OTG2_DM, 12U))

/*
 * GPIOC setup:
 *
 * PC0  - ARD_A1 ADC123_IN10        (input pullup).
 * PC1  - RMII_MDC                  (alternate 11).
 * PC2  - ZIO_A7 ADC123_IN12        (input pullup).
 * PC3  - ARD_A2 ADC123_IN13        (input pullup).
 * PC4  - RMII_RXD0                 (alternate 11).
 * PC5  - RMII_RXD1                 (alternate 11).
 * PC6  - ZIO_D16 I2S2_MCK          (input pullup).
 * PC7  - ZIO_D21 I2S3_MCK          (input pullup).
 * PC8  - ZIO_D43 SDMMC_D0          (input pullup).
 * PC9  - ZIO_D44 SDMMC_D1          (input pullup).
 * PC10 - ZIO_D45 SDMMC_D2          (input pullup).
 * PC11 - ZIO_D46 SDMMC_D3          (input pullup).
 * PC12 - ZIO_D47 SDMMC_CK          (input pullup).
 * PC13 - BUTTON                    (input floating).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (input floating).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_ARD_A1) |         \
                                     PIN_MODE_ALTERNATE(GPIOC_RMII_MDC) |   \
                                     PIN_MODE_INPUT(GPIOC_ZIO_A7) |         \
                                     PIN_MODE_INPUT(GPIOC_ARD_A2) |         \
                                     PIN_MODE_ALTERNATE(GPIOC_RMII_RXD0) |  \
                                     PIN_MODE_ALTERNATE(GPIOC_RMII_RXD1) |  \
                                     PIN_MODE_INPUT(GPIOC_ZIO_D16) |        \
                                     PIN_MODE_INPUT(GPIOC_ZIO_D21) |        \
                                     PIN_MODE_INPUT(GPIOC_ZIO_D43) |        \
                                     PIN_MODE_INPUT(GPIOC_ZIO_D44) |        \
                                     PIN_MODE_INPUT(GPIOC_ZIO_D45) |        \
                                     PIN_MODE_INPUT(GPIOC_ZIO_D46) |        \
                                     PIN_MODE_INPUT(GPIOC_ZIO_D47) |        \
                                     PIN_MODE_INPUT(GPIOC_BUTTON) |         \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_ARD_A1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_RMII_MDC) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ZIO_A7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ARD_A2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_RMII_RXD0) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_RMII_RXD1) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ZIO_D16) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ZIO_D21) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ZIO_D43) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ZIO_D44) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ZIO_D45) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ZIO_D46) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ZIO_D47) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_BUTTON) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_ARD_A1) |        \
                                     PIN_OSPEED_HIGH(GPIOC_RMII_MDC) |      \
                                     PIN_OSPEED_HIGH(GPIOC_ZIO_A7) |        \
                                     PIN_OSPEED_HIGH(GPIOC_ARD_A2) |        \
                                     PIN_OSPEED_HIGH(GPIOC_RMII_RXD0) |     \
                                     PIN_OSPEED_HIGH(GPIOC_RMII_RXD1) |     \
                                     PIN_OSPEED_HIGH(GPIOC_ZIO_D16) |       \
                                     PIN_OSPEED_HIGH(GPIOC_ZIO_D21) |       \
                                     PIN_OSPEED_HIGH(GPIOC_ZIO_D43) |       \
                                     PIN_OSPEED_HIGH(GPIOC_ZIO_D44) |       \
                                     PIN_OSPEED_HIGH(GPIOC_ZIO_D45) |       \
                                     PIN_OSPEED_HIGH(GPIOC_ZIO_D46) |       \
                                     PIN_OSPEED_HIGH(GPIOC_ZIO_D47) |       \
                                     PIN_OSPEED_HIGH(GPIOC_BUTTON) |        \
                                     PIN_OSPEED_VERYLOW(GPIOC_OSC32_IN) |   \
                                     PIN_OSPEED_VERYLOW(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_ARD_A1) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_RMII_MDC) |   \
                                     PIN_PUPDR_PULLUP(GPIOC_ZIO_A7) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_ARD_A2) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_RMII_RXD0) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_RMII_RXD1) |  \
                                     PIN_PUPDR_PULLUP(GPIOC_ZIO_D16) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_ZIO_D21) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_ZIO_D43) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_ZIO_D44) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_ZIO_D45) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_ZIO_D46) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_ZIO_D47) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_BUTTON) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_ARD_A1) |           \
                                     PIN_ODR_HIGH(GPIOC_RMII_MDC) |         \
                                     PIN_ODR_HIGH(GPIOC_ZIO_A7) |           \
                                     PIN_ODR_HIGH(GPIOC_ARD_A2) |           \
                                     PIN_ODR_HIGH(GPIOC_RMII_RXD0) |        \
                                     PIN_ODR_HIGH(GPIOC_RMII_RXD1) |        \
                                     PIN_ODR_HIGH(GPIOC_ZIO_D16) |          \
                                     PIN_ODR_HIGH(GPIOC_ZIO_D21) |          \
                                     PIN_ODR_HIGH(GPIOC_ZIO_D43) |          \
                                     PIN_ODR_HIGH(GPIOC_ZIO_D44) |          \
                                     PIN_ODR_HIGH(GPIOC_ZIO_D45) |          \
                                     PIN_ODR_HIGH(GPIOC_ZIO_D46) |          \
                                     PIN_ODR_HIGH(GPIOC_ZIO_D47) |          \
                                     PIN_ODR_HIGH(GPIOC_BUTTON) |           \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_ARD_A1, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_RMII_MDC, 11U) |     \
                                     PIN_AFIO_AF(GPIOC_ZIO_A7, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_ARD_A2, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_RMII_RXD0, 11U) |    \
                                     PIN_AFIO_AF(GPIOC_RMII_RXD1, 11U) |    \
                                     PIN_AFIO_AF(GPIOC_ZIO_D16, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_ZIO_D21, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_ZIO_D43, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_ZIO_D44, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_ZIO_D45, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_ZIO_D46, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_ZIO_D47, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_BUTTON, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - ZIO_D67 CAN1_RX           (input pullup).
 * PD1  - ZIO_D66 CAN1_TX           (input pullup).
 * PD2  - ZIO_D48 SDMMC_CMD         (input pullup).
 * PD3  - ZIO_D55 USART2_CTS        (input pullup).
 * PD4  - ZIO_D54 USART2_RTS        (input pullup).
 * PD5  - ZIO_D53 USART2_TX         (input pullup).
 * PD6  - ZIO_D52 USART2_RX         (input pullup).
 * PD7  - ZIO_D51 USART2_SCLK       (input pullup).
 * PD8  - USART3_RX STLK_RX         (alternate 7).
 * PD9  - USART3_TX STLK_TX         (alternate 7).
 * PD10 - PIN10                     (input pullup).
 * PD11 - ZIO_D30                   (input pullup).
 * PD12 - ZIO_D29                   (input pullup).
 * PD13 - ZIO_D28                   (input pullup).
 * PD14 - ARD_D10 SPI1_NSS          (input pullup).
 * PD15 - ARD_D9 TIM4_CH4           (input pullup).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_ZIO_D67) |        \
                                     PIN_MODE_INPUT(GPIOD_ZIO_D66) |        \
                                     PIN_MODE_INPUT(GPIOD_ZIO_D48) |        \
                                     PIN_MODE_INPUT(GPIOD_ZIO_D55) |        \
                                     PIN_MODE_INPUT(GPIOD_ZIO_D54) |        \
                                     PIN_MODE_INPUT(GPIOD_ZIO_D53) |        \
                                     PIN_MODE_INPUT(GPIOD_ZIO_D52) |        \
                                     PIN_MODE_INPUT(GPIOD_ZIO_D51) |        \
                                     PIN_MODE_ALTERNATE(GPIOD_USART3_RX) |  \
                                     PIN_MODE_ALTERNATE(GPIOD_USART3_TX) |  \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_ZIO_D30) |        \
                                     PIN_MODE_INPUT(GPIOD_ZIO_D29) |        \
                                     PIN_MODE_OUTPUT(GPIOD_LED0) |          \
                                     PIN_MODE_OUTPUT(GPIOD_LED1) |          \
                                     PIN_MODE_OUTPUT(GPIOD_LED2))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D67) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D66) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D48) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D55) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D54) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D53) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D52) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D51) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_USART3_RX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_USART3_TX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D30) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_ZIO_D29) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED2))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_ZIO_D67) |       \
                                     PIN_OSPEED_HIGH(GPIOD_ZIO_D66) |       \
                                     PIN_OSPEED_HIGH(GPIOD_ZIO_D48) |       \
                                     PIN_OSPEED_HIGH(GPIOD_ZIO_D55) |       \
                                     PIN_OSPEED_HIGH(GPIOD_ZIO_D54) |       \
                                     PIN_OSPEED_HIGH(GPIOD_ZIO_D53) |       \
                                     PIN_OSPEED_HIGH(GPIOD_ZIO_D52) |       \
                                     PIN_OSPEED_HIGH(GPIOD_ZIO_D51) |       \
                                     PIN_OSPEED_HIGH(GPIOD_USART3_RX) |     \
                                     PIN_OSPEED_HIGH(GPIOD_USART3_TX) |     \
                                     PIN_OSPEED_VERYLOW(GPIOD_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOD_ZIO_D30) |    \
                                     PIN_OSPEED_VERYLOW(GPIOD_ZIO_D29) |    \
                                     PIN_OSPEED_VERYLOW(GPIOD_LED0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_LED1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOD_LED2))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_ZIO_D67) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_ZIO_D66) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_ZIO_D48) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_ZIO_D55) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_ZIO_D54) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_ZIO_D53) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_ZIO_D52) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_ZIO_D51) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_USART3_RX) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_USART3_TX) |  \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_ZIO_D30) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_ZIO_D29) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_LED0) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_LED1) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_LED2))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_ZIO_D67) |          \
                                     PIN_ODR_HIGH(GPIOD_ZIO_D66) |          \
                                     PIN_ODR_HIGH(GPIOD_ZIO_D48) |          \
                                     PIN_ODR_HIGH(GPIOD_ZIO_D55) |          \
                                     PIN_ODR_HIGH(GPIOD_ZIO_D54) |          \
                                     PIN_ODR_HIGH(GPIOD_ZIO_D53) |          \
                                     PIN_ODR_HIGH(GPIOD_ZIO_D52) |          \
                                     PIN_ODR_HIGH(GPIOD_ZIO_D51) |          \
                                     PIN_ODR_HIGH(GPIOD_USART3_RX) |        \
                                     PIN_ODR_HIGH(GPIOD_USART3_TX) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_ZIO_D30) |          \
                                     PIN_ODR_HIGH(GPIOD_ZIO_D29) |          \
                                     PIN_ODR_HIGH(GPIOD_LED0) |             \
                                     PIN_ODR_HIGH(GPIOD_LED1) |             \
                                     PIN_ODR_HIGH(GPIOD_LED2))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_ZIO_D67, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_ZIO_D66, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_ZIO_D48, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_ZIO_D55, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_ZIO_D54, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_ZIO_D53, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_ZIO_D52, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_ZIO_D51, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_USART3_RX, 7U) |     \
                                     PIN_AFIO_AF(GPIOD_USART3_TX, 7U) |     \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_ZIO_D30, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_ZIO_D29, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_LED0, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_LED1, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_LED2, 0U))

/*
 * GPIOE setup:
 *
 * PE0  - ZIO_D34 TIM4_ETR          (input pullup).
 * PE1  - PIN1                      (input pullup).
 * PE2  - ZIO_D31 ZIO_D56 SAI1_MCLK_A(input pullup).
 * PE3  - ZIO_D60 SAI1_SD_B         (input pullup).
 * PE4  - ZIO_D57 SAI1_FS_A         (input pullup).
 * PE5  - ZIO_D58 SAI1_SCK_A        (input pullup).
 * PE6  - ZIO_D59 SAI1_SD_A         (input pullup).
 * PE7  - ZIO_D41 TIM1_ETR          (input pullup).
 * PE8  - ZIO_D42 TIM1_CH1N         (input pullup).
 * PE9  - ARD_D6 TIM1_CH1           (input pullup).
 * PE10 - ZIO_D40 TIM1_CH2N         (input pullup).
 * PE11 - ARD_D5 TIM1_CH2           (input pullup).
 * PE12 - ZIO_D39 TIM1_CH3N         (input pullup).
 * PE13 - ARD_D3 TIM1_CH3           (input pullup).
 * PE14 - ZIO_D38                   (input pullup).
 * PE15 - ZIO_D37 TIM1_BKIN1        (input pullup).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_ZIO_D34) |        \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D31) |        \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D60) |        \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D57) |        \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D58) |        \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D59) |        \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D41) |        \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D42) |        \
                                     PIN_MODE_INPUT(GPIOE_ARD_D6) |         \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D40) |        \
                                     PIN_MODE_INPUT(GPIOE_ARD_D5) |         \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D39) |        \
                                     PIN_MODE_INPUT(GPIOE_ARD_D3) |         \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D38) |        \
                                     PIN_MODE_INPUT(GPIOE_ZIO_D37))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D34) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D31) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D60) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D57) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D58) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D59) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D41) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D42) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ARD_D6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D40) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ARD_D5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D39) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ARD_D3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D38) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ZIO_D37))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_ZIO_D34) |       \
                                     PIN_OSPEED_VERYLOW(GPIOE_PIN1) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D31) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D60) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D57) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D58) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D59) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D41) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D42) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ARD_D6) |        \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D40) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ARD_D5) |        \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D39) |       \
                                     PIN_OSPEED_HIGH(GPIOE_ARD_D3) |        \
                                     PIN_OSPEED_VERYLOW(GPIOE_ZIO_D38) |    \
                                     PIN_OSPEED_HIGH(GPIOE_ZIO_D37))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLUP(GPIOE_ZIO_D34) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D31) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D60) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D57) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D58) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D59) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D41) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D42) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ARD_D6) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D40) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ARD_D5) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D39) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ARD_D3) |       \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D38) |      \
                                     PIN_PUPDR_PULLUP(GPIOE_ZIO_D37))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_ZIO_D34) |          \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D31) |          \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D60) |          \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D57) |          \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D58) |          \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D59) |          \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D41) |          \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D42) |          \
                                     PIN_ODR_HIGH(GPIOE_ARD_D6) |           \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D40) |          \
                                     PIN_ODR_HIGH(GPIOE_ARD_D5) |           \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D39) |          \
                                     PIN_ODR_HIGH(GPIOE_ARD_D3) |           \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D38) |          \
                                     PIN_ODR_HIGH(GPIOE_ZIO_D37))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_ZIO_D34, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_ZIO_D31, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_ZIO_D60, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_ZIO_D57, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_ZIO_D58, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_ZIO_D59, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_ZIO_D41, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_ZIO_D42, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_ARD_D6, 0U) |        \
                                     PIN_AFIO_AF(GPIOE_ZIO_D40, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_ARD_D5, 0U) |        \
                                     PIN_AFIO_AF(GPIOE_ZIO_D39, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_ARD_D3, 0U) |        \
                                     PIN_AFIO_AF(GPIOE_ZIO_D38, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_ZIO_D37, 0U))

/*
 * GPIOF setup:
 *
 * PF0  - ZIO_D68 I2C2_SDA          (input pullup).
 * PF1  - ZIO_D69 I2C2_SCL          (input pullup).
 * PF2  - ZIO_D70 I2C2_SMBA         (input pullup).
 * PF3  - ARD_A3 ADC3_IN9           (input pullup).
 * PF4  - ZIO_A8 ADC3_IN14          (input pullup).
 * PF5  - ARD_A4 ADC3_IN15          (input pullup).
 * PF6  - PIN6                      (input pullup).
 * PF7  - ZIO_D62 SAI1_MCLK_B       (input pullup).
 * PF8  - ZIO_D61 SAI1_SCK_B        (input pullup).
 * PF9  - ZIO_D63 SAI1_FS_B         (input pullup).
 * PF10 - ARD_A5 ADC3_IN8           (input pullup).
 * PF11 - PIN11                     (input pullup).
 * PF12 - ARD_D8                    (input pullup).
 * PF13 - ARD_D7                    (input pullup).
 * PF14 - ARD_D4                    (input pullup).
 * PF15 - ARD_D2                    (input pullup).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_ZIO_D68) |        \
                                     PIN_MODE_INPUT(GPIOF_ZIO_D69) |        \
                                     PIN_MODE_INPUT(GPIOF_ZIO_D70) |        \
                                     PIN_MODE_INPUT(GPIOF_ARD_A3) |         \
                                     PIN_MODE_INPUT(GPIOF_ZIO_A8) |         \
                                     PIN_MODE_INPUT(GPIOF_ARD_A4) |         \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_ZIO_D62) |        \
                                     PIN_MODE_INPUT(GPIOF_ZIO_D61) |        \
                                     PIN_MODE_INPUT(GPIOF_ZIO_D63) |        \
                                     PIN_MODE_INPUT(GPIOF_ARD_A5) |         \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_ARD_D8) |         \
                                     PIN_MODE_INPUT(GPIOF_ARD_D7) |         \
                                     PIN_MODE_INPUT(GPIOF_ARD_D4) |         \
                                     PIN_MODE_INPUT(GPIOF_ARD_D2))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_ZIO_D68) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ZIO_D69) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ZIO_D70) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ARD_A3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ZIO_A8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ARD_A4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ZIO_D62) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ZIO_D61) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ZIO_D63) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ARD_A5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ARD_D8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ARD_D7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ARD_D4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_ARD_D2))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_ZIO_D68) |       \
                                     PIN_OSPEED_HIGH(GPIOF_ZIO_D69) |       \
                                     PIN_OSPEED_HIGH(GPIOF_ZIO_D70) |       \
                                     PIN_OSPEED_HIGH(GPIOF_ARD_A3) |        \
                                     PIN_OSPEED_HIGH(GPIOF_ZIO_A8) |        \
                                     PIN_OSPEED_HIGH(GPIOF_ARD_A4) |        \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN6) |       \
                                     PIN_OSPEED_HIGH(GPIOF_ZIO_D62) |       \
                                     PIN_OSPEED_HIGH(GPIOF_ZIO_D61) |       \
                                     PIN_OSPEED_HIGH(GPIOF_ZIO_D63) |       \
                                     PIN_OSPEED_HIGH(GPIOF_ARD_A5) |        \
                                     PIN_OSPEED_VERYLOW(GPIOF_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOF_ARD_D8) |     \
                                     PIN_OSPEED_VERYLOW(GPIOF_ARD_D7) |     \
                                     PIN_OSPEED_VERYLOW(GPIOF_ARD_D4) |     \
                                     PIN_OSPEED_VERYLOW(GPIOF_ARD_D2))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_PULLUP(GPIOF_ZIO_D68) |      \
                                     PIN_PUPDR_PULLUP(GPIOF_ZIO_D69) |      \
                                     PIN_PUPDR_PULLUP(GPIOF_ZIO_D70) |      \
                                     PIN_PUPDR_PULLUP(GPIOF_ARD_A3) |       \
                                     PIN_PUPDR_PULLUP(GPIOF_ZIO_A8) |       \
                                     PIN_PUPDR_PULLUP(GPIOF_ARD_A4) |       \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_ZIO_D62) |      \
                                     PIN_PUPDR_PULLUP(GPIOF_ZIO_D61) |      \
                                     PIN_PUPDR_PULLUP(GPIOF_ZIO_D63) |      \
                                     PIN_PUPDR_PULLUP(GPIOF_ARD_A5) |       \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_ARD_D8) |       \
                                     PIN_PUPDR_PULLUP(GPIOF_ARD_D7) |       \
                                     PIN_PUPDR_PULLUP(GPIOF_ARD_D4) |       \
                                     PIN_PUPDR_PULLUP(GPIOF_ARD_D2))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_ZIO_D68) |          \
                                     PIN_ODR_HIGH(GPIOF_ZIO_D69) |          \
                                     PIN_ODR_HIGH(GPIOF_ZIO_D70) |          \
                                     PIN_ODR_HIGH(GPIOF_ARD_A3) |           \
                                     PIN_ODR_HIGH(GPIOF_ZIO_A8) |           \
                                     PIN_ODR_HIGH(GPIOF_ARD_A4) |           \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_ZIO_D62) |          \
                                     PIN_ODR_HIGH(GPIOF_ZIO_D61) |          \
                                     PIN_ODR_HIGH(GPIOF_ZIO_D63) |          \
                                     PIN_ODR_HIGH(GPIOF_ARD_A5) |           \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_ARD_D8) |           \
                                     PIN_ODR_HIGH(GPIOF_ARD_D7) |           \
                                     PIN_ODR_HIGH(GPIOF_ARD_D4) |           \
                                     PIN_ODR_HIGH(GPIOF_ARD_D2))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_ZIO_D68, 0U) |       \
                                     PIN_AFIO_AF(GPIOF_ZIO_D69, 0U) |       \
                                     PIN_AFIO_AF(GPIOF_ZIO_D70, 0U) |       \
                                     PIN_AFIO_AF(GPIOF_ARD_A3, 0U) |        \
                                     PIN_AFIO_AF(GPIOF_ZIO_A8, 0U) |        \
                                     PIN_AFIO_AF(GPIOF_ARD_A4, 0U) |        \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_ZIO_D62, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_ZIO_D61, 0U) |       \
                                     PIN_AFIO_AF(GPIOF_ZIO_D63, 0U) |       \
                                     PIN_AFIO_AF(GPIOF_ARD_A5, 0U) |        \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_ARD_D8, 0U) |        \
                                     PIN_AFIO_AF(GPIOF_ARD_D7, 0U) |        \
                                     PIN_AFIO_AF(GPIOF_ARD_D4, 0U) |        \
                                     PIN_AFIO_AF(GPIOF_ARD_D2, 0U))

/*
 * GPIOG setup:
 *
 * PG0  - ZIO_D65                   (input pullup).
 * PG1  - ZIO_D64                   (input pullup).
 * PG2  - ZIO_D49                   (input pullup).
 * PG3  - ZIO_D50                   (input pullup).
 * PG4  - PIN4                      (input pullup).
 * PG5  - PIN5                      (input pullup).
 * PG6  - USB_GPIO_OUT              (input pullup).
 * PG7  - USB_GPIO_IN               (input pullup).
 * PG8  - PIN8                      (input pullup).
 * PG9  - ARD_D0 USART6_RX          (input pullup).
 * PG10 - PIN10                     (input pullup).
 * PG11 - RMII_TX_EN                (alternate 11).
 * PG12 - PIN12                     (input pullup).
 * PG13 - RMII_TXD0                 (alternate 11).
 * PG14 - ARD_D1 USART6_TX          (input pullup).
 * PG15 - PIN15                     (input pullup).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(GPIOG_ZIO_D65) |        \
                                     PIN_MODE_INPUT(GPIOG_ZIO_D64) |        \
                                     PIN_MODE_INPUT(GPIOG_ZIO_D49) |        \
                                     PIN_MODE_INPUT(GPIOG_ZIO_D50) |        \
                                     PIN_MODE_INPUT(GPIOG_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOG_USB_GPIO_OUT) |   \
                                     PIN_MODE_INPUT(GPIOG_USB_GPIO_IN) |    \
                                     PIN_MODE_INPUT(GPIOG_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOG_ARD_D0) |         \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |          \
                                     PIN_MODE_ALTERNATE(GPIOG_RMII_TX_EN) | \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |          \
                                     PIN_MODE_ALTERNATE(GPIOG_RMII_TXD0) |  \
                                     PIN_MODE_INPUT(GPIOG_ARD_D1) |         \
                                     PIN_MODE_INPUT(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_ZIO_D65) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_ZIO_D64) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_ZIO_D49) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_ZIO_D50) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_USB_GPIO_OUT) |\
                                     PIN_OTYPE_PUSHPULL(GPIOG_USB_GPIO_IN) |\
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_ARD_D0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_RMII_TX_EN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_RMII_TXD0) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_ARD_D1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOG_ZIO_D65) |    \
                                     PIN_OSPEED_VERYLOW(GPIOG_ZIO_D64) |    \
                                     PIN_OSPEED_VERYLOW(GPIOG_ZIO_D49) |    \
                                     PIN_OSPEED_VERYLOW(GPIOG_ZIO_D50) |    \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN5) |       \
                                     PIN_OSPEED_HIGH(GPIOG_USB_GPIO_OUT) |  \
                                     PIN_OSPEED_HIGH(GPIOG_USB_GPIO_IN) |   \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN8) |       \
                                     PIN_OSPEED_HIGH(GPIOG_ARD_D0) |        \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN10) |      \
                                     PIN_OSPEED_HIGH(GPIOG_RMII_TX_EN) |    \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN12) |      \
                                     PIN_OSPEED_HIGH(GPIOG_RMII_TXD0) |     \
                                     PIN_OSPEED_HIGH(GPIOG_ARD_D1) |        \
                                     PIN_OSPEED_VERYLOW(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_PULLUP(GPIOG_ZIO_D65) |      \
                                     PIN_PUPDR_PULLUP(GPIOG_ZIO_D64) |      \
                                     PIN_PUPDR_PULLUP(GPIOG_ZIO_D49) |      \
                                     PIN_PUPDR_PULLUP(GPIOG_ZIO_D50) |      \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_USB_GPIO_OUT) | \
                                     PIN_PUPDR_PULLUP(GPIOG_USB_GPIO_IN) |  \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_ARD_D0) |       \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN10) |        \
                                     PIN_PUPDR_FLOATING(GPIOG_RMII_TX_EN) | \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN12) |        \
                                     PIN_PUPDR_FLOATING(GPIOG_RMII_TXD0) |  \
                                     PIN_PUPDR_PULLUP(GPIOG_ARD_D1) |       \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_ZIO_D65) |          \
                                     PIN_ODR_HIGH(GPIOG_ZIO_D64) |          \
                                     PIN_ODR_HIGH(GPIOG_ZIO_D49) |          \
                                     PIN_ODR_HIGH(GPIOG_ZIO_D50) |          \
                                     PIN_ODR_HIGH(GPIOG_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOG_USB_GPIO_OUT) |     \
                                     PIN_ODR_HIGH(GPIOG_USB_GPIO_IN) |      \
                                     PIN_ODR_HIGH(GPIOG_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOG_ARD_D0) |           \
                                     PIN_ODR_HIGH(GPIOG_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOG_RMII_TX_EN) |       \
                                     PIN_ODR_HIGH(GPIOG_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOG_RMII_TXD0) |        \
                                     PIN_ODR_HIGH(GPIOG_ARD_D1) |           \
                                     PIN_ODR_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_ZIO_D65, 0U) |       \
                                     PIN_AFIO_AF(GPIOG_ZIO_D64, 0U) |       \
                                     PIN_AFIO_AF(GPIOG_ZIO_D49, 0U) |       \
                                     PIN_AFIO_AF(GPIOG_ZIO_D50, 0U) |       \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_USB_GPIO_OUT, 0U) |  \
                                     PIN_AFIO_AF(GPIOG_USB_GPIO_IN, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_ARD_D0, 0U) |        \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_RMII_TX_EN, 11U) |   \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_RMII_TXD0, 11U) |    \
                                     PIN_AFIO_AF(GPIOG_ARD_D1, 0U) |        \
                                     PIN_AFIO_AF(GPIOG_PIN15, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (input pullup).
 * PH3  - PIN3                      (input pullup).
 * PH4  - PIN4                      (input pullup).
 * PH5  - PIN5                      (input pullup).
 * PH6  - PIN6                      (input pullup).
 * PH7  - PIN7                      (input pullup).
 * PH8  - PIN8                      (input pullup).
 * PH9  - PIN9                      (input pullup).
 * PH10 - PIN10                     (input pullup).
 * PH11 - PIN11                     (input pullup).
 * PH12 - PIN12                     (input pullup).
 * PH13 - PIN13                     (input pullup).
 * PH14 - PIN14                     (input pullup).
 * PH15 - PIN15                     (input pullup).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input pullup).
 * PI1  - PIN1                      (input pullup).
 * PI2  - PIN2                      (input pullup).
 * PI3  - PIN3                      (input pullup).
 * PI4  - PIN4                      (input pullup).
 * PI5  - PIN5                      (input pullup).
 * PI6  - PIN6                      (input pullup).
 * PI7  - PIN7                      (input pullup).
 * PI8  - PIN8                      (input pullup).
 * PI9  - PIN9                      (input pullup).
 * PI10 - PIN10                     (input pullup).
 * PI11 - PIN11                     (input pullup).
 * PI12 - PIN12                     (input pullup).
 * PI13 - PIN13                     (input pullup).
 * PI14 - PIN14                     (input pullup).
 * PI15 - PIN15                     (input pullup).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOI_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLUP(GPIOI_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))

/*
 * GPIOJ setup:
 *
 * PJ0  - PIN0                      (input pullup).
 * PJ1  - PIN1                      (input pullup).
 * PJ2  - PIN2                      (input pullup).
 * PJ3  - PIN3                      (input pullup).
 * PJ4  - PIN4                      (input pullup).
 * PJ5  - PIN5                      (input pullup).
 * PJ6  - PIN6                      (input pullup).
 * PJ7  - PIN7                      (input pullup).
 * PJ8  - PIN8                      (input pullup).
 * PJ9  - PIN9                      (input pullup).
 * PJ10 - PIN10                     (input pullup).
 * PJ11 - PIN11                     (input pullup).
 * PJ12 - PIN12                     (input pullup).
 * PJ13 - PIN13                     (input pullup).
 * PJ14 - PIN14                     (input pullup).
 * PJ15 - PIN15                     (input pullup).
 */
#define VAL_GPIOJ_MODER             (PIN_MODE_INPUT(GPIOJ_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN15))
#define VAL_GPIOJ_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOJ_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN15))
#define VAL_GPIOJ_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOJ_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOJ_PIN15))
#define VAL_GPIOJ_PUPDR             (PIN_PUPDR_PULLUP(GPIOJ_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOJ_PIN15))
#define VAL_GPIOJ_ODR               (PIN_ODR_HIGH(GPIOJ_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN15))
#define VAL_GPIOJ_AFRL              (PIN_AFIO_AF(GPIOJ_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN7, 0U))
#define VAL_GPIOJ_AFRH              (PIN_AFIO_AF(GPIOJ_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN15, 0U))

/*
 * GPIOK setup:
 *
 * PK0  - PIN0                      (input pullup).
 * PK1  - PIN1                      (input pullup).
 * PK2  - PIN2                      (input pullup).
 * PK3  - PIN3                      (input pullup).
 * PK4  - PIN4                      (input pullup).
 * PK5  - PIN5                      (input pullup).
 * PK6  - PIN6                      (input pullup).
 * PK7  - PIN7                      (input pullup).
 * PK8  - PIN8                      (input pullup).
 * PK9  - PIN9                      (input pullup).
 * PK10 - PIN10                     (input pullup).
 * PK11 - PIN11                     (input pullup).
 * PK12 - PIN12                     (input pullup).
 * PK13 - PIN13                     (input pullup).
 * PK14 - PIN14                     (input pullup).
 * PK15 - PIN15                     (input pullup).
 */
#define VAL_GPIOK_MODER             (PIN_MODE_INPUT(GPIOK_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN15))
#define VAL_GPIOK_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOK_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN15))
#define VAL_GPIOK_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOK_PIN0) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN3) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN5) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN6) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN7) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN15))
#define VAL_GPIOK_PUPDR             (PIN_PUPDR_PULLUP(GPIOK_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN15))
#define VAL_GPIOK_ODR               (PIN_ODR_HIGH(GPIOK_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN15))
#define VAL_GPIOK_AFRL              (PIN_AFIO_AF(GPIOK_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN7, 0U))
#define VAL_GPIOK_AFRH              (PIN_AFIO_AF(GPIOK_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN15, 0U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
