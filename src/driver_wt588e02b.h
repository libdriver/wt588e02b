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
 * @file      driver_wt588e02b.h
 * @brief     driver wt588e02b header file
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

#ifndef DRIVER_WT588E02B_H
#define DRIVER_WT588E02B_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup wt588e02b_driver wt588e02b driver function
 * @brief    wt588e02b driver modules
 * @{
 */

/**
 * @addtogroup wt588e02b_basic_driver
 * @{
 */

/**
 * @brief wt588e02b bool enumeration definition
 */
typedef enum
{
    WT588E02B_BOOL_FALSE = 0x00,        /**< disable */
    WT588E02B_BOOL_TRUE  = 0x01,        /**< enable */
} wt588e02b_bool_t;

/**
 * @brief wt588e02b handle structure definition
 */
typedef struct wt588e02b_handle_s
{
    uint8_t (*sclk_gpio_init)(void);                                           /**< point to a sclk_gpio_init function address */
    uint8_t (*sclk_gpio_deinit)(void);                                         /**< point to a sclk_gpio_deinit function address */
    uint8_t (*sclk_gpio_write)(uint8_t data);                                  /**< point to a sclk_gpio_write function address */
    uint8_t (*mosi_gpio_init)(void);                                           /**< point to a mosi_gpio_init function address */
    uint8_t (*mosi_gpio_deinit)(void);                                         /**< point to a mosi_gpio_deinit function address */
    uint8_t (*mosi_gpio_write)(uint8_t data);                                  /**< point to a mosi_gpio_write function address */
    uint8_t (*miso_gpio_init)(void);                                           /**< point to a miso_gpio_init function address */
    uint8_t (*miso_gpio_deinit)(void);                                         /**< point to a miso_gpio_deinit function address */
    uint8_t (*miso_gpio_read)(uint8_t *data);                                  /**< point to a miso_gpio_read function address */
    uint8_t (*cs_gpio_init)(void);                                             /**< point to a cs_gpio_init function address */
    uint8_t (*cs_gpio_deinit)(void);                                           /**< point to a cs_gpio_deinit function address */
    uint8_t (*cs_gpio_write)(uint8_t data);                                    /**< point to a cs_gpio_write function address */
    void (*delay_ms)(uint32_t ms);                                             /**< point to a delay_ms function address */
    void (*delay_us)(uint32_t us);                                             /**< point to a delay_us function address */
    void (*debug_print)(const char *const fmt, ...);                           /**< point to a debug_print function address */
    uint8_t (*bin_read_init)(char *name, uint32_t *size);                      /**< point to a bin_read_init function address */
    uint8_t (*bin_read)(uint32_t addr, uint16_t size, uint8_t *buffer);        /**< point to a bin_read function address */
    uint8_t (*bin_read_deinit)(void);                                          /**< point to a bin_read_deinit function address */
    uint8_t inited;                                                            /**< inited flag */
    uint16_t sum;                                                              /**< sum */
    uint8_t buf[512];                                                          /**< inner buffer */
} wt588e02b_handle_t;

/**
 * @brief wt588e02b information structure definition
 */
typedef struct wt588e02b_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} wt588e02b_info_t;

/**
 * @}
 */

/**
 * @defgroup wt588e02b_link_driver wt588e02b link driver function
 * @brief    wt588e02b link driver modules
 * @ingroup  wt588e02b_driver
 * @{
 */

