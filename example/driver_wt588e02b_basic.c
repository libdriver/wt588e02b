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
 * @file      driver_wt588e02b_basic.c
 * @brief     driver wt588e02b basic source file
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

#include "driver_wt588e02b_basic.h"

static wt588e02b_handle_t gs_handle;        /**< wt588e02b handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t wt588e02b_basic_init(void)
{
    uint8_t res;
    
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
    
    /* init */
    res = wt588e02b_init(&gs_handle);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: init failed.\n");
       
        return 1;
    }
    
    /* set default vol */
    res = wt588e02b_set_vol(&gs_handle, WT588E02B_BASIC_DEFAULT_VOLUME);
    if (res != 0)
    {
        wt588e02b_interface_debug_print("wt588e02b: set vol failed.\n");
        (void)wt588e02b_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example poll
 * @return status code
 *         - 0 success
 *         - 1 poll failed
 * @note   none
 */
uint8_t wt588e02b_basic_poll(void)
{
    uint8_t res;
    wt588e02b_bool_t enable;
    
    /* check busy */
    enable = WT588E02B_BOOL_TRUE;
    while (enable == WT588E02B_BOOL_TRUE)
    {
        /* delay 100ms */
        wt588e02b_interface_delay_ms(100);
        
        res = wt588e02b_check_busy(&gs_handle, &enable);
        if (res != 0)
        {
            return 1;
        }
    }
    
    return 0;
}

/**
 * @brief     basic example play
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 play failed
 * @note      none
 */
uint8_t wt588e02b_basic_play(uint8_t ind)
{
   uint8_t res;
    
    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* delay 100ms */
    wt588e02b_interface_delay_ms(100);
    
    /* play */
    res = wt588e02b_play(&gs_handle, ind);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example play list
 * @param[in] *list pointer to a list buffer
 * @param[in] len length of list
 * @return    status code
 *            - 0 success
 *            - 1 play list failed
 * @note      none
 */
uint8_t wt588e02b_basic_play_list(uint8_t *list, uint8_t len)
{
   uint8_t res;
    
    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* delay 100ms */
    wt588e02b_interface_delay_ms(100);
    
    /* play list */
    res = wt588e02b_play_list(&gs_handle, list, len);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set volume
 * @param[in] vol volume
 * @return    status code
 *            - 0 success
 *            - 1 set vol failed
 * @note      none
 */
uint8_t wt588e02b_basic_set_vol(uint8_t vol)
{
    uint8_t res;
    
    /* set vol */
    res = wt588e02b_set_vol(&gs_handle, vol);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example play loop
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 play loop failed
 * @note      none
 */
uint8_t wt588e02b_basic_play_loop(uint8_t ind)
{
    uint8_t res;
    
    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* delay 100ms */
    wt588e02b_interface_delay_ms(100);
    
    /* play loop */
    res = wt588e02b_play_loop(&gs_handle, ind);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example play loop advance
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 play loop advance failed
 * @note      none
 */
uint8_t wt588e02b_basic_play_loop_advance(uint8_t ind)
{
    uint8_t res;
    
    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* delay 100ms */
    wt588e02b_interface_delay_ms(100);
    
    /* play loop advance */
    res = wt588e02b_play_loop_advance(&gs_handle, ind);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example play loop all
 * @return status code
 *         - 0 success
 *         - 1 play loop all failed
 * @note   none
 */
uint8_t wt588e02b_basic_play_loop_all(void)
{
    uint8_t res;
    
    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* delay 100ms */
    wt588e02b_interface_delay_ms(100);
    
    /* play loop all */
    res = wt588e02b_play_loop_all(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example stop
 * @return status code
 *         - 0 success
 *         - 1 stop failed
 * @note   none
 */
uint8_t wt588e02b_basic_stop(void)
{
    uint8_t res;
    
    /* stop */
    res = wt588e02b_stop(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example update
 * @param[in] ind index
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 update failed
 * @note      none
 */
uint8_t wt588e02b_basic_update(uint8_t ind, char *path)
{
    uint8_t res;
    
    /* update */
    res = wt588e02b_update(&gs_handle, ind, path);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example update all
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 update all failed
 * @note      none
 */
uint8_t wt588e02b_basic_update_all(char *path)
{
    uint8_t res;
    
    /* update all */
    res = wt588e02b_update_all(&gs_handle, path);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t wt588e02b_basic_deinit(void)
{
    uint8_t res;
    
    /* deinit */
    res = wt588e02b_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
