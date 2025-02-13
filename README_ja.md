[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WT588E02B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/wt588e02b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

WT588E02B-8Sは、深セン衛創智音電子有限公司が開発した16ビットDSP音声チップです。32MHzの内部発振と16ビットPWMデコードを備えています。強力な機能により、WT588E02B-8Sは音声チップ業界のリーダーとなっています。現在、WT588E02B-8Sは、より高音質で最大170秒の音声コンテンツを保存できます（顧客が音質を要求しない場合は、最大320秒の音声コンテンツを保存できます）。WT588E02B-8Sは従来のOTPチップとは異なり、その最大のブレークスルーは、顧客がMCUまたは対応するダウンローダーを介してチップの内部音声コンテンツをオンラインで置き換えることができることです。また、チップにはハードウェアSPI UART、IIC、コンパレータなどのさまざまなリソースが組み込まれており、顧客向けにパーソナライズされた機能製品をカスタマイズできます。

LibDriver WT588E02B は、LibDriver がリリースした WT588E02B のフル機能ドライバーです。オーディオ再生などの機能を提供します。LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver WT588E02Bのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver WT588E02B用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver WT588E02Bドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver WT588E02Bプログラミング例が含まれています。

/ docディレクトリには、LibDriver WT588E02Bオフラインドキュメントが含まれています。

/ datasheetディレクトリには、WT588E02Bデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/wt588e02b/index.html](https://www.libdriver.com/docs/wt588e02b/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。