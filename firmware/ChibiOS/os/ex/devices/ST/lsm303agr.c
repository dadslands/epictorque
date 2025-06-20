/*
    ChibiOS - Copyright (C) 2016..2019 Rocco Marco Guglielmi

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
*/

/**
 * @file    lsm303agr.c
 * @brief   LSM303AGR MEMS interface module code.
 *
 * @addtogroup LSM303AGR
 * @ingroup EX_ST
 * @{
 */

#include "hal.h"
#include "lsm303agr.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief  Accelerometer and Compass Slave Address.
 */
typedef enum {
  LSM303AGR_SAD_ACC = 0x19,        /**< SAD for accelerometer.             */
  LSM303AGR_SAD_COMP = 0x1E        /**< SAD for compass.                   */
} lsm303agr_sad_t;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (LSM303AGR_USE_I2C == TRUE)
static void lsm303agrStartBus(const LSM303AGRConfig *config) {
  i2cStart(config->i2cp,
           config->i2ccfg);
  osalDbgAssert((config->i2cp->state == I2C_READY),
                "lsm303agr, channel not ready");
}

static void lsm303agrStopBus(const LSM303AGRConfig *config) {
  i2cStop(config->i2cp);
}

#if (LSM303AGR_SHARED_I2C == TRUE)
static void lsm303agrAccureBus(const LSM303AGRConfig *config) {
  i2cAcquireBus(config->i2cp);
}

static void lsm303agrReleaseBus(const LSM303AGRConfig *config) {
  i2cReleaseBus(config->i2cp);
}
#endif
#endif

#if (LSM303AGR_USE_SPI == TRUE)
static void lsm303agrStartBus(const LSM303AGRConfig *config) {
  spiStart(config->spip,
           config->spicfg);
  osalDbgAssert((config->spip->state == SPI_READY),
                "lsm303agr, channel not ready");
}

static void lsm303agrStopBus(const LSM303AGRConfig *config) {
  spiStop(config->spip);
}
#if (LSM303AGR_SHARED_SPI == TRUE)
static void lsm303agrAccureBus(const LSM303AGRConfig *config) {
  spiAcquireBus(config->spip);
}

static void lsm303agrReleaseBus(const LSM303AGRConfig *config) {
  spiReleaseBus(config->spip);
}
#endif
#endif

/**
 * @brief   Reads registers value using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 * @note    IF_ADD_INC bit must be 1 in CTRL_REG8.
 *
 * @param[in] i2cp       pointer to the I2C interface.
 * @param[in] sad        slave address without R bit.
 * @param[in] reg        first sub-register address.
 * @param[in] rxbuf      receiving buffer.
 * @param[in] n          size of rxbuf.
 * @return               the operation status.
 */
static msg_t lsm303agrReadRegister(const LSM303AGRConfig *config, lsm303agr_sad_t sad,
                                   uint8_t reg, uint8_t *rxbuf, size_t n) {
#if (LSM303AGR_USE_I2C == TRUE)
  uint8_t txbuf = reg | LSM303AGR_MS;
  return i2cMasterTransmitTimeout(config->i2cp, sad, &txbuf, 1, rxbuf, n,
                                  TIME_INFINITE);
#endif
#if (LSM303AGR_USE_SPI == TRUE)
  uint8_t cmd = (reg & LSM303AGR_SPI_AD_MASK) | LSM303AGR_SPI_MS | LSM303AGR_SPI_RD;

  /* SPI mode supports only Accel */
  if (sad != LSM303AGR_SAD_ACC)
    return MSG_OK;

  spiSelect(config->spip);
  spiSend(config->spip, 1, &cmd);
  spiReceive(config->spip, n, rxbuf);
  spiUnselect(config->spip);

  return MSG_OK;
#endif
}

/**
 * @brief   Writes a value into a register using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in] i2cp      pointer to the I2C interface.
 * @param[in] sad       slave address without R bit.
 * @param[in] txbuf     buffer containing sub-address value in first position
 *                      and values to write.
 * @param[in] n         size of txbuf less one (not considering the first
 *                      element).
 * @return              the operation status.
 */
