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
 * @file      driver_wt588e02b.c
 * @brief     driver wt588e02b source file
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

#include "driver_wt588e02b.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Waytronic Electronic WT588E02B"        /**< chip name */
#define MANUFACTURER_NAME         "Waytronic Electronic"                  /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.0f                                    /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                                    /**< chip max supply voltage */
#define MAX_CURRENT               16.0f                                   /**< chip max current */
#define TEMPERATURE_MIN           -20.0f                                  /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                                   /**< chip max operating temperature */
#define DRIVER_VERSION            1000                                    /**< driver version */

/**
 * @brief chip command definition
 */
#define WT588E02B_COMMAND_PLAY                 0xF0        /**< play command */
#define WT588E02B_COMMAND_VOL                  0xF1        /**< vol command */
#define WT588E02B_COMMAND_PLAY_LOOP            0xF2        /**< play loop command */
#define WT588E02B_COMMAND_PLAY_LIST            0xF3        /**< play list command */
#define WT588E02B_COMMAND_STOP                 0xFF        /**< stop command */
#define WT588E02B_COMMAND_UPDATE_ADDR          0xE0        /**< update address command */
#define WT588E02B_COMMAND_UPDATE_ALL           0xE1        /**< update all command */
#define WT588E02B_COMMAND_UPDATE_STATUS        0xDF        /**< update status command */
#define WT588E02B_COMMAND_UPDATE_END           0xEF        /**< update end command */

/**
 * @brief      check busy
 * @param[in]  *handle pointer to a wt588e02b handle structure
 * @param[out] *busy pointer to a busy buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_wt588e02b_check_busy(wt588e02b_handle_t *handle, uint8_t *busy)
{
    uint8_t res;
    uint8_t miso;
    
    res = handle->miso_gpio_read(&miso);        /* read data */
    if (res != 0)                               /* check result */
    {
        return 1;                               /* return error */
    }
    if (miso != 0)                              /* check busy */
    {
        *busy = 0;                              /* no busy */
    }
    else
    {
        *busy = 1;                              /* busy */
    }
    
    return 0;                                   /* return error */
}

/**
 * @brief     write with no cs
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] us delay us in writing
 * @param[in] data input data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_wt588e02b_write_with_no_cs(wt588e02b_handle_t *handle, uint32_t us, uint8_t data)
{
    uint8_t res;
    uint8_t mosi;
    uint8_t i;
    
    for (i = 0; i < 8; i++)                         /* loop 8 bits */
    {
        mosi = (data >> (7 - i)) & 0x01;            /* get output bit */
        
        res = handle->mosi_gpio_write(mosi);        /* write one bit */
        if (res != 0)                               /* check result */
        {
            return 1;                               /* return error */
        }
        res = handle->sclk_gpio_write(1);           /* set sclk high */
        if (res != 0)                               /* check result */
        {
            return 1;                               /* return error */
        }
        handle->delay_us(us);                       /* delay us */
        res = handle->sclk_gpio_write(0);           /* set sclk low */
        if (res != 0)                               /* check result */
        {
            return 1;                               /* return error */
        }
        handle->delay_us(us);                       /* delay us */
    }
    
    return 0;                                       /* return error */
}

/**
 * @brief      read with no cs
 * @param[in]  *handle pointer to a wt588e02b handle structure
 * @param[in]  us delay us in reading
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_wt588e02b_read_with_no_cs(wt588e02b_handle_t *handle, uint32_t us, uint8_t *data)
{
    uint8_t res;
    uint8_t miso;
    uint8_t i;
    
    res = handle->mosi_gpio_write(0);               /* set low */
    if (res != 0)                                   /* check result */
    {
        return 1;                                   /* return error */
    }
    *data = 0;                                      /* init 0 */
    for (i = 0; i < 8; i++)                         /* loop 8 bits */
    {
        res = handle->sclk_gpio_write(1);           /* set sclk high */
        if (res != 0)                               /* check result */
        {
            return 1;                               /* return error */
        }
        handle->delay_us(us);                       /* delay us */
        res = handle->sclk_gpio_write(0);           /* set sclk low */
        if (res != 0)                               /* check result */
        {
            return 1;                               /* return error */
        }
        res = handle->miso_gpio_read(&miso);        /* read data */
        if (res != 0)                               /* check result */
        {
            return 1;                               /* return error */
        }
        if (miso != 0)                              /* check 1 */
        {
            *data |= 1 << (7 - i);                  /* set bit */
        }
        handle->delay_us(us);                       /* delay us */
    }
    
    return 0;                                       /* return error */
}

