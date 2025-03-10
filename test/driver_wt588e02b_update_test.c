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
 * @file      driver_wt588e02b_update_test.c
 * @brief     driver wt588e02b update test source file
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

#include "driver_wt588e02b_update_test.h"
#include <stdlib.h>

static wt588e02b_handle_t gs_handle;        /**< wt588e02b handle */

/**
 * @brief     update all test
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t wt588e02b_update_all_test(char *path)
{
    uint8_t res;
    wt588e02b_info_t info;

    /* link driver */
    DRIVER_WT588E02B_LINK_INIT(&gs_handle, wt588e02b_handle_t);
    DRIVER_WT588E02B_LINK_SCLK_GPIO_INIT(&gs_handle, wt588e02b_interface_sclk_gpio_init);
    DRIVER_WT588E02B_LINK_SCLK_GPIO_DEINIT(&gs_handle, wt588e02b_interface_sclk_gpio_deinit);
    DRIVER_WT588E02B_LINK_SCLK_GPIO_WRITE(&gs_handle, wt588e02b_interface_sclk_gpio_write);
    DRIVER_WT588E02B_LINK_MOSI_GPIO_INIT(&gs_handle, wt588e02b_interface_mosi_gpio_init);
    DRIVER_WT588E02B_LINK_MOSI_GPIO_DEINIT(&gs_handle, wt588e02b_interface_mosi_gpio_deinit);
    DRIVER_WT588E02B_LINK_MOSI_GPIO_WRITE(&gs_handle, wt588e02b_interface_mosi_gpio_write);
    DRIVER_WT588E02B_LINK_MISO_GPIO_INIT(&gs_handle, wt588e02b_interface_miso_gpio_init);
    DRIVER_WT588E02B_LINK_MISO_GPIO_DEINIT(&gs_handle, wt588e02b_interface_miso_gpio_deinit);
    DRIVER_WT588E02B_LINK_MISO_GPIO_READ(&gs_handle, wt588e02b_interface_miso_gpio_read);
    DRIVER_WT588E02B_LINK_CS_GPIO_INIT(&gs_handle, wt588e02b_interface_cs_gpio_init);
    DRIVER_WT588E02B_LINK_CS_GPIO_DEINIT(&gs_handle, wt588e02b_interface_cs_gpio_deinit);
    DRIVER_WT588E02B_LINK_CS_GPIO_WRITE(&gs_handle, wt588e02b_interface_cs_gpio_write);
    DRIVER_WT588E02B_LINK_BIN_READ_INIT(&gs_handle, wt588e02b_interface_bin_read_init);
    DRIVER_WT588E02B_LINK_BIN_READ(&gs_handle, wt588e02b_interface_bin_read);
    DRIVER_WT588E02B_LINK_BIN_READ_DEINIT(&gs_handle, wt588e02b_interface_bin_read_deinit);
    DRIVER_WT588E02B_LINK_DELAY_MS(&gs_handle, wt588e02b_interface_delay_ms);
    DRIVER_WT588E02B_LINK_DELAY_US(&gs_handle, wt588e02b_interface_delay_us);
    DRIVER_WT588E02B_LINK_DEBUG_PRINT(&gs_handle, wt588e02b_interface_debug_print);

    /* get information */
    res = wt588e02b_info(&info);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: get info failed.\n");

        return 1;
    }
    else
    {
        /* print chip info */
        wt588e02b_interface_debug_print("wt588e02b: chip is %s.\n", info.chip_name);
        wt588e02b_interface_debug_print("wt588e02b: manufacturer is %s.\n", info.manufacturer_name);
        wt588e02b_interface_debug_print("wt588e02b: interface is %s.\n", info.interface);
        wt588e02b_interface_debug_print("wt588e02b: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        wt588e02b_interface_debug_print("wt588e02b: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        wt588e02b_interface_debug_print("wt588e02b: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        wt588e02b_interface_debug_print("wt588e02b: max current is %0.2fmA.\n", info.max_current_ma);
        wt588e02b_interface_debug_print("wt588e02b: max temperature is %0.1fC.\n", info.temperature_max);
        wt588e02b_interface_debug_print("wt588e02b: min temperature is %0.1fC.\n", info.temperature_min);
    }

    /* start update all test */
    wt588e02b_interface_debug_print("wt588e02b: start update all test.\n");

    /* init */
    res = wt588e02b_init(&gs_handle);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: init failed.\n");

        return 1;
    }

    /* start update all */
    wt588e02b_interface_debug_print("wt588e02b: start update all...\n");

    /* update all */
    res = wt588e02b_update_all(&gs_handle, path);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: update all failed.\n");
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }

    /* finish update */
    wt588e02b_interface_debug_print("wt588e02b: finish update.\n");

    /* finish update all test */
    wt588e02b_interface_debug_print("wt588e02b: finish update all test.\n");
    (void)wt588e02b_deinit(&gs_handle);

    return 0;
}

