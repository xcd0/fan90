# fan90

* Pro Micro

  | pin | name    | use            | io  |     | pin | name  | use            | io  |
  | --- | ---     | ---            | --- | --- | --- | ---   | ---            | --- |
  | 1   | TX0/PD3 | -              | -   |     | 24  | VCC   | -              | -   |
  | 2   | RX1/PD2 | -              | -   |     | 23  | GND   | GND            | -   |
  | 3   | GND     | GND            | -   |     | 22  | RESET | hardware reset | i   |
  | 4   | GND     | GND            | -   |     | 21  | VCC   | VCC            | -   |
  | 5   | PD1     | -              | -   |     | 20  | PF4   | -              | -   |
  | 6   | PD0     | -              | -   |     | 19  | PF5   | -              | -   |
  | 7   | PD4     | software reset | i   |     | 18  | PF6   | row00          | i   |
  | 8   | PC6     | SER            | o   |     | 17  | PF7   | row01          | i   |
  | 9   | PD7     | SCK            | o   |     | 16  | PB1   | row02          | i   |
  | 10  | PE6     | SCL            | o   |     | 15  | PB3   | row03          | i   |
  | 11  | PB4     | RCK            | o   |     | 14  | PB2   | row04          | i   |
  | 12  | PB5     | OE             | o   |     | 13  | PB6   | row05          | i   |

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

