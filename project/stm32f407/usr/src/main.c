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
 * @file      main.c
 * @brief     main source file
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
#include "driver_wt588e02b_update_test.h"
#include "driver_wt588e02b_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                        /**< uart buffer */
uint16_t volatile g_len;                   /**< uart buffer length */

/**
 * @brief     wt588e02b full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t wt588e02b(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"file", required_argument, NULL, 1},
        {"index", required_argument, NULL, 2},
        {"vol", required_argument, NULL, 3},
        {"list", required_argument, NULL, 4},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    char path[73]= "update.bin";
    uint8_t index = 0;
    uint8_t vol = 63;
    uint16_t number = 123;
    uint8_t number_len = 3;
    uint8_t list[63];
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* file path */
            case 1 :
            {
                /* set the file path */
                memset(path, 0, sizeof(char) * 73);
                strncpy(path, optarg, 72);
                
                break;
            }
            
            /* index */
            case 2 :
            {
                /* set the index */
                index = atoi(optarg);
                
                break;
            }
            
            /* vol */
            case 3 :
            {
                /* set the volume */
                vol = atoi(optarg);
                
                break;
            }
            
            /* number */
            case 4 :
            {
                uint8_t a0;
                uint8_t a1;
                uint8_t a2;
                uint8_t a3;
                uint8_t a4;
                
                /* set the number */
                number = atoi(optarg);
                
                a0 = number / 10000;
                a1 = (number % 10000) / 1000;
                a2 = (number % 1000) / 100;
                a3 = (number % 100) / 10;
                a4 = (number % 10) / 1;
                number_len = 0;
                if (a0 != 0)
                {
                    list[number_len] = a0;
                    number_len++;
                    list[number_len] = a1;
                    number_len++;
                    list[number_len] = a2;
                    number_len++;
                    list[number_len] = a3;
                    number_len++;
                    list[number_len] = a4;
                    number_len++;
                }
                else if (a1 != 0)
                {
                    list[number_len] = a1;
                    number_len++;
                    list[number_len] = a2;
                    number_len++;
                    list[number_len] = a3;
                    number_len++;
                    list[number_len] = a4;
                    number_len++;
                }
                else if (a2 != 0)
                {
                    list[number_len] = a2;
                    number_len++;
                    list[number_len] = a3;
                    number_len++;
                    list[number_len] = a4;
                    number_len++;
                }
                else if (a3 != 0)
                {
                    list[number_len] = a3;
                    number_len++;
                    list[number_len] = a4;
                    number_len++;
                }
                else
                {
                    list[number_len] = a4;
                    number_len++;
                }
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_play", type) == 0)
    {
        uint8_t res;
        
        /* run the play test */
        res = wt588e02b_play_test(index);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_update", type) == 0)
    {
        uint8_t res;
        
        /* run the update test */
        res = wt588e02b_update_test(index, path);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_update-all", type) == 0)
    {
        uint8_t res;
        
        /* run the update all test */
        res = wt588e02b_update_all_test(path);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_play", type) == 0)
    {
        uint8_t res;
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: play index %d.\n", index);
        
        /* basic init */
        res = wt588e02b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* play */
        res = wt588e02b_basic_play(index);
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* poll */
        res = wt588e02b_basic_poll();
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: play end.\n");
        
        /* deinit */
        (void)wt588e02b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_play-list", type) == 0)
    {
        uint8_t res;
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: play list %d.\n", number);
        
        /* basic init */
        res = wt588e02b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* play list */
        res = wt588e02b_basic_play_list(list, number_len);
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* poll */
        res = wt588e02b_basic_poll();
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: play list end.\n");
        
        /* deinit */
        (void)wt588e02b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_play-loop", type) == 0)
    {
        uint8_t res;
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: play loop index %d.\n", index);
        
        /* basic init */
        res = wt588e02b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* play loop */
        res = wt588e02b_basic_play_loop(index);
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* deinit */
        (void)wt588e02b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_play-loop-advance", type) == 0)
    {
        uint8_t res;
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: play loop advance index %d.\n", index);
        
        /* basic init */
        res = wt588e02b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* play loop advance */
        res = wt588e02b_basic_play_loop_advance(index);
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* deinit */
        (void)wt588e02b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_play-loop-all", type) == 0)
    {
        uint8_t res;
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: play loop all.\n");
        
        /* basic init */
        res = wt588e02b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* play loop all */
        res = wt588e02b_basic_play_loop_all();
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* deinit */
        (void)wt588e02b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_stop", type) == 0)
    {
        uint8_t res;
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: stop.\n");
        
        /* basic init */
        res = wt588e02b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* stop */
        res = wt588e02b_basic_stop();
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* deinit */
        (void)wt588e02b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_volume", type) == 0)
    {
        uint8_t res;
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: set volume %d.\n", vol);
        
        /* basic init */
        res = wt588e02b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* set vol */
        res = wt588e02b_basic_set_vol(vol);
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* deinit */
        (void)wt588e02b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_update", type) == 0)
    {
        uint8_t res;
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: update index %d.\n", index);
        
        /* basic init */
        res = wt588e02b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* update */
        res = wt588e02b_basic_update(index, path);
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: update end.\n");
        
        /* deinit */
        (void)wt588e02b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_update-all", type) == 0)
    {
        uint8_t res;
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: update all.\n");
        
        /* basic init */
        res = wt588e02b_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* update all */
        res = wt588e02b_basic_update_all(path);
        if (res != 0)
        {
            (void)wt588e02b_basic_deinit();
            
            return 1;
        }
        
        /* output */
        wt588e02b_interface_debug_print("wt588e02b: update end.\n");
        
        /* deinit */
        (void)wt588e02b_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        wt588e02b_interface_debug_print("Usage:\n");
        wt588e02b_interface_debug_print("  wt588e02b (-i | --information)\n");
        wt588e02b_interface_debug_print("  wt588e02b (-h | --help)\n");
        wt588e02b_interface_debug_print("  wt588e02b (-p | --port)\n");
        wt588e02b_interface_debug_print("  wt588e02b (-t play | --test=play) [--index=<index>]\n");
        wt588e02b_interface_debug_print("  wt588e02b (-t update | --test=update) [--index=<index>] [--file=<path>]\n");
        wt588e02b_interface_debug_print("  wt588e02b (-t update-all | --test=update-all) [--file=<path>]\n");
        wt588e02b_interface_debug_print("  wt588e02b (-e play | --example=play) [--index=<index>]\n");
        wt588e02b_interface_debug_print("  wt588e02b (-e play-list | --example=play-list) [--list=<number>]\n");
        wt588e02b_interface_debug_print("  wt588e02b (-e play-loop | --example=play-loop) [--index=<index>]\n");
        wt588e02b_interface_debug_print("  wt588e02b (-e play-loop-advance | --example=play-loop-advance) [--index=<index>]\n");
        wt588e02b_interface_debug_print("  wt588e02b (-e play-loop-all | --example=play-loop-all)\n");
        wt588e02b_interface_debug_print("  wt588e02b (-e stop | --example=stop)\n");
        wt588e02b_interface_debug_print("  wt588e02b (-e volume | --example=volume) [--vol=<volume>]\n");
        wt588e02b_interface_debug_print("  wt588e02b (-e update | --example=update) [--index=<index>] [--file=<path>]\n");
        wt588e02b_interface_debug_print("  wt588e02b (-e update-all | --example=update-all) [--file=<path>]\n");
        wt588e02b_interface_debug_print("\n");
        wt588e02b_interface_debug_print("Options:\n");
        wt588e02b_interface_debug_print("  -e <play | play-list | play-loop | play-loop-advance | play-loop-all | stop | volume | update | update-all>,\n"); 
        wt588e02b_interface_debug_print("      --example=<play | play-list | play-loop | play-loop-advance | play-loop-all | stop | volume | update | update-all>\n");
        wt588e02b_interface_debug_print("                          Run the driver example.\n");
        wt588e02b_interface_debug_print("      --file=<path>       Set the bin file path.([default: update.bin])\n");
        wt588e02b_interface_debug_print("  -h, --help              Show the help.\n");
        wt588e02b_interface_debug_print("  -i, --information       Show the chip information.\n");
        wt588e02b_interface_debug_print("      --index=<index>     Set the index of the voice.([default: 0])\n");
        wt588e02b_interface_debug_print("      --list=<number>     Set the list of the voice.([default: 123])\n");
        wt588e02b_interface_debug_print("      --vol=<volume>      Set the volume of the voice.([default: 63])\n");
        wt588e02b_interface_debug_print("  -p, --port              Display the pin connections of the current board.\n");
        wt588e02b_interface_debug_print("  -t <play | update | update-all>, --test=<play | update | update-all>\n");
        wt588e02b_interface_debug_print("                          Run the driver test.\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        wt588e02b_info_t info;
        
        /* print wt588e02b info */
        wt588e02b_info(&info);
        wt588e02b_interface_debug_print("wt588e02b: chip is %s.\n", info.chip_name);
        wt588e02b_interface_debug_print("wt588e02b: manufacturer is %s.\n", info.manufacturer_name);
        wt588e02b_interface_debug_print("wt588e02b: interface is %s.\n", info.interface);
        wt588e02b_interface_debug_print("wt588e02b: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        wt588e02b_interface_debug_print("wt588e02b: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        wt588e02b_interface_debug_print("wt588e02b: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        wt588e02b_interface_debug_print("wt588e02b: max current is %0.2fmA.\n", info.max_current_ma);
        wt588e02b_interface_debug_print("wt588e02b: max temperature is %0.1fC.\n", info.temperature_max);
        wt588e02b_interface_debug_print("wt588e02b: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        wt588e02b_interface_debug_print("wt588e02b: SCLK connected to GPIOA PIN0.\n");
        wt588e02b_interface_debug_print("wt588e02b: MISO connected to GPIOA PIN8.\n");
        wt588e02b_interface_debug_print("wt588e02b: MOSI connected to GPIOA PIN1.\n");
        wt588e02b_interface_debug_print("wt588e02b: CS connected to GPIOA PIN4.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register wt588e02b function */
    shell_init();
    shell_register("wt588e02b", wt588e02b);
    uart_print("wt588e02b: welcome to libdriver wt588e02b.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("wt588e02b: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("wt588e02b: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("wt588e02b: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("wt588e02b: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("wt588e02b: param is invalid.\n");
            }
            else
            {
                uart_print("wt588e02b: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
