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
 * @file      driver_wt588e02b_basic.h
 * @brief     driver wt588e02b basic header file
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

#ifndef DRIVER_WT588E02B_BASIC_H
#define DRIVER_WT588E02B_BASIC_H

#include "driver_wt588e02b_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup wt588e02b_example_driver wt588e02b example driver function
 * @brief    wt588e02b example driver modules
 * @ingroup  wt588e02b_driver
 * @{
 */

/**
 * @brief wt588e02b basic example default definition
 */
#define WT588E02B_BASIC_DEFAULT_VOLUME          0x3F        /**< 0x3F */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t wt588e02b_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t wt588e02b_basic_deinit(void);

/**
 * @brief     basic example play
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 play failed
 * @note      none
 */
uint8_t wt588e02b_basic_play(uint8_t ind);

/**
 * @brief     basic example play loop
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 play loop failed
 * @note      none
 */
uint8_t wt588e02b_basic_play_loop(uint8_t ind);

/**
 * @brief     basic example play loop advance
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 play loop advance failed
 * @note      none
 */
uint8_t wt588e02b_basic_play_loop_advance(uint8_t ind);

/**
 * @brief  basic example play loop all
 * @return status code
 *         - 0 success
 *         - 1 play loop all failed
 * @note   none
 */
uint8_t wt588e02b_basic_play_loop_all(void);

/**
 * @brief     basic example play list
 * @param[in] *list pointer to a list buffer
 * @param[in] len length of list
 * @return    status code
 *            - 0 success
 *            - 1 play list failed
 * @note      none
 */
uint8_t wt588e02b_basic_play_list(uint8_t *list, uint8_t len);

/**
 * @brief  basic example poll
 * @return status code
 *         - 0 success
 *         - 1 poll failed
 * @note   none
 */
uint8_t wt588e02b_basic_poll(void);

/**
 * @brief  basic example stop
 * @return status code
 *         - 0 success
 *         - 1 stop failed
 * @note   none
 */
uint8_t wt588e02b_basic_stop(void);

/**
 * @brief     basic example set volume
 * @param[in] vol volume
 * @return    status code
 *            - 0 success
 *            - 1 set vol failed
 * @note      none
 */
uint8_t wt588e02b_basic_set_vol(uint8_t vol);

/**
 * @brief     basic example update
 * @param[in] ind index
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 update failed
 * @note      none
 */
uint8_t wt588e02b_basic_update(uint8_t ind, char *path);

/**
 * @brief     basic example update all
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 update all failed
 * @note      none
 */
uint8_t wt588e02b_basic_update_all(char *path);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
