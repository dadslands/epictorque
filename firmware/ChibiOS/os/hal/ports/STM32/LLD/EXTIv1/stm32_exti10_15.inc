/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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

/**
 * @file    EXTIv1/stm32_exti10_15.inc
 * @brief   Shared EXTI10_15 handler.
 *
 * @addtogroup STM32_EXTI10_15_HANDLER
 * @{
 */

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Priority settings checks.*/
#if !defined(STM32_IRQ_EXTI10_15_PRIORITY)
#error "STM32_IRQ_EXTI10_15_PRIORITY not defined in mcuconf.h"
#endif

#if !defined(STM32_DISABLE_EXTI10_15_HANDLER) && !OSAL_IRQ_IS_VALID_PRIORITY(STM32_IRQ_EXTI10_15_PRIORITY)
#error "Invalid IRQ priority assigned to STM32_IRQ_EXTI10_15_PRIORITY"
#endif

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static inline void exti10_15_irq_init(void) {
#if (HAL_USE_PAL && (PAL_USE_WAIT || PAL_USE_CALLBACKS))
  nvicEnableVector(STM32_EXTI10_15_NUMBER, STM32_IRQ_EXTI10_15_PRIORITY);
#endif
}

static inline void exti10_15_irq_deinit(void) {
#if (HAL_USE_PAL && (PAL_USE_WAIT || PAL_USE_CALLBACKS))
  nvicDisableVector(STM32_EXTI10_15_NUMBER);
#endif
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if (HAL_USE_PAL && (PAL_USE_WAIT || PAL_USE_CALLBACKS)) || defined(__DOXYGEN__)
#if !defined(STM32_DISABLE_EXTI10_15_HANDLER)
/**
 * @brief   EXTI[10]..EXTI[15] interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_EXTI10_15_HANDLER) {
  uint32_t pr;

  OSAL_IRQ_PROLOGUE();

  extiGetAndClearGroup1((1U << 10) | (1U << 11) | (1U << 12) | (1U << 13) |
                        (1U << 14) | (1U << 15), pr);

  exti_serve_irq(pr, 10);
  exti_serve_irq(pr, 11);
  exti_serve_irq(pr, 12);
  exti_serve_irq(pr, 13);
  exti_serve_irq(pr, 14);
  exti_serve_irq(pr, 15);

  OSAL_IRQ_EPILOGUE();
}
#endif
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/** @} */
