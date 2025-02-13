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
 * @file      stm32f407_driver_wt588e02b_interface.c
 * @brief     stm32f407 driver wt588e02b interface source file
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

#include "driver_wt588e02b_interface.h"
#include "delay.h"
#include "ff.h"
#include "wire.h"
#include "uart.h"
#include <stdarg.h>

/**
 * @brief fs var definition
 */
FATFS g_fs;        /**< fatfs handle */
FIL g_file;        /**< fs handle */

/**
 * @brief  interface sclk gpio init
 * @return status code
 *         - 0 success
 *         - 1 sclk gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_sclk_gpio_init(void)
{
    return wire_clock_init();
}

/**
 * @brief  interface sclk gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 sclk gpio deinit failed
 * @note   none
 */
uint8_t wt588e02b_interface_sclk_gpio_deinit(void)
{
    return wire_clock_deinit();
}

/**
 * @brief     interface sclk gpio write
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wt588e02b_interface_sclk_gpio_write(uint8_t data)
{
    return wire_clock_write(data);
}

/**
 * @brief  interface mosi gpio init
 * @return status code
 *         - 0 success
 *         - 1 mosi gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_mosi_gpio_init(void)
{
    return wire_data_init();
}

/**
 * @brief  interface mosi gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 mosi gpio deinit failed
 * @note   none
 */
uint8_t wt588e02b_interface_mosi_gpio_deinit(void)
{
    return wire_data_deinit();
}

/**
 * @brief     interface mosi gpio write
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wt588e02b_interface_mosi_gpio_write(uint8_t data)
{
    return wire_data_write(data);
}

/**
 * @brief  interface miso gpio init
 * @return status code
 *         - 0 success
 *         - 1 miso gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_miso_gpio_init(void)
{
    return wire_init();
}

/**
 * @brief  interface miso gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 miso gpio deinit failed
 * @note   none
 */
uint8_t wt588e02b_interface_miso_gpio_deinit(void)
{
    return wire_deinit();
}

/**
 * @brief      interface miso_gpio_read
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t wt588e02b_interface_miso_gpio_read(uint8_t *data)
{
    return wire_read(data);
}

/**
 * @brief  interface cs gpio init
 * @return status code
 *         - 0 success
 *         - 1 cs gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_cs_gpio_init(void)
{
    return wire_cs_init();
}

/**
 * @brief  interface cs gpio init
 * @return status code
 *         - 0 success
 *         - 1 cs gpio init failed
 * @note   none
 */
uint8_t wt588e02b_interface_cs_gpio_deinit(void)
{
    return wire_cs_deinit();
}

/**
 * @brief     interface cs gpio write
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t wt588e02b_interface_cs_gpio_write(uint8_t data)
{
    return wire_cs_write(data);
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void wt588e02b_interface_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}

/**
 * @brief     interface delay us
 * @param[in] us time
 * @note      none
 */
void wt588e02b_interface_delay_us(uint32_t us)
{
    delay_us(us);
}

/**
 * @brief      interface bin read init
 * @param[in]  *name pointer to a name buffer
 * @param[out] *size pointer to a file size buffer
 * @return     status code
 *             - 0 success
 *             - 1 bin read init failed
 * @note       none
 */
uint8_t wt588e02b_interface_bin_read_init(char *name, uint32_t *size)
{
    FRESULT res;
    
    res = f_mount(&g_fs, "0:", 1);
    if (res != FR_OK)
    {
        return 1;
    }
    res = f_open(&g_file, name, FA_READ);
    if (res != FR_OK)
    {
        return 1;
    }
    *size = f_size(&g_file);
    
    return 0;
}

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
uint8_t wt588e02b_interface_bin_read(uint32_t addr, uint16_t size, uint8_t *buffer)
{
    FRESULT res;
    UINT bw;
    
    res = f_lseek(&g_file, addr);
    if (res != FR_OK)
    {
        return 1;
    }
    res = f_read(&g_file, buffer, size, &bw);
    if (res != FR_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  interface bin read deinit
 * @return status code
 *         - 0 success
 *         - 1 bin read deinit failed
 * @note   none
 */
uint8_t wt588e02b_interface_bin_read_deinit(void)
{
    FRESULT res;
    
    res = f_close(&g_file);
    if (res != FR_OK)
    {
        return 1;
    }
    res = f_unmount("0:");
    if (res != FR_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void wt588e02b_interface_debug_print(const char *const fmt, ...)
{
    char str[256];
    uint16_t len;
    va_list args;
    
    memset((char *)str, 0, sizeof(char) * 256); 
    va_start(args, fmt);
    vsnprintf((char *)str, 255, (char const *)fmt, args);
    va_end(args);
    
    len = strlen((char *)str);
    (void)uart_write((uint8_t *)str, len);
}