/**
 * @brief      update get status
 * @param[in]  *handle pointer to a wt588e02b handle structure
 * @param[out] *sum pointer to a sum buffer
 * @return     status code
 *             - 0 success
 *             - 1 update get status failed
 * @note       none
 */
static uint8_t a_update_get_status(wt588e02b_handle_t *handle, uint16_t *sum)
{
    uint8_t res;
    uint8_t data1;
    uint8_t data2;
    
    *sum = 0;                                                                               /* init 0 */
    res = handle->sclk_gpio_write(0);                                                       /* set sclk low */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");                        /* sclk gpio write failed */
        
        return 1;                                                                           /* return error */
    }
    res = handle->cs_gpio_write(0);                                                         /* set cs low */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                          /* cs gpio write failed */
        
        return 1;                                                                           /* return error */
    }
    handle->delay_ms(5);                                                                    /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 20, WT588E02B_COMMAND_UPDATE_STATUS);        /* write command */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                       /* write with no cs failed */
        
        return 1;                                                                           /* return error */
    }
    handle->delay_us(20);                                                                   /* delay 20us */
    res = a_wt588e02b_read_with_no_cs(handle, 20, &data1);                                  /* read one byte */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("wt588e02b: read with no cs failed.\n");                        /* read with no cs failed */
        
        return 1;                                                                           /* return error */
    }
    handle->delay_us(20);                                                                   /* delay 20us */
    res = a_wt588e02b_read_with_no_cs(handle, 20, &data2);                                  /* read one byte */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("wt588e02b: read2 with no cs failed.\n");                        /* read with no cs failed */
        
        return 1;                                                                           /* return error */
    }
    *sum = (uint16_t)((uint16_t)(data2) << 8) | data1;                                      /* get sum */
    res = handle->cs_gpio_write(1);                                                         /* set cs high */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                          /* cs gpio write failed */
        
        return 1;                                                                           /* return error */
    }
    
    return 0;                                                                               /* success return 0 */
}

/**
 * @brief     update
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] addr input address
 * @return    status code
 *            - 0 success
 *            - 1 update failed
 * @note      none
 */
