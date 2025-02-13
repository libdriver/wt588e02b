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
 * @file      driver_wt588e02b_update_test.h
 * @brief     driver wt588e02b update test header file
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

#ifndef DRIVER_WT588E02B_UPDATE_TEST_H
#define DRIVER_WT588E02B_UPDATE_TEST_H

#include "driver_wt588e02b_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup wt588e02b_test_driver
 * @{
 */

/**
 * @brief     update all test
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t wt588e02b_update_all_test(char *path);

/**
 * @brief     update test
 * @param[in] ind index
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t wt588e02b_update_test(uint8_t ind, char *path);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