/**
 * @brief     initialize wt588e02b_handle_t structure
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] STRUCTURE wt588e02b_handle_t
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_INIT(HANDLE, STRUCTURE)                    memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link sclk_gpio_init function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a sclk_gpio_init function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_SCLK_GPIO_INIT(HANDLE, FUC)                (HANDLE)->sclk_gpio_init = FUC

/**
 * @brief     link sclk_gpio_deinit function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a sclk_gpio_deinit function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_SCLK_GPIO_DEINIT(HANDLE, FUC)              (HANDLE)->sclk_gpio_deinit = FUC

/**
 * @brief     link sclk_gpio_write function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a sclk_gpio_write function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_SCLK_GPIO_WRITE(HANDLE, FUC)               (HANDLE)->sclk_gpio_write = FUC

/**
 * @brief     link mosi_gpio_init function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a mosi_gpio_init function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_MOSI_GPIO_INIT(HANDLE, FUC)                (HANDLE)->mosi_gpio_init = FUC

/**
 * @brief     link mosi_gpio_deinit function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a mosi_gpio_deinit function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_MOSI_GPIO_DEINIT(HANDLE, FUC)              (HANDLE)->mosi_gpio_deinit = FUC

/**
 * @brief     link mosi_gpio_write function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a mosi_gpio_write function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_MOSI_GPIO_WRITE(HANDLE, FUC)               (HANDLE)->mosi_gpio_write = FUC

/**
 * @brief     link miso_gpio_init function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a miso_gpio_init function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_MISO_GPIO_INIT(HANDLE, FUC)                (HANDLE)->miso_gpio_init = FUC

/**
 * @brief     link miso_gpio_deinit function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a miso_gpio_deinit function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_MISO_GPIO_DEINIT(HANDLE, FUC)              (HANDLE)->miso_gpio_deinit = FUC

/**
 * @brief     link miso_gpio_read function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a miso_gpio_read function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_MISO_GPIO_READ(HANDLE, FUC)                (HANDLE)->miso_gpio_read = FUC

/**
 * @brief     link cs_gpio_init function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a cs_gpio_init function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_CS_GPIO_INIT(HANDLE, FUC)                  (HANDLE)->cs_gpio_init = FUC

/**
 * @brief     link cs_gpio_deinit function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a cs_gpio_deinit function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_CS_GPIO_DEINIT(HANDLE, FUC)                (HANDLE)->cs_gpio_deinit = FUC

/**
 * @brief     link cs_gpio_write function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a cs_gpio_write function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_CS_GPIO_WRITE(HANDLE, FUC)                 (HANDLE)->cs_gpio_write = FUC

/**
 * @brief     link bin_read_init function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a bin_read_init function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_BIN_READ_INIT(HANDLE, FUC)                 (HANDLE)->bin_read_init = FUC

/**
 * @brief     link bin_read function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a bin_read function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_BIN_READ(HANDLE, FUC)                      (HANDLE)->bin_read = FUC

/**
 * @brief     link bin_read_deinit function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a bin_read_deinit function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_BIN_READ_DEINIT(HANDLE, FUC)               (HANDLE)->bin_read_deinit = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_DELAY_MS(HANDLE, FUC)                      (HANDLE)->delay_ms = FUC

/**
 * @brief     link delay_us function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a delay_us function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_DELAY_US(HANDLE, FUC)                      (HANDLE)->delay_us = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a wt588e02b handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_WT588E02B_LINK_DEBUG_PRINT(HANDLE, FUC)                   (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup wt588e02b_basic_driver wt588e02b basic driver function
 * @brief    wt588e02b basic driver modules
 * @ingroup  wt588e02b_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a wt588e02b info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t wt588e02b_info(wt588e02b_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 gpio initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t wt588e02b_init(wt588e02b_handle_t *handle);

/**
 * @brief     deinit the chip
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wt588e02b_deinit(wt588e02b_handle_t *handle);

/**
 * @brief      check chip busy
 * @param[in]  *handle pointer to a wt588e02b handle structure
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 check busy failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wt588e02b_check_busy(wt588e02b_handle_t *handle, wt588e02b_bool_t *enable);

/**
 * @brief     play audio
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 play failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 ind > 0xDF
 *            - 5 chip is busy
 * @note      ind > 0xDF
 */
uint8_t wt588e02b_play(wt588e02b_handle_t *handle, uint8_t ind);

/**
 * @brief     stop audio
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wt588e02b_stop(wt588e02b_handle_t *handle);

/**
 * @brief     set the volume
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] vol volume
 * @return    status code
 *            - 0 success
 *            - 1 set vol failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vol > 0x3F
 * @note      vol > 0x3F
 */
uint8_t wt588e02b_set_vol(wt588e02b_handle_t *handle, uint8_t vol);

/**
 * @brief     play loop
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 play loop failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 ind > 0xDF
 *            - 5 chip is busy
 * @note      ind > 0xDF
 */
uint8_t wt588e02b_play_loop(wt588e02b_handle_t *handle, uint8_t ind);

/**
 * @brief     play loop advance
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] ind index
 * @return    status code
 *            - 0 success
 *            - 1 play loop advance failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 ind > 0xDF
 *            - 5 chip is busy
 * @note      ind > 0xDF
 */
uint8_t wt588e02b_play_loop_advance(wt588e02b_handle_t *handle, uint8_t ind);

/**
 * @brief     play loop all
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 play loop all failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 chip is busy
 * @note      none
 */
uint8_t wt588e02b_play_loop_all(wt588e02b_handle_t *handle);

/**
 * @brief     play list
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] *list pointer to a list buffer
 * @param[in] len length of list
 * @return    status code
 *            - 0 success
 *            - 1 play list failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 len > 40
 *            - 5 list is invalid
 *            - 6 chip is busy
 * @note      len > 40
 *            list > 0xDF
 */
uint8_t wt588e02b_play_list(wt588e02b_handle_t *handle, uint8_t *list, uint8_t len);

/**
 * @brief     update audio
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] ind index
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 update failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 bin read init failed
 *            - 5 ind > 0xDF
 * @note      ind > 0xDF
 */
uint8_t wt588e02b_update(wt588e02b_handle_t *handle, uint8_t ind, char *path);

/**
 * @brief     update all audio
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] *path pointer to a path buffer
 * @return    status code
 *            - 0 success
 *            - 1 update failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 bin read init failed
 *            - 5 bin size is invalid
 * @note      none
 */
uint8_t wt588e02b_update_all(wt588e02b_handle_t *handle, char *path);

/**
 * @}
 */

/**
 * @defgroup wt588e02b_extern_driver wt588e02b extern driver function
 * @brief    wt588e02b extern driver modules
 * @ingroup  wt588e02b_driver
 * @{
 */

/**
 * @}
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @param[in] us delay us
 * @return    status code
 *            - 0 success
 *            - 1 set reg failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t wt588e02b_set_reg(wt588e02b_handle_t *handle, uint8_t *buf, uint16_t len, uint32_t us);

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a wt588e02b handle structure
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @param[in]  us delay us
 * @return     status code
 *             - 0 success
 *             - 1 get reg failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t wt588e02b_get_reg(wt588e02b_handle_t *handle, uint8_t *buf, uint16_t len, uint32_t us);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