static msg_t lsm303agrWriteRegister(const LSM303AGRConfig *config, lsm303agr_sad_t sad,
                                    uint8_t reg, uint8_t *txdata, size_t n) {
#if (LSM303AGR_USE_I2C == TRUE)
  int i;
  uint8_t txbuf[1 + 8];

  if (n > 8)
    return MSG_RESET;

  txbuf[0] = reg;
  if (n != 1)
    txbuf[0] |= LSM303AGR_MS;
  for (i = 0; i < n; i++)
    txbuf[i + 1] = txdata[i];
  return i2cMasterTransmitTimeout(config->i2cp, sad, txbuf, n + 1, NULL, 0,
                                  TIME_INFINITE);
#endif
#if (LSM303AGR_USE_SPI == TRUE)
  uint8_t cmd = (reg & LSM303AGR_SPI_AD_MASK) | LSM303AGR_SPI_MS;

  /* SPI mode supports only Accel */
  if (sad != LSM303AGR_SAD_ACC)
    return MSG_OK;

  spiSelect(config->spip);
  spiSend(config->spip, 1, &cmd);
  spiSend(config->spip, n, txdata);
  spiUnselect(config->spip);

  return MSG_OK;
#endif
}

/**
 * @brief   Return the number of axes of the BaseAccelerometer.
 *
 * @param[in] ip        pointer to @p BaseAccelerometer interface.
 *
 * @return              the number of axes.
 */
static size_t acc_get_axes_number(void *ip) {
  (void)ip;

  return LSM303AGR_ACC_NUMBER_OF_AXES;
}

/**
 * @brief   Retrieves raw data from the BaseAccelerometer.
 * @note    This data is retrieved from MEMS register without any algebraical
 *          manipulation.
 * @note    The axes array must be at least the same size of the
 *          BaseAccelerometer axes number.
 *
 * @param[in] ip        pointer to @p BaseAccelerometer interface.
 * @param[out] axes     a buffer which would be filled with raw data.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end.
 */
static msg_t acc_read_raw(void *ip, int32_t axes[]) {
  LSM303AGRDriver* devp;
  uint8_t buff [LSM303AGR_ACC_NUMBER_OF_AXES * 2], i;
  int16_t tmp;
  msg_t msg;

  osalDbgCheck((ip != NULL) && (axes != NULL));

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseAccelerometer*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "acc_read_raw(), invalid state");

#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
  lsm303agrAccureBus(devp->config);
  lsm303agrStartBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */

  msg = lsm303agrReadRegister(devp->config, LSM303AGR_SAD_ACC,
                              LSM303AGR_AD_OUT_X_L_A, buff,
                              LSM303AGR_ACC_NUMBER_OF_AXES * 2);

#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
  lsm303agrReleaseBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */

  if(msg == MSG_OK)
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      tmp = buff[2 * i] + (buff[2 * i + 1] << 8);
      axes[i] = (int32_t)tmp;
    }
  return msg;
}

/**
 * @brief   Retrieves cooked data from the BaseAccelerometer.
 * @note    This data is manipulated according to the formula
 *          cooked = (raw * sensitivity) - bias.
 * @note    Final data is expressed as milli-G.
 * @note    The axes array must be at least the same size of the
 *          BaseAccelerometer axes number.
 *
 * @param[in] ip        pointer to @p BaseAccelerometer interface.
 * @param[out] axes     a buffer which would be filled with cooked data.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end.
 */
static msg_t acc_read_cooked(void *ip, float axes[]) {
  LSM303AGRDriver* devp;
  uint32_t i;
  int32_t raw[LSM303AGR_ACC_NUMBER_OF_AXES];
  msg_t msg;

  osalDbgCheck((ip != NULL) && (axes != NULL));

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseAccelerometer*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "acc_read_cooked(), invalid state");

  msg = acc_read_raw(ip, raw);
  for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
    axes[i] = (raw[i] * devp->accsensitivity[i]) - devp->accbias[i];
  }
  return msg;
}

/**
 * @brief   Set bias values for the BaseAccelerometer.
 * @note    Bias must be expressed as milli-G.
 * @note    The bias buffer must be at least the same size of the
 *          BaseAccelerometer axes number.
 *
 * @param[in] ip        pointer to @p BaseAccelerometer interface.
 * @param[in] bp        a buffer which contains biases.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 */
