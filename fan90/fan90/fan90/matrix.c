#include "matrix.h"
#include "debounce.h"
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "quantum.h"

/* pro micro pin
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
*/
// https://docs.qmk.fm/#/custom_matrix
// https://github.com/qmk/qmk_firmware/blob/ece14278efe5168ef20298984bff4b1d5eb43e4b/quantum/matrix_common.c#L108
// https://synapse.kyoto/glossary/74hc595/page001.html


static int row_pins[] = { F6,F7,B1,B3,B2,B6 };
static bool readRowPin(int rowNum ){ return readPin(row_pins[rowNum]); }
static void GPIO_DELAY(void){
	// GPIOでシフトレジスタを制御する際に各信号間で遅延を入れたい場合ここに入れる // delayMicroseconds( 10 ); // <- 使えるか知らない
	_delay_us(10);
}

static void SR_SER_HIGH(void){ writePinHigh(C6); GPIO_DELAY(); }                // C6 SER
static void SR_SER_LOW(void){ writePinLow(C6); GPIO_DELAY(); }                  // C6 SER
static void SR_CLEAR(void){ writePinLow(E6); GPIO_DELAY(); writePinHigh(E6); GPIO_DELAY();}  // E6 CLR
static void SR_CLOCK(void){ writePinLow(D7); GPIO_DELAY(); writePinHigh(D7); GPIO_DELAY();}  // D7 CLK
static void SR_RCLOCK(void){ writePinLow(B4); GPIO_DELAY(); writePinHigh(B4); GPIO_DELAY();} // B4 RCK
//static void SR_OE_OUTPUT_DISABLE(){ writePinHigh(D9); GPIO_DELAY(); }     // D9 OE
//static void SR_OE_OUTPOT_ENABLE(){ writePinLow(D9); GPIO_DELAY(); }     // D9 OE

static void SR_SCAN_COL_SET( int colNum ){
	SR_CLEAR(); // クリア
	uint16_t col = 1;
	col <<= colNum;
	for( uint16_t i = 0; i < MATRIX_COLS; i++ ){
		if( col & 0b1000000000000000 ){
			SR_SER_HIGH();
		} else {
			SR_SER_LOW();
		}
		SR_CLOCK();
	}
	SR_RCLOCK(); // ピンに出力
}

void matrix_init_custom(void) { // {{{
	// TODO: initialize hardware here

	//setPinInputHigh(pin); // Set pin as input with builtin pull-up resistor
	//setPinOutput(pin); // Set pin as output
	//writePinHigh(pin); // Set pin level as high, assuming it is an output
	//writePinLow(pin); // Set pin level as low, assuming it is an output
	//readPin(pin); // Returns the level of the pin

	// シフトレジスタの設定
	// ピンの入出力設定
	setPinInputHigh(D4);
	setPinInputHigh(F6);
	setPinInputHigh(F7);
	setPinInputHigh(B1);
	setPinInputHigh(B3);
	setPinInputHigh(B2);
	setPinInputHigh(B6);
	setPinOutput(C6);
	setPinOutput(D7);
	setPinOutput(E6);
	setPinOutput(B4);
	setPinOutput(B5);
	SR_CLEAR();
	SR_RCLOCK();
} // }}}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
	bool matrix_has_changed = false;
	// TODO: add matrix scanning routine here

	for (uint16_t c = 0; c < MATRIX_COLS; c++) {
		SR_SCAN_COL_SET(c); // シフトレジスタでc列だけHIGHにする
		for( uint8_t r = 0; r < MATRIX_ROWS; r++ ){
			matrix_row_t last_row_value = current_matrix[r];
			current_matrix[c] = readRowPin(r) ? 0 : (MATRIX_ROW_SHIFTER << c);
			matrix_has_changed |= (last_row_value != current_matrix[c]);
		}
	}

	return matrix_has_changed;
}

