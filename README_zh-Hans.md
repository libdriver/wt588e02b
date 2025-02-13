[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WT588E02B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/wt588e02b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

WT588E02B-8S 是深圳唯创知音电子有限公司最新研发的一款16 位DSP 语音芯片、内部振荡32Mhz，16 位的PWM 解码。强大功能让WT588E02B-8S 成为语音芯片行业中的佼佼者。目前WT588E02B-8S，较高音质最大可以支持存放170 秒语音内容（若客户对音质没有要求，最大可以存放320 秒的语音内容）。WT588E02B-8S 区别于传统OTP 芯片，最大的突破是客户可以自己通过MCU 或配套下载器实现在线更换芯片内部语音内容；并且芯片内置硬件SPI、UART、IIC、比较器等各类资源，可以为客户定制各种不同的个性化功能产品。

LibDriver WT588E02B 是LibDriver推出的WT588E02B的全功能驱动，该驱动提供语音播放等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver WT588E02B的源文件。

/interface目录包含了LibDriver WT588E02B与平台无关的SPI总线模板。

/test目录包含了LibDriver WT588E02B驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver WT588E02B编程范例。

/doc目录包含了LibDriver WT588E02B离线文档。

/datasheet目录包含了WT588E02B数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SPI总线模板，完成指定平台的SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/wt588e02b/index.html](https://www.libdriver.com/docs/wt588e02b/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。