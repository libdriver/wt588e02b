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
 * @file      driver_wt588e02b_play_test.c
 * @brief     driver wt588e02b play test source file
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

#include "driver_wt588e02b_play_test.h"
#include <stdlib.h>

static wt588e02b_handle_t gs_handle;        /**< wt588e02b handle */

/**
 * @brief     play test
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t wt588e02b_play_test(uint8_t ind)
{
    uint8_t res;
    uint8_t list[2];
    wt588e02b_bool_t enable;
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

    /* start play test */
    wt588e02b_interface_debug_print("wt588e02b: start play test.\n");

    /* init */
    res = wt588e02b_init(&gs_handle);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: init failed.\n");

        return 1;
    }
    
    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: stop failed.\n");
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }
    
    /* delay 1000ms */
    wt588e02b_interface_delay_ms(1000);
    
    /* set vol */
    res = wt588e02b_set_vol(&gs_handle, 0x3F);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: set vol failed.\n");
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }

    /* play test */
    wt588e02b_interface_debug_print("wt588e02b: play test.\n");

    /* play */
    res = wt588e02b_play(&gs_handle, ind);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: play failed.\n");
        (void)wt588e02b_stop(&gs_handle);
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }
    
    /* check busy */
    enable = WT588E02B_BOOL_TRUE;
    while (enable == WT588E02B_BOOL_TRUE)
    {
        /* delay 100ms */
        wt588e02b_interface_delay_ms(100);
        
        res = wt588e02b_check_busy(&gs_handle, &enable);
        if (res != 0)
        {
            wt588e02b_interface_debug_print("wt588e02b: check busy failed.\n");
            (void)wt588e02b_stop(&gs_handle);
            (void)wt588e02b_deinit(&gs_handle);

            return 1;
        }
    }

    /* play list test */
    wt588e02b_interface_debug_print("wt588e02b: play list test.\n");
    
    /* play list */
    list[0] = 2;
    list[1] = 3;
    res = wt588e02b_play_list(&gs_handle, list, 2);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: play list failed.\n");
        (void)wt588e02b_stop(&gs_handle);
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }
    
    /* check busy */
    enable = WT588E02B_BOOL_TRUE;
    while (enable == WT588E02B_BOOL_TRUE)
    {
        /* delay 100ms */
        wt588e02b_interface_delay_ms(100);
        
        res = wt588e02b_check_busy(&gs_handle, &enable);
        if (res != 0)
        {
            wt588e02b_interface_debug_print("wt588e02b: check busy failed.\n");
            (void)wt588e02b_stop(&gs_handle);
            (void)wt588e02b_deinit(&gs_handle);

            return 1;
        }
    }
    
    /* play loop test */
    wt588e02b_interface_debug_print("wt588e02b: play loop test.\n");

    /* play loop */
    res = wt588e02b_play_loop(&gs_handle, ind);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: play loop failed.\n");
        (void)wt588e02b_stop(&gs_handle);
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }

    /* delay 10000ms */
    wt588e02b_interface_delay_ms(10000);

    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: stop failed.\n");
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }

    /* delay 1000ms */
    wt588e02b_interface_delay_ms(1000);

    /* play loop advance test */
    wt588e02b_interface_debug_print("wt588e02b: play loop advance test.\n");

    /* play loop advance */
    res = wt588e02b_play_loop_advance(&gs_handle, ind);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: play loop advance failed.\n");
        (void)wt588e02b_stop(&gs_handle);
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }

    /* delay 10000ms */
    wt588e02b_interface_delay_ms(10000);

    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: stop failed.\n");
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }

    /* delay 1000ms */
    wt588e02b_interface_delay_ms(1000);

    /* play loop all test */
    wt588e02b_interface_debug_print("wt588e02b: play loop all test.\n");

    /* play loop all */
    res = wt588e02b_play_loop_all(&gs_handle);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: play loop all failed.\n");
        (void)wt588e02b_stop(&gs_handle);
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }

    /* delay 10000ms */
    wt588e02b_interface_delay_ms(10000);

    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: stop failed.\n");
        (void)wt588e02b_deinit(&gs_handle);

        return 1;
    }

    /* delay 1000ms */
    wt588e02b_interface_delay_ms(1000);

    /* finish play test */
    wt588e02b_interface_debug_print("wt588e02b: finish play test.\n");
    (void)wt588e02b_deinit(&gs_handle);

    return 0;
}
