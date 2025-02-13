/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_wt588e02b_interface.h
 * @brief     driver wt588e02b interface header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-01-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/01/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_WT588E02B_INTERFACE_H
#define DRIVER_WT588E02B_INTERFACE_H

#include "driver_wt588e02b.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup wt588e02b_interface_driver wt588e02b interface driver function
 * @brief    wt588e02b interface driver modules
 * @ingroup  wt588e02b_driver
 * @{
 */

/**
 * @brief  interface sclk gpio init
 * @return status code
 *         - 0 success
 *         - 1 sclk gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_sclk_gpio_init(void);

/**
 * @brief  interface sclk gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 sclk gpio deinit failed
 * @note   none
 */
uint8_t wt588e02b_interface_sclk_gpio_deinit(void);

/**
 * @brief     interface sclk gpio write
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wt588e02b_interface_sclk_gpio_write(uint8_t data);

/**
 * @brief  interface mosi gpio init
 * @return status code
 *         - 0 success
 *         - 1 mosi gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_mosi_gpio_init(void);

/**
 * @brief  interface mosi gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 mosi gpio deinit failed
 * @note   none
 */
uint8_t wt588e02b_interface_mosi_gpio_deinit(void);

/**
 * @brief     interface mosi gpio write
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wt588e02b_interface_mosi_gpio_write(uint8_t data);

/**
 * @brief  interface miso gpio init
 * @return status code
 *         - 0 success
 *         - 1 miso gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_miso_gpio_init(void);

/**
 * @brief  interface miso gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 miso gpio deinit failed
 * @note   none
 */
uint8_t wt588e02b_interface_miso_gpio_deinit(void);

/**
 * @brief      interface miso_gpio_read
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t wt588e02b_interface_miso_gpio_read(uint8_t *data);

/**
 * @brief  interface cs gpio init
 * @return status code
 *         - 0 success
 *         - 1 cs gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_cs_gpio_init(void);

/**
 * @brief  interface cs gpio init
 * @return status code
 *         - 0 success
 *         - 1 cs gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_cs_gpio_deinit(void);

/**
 * @brief     interface cs gpio write
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wt588e02b_interface_cs_gpio_write(uint8_t data);

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void wt588e02b_interface_delay_ms(uint32_t ms);

/**
 * @brief     interface delay us
 * @param[in] us time
 * @note      none
 */
void wt588e02b_interface_delay_us(uint32_t us);

/**
 * @brief      interface bin read init
 * @param[in]  *name pointer to a name buffer
 * @param[out] *size pointer to a file size buffer
 * @return     status code
 *             - 0 success
 *             - 1 bin read init failed
 * @note       none
 */
uint8_t wt588e02b_interface_bin_read_init(char *name, uint32_t *size);

/**
 * @brief      interface bin read
 * @param[in]  addr file address
 * @param[in]  size read size
 * @param[out] *buffer pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 bin read failed
 * @note       none
 */
uint8_t wt588e02b_interface_bin_read(uint32_t addr, uint16_t size, uint8_t *buffer);

/**
 * @brief  interface bin read deinit
 * @return status code
 *         - 0 success
 *         - 1 bin read deinit failed
 * @note   none
 */
uint8_t wt588e02b_interface_bin_read_deinit(void);

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void wt588e02b_interface_debug_print(const char *const fmt, ...);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