static msg_t acc_set_bias(void *ip, float *bp) {
  LSM303AGRDriver* devp;
  uint32_t i;
  msg_t msg = MSG_OK;

  osalDbgCheck((ip != NULL) && (bp != NULL));

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseAccelerometer*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "acc_set_bias(), invalid state");

  for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
    devp->accbias[i] = bp[i];
  }
  return msg;
}

/**
 * @brief   Reset bias values for the BaseAccelerometer.
 * @note    Default biases value are obtained from device datasheet when
 *          available otherwise they are considered zero.
 *
 * @param[in] ip        pointer to @p BaseAccelerometer interface.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 */
static msg_t acc_reset_bias(void *ip) {
  LSM303AGRDriver* devp;
  uint32_t i;
  msg_t msg = MSG_OK;

  osalDbgCheck(ip != NULL);

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseAccelerometer*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "acc_reset_bias(), invalid state");

  for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++)
    devp->accbias[i] = LSM303AGR_ACC_BIAS;
  return msg;
}

/**
 * @brief   Set sensitivity values for the BaseAccelerometer.
 * @note    Sensitivity must be expressed as milli-G/LSB.
 * @note    The sensitivity buffer must be at least the same size of the
 *          BaseAccelerometer axes number.
 *
 * @param[in] ip        pointer to @p BaseAccelerometer interface.
 * @param[in] sp        a buffer which contains sensitivities.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 */
static msg_t acc_set_sensivity(void *ip, float *sp) {
  LSM303AGRDriver* devp;
  uint32_t i;
  msg_t msg = MSG_OK;

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseAccelerometer*)ip);

  osalDbgCheck((ip != NULL) && (sp != NULL));

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "acc_set_sensivity(), invalid state");

  for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
    devp->accsensitivity[i] = sp[i];
  }
  return msg;
}

/**
 * @brief   Reset sensitivity values for the BaseAccelerometer.
 * @note    Default sensitivities value are obtained from device datasheet.
 *
 * @param[in] ip        pointer to @p BaseAccelerometer interface.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    otherwise.
 */
static msg_t acc_reset_sensivity(void *ip) {
  LSM303AGRDriver* devp;
  uint32_t i;
  msg_t msg = MSG_OK;

  osalDbgCheck(ip != NULL);

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseAccelerometer*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "acc_reset_sensivity(), invalid state");

  if(devp->config->accfullscale == LSM303AGR_ACC_FS_2G) {
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      devp->accsensitivity[i] = LSM303AGR_ACC_SENS_2G;
    }
  }
  else if(devp->config->accfullscale == LSM303AGR_ACC_FS_4G) {
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      devp->accsensitivity[i] = LSM303AGR_ACC_SENS_4G;
    }
  }
  else if(devp->config->accfullscale == LSM303AGR_ACC_FS_8G) {
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      devp->accsensitivity[i] = LSM303AGR_ACC_SENS_8G;
    }
  }
  else if(devp->config->accfullscale == LSM303AGR_ACC_FS_16G) {
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      devp->accsensitivity[i] = LSM303AGR_ACC_SENS_16G;
    }
  }
  else {
    osalDbgAssert(FALSE, "reset_sensivity(), accelerometer full scale issue");
    msg = MSG_RESET;
  }
  return msg;
}

/**
 * @brief   Changes the LSM303AGRDriver accelerometer fullscale value.
 * @note    This function also rescale sensitivities and biases based on
 *          previous and next fullscale value.
 * @note    A recalibration is highly suggested after calling this function.
 *
 * @param[in] devp      pointer to @p LSM303AGRDriver interface.
 * @param[in] fs        new fullscale value.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    otherwise.
 */
