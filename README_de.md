[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver WT588E02B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/wt588e02b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

WT588E02B-8S ist ein 16-Bit-DSP-Sprachchip, der von Shenzhen Weichuang Zhiyin Electronics Co., Ltd. entwickelt wurde. Er verfügt über eine interne Schwingung von 32 MHz und 16-Bit-PWM-Dekodierung. Die leistungsstarken Funktionen machen WT588E02B-8S zu einem Marktführer in der Sprachchipbranche. Derzeit kann WT588E02B-8S bis zu 170 Sekunden Sprachinhalte mit höherer Tonqualität speichern (wenn der Kunde keine Anforderungen an die Tonqualität hat, kann er bis zu 320 Sekunden Sprachinhalte speichern). WT588E02B-8S unterscheidet sich von herkömmlichen OTP-Chips und sein größter Durchbruch besteht darin, dass Kunden die internen Sprachinhalte des Chips online über MCU oder einen passenden Downloader ersetzen können. Außerdem verfügt der Chip über integrierte Hardware SPI UART, IIC und verschiedene Ressourcen wie Komparatoren, mit denen personalisierte Funktionsprodukte für Kunden angepasst werden können.

LibDriver WT588E02B ist der voll funktionsfähige Treiber von WT588E02B, der von LibDriver veröffentlicht wurde. Er bietet Audiowiedergabe und andere Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver WT588E02B-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver WT588E02B SPI.

/test enthält den Testcode des LibDriver WT588E02B-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver WT588E02B-Beispielcode.

/doc enthält das LibDriver WT588E02B-Offlinedokument.

/Datenblatt enthält WT588E02B-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/wt588e02b/index.html](https://www.libdriver.com/docs/wt588e02b/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.