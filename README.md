[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WT588E02B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/wt588e02b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

WT588E02B-8S is a 16 bit DSP voice chip developed by Shenzhen Weichuang Zhiyin Electronics Co., Ltd. It has an internal oscillation of 32MHz and 16 bit PWM decoding. The powerful features make WT588E02B-8S a leader in the voice chip industry. At present, WT588E02B-8S can store up to 170 seconds of voice content with higher sound quality (if the customer has no requirements for sound quality, it can store up to 320 seconds of voice content). WT588E02B-8S is different from traditional OTP chips, and its biggest breakthrough is that customers can replace the internal voice content of the chip online through MCU or a matching downloader; And the chip has built-in hardware SPI UART、IIC、 Various resources such as comparators can be used to customize personalized functional products for customers.

LibDriver WT588E02B is a full-featured driver of WT588E02B launched by LibDriver.It provides audio playing and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver WT588E02B source files.

/interface includes LibDriver WT588E02B SPI platform independent template.

/test includes LibDriver WT588E02B driver test code and this code can test the chip necessary function simply.

/example includes LibDriver WT588E02B sample code.

/doc includes LibDriver WT588E02B offline document.

/datasheet includes WT588E02B datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_wt588e02b_basic.h"

uint8_t res;
uint8_t list[2];

/* basic init */
res = wt588e02b_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* play */
res = wt588e02b_basic_play(0);
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

...
    
/* play list */
list[0] = 5;
list[1] = 6;
res = wt588e02b_basic_play_list(list, 2);
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

...
    
/* play loop */
res = wt588e02b_basic_play_loop(0);
if (res != 0)
{
    (void)wt588e02b_basic_deinit();

    return 1;
}

...
    
/* play loop advance */
res = wt588e02b_basic_play_loop_advance(1);
if (res != 0)
{
    (void)wt588e02b_basic_deinit();

    return 1;
}

...
    
/* play loop all */
res = wt588e02b_basic_play_loop_all();
if (res != 0)
{
    (void)wt588e02b_basic_deinit();

    return 1;
}

...
    
/* stop */
res = wt588e02b_basic_stop();
if (res != 0)
{
    (void)wt588e02b_basic_deinit();

    return 1;
}

...

/* update */
res = wt588e02b_basic_update(0, "0:single.t3z");
if (res != 0)
{
    (void)wt588e02b_basic_deinit();

    return 1;
}

...
    
/* update all */
res = wt588e02b_basic_update_all("0:all.bin");
if (res != 0)
{
    (void)wt588e02b_basic_deinit();

    return 1;
}

...

/* deinit */
(void)wt588e02b_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/wt588e02b/index.html](https://www.libdriver.com/docs/wt588e02b/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.