static msg_t acc_set_full_scale(LSM303AGRDriver *devp,
                                lsm303agr_acc_fs_t fs) {
  float newfs, scale;
  uint8_t i, buff[1];
  msg_t msg;

  osalDbgCheck(devp != NULL);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "acc_set_full_scale(), invalid state");

  /* Computing new fullscale value.*/
  if(fs == LSM303AGR_ACC_FS_2G) {
    newfs = LSM303AGR_ACC_2G;
  }
  else if(fs == LSM303AGR_ACC_FS_4G) {
    newfs = LSM303AGR_ACC_4G;
  }
  else if(fs == LSM303AGR_ACC_FS_8G) {
    newfs = LSM303AGR_ACC_8G;
  }
  else if(fs == LSM303AGR_ACC_FS_16G) {
    newfs = LSM303AGR_ACC_16G;
  }
  else {
    msg = MSG_RESET;
    return msg;
  }

  if(newfs != devp->accfullscale) {
    /* Computing scale value.*/
    scale = newfs / devp->accfullscale;
    devp->accfullscale = newfs;

#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
    lsm303agrAccureBus(devp->config);
    lsm303agrStartBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */

    /* Updating register.*/
    msg = lsm303agrReadRegister(devp->config,
                                LSM303AGR_SAD_ACC,
                                LSM303AGR_AD_CTRL_REG4_A,
                                &buff[1], 1);

    if(msg != MSG_OK)
      return msg;

    buff[0] &= ~(LSM303AGR_CTRL_REG4_A_FS_MASK);
    buff[0] |= fs;

    msg = lsm303agrWriteRegister(devp->config, LSM303AGR_SAD_ACC,
                                 LSM303AGR_AD_CTRL_REG4_A, buff, 1);

#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
    lsm303agrReleaseBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */

    if(msg != MSG_OK)
      return msg;

    /* Scaling sensitivity and bias. Re-calibration is suggested anyway.*/
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      devp->accsensitivity[i] *= scale;
      devp->accbias[i] *= scale;
    }
  }
  return msg;
}

/**
 * @brief   Return the number of axes of the BaseCompass.
 *
 * @param[in] ip        pointer to @p BaseCompass interface
 *
 * @return              the number of axes.
 */
static size_t comp_get_axes_number(void *ip) {

  osalDbgCheck(ip != NULL);
  return LSM303AGR_COMP_NUMBER_OF_AXES;
}

/**
 * @brief   Retrieves raw data from the BaseCompass.
 * @note    This data is retrieved from MEMS register without any algebraical
 *          manipulation.
 * @note    The axes array must be at least the same size of the
 *          BaseCompass axes number.
 *
 * @param[in] ip        pointer to @p BaseCompass interface.
 * @param[out] axes     a buffer which would be filled with raw data.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end.
 */
static msg_t comp_read_raw(void *ip, int32_t axes[]) {
  LSM303AGRDriver* devp;
  uint8_t buff [LSM303AGR_COMP_NUMBER_OF_AXES * 2], i;
  int16_t tmp;
  msg_t msg;

  osalDbgCheck((ip != NULL) && (axes != NULL));

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseCompass*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "comp_read_raw(), invalid state");

#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
  lsm303agrAccureBus(devp->config);
  lsm303agrStartBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */

  msg = lsm303agrReadRegister(devp->config, LSM303AGR_SAD_COMP,
                              LSM303AGR_AD_OUTX_L_REG_M, buff,
                              LSM303AGR_COMP_NUMBER_OF_AXES * 2);

#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
  lsm303agrReleaseBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */

  if(msg == MSG_OK)
    for(i = 0; i < LSM303AGR_COMP_NUMBER_OF_AXES; i++) {
      tmp = buff[2 * i] + (buff[2 * i + 1] << 8);
      axes[i] = (int32_t)tmp;
    }
  return msg;
}

/**
 * @brief   Retrieves cooked data from the BaseCompass.
 * @note    This data is manipulated according to the formula
 *          cooked = (raw * sensitivity) - bias.
 * @note    Final data is expressed as G.
 * @note    The axes array must be at least the same size of the
 *          BaseCompass axes number.
 *
 * @param[in] ip        pointer to @p BaseCompass interface.
 * @param[out] axes     a buffer which would be filled with cooked data.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    if one or more I2C errors occurred, the errors can
 *                      be retrieved using @p i2cGetErrors().
 * @retval MSG_TIMEOUT  if a timeout occurred before operation end.
 */
static msg_t comp_read_cooked(void *ip, float axes[]) {
  LSM303AGRDriver* devp;
  uint32_t i;
  int32_t raw[LSM303AGR_COMP_NUMBER_OF_AXES];
  msg_t msg;

  osalDbgCheck((ip != NULL) && (axes != NULL));


  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseCompass*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "comp_read_cooked(), invalid state");

  msg = comp_read_raw(ip, raw);
  for(i = 0; i < LSM303AGR_COMP_NUMBER_OF_AXES ; i++) {
    axes[i] = (raw[i] * devp->compsensitivity[i]) - devp->compbias[i];
  }
  return msg;
}

/**
 * @brief   Set bias values for the BaseCompass.
 * @note    Bias must be expressed as G.
 * @note    The bias buffer must be at least the same size of the
 *          BaseCompass axes number.
 *
 * @param[in] ip        pointer to @p BaseCompass interface.
 * @param[in] bp        a buffer which contains biases.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 */
static msg_t comp_set_bias(void *ip, float *bp) {
  LSM303AGRDriver* devp;
  uint32_t i;
  msg_t msg = MSG_OK;

  osalDbgCheck((ip != NULL) && (bp != NULL));

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseCompass*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "comp_set_bias(), invalid state");

  for(i = 0; i < LSM303AGR_COMP_NUMBER_OF_AXES; i++) {
    devp->compbias[i] = bp[i];
  }
  return msg;
}

/**
 * @brief   Reset bias values for the BaseCompass.
 * @note    Default biases value are obtained from device datasheet when
 *          available otherwise they are considered zero.
 *
 * @param[in] ip        pointer to @p BaseCompass interface.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 */
static msg_t comp_reset_bias(void *ip) {
  LSM303AGRDriver* devp;
  uint32_t i;
  msg_t msg = MSG_OK;

  osalDbgCheck(ip != NULL);

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseCompass*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "comp_reset_bias(), invalid state");

  for(i = 0; i < LSM303AGR_COMP_NUMBER_OF_AXES; i++)
    devp->compbias[i] = LSM303AGR_COMP_BIAS;
  return msg;
}

/**
 * @brief   Set sensitivity values for the BaseCompass.
 * @note    Sensitivity must be expressed as G/LSB.
 * @note    The sensitivity buffer must be at least the same size of the
 *          BaseCompass axes number.
 *
 * @param[in] ip        pointer to @p BaseCompass interface.
 * @param[in] sp        a buffer which contains sensitivities.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 */
static msg_t comp_set_sensivity(void *ip, float *sp) {
  LSM303AGRDriver* devp;
  uint32_t i;
  msg_t msg = MSG_OK;

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseCompass*)ip);

  osalDbgCheck((ip != NULL) && (sp != NULL));

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "comp_set_sensivity(), invalid state");

  for(i = 0; i < LSM303AGR_COMP_NUMBER_OF_AXES; i++) {
    devp->compsensitivity[i] = sp[i];
  }
  return msg;
}

/**
 * @brief   Reset sensitivity values for the BaseCompass.
 * @note    Default sensitivities value are obtained from device datasheet.
 *
 * @param[in] ip        pointer to @p BaseCompass interface.
 *
 * @return              The operation status.
 * @retval MSG_OK       if the function succeeded.
 * @retval MSG_RESET    otherwise.
 */
static msg_t comp_reset_sensivity(void *ip) {
  LSM303AGRDriver* devp;
  uint32_t i;
  msg_t msg = MSG_OK;

  osalDbgCheck(ip != NULL);

  /* Getting parent instance pointer.*/
  devp = objGetInstance(LSM303AGRDriver*, (BaseCompass*)ip);

  osalDbgAssert((devp->state == LSM303AGR_READY),
                "comp_reset_sensivity(), invalid state");

  for(i = 0; i < LSM303AGR_COMP_NUMBER_OF_AXES; i++)
    devp->compsensitivity[i] = LSM303AGR_COMP_SENS_50GA;
  
  return msg;
}

static const struct LSM303AGRVMT vmt_device = {
  (size_t)0,
  acc_set_full_scale
};