/**
 * @brief     update test
 * @param[in] ind index
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t wt588e02b_update_test(uint8_t ind, char *path)
{
    uint8_t res;
    wt588e02b_info_t info;

    /* link driver */
    DRIVER_WT588E02B_LINK_INIT(&gs_handle, wt588e02b_handle_t);
    DRIVER_WT588E02B_LINK_SCLK_GPIO_INIT(&gs_handle, wt588e02b_interface_sclk_gpio_init);
    DRIVER_WT588E02B_LINK_SCLK_GPIO_DEINIT(&gs_handle, wt588e02b_interface_sclk_gpio_deinit);
    DRIVER_WT588E02B_LINK_SCLK_GPIO_WRITE(&gs_handle, wt588e02b_interface_sclk_gpio_write);
    DRIVER_WT588E02B_LINK_MOSI_GPIO_INIT(&gs_handle, wt588e02b_interface_mosi_gpio_init);
    DRIVER_WT588E02B_LINK_MOSI_GPIO_DEINIT(&gs_handle, wt588e02b_interface_mosi_gpio_deinit);
    DRIVER_WT588E02B_LINK_MOSI_GPIO_WRITE(&gs_handle, wt588e02b_interface_mosi_gpio_write);
    DRIVER_WT588E02B_LINK_MISO_GPIO_INIT(&gs_handle, wt588e02b_interface_miso_gpio_init);
    DRIVER_WT588E02B_LINK_MISO_GPIO_DEINIT(&gs_handle, wt588e02b_interface_miso_gpio_deinit);
    DRIVER_WT588E02B_LINK_MISO_GPIO_READ(&gs_handle, wt588e02b_interface_miso_gpio_read);
    DRIVER_WT588E02B_LINK_CS_GPIO_INIT(&gs_handle, wt588e02b_interface_cs_gpio_init);
    DRIVER_WT588E02B_LINK_CS_GPIO_DEINIT(&gs_handle, wt588e02b_interface_cs_gpio_deinit);
    DRIVER_WT588E02B_LINK_CS_GPIO_WRITE(&gs_handle, wt588e02b_interface_cs_gpio_write);
    DRIVER_WT588E02B_LINK_BIN_READ_INIT(&gs_handle, wt588e02b_interface_bin_read_init);
    DRIVER_WT588E02B_LINK_BIN_READ(&gs_handle, wt588e02b_interface_bin_read);
    DRIVER_WT588E02B_LINK_BIN_READ_DEINIT(&gs_handle, wt588e02b_interface_bin_read_deinit);
    DRIVER_WT588E02B_LINK_DELAY_MS(&gs_handle, wt588e02b_interface_delay_ms);
    DRIVER_WT588E02B_LINK_DELAY_US(&gs_handle, wt588e02b_interface_delay_us);
    DRIVER_WT588E02B_LINK_DEBUG_PRINT(&gs_handle, wt588e02b_interface_debug_print);

    /* get information */
    res = wt588e02b_info(&info);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: get info failed.\n");

        return 1;
    }
    else
    {
        /* print chip info */
        wt588e02b_interface_debug_print("wt588e02b: chip is %s.\n", info.chip_name);
        wt588e02b_interface_debug_print("wt588e02b: manufacturer is %s.\n", info.manufacturer_name);
        wt588e02b_interface_debug_print("wt588e02b: interface is %s.\n", info.interface);
        wt588e02b_interface_debug_print("wt588e02b: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        wt588e02b_interface_debug_print("wt588e02b: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        wt588e02b_interface_debug_print("wt588e02b: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        wt588e02b_interface_debug_print("wt588e02b: max current is %0.2fmA.\n", info.max_current_ma);
        wt588e02b_interface_debug_print("wt588e02b: max temperature is %0.1fC.\n", info.temperature_max);
        wt588e02b_interface_debug_print("wt588e02b: min temperature is %0.1fC.\n", info.temperature_min);
    }

    /* start update test */
    wt588e02b_interface_debug_print("wt588e02b: start update test.\n");

    /* init */
    res = wt588e02b_init(&gs_handle);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: init failed.\n");

        return 1;
    }

    /* start update */
    wt588e02b_interface_debug_print("wt588e02b: start update...\n");

    /* update */
    res = wt588e02b_update(&gs_handle, ind, path);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: update failed.\n");
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }

    /* finish update */
    wt588e02b_interface_debug_print("wt588e02b: finish update.\n");

    /* finish update test */
    wt588e02b_interface_debug_print("wt588e02b: finish update test.\n");
    (void)wt588e02b_deinit(&gs_handle);

    return 0;
}
