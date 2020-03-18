# fan90


* Pro Micro

| ピン | 名前       | 説明           | io  |
| ---  | ---        | ---            | --- |
| 1    | TX0/D3     | -              | -   |
| 2    | RX1/D2     | -              | -   |
| 3    | GND        | GND            | -   |
| 4    | GND        | GND            | -   |
| 5    | D2/        | -              | -   |
| 6    | D3/        | -              | -   |
| 7    | D4/        | software reset | i   |
| 8    | D5/        | SER            | o   |
| 9    | D6/        | SCK            | o   |
| 10   | D7/        | SCL            | o   |
| 11   | D8/        | RCK            | o   |
| 12   | D9/        | OE             | o   |
| 13   | B6/10/D10  | row05          | i   |
| 14   | B2/16/MOSI | row04          | i   |
| 15   | B3/14/MISO | row03          | i   |
| 16   | B1/15/SCK  | row02          | i   |
| 17   | F7/A0      | row01          | i   |
| 18   | F6/A1      | row00          | i   |
| 19   | F5/A2      | -              | -   |
| 20   | F4/A3      | -              | -   |
| 21   | VCC        | VCC            | -   |
| 22   | RESET      | hardware reset | i   |
| 23   | GND        | GND            | -   |
| 24   | VCC        | -              | -   |


* SN74HC595N

| ピン    | 名前       | 入出力 | 説明                                         |
| ---     | ---        | ---    | ---                                          |
| 8       | GND        | -–     | グラウンド                                   |
| 10      | SRCLR      | 入力   | シフトレジスタのクリア                       |
| 11      | SRCLK      | 入力   | シフトレジスタのクロック信号                 |
| 12      | RCLK       | 入力   | ストレージレジスタのクロック信号             |
| 13      | OE         | 入力   | 出力の有効化                                 |
| 14      | SER        | 入力   | シリアル入力                                 |
| 16      | Vcc        | -      | –電源                                        |
| 15,1〜7 | QA、QB〜QH | 出力   | パラレル出力                                 |
| 9       | QH’        | 出力   | シフトレジスタの最上位ビットの状態を常に出力 |

##

![fan90](imgur.com image replace me!)

A short description of the keyboard/project

* Keyboard Maintainer: [xcd0](https://github.com/yourusername)
* Hardware Supported: The PCBs, controllers supported
* Hardware Availability: Links to where you can find this hardware

Make example for this keyboard (after setting up your build environment):

    make fan90:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