static const struct BaseAccelerometerVMT vmt_accelerometer = {
  sizeof(struct LSM303AGRVMT*),
  acc_get_axes_number, acc_read_raw, acc_read_cooked,
  acc_set_bias, acc_reset_bias, acc_set_sensivity, acc_reset_sensivity
};

static const struct BaseCompassVMT vmt_compass = {
  sizeof(struct LSM303AGRVMT*) + sizeof(BaseAccelerometer),
  comp_get_axes_number, comp_read_raw, comp_read_cooked,
  comp_set_bias, comp_reset_bias, comp_set_sensivity, comp_reset_sensivity
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p LSM303AGRDriver object
 *
 * @init
 */
void lsm303agrObjectInit(LSM303AGRDriver *devp) {
  devp->vmt = &vmt_device;
  devp->acc_if.vmt = &vmt_accelerometer;
  devp->comp_if.vmt = &vmt_compass;

  devp->config = NULL;

  devp->accaxes = LSM303AGR_ACC_NUMBER_OF_AXES;
  devp->compaxes = LSM303AGR_COMP_NUMBER_OF_AXES;

  devp->state = LSM303AGR_STOP;
}

/**
 * @brief   Configures and activates LSM303AGR Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p LSM303AGRDriver object
 * @param[in] config    pointer to the @p LSM303AGRConfig object
 *
 * @api
 */
msg_t lsm303agrStart(LSM303AGRDriver *devp, const LSM303AGRConfig *config) {
  uint32_t i;
  uint8_t devid;
  uint8_t cr[4];
  osalDbgCheck((devp != NULL) && (config != NULL));

  osalDbgAssert((devp->state == LSM303AGR_STOP) ||
                (devp->state == LSM303AGR_READY),
                "lsm303agrStart(), invalid state");

  devp->config = config;

#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
  lsm303agrAccureBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */
  lsm303agrStartBus(devp->config);

  /* Check WHO_I_AM */
  lsm303agrReadRegister(devp->config, LSM303AGR_SAD_ACC,
                          LSM303AGR_AD_WHO_AM_I_A, &devid, 1);
  if (devid != 0x33)
  {
#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
    lsm303agrReleaseBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */
    return MSG_RESET;
  }

  /* Configuring Accelerometer subsystem.*/

  /* Control register 1 configuration block.*/
  {
    cr[0] = LSM303AGR_ACC_AE_XYZ | devp->config->accoutdatarate;
#if LSM303AGR_USE_ADVANCED || defined(__DOXYGEN__)
    if(devp->config->accmode == LSM303AGR_ACC_MODE_LPOW)
      cr[0] |= LSM303AGR_CTRL_REG1_A_LPEN;
#endif
  }

  /* Control register 2 configuration block.*/
  {
    cr[1] = 0;
  }

  /* Control register 3 configuration block.*/
  {
    cr[2] = 0;
  }

  /* Control register 4 configuration block.*/
  {
    cr[3] = devp->config->accfullscale;
#if LSM303AGR_USE_ADVANCED || defined(__DOXYGEN__)
    cr[3] |= devp->config->accendianess |
             devp->config->accblockdataupdate;
    if(devp->config->accmode == LSM303AGR_ACC_MODE_HRES)
      cr[3] |= LSM303AGR_CTRL_REG4_A_HR;
#endif
  }

  /* Storing sensitivity according to user settings */
  if(devp->config->accfullscale == LSM303AGR_ACC_FS_2G) {
    devp->accfullscale = LSM303AGR_ACC_2G;
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      if(devp->config->accsensitivity == NULL)
        devp->accsensitivity[i] = LSM303AGR_ACC_SENS_2G;
      else
        devp->accsensitivity[i] = devp->config->accsensitivity[i];
    }
  }
  else if(devp->config->accfullscale == LSM303AGR_ACC_FS_4G) {
    devp->accfullscale = LSM303AGR_ACC_4G;
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      if(devp->config->accsensitivity == NULL)
        devp->accsensitivity[i] = LSM303AGR_ACC_SENS_4G;
      else
        devp->accsensitivity[i] = devp->config->accsensitivity[i];
    }
  }
  else if(devp->config->accfullscale == LSM303AGR_ACC_FS_8G) {
    devp->accfullscale = LSM303AGR_ACC_8G;
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      if(devp->config->accsensitivity == NULL)
        devp->accsensitivity[i] = LSM303AGR_ACC_SENS_8G;
      else
        devp->accsensitivity[i] = devp->config->accsensitivity[i];
    }
  }
  else if(devp->config->accfullscale == LSM303AGR_ACC_FS_16G) {
    devp->accfullscale = LSM303AGR_ACC_16G;
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++) {
      if(devp->config->accsensitivity == NULL)
        devp->accsensitivity[i] = LSM303AGR_ACC_SENS_16G;
      else
        devp->accsensitivity[i] = devp->config->accsensitivity[i];
    }
  }
  else
    osalDbgAssert(FALSE, "lsm303dlhcStart(), accelerometer full scale issue");

  /* Storing bias information */
  if(devp->config->accbias != NULL)
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++)
      devp->accbias[i] = devp->config->accbias[i];
  else
    for(i = 0; i < LSM303AGR_ACC_NUMBER_OF_AXES; i++)
      devp->accbias[i] = LSM303AGR_ACC_BIAS;

  lsm303agrWriteRegister(devp->config, LSM303AGR_SAD_ACC,
                         LSM303AGR_AD_CTRL_REG1_A, cr, 4);
  
  /* Configuring Compass subsystem */

  /* Control register A configuration block.*/
  {
    cr[0] = devp->config->compoutputdatarate;
#if LSM303AGR_USE_ADVANCED || defined(__DOXYGEN__)
    cr[0] |= devp->config->compmode | devp->config->complp;
#endif
  }

  /* Control register B configuration block.*/
  {
    cr[1] = 0;
  }

  /* Control register C configuration block.*/
  {
    cr[2] = 0;
  }

  lsm303agrWriteRegister(devp->config, LSM303AGR_SAD_COMP,
                         LSM303AGR_AD_CFG_REG_A_M, cr, 3);