static uint8_t a_update(wt588e02b_handle_t *handle, uint8_t addr)
{
    uint8_t res;
    
    handle->sum = 0;                                                                     /* init 0 */
    res = handle->sclk_gpio_write(0);                                                    /* set sclk low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");                     /* sclk gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(0);                                                      /* set cs low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    handle->delay_ms(5);                                                                 /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_UPDATE_ADDR);      /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    handle->sum += WT588E02B_COMMAND_UPDATE_ADDR;                                        /* add sum */
    handle->delay_us(20);                                                                /* delay 20us */
    res = a_wt588e02b_write_with_no_cs(handle, 100, addr);                               /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    handle->sum += addr;                                                                 /* add sum */
    res = handle->cs_gpio_write(1);                                                      /* set cs high */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     update all
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 update all failed
 * @note      none
 */
static uint8_t a_update_all(wt588e02b_handle_t *handle)
{
    uint8_t res;
    
    handle->sum = 0;                                                                     /* init 0 */
    res = handle->sclk_gpio_write(0);                                                    /* set sclk low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");                     /* sclk gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(0);                                                      /* set cs low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    handle->delay_ms(5);                                                                 /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_UPDATE_ALL);       /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    handle->sum += WT588E02B_COMMAND_UPDATE_ALL;                                         /* add sum */
    handle->delay_us(20);                                                                /* delay 20us */
    res = a_wt588e02b_write_with_no_cs(handle, 100, 0xFF);                               /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    handle->sum += 0xFF;                                                                 /* add sum */
    res = handle->cs_gpio_write(1);                                                      /* set cs high */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     update end
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @return    status code
 *            - 0 success
 *            - 1 update end failed
 * @note      none
 */
static uint8_t a_update_end(wt588e02b_handle_t *handle)
{
    uint8_t res;
    
    res = handle->sclk_gpio_write(0);                                                    /* set sclk low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");                     /* sclk gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(0);                                                      /* set cs low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    handle->delay_ms(5);                                                                 /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_UPDATE_END);       /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(1);                                                      /* set cs high */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

/**
 * @brief     update send pack
 * @param[in] *handle pointer to a wt588e02b handle structure
 * @param[in] *buf pointer to a buffer address
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 update send pack failed
 * @note      none
 */
static uint8_t a_update_send_pack(wt588e02b_handle_t *handle, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    uint16_t check;
    uint16_t i;
    
    handle->sum = 0;                                                             /* init 0 */
    res = handle->sclk_gpio_write(0);                                            /* set sclk low */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");             /* sclk gpio write failed */
        
        return 1;                                                                /* return error */
    }
    res = handle->cs_gpio_write(0);                                              /* set cs low */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");               /* cs gpio write failed */
        
        return 1;                                                                /* return error */
    }
    for (i = 0; i < len; i++)                                                    /* loop all */
    {
        handle->delay_us(20);
        res = a_wt588e02b_write_with_no_cs(handle, 2, buf[i]);                   /* write command */
        if (res != 0)                                                            /* check result */
        {
            handle->debug_print("wt588e02b: write with no cs failed.\n");        /* write with no cs failed */
            
            return 1;                                                            /* return error */
        }
        if ((i % 2) != 0)                                                        /* the second */
        {
            check = check | ((uint16_t)(buf[i]) << 8);                           /* set sum */
            handle->sum += check;                                                /* add sum */
        }
        else
        {
            check = buf[i];                                                      /* set sum */
        }
    }
    res = handle->cs_gpio_write(1);                                              /* set cs high */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");               /* cs gpio write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t wt588e02b_play(wt588e02b_handle_t *handle, uint8_t ind)
{
    uint8_t res;
    uint8_t busy;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    if (ind > 0xDF)                                                                 /* check result */
    {
        handle->debug_print("wt588e02b: ind > 0xDF.\n");                            /* ind > 0xDF */
        
        return 4;                                                                   /* return error */
    }
    res = a_wt588e02b_check_busy(handle, &busy);                                    /* read busy */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("wt588e02b: check busy failed.\n");                     /* check busy failed */
        
        return 1;                                                                   /* return error */
    }
    if (busy != 0)                                                                  /* check busy */
    {
        handle->debug_print("wt588e02b: chip is busy.\n");                          /* chip is busy */
        
        return 5;                                                                   /* return error */
    }
    
    res = handle->sclk_gpio_write(0);                                               /* set sclk low */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");                /* sclk gpio write failed */
        
        return 1;                                                                   /* return error */
    }
    res = handle->cs_gpio_write(0);                                                 /* set cs low */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                  /* cs gpio write failed */
        
        return 1;                                                                   /* return error */
    }
    handle->delay_ms(5);                                                            /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_PLAY);        /* write command */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");               /* write with no cs failed */
        
        return 1;                                                                   /* return error */
    }
    res = a_wt588e02b_write_with_no_cs(handle, 100, ind);                           /* write command */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");               /* write with no cs failed */
        
        return 1;                                                                   /* return error */
    }
    res = handle->cs_gpio_write(1);                                                 /* set cs high */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                  /* cs gpio write failed */
        
        return 1;                                                                   /* return error */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t wt588e02b_set_vol(wt588e02b_handle_t *handle, uint8_t vol)
{
    uint8_t res;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    if (vol > 0x3F)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: vol > 0x3F.\n");                           /* vol > 0x3F */
        
        return 4;                                                                  /* return error */
    }
    
    res = handle->sclk_gpio_write(0);                                              /* set sclk low */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");               /* sclk gpio write failed */
        
        return 1;                                                                  /* return error */
    }
    res = handle->cs_gpio_write(0);                                                /* set cs low */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                 /* cs gpio write failed */
        
        return 1;                                                                  /* return error */
    }
    handle->delay_ms(5);                                                           /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_VOL);        /* write command */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");              /* write with no cs failed */
        
        return 1;                                                                  /* return error */
    }
    res = a_wt588e02b_write_with_no_cs(handle, 100, vol);                          /* write command */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");              /* write with no cs failed */
        
        return 1;                                                                  /* return error */
    }
    res = handle->cs_gpio_write(1);                                                /* set cs high */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                 /* cs gpio write failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wt588e02b_stop(wt588e02b_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    
    res = handle->sclk_gpio_write(0);                                              /* set sclk low */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");               /* sclk gpio write failed */
        
        return 1;                                                                  /* return error */
    }
    res = handle->cs_gpio_write(0);                                                /* set cs low */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                 /* cs gpio write failed */
        
        return 1;                                                                  /* return error */
    }
    handle->delay_ms(5);                                                           /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_STOP);       /* write command */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");              /* write with no cs failed */
        
        return 1;                                                                  /* return error */
    }
    res = a_wt588e02b_write_with_no_cs(handle, 100, 0xEF);                         /* write command */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");              /* write with no cs failed */
        
        return 1;                                                                  /* return error */
    }
    res = handle->cs_gpio_write(1);                                                /* set cs high */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                 /* cs gpio write failed */
        
        return 1;                                                                  /* return error */
    }
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t wt588e02b_play_list(wt588e02b_handle_t *handle, uint8_t *list, uint8_t len)
{
    uint8_t i;
    uint8_t res;
    uint8_t busy;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    if (len > 40)                                                                        /* check length */
    {
        handle->debug_print("wt588e02b: len > 40.\n");                                   /* len > 40 */
        
        return 4;                                                                        /* return error */
    }
    for (i = 0; i < len; i++)                                                            /* check all */
    {
        if (list[i] > 0xDF)                                                              /* check range */
        {
            handle->debug_print("wt588e02b: list[%d] > 0xDF.\n", i);                     /* list > 0xDF */
            
            return 5;                                                                    /* return error */
        }
    }
    res = a_wt588e02b_check_busy(handle, &busy);                                         /* read busy */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: check busy failed.\n");                          /* check busy failed */
        
        return 1;                                                                        /* return error */
    }
    if (busy != 0)                                                                       /* check busy */
    {
        handle->debug_print("wt588e02b: chip is busy.\n");                               /* chip is busy */
        
        return 6;                                                                        /* return error */
    }
    
    res = handle->sclk_gpio_write(0);                                                    /* set sclk low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");                     /* sclk gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(0);                                                      /* set cs low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    handle->delay_ms(5);                                                                 /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_PLAY_LIST);        /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    for (i = 0; i < len; i ++)                                                           /* write all */
    {
        res = a_wt588e02b_write_with_no_cs(handle, 100, list[i]);                        /* write command */
        if (res != 0)                                                                    /* check result */
        {
            handle->debug_print("wt588e02b: write with no cs failed.\n");                /* write with no cs failed */
            
            return 1;                                                                    /* return error */
        }
    }
    res = handle->cs_gpio_write(1);                                                      /* set cs high */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t wt588e02b_play_loop(wt588e02b_handle_t *handle, uint8_t ind)
{
    uint8_t res;
    uint8_t busy;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    if (ind > 0xDF)                                                                      /* check result */
    {
        handle->debug_print("wt588e02b: ind > 0xDF.\n");                                 /* ind > 0xDF */
        
        return 4;                                                                        /* return error */
    }
    
    res = a_wt588e02b_check_busy(handle, &busy);                                         /* read busy */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: check busy failed.\n");                          /* check busy failed */
        
        return 1;                                                                        /* return error */
    }
    if (busy != 0)                                                                       /* check busy */
    {
        handle->debug_print("wt588e02b: chip is busy.\n");                               /* chip is busy */
        
        return 5;                                                                        /* return error */
    }
    
    res = handle->sclk_gpio_write(0);                                                    /* set sclk low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");                     /* sclk gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(0);                                                      /* set cs low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    handle->delay_ms(5);                                                                 /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_PLAY_LOOP);        /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    res = a_wt588e02b_write_with_no_cs(handle, 100, 0x02);                               /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    res = a_wt588e02b_write_with_no_cs(handle, 100, ind);                                /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(1);                                                      /* set cs high */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t wt588e02b_play_loop_advance(wt588e02b_handle_t *handle, uint8_t ind)
{
    uint8_t res;
    uint8_t busy;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    if (ind > 0xDF)                                                                      /* check result */
    {
        handle->debug_print("wt588e02b: ind > 0xDF.\n");                                 /* ind > 0xDF */
        
        return 4;                                                                        /* return error */
    }
    
    res = a_wt588e02b_check_busy(handle, &busy);                                         /* read busy */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: check busy failed.\n");                          /* check busy failed */
        
        return 1;                                                                        /* return error */
    }
    if (busy != 0)                                                                       /* check busy */
    {
        handle->debug_print("wt588e02b: chip is busy.\n");                               /* chip is busy */
        
        return 5;                                                                        /* return error */
    }
    
    res = handle->sclk_gpio_write(0);                                                    /* set sclk low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");                     /* sclk gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(0);                                                      /* set cs low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    handle->delay_ms(5);                                                                 /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_PLAY_LOOP);        /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    res = a_wt588e02b_write_with_no_cs(handle, 100, 0x01);                               /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    res = a_wt588e02b_write_with_no_cs(handle, 100, ind);                                /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(1);                                                      /* set cs high */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t wt588e02b_play_loop_all(wt588e02b_handle_t *handle)
{
    uint8_t res;
    uint8_t busy;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    res = a_wt588e02b_check_busy(handle, &busy);                                         /* read busy */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: check busy failed.\n");                          /* check busy failed */
        
        return 1;                                                                        /* return error */
    }
    if (busy != 0)                                                                       /* check busy */
    {
        handle->debug_print("wt588e02b: chip is busy.\n");                               /* chip is busy */
        
        return 4;                                                                        /* return error */
    }
    
    res = handle->sclk_gpio_write(0);                                                    /* set sclk low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");                     /* sclk gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(0);                                                      /* set cs low */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    handle->delay_ms(5);                                                                 /* delay 5ms */
    res = a_wt588e02b_write_with_no_cs(handle, 100, WT588E02B_COMMAND_PLAY_LOOP);        /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    res = a_wt588e02b_write_with_no_cs(handle, 100, 0x03);                               /* write command */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: write with no cs failed.\n");                    /* write with no cs failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->cs_gpio_write(1);                                                      /* set cs high */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");                       /* cs gpio write failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t wt588e02b_update(wt588e02b_handle_t *handle, uint8_t ind, char *path)
{
    uint8_t res;
    uint16_t sum;
    uint32_t size;
    uint32_t i;
    uint32_t m;
    uint32_t n;
    uint32_t addr;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (ind > 0xDF)                                                               /* check result */
    {
        handle->debug_print("wt588e02b: ind > 0xDF.\n");                          /* ind > 0xDF */
        
        return 5;                                                                 /* return error */
    }
    
    res = handle->bin_read_init(path, &size);                                     /* bin read init */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("wt588e02b: bin read init failed.\n");                /* bin read init failed */
        
        return 4;                                                                 /* return error */
    }
    
    m = size / 512;                                                               /* get package number */
    n = size - m * 512;                                                           /* get package remain */
    res = a_update(handle, ind);                                                  /* update */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("wt588e02b: update failed.\n");                       /* update failed */
        (void)handle->bin_read_deinit();                                          /* bin read deinit */
        
        return 1;                                                                 /* return error */
    }
    handle->delay_ms(30);                                                         /* delay 30ms */
    addr = 0;                                                                     /* init 0 */
    for (i = 0; i < m; i++)                                                       /* loop all */
    {
        handle->delay_ms(16);                                                     /* delay 16ms */
        res = handle->bin_read(addr, 512, handle->buf);                           /* bin read */
        if (res != 0)                                                             /* check result */
        {
            handle->debug_print("wt588e02b: bin read failed.\n");                 /* bin read failed */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
        addr += 512;                                                              /* add 512 */
        res = a_update_get_status(handle, &sum);                                  /* get status */
        if (res != 0)                                                             /* check result */
        {
            handle->debug_print("wt588e02b: update get status failed.\n");        /* update get status failed */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
        if (handle->sum != sum)                                                   /* check sum */
        {
            handle->debug_print("wt588e02b: sum check error.\n");                 /* sum check error */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
        handle->delay_ms(1);                                                      /* delay 1ms */
        res = a_update_send_pack(handle, handle->buf, 512);                       /* send pack */
        if (res != 0)                                                             /* check sum */
        {
            handle->debug_print("wt588e02b: update send pack failed.\n");         /* update send pack failed */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
    }
    if (n != 0)                                                                   /* check remain */
    {
        handle->delay_ms(16);                                                     /* delay 16ms */
        memset(handle->buf, 0, sizeof(uint8_t) * 512);                            /* init 0 */
        res = handle->bin_read(addr, n, handle->buf);                             /* bin read */
        if (res != 0)                                                             /* check result */
        {
            handle->debug_print("wt588e02b: bin read failed.\n");                 /* bin read failed */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
        addr += n;                                                                /* add n */
        res = a_update_get_status(handle, &sum);                                  /* get status */
        if (res != 0)                                                             /* check result */
        {
            handle->debug_print("wt588e02b: update get status failed.\n");        /* update get status failed */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
        if (handle->sum != sum)                                                   /* check sum */
        {
            handle->debug_print("wt588e02b: sum check error.\n");                 /* sum check error */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
        handle->delay_ms(1);                                                      /* delay 1ms */
        res = a_update_send_pack(handle, handle->buf, 512);                       /* send pack */
        if (res != 0)                                                             /* check sum */
        {
            handle->debug_print("wt588e02b: update send pack failed.\n");         /* update send pack failed */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
    }
    res = a_update_end(handle);                                                   /* update end */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("wt588e02b: update end failed.\n");                   /* update end failed */
        (void)handle->bin_read_deinit();                                          /* bin read deinit */
        
        return 1;                                                                 /* return error */
    }
    res = handle->bin_read_deinit();                                              /* bin read deinit */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("wt588e02b: bin read deinit failed.\n");              /* bin read deinit failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t wt588e02b_update_all(wt588e02b_handle_t *handle, char *path)
{
    uint8_t res;
    uint16_t sum;
    uint32_t size;
    uint32_t i;
    uint32_t m;
    uint32_t addr;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = handle->bin_read_init(path, &size);                                     /* bin read init */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("wt588e02b: bin read init failed.\n");                /* bin read init failed */
        
        return 4;                                                                 /* return error */
    }
    if ((size % 512) != 0)                                                        /* check size */
    {
        handle->debug_print("wt588e02b: bin size is invalid.\n");                 /* bin size is invalid */
        (void)handle->bin_read_deinit();                                          /* bin read deinit */
        
        return 5;                                                                 /* return error */
    }
    
    m = size / 512;                                                               /* get package number */
    res = a_update_all(handle);                                                   /* update all */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("wt588e02b: update all failed.\n");                   /* update all failed */
        (void)handle->bin_read_deinit();                                          /* bin read deinit */
        
        return 1;                                                                 /* return error */
    }
    handle->delay_ms(30);                                                         /* delay 30ms */
    addr = 0;                                                                     /* init 0 */
    for (i = 0; i < m; i++)                                                       /* loop all */
    {
        handle->delay_ms(16);                                                     /* delay 16ms */
        res = handle->bin_read(addr, 512, handle->buf);                           /* bin read */
        if (res != 0)                                                             /* check result */
        {
            handle->debug_print("wt588e02b: bin read failed.\n");                 /* bin read failed */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
        addr += 512;                                                              /* add 512 */
        res = a_update_get_status(handle, &sum);                                  /* get status */
        if (res != 0)                                                             /* check result */
        {
            handle->debug_print("wt588e02b: update get status failed.\n");        /* update get status failed */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
        if (handle->sum != sum)                                                   /* check sum */
        {
            handle->debug_print("wt588e02b: sum check error.\n");                 /* sum check error */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
        handle->delay_ms(1);                                                      /* delay 1ms */
        res = a_update_send_pack(handle, handle->buf, 512);                       /* send pack */
        if (res != 0)                                                             /* check sum */
        {
            handle->debug_print("wt588e02b: update send pack failed.\n");         /* update send pack failed */
            (void)handle->bin_read_deinit();                                      /* bin read deinit */
            
            return 1;                                                             /* return error */
        }
    }
    res = a_update_end(handle);                                                   /* update end */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("wt588e02b: update end failed.\n");                   /* update end failed */
        (void)handle->bin_read_deinit();                                          /* bin read deinit */
        
        return 1;                                                                 /* return error */
    }
    res = handle->bin_read_deinit();                                              /* bin read deinit */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("wt588e02b: bin read deinit failed.\n");              /* bin read deinit failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t wt588e02b_check_busy(wt588e02b_handle_t *handle, wt588e02b_bool_t *enable)
{
    uint8_t res;
    uint8_t busy;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }

    res = a_wt588e02b_check_busy(handle, &busy);                       /* read busy */
    if (res != 0)                                                      /* check result */
    {
        handle->debug_print("wt588e02b: check busy failed.\n");        /* check busy failed */
        
        return 1;                                                      /* return error */
    }
    if (busy != 0)                                                     /* check busy */
    {
        *enable = WT588E02B_BOOL_TRUE;                                 /* set true */
    }
    else
    {
        *enable = WT588E02B_BOOL_FALSE;                                /* set false */
    }

    return 0;                                                          /* success return 0 */
}

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
uint8_t wt588e02b_init(wt588e02b_handle_t *handle)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->debug_print == NULL)                                         /* check debug_print */
    {
        return 3;                                                            /* return error */
    }
    if (handle->sclk_gpio_init == NULL)                                      /* check sclk_gpio_init */
    {
        handle->debug_print("wt588e02b: sclk_gpio_init is null.\n");         /* sclk_gpio_init is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->sclk_gpio_deinit == NULL)                                    /* check sclk_gpio_deinit */
    {
        handle->debug_print("wt588e02b: sclk_gpio_deinit is null.\n");       /* sclk_gpio_deinit is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->sclk_gpio_write == NULL)                                     /* check sclk_gpio_write */
    {
        handle->debug_print("wt588e02b: sclk_gpio_write is null.\n");        /* sclk_gpio_write is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->mosi_gpio_init == NULL)                                      /* check mosi_gpio_init */
    {
        handle->debug_print("wt588e02b: mosi_gpio_init is null.\n");         /* mosi_gpio_init is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->mosi_gpio_deinit == NULL)                                    /* check mosi_gpio_deinit */
    {
        handle->debug_print("wt588e02b: mosi_gpio_deinit is null.\n");       /* mosi_gpio_deinit is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->mosi_gpio_write == NULL)                                     /* check mosi_gpio_write */
    {
        handle->debug_print("wt588e02b: mosi_gpio_write is null.\n");        /* mosi_gpio_write is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->miso_gpio_init == NULL)                                      /* check miso_gpio_init */
    {
        handle->debug_print("wt588e02b: miso_gpio_init is null.\n");         /* miso_gpio_init is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->miso_gpio_deinit == NULL)                                    /* check miso_gpio_deinit */
    {
        handle->debug_print("wt588e02b: miso_gpio_deinit is null.\n");       /* miso_gpio_deinit is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->miso_gpio_read == NULL)                                      /* check miso_gpio_read */
    {
        handle->debug_print("wt588e02b: miso_gpio_read is null.\n");         /* miso_gpio_read is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->cs_gpio_init == NULL)                                        /* check cs_gpio_init */
    {
        handle->debug_print("wt588e02b: cs_gpio_init is null.\n");           /* cs_gpio_init is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->cs_gpio_deinit == NULL)                                      /* check cs_gpio_deinit */
    {
        handle->debug_print("wt588e02b: cs_gpio_deinit is null.\n");         /* cs_gpio_deinit is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->cs_gpio_write == NULL)                                       /* check cs_gpio_write */
    {
        handle->debug_print("wt588e02b: cs_gpio_write is null.\n");          /* cs_gpio_write is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->delay_ms == NULL)                                            /* check delay_ms */
    {
        handle->debug_print("wt588e02b: delay_ms is null.\n");               /* delay_ms is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->delay_us == NULL)                                            /* check delay_us */
    {
        handle->debug_print("wt588e02b: delay_us is null.\n");               /* delay_us is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->bin_read_init == NULL)                                       /* check bin_read_init */
    {
        handle->debug_print("wt588e02b: bin_read_init is null.\n");          /* bin_read_init is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->bin_read == NULL)                                            /* check bin_read */
    {
        handle->debug_print("wt588e02b: bin_read is null.\n");               /* bin_read is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->bin_read_deinit == NULL)                                     /* check bin_read_deinit */
    {
        handle->debug_print("wt588e02b: bin_read_deinit is null.\n");        /* bin_read_deinit is null */
       
        return 3;                                                            /* return error */
    }
    
    if (handle->sclk_gpio_init() != 0)                                       /* sclk gpio init */
    {
        handle->debug_print("wt588e02b: sclk gpio init failed.\n");          /* sclk gpio init failed */
       
        return 1;                                                            /* return error */
    }
    if (handle->mosi_gpio_init() != 0)                                       /* mosi gpio init */
    {
        handle->debug_print("wt588e02b: mosi gpio init failed.\n");          /* mosi gpio init failed */
        (void)handle->sclk_gpio_deinit();                                    /* sclk gpio deinit */
        
        return 1;                                                            /* return error */
    }
    if (handle->miso_gpio_init() != 0)                                       /* miso gpio init */
    {
        handle->debug_print("wt588e02b: miso gpio init failed.\n");          /* miso gpio init failed */
        (void)handle->sclk_gpio_deinit();                                    /* sclk gpio deinit */
        (void)handle->mosi_gpio_deinit();                                    /* mosi gpio deinit */
        
        return 1;                                                            /* return error */
    }
    if (handle->cs_gpio_init() != 0)                                         /* cs gpio init */
    {
        handle->debug_print("wt588e02b: cs gpio init failed.\n");            /* cs gpio init failed */
        (void)handle->sclk_gpio_deinit();                                    /* sclk gpio deinit */
        (void)handle->mosi_gpio_deinit();                                    /* mosi gpio deinit */
        (void)handle->miso_gpio_deinit();                                    /* miso gpio deinit */
        
        return 1;                                                            /* return error */
    }
    handle->sum = 0;                                                         /* init 0 */
    handle->inited = 1;                                                      /* flag finished */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wt588e02b_deinit(wt588e02b_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = handle->sclk_gpio_deinit();                                        /* sclk gpio deinit failed */
    if (res != 0)                                                            /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio deinit failed.\n");        /* sclk gpio deinit failed */
        
        return 1;                                                            /* return error */
    }
    res = handle->mosi_gpio_deinit();                                        /* mosi gpio deinit failed */
    if (res != 0)                                                            /* check result */
    {
        handle->debug_print("wt588e02b: mosi gpio deinit failed.\n");        /* mosi gpio deinit failed */
        
        return 1;                                                            /* return error */
    }
    res = handle->miso_gpio_deinit();                                        /* miso gpio deinit failed */
    if (res != 0)                                                            /* check result */
    {
        handle->debug_print("wt588e02b: miso gpio deinit failed.\n");        /* miso gpio deinit failed */
        
        return 1;                                                            /* return error */
    }
    res = handle->cs_gpio_deinit();                                          /* cs gpio deinit failed */
    if (res != 0)                                                            /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio deinit failed.\n");          /* cs gpio deinit failed */
        
        return 1;                                                            /* return error */
    }
    handle->inited = 0;                                                      /* flag closed */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t wt588e02b_set_reg(wt588e02b_handle_t *handle, uint8_t *buf, uint16_t len, uint32_t us)
{
    uint8_t res;
    uint16_t i;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = handle->sclk_gpio_write(0);                                            /* set sclk low */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");             /* sclk gpio write failed */
        
        return 1;                                                                /* return error */
    }
    res = handle->cs_gpio_write(0);                                              /* set cs low */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");               /* cs gpio write failed */
        
        return 1;                                                                /* return error */
    }
    for (i = 0; i < len; i++)                                                    /* write all */
    {
        handle->delay_ms(5);                                                     /* delay 5ms */
        res = a_wt588e02b_write_with_no_cs(handle, us, buf[i]);                  /* write command */
        if (res != 0)                                                            /* check result */
        {
            handle->debug_print("wt588e02b: write with no cs failed.\n");        /* write with no cs failed */
            
            return 1;                                                            /* return error */
        }
    }
    res = handle->cs_gpio_write(1);                                              /* set cs high */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");               /* cs gpio write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t wt588e02b_get_reg(wt588e02b_handle_t *handle, uint8_t *buf, uint16_t len, uint32_t us)
{
    uint8_t res;
    uint16_t i;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = handle->sclk_gpio_write(0);                                            /* set sclk low */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: sclk gpio write failed.\n");             /* sclk gpio write failed */
        
        return 1;                                                                /* return error */
    }
    res = handle->cs_gpio_write(0);                                              /* set cs low */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");               /* cs gpio write failed */
        
        return 1;                                                                /* return error */
    }
    for (i = 0; i < len; i++)                                                    /* write all */
    {
        handle->delay_ms(5);                                                     /* delay 5ms */
        res = a_wt588e02b_read_with_no_cs(handle, us, &buf[i]);                  /* read data */
        if (res != 0)                                                            /* check result */
        {
            handle->debug_print("wt588e02b: read with no cs failed.\n");         /* read with no cs failed */
            
            return 1;                                                            /* return error */
        }
    }
    res = handle->cs_gpio_write(1);                                              /* set cs high */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("wt588e02b: cs gpio write failed.\n");               /* cs gpio write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a wt588e02b info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t wt588e02b_info(wt588e02b_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(wt588e02b_info_t));                      /* initialize wt588e02b info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