#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
  lsm303agrReleaseBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */

  devp->compfullscale = LSM303AGR_COMP_50GA;
  for(i = 0; i < LSM303AGR_COMP_NUMBER_OF_AXES; i++) {
    if(devp->config->compsensitivity == NULL) {
      devp->compsensitivity[i] = LSM303AGR_COMP_SENS_50GA;
    }
    else {
      devp->compsensitivity[i] = devp->config->compsensitivity[i];
    }
  }
    
  /* This is the MEMS transient recovery time */
  osalThreadSleepMilliseconds(5);

  devp->state = LSM303AGR_READY;

  return MSG_OK;
}

/**
 * @brief   Deactivates the LSM303AGR Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p LSM303AGRDriver object
 *
 * @api
 */
void lsm303agrStop(LSM303AGRDriver *devp) {
  uint8_t cr[1];
  osalDbgCheck(devp != NULL);

  osalDbgAssert((devp->state == LSM303AGR_STOP) ||
                (devp->state == LSM303AGR_READY),
                "lsm303agrStop(), invalid state");

  if (devp->state == LSM303AGR_READY) {
#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
    lsm303agrAccureBus(devp->config);
    lsm303agrStartBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */

    /* Disabling accelerometer. */
    cr[0] = LSM303AGR_ACC_AE_DISABLED | LSM303AGR_ACC_ODR_PD;
    lsm303agrWriteRegister(devp->config, LSM303AGR_SAD_ACC,
                           LSM303AGR_AD_CTRL_REG1_A, cr, 1);

    /* Disabling compass. */
    cr[0] = LSM303AGR_COMP_MODE_IDLE;
    lsm303agrWriteRegister(devp->config, LSM303AGR_SAD_COMP,
                           LSM303AGR_AD_CFG_REG_A_M, cr, 1);

    lsm303agrStopBus((devp)->config);
#if (LSM303AGR_SHARED_I2C == TRUE) || (LSM303AGR_SHARED_SPI == TRUE)
    lsm303agrReleaseBus(devp->config);
#endif /* LSM303AGR_SHARED_I2C || LSM303AGR_SHARED_SPI */
  }			
  devp->state = LSM303AGR_STOP;
}
/** @} */
