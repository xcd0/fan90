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


//static int row_pins[] = { F6,F7,B1,B3,B2,B6 };
static bool readRowPin(int pin){
	switch(pin){
		case 0: return readPin(F6);
		case 1: return readPin(F7);
		case 2: return readPin(B1);
		case 3: return readPin(B3);
		case 4: return readPin(B2);
		case 5: return readPin(B6);
	}
	return false;
}
static void GPIO_DELAY(void){
	// GPIOでシフトレジスタを制御する際に各信号間で遅延を入れたい場合ここに入れる
	_delay_us(1);
}

static void SR_SER_HIGH(void){ writePinHigh(C6); GPIO_DELAY(); }                // C6 SER
static void SR_SER_LOW(void){ writePinLow(C6); GPIO_DELAY(); }                  // C6 SER
static void SR_CLEAR(void){ writePinLow(E6); GPIO_DELAY(); writePinHigh(E6); GPIO_DELAY();}  // E6 CLR
static void SR_CLOCK(void){ writePinLow(D7); GPIO_DELAY(); writePinHigh(D7); GPIO_DELAY();}  // D7 CLK
static void SR_RCLOCK(void){ writePinLow(B4); GPIO_DELAY(); writePinHigh(B4); GPIO_DELAY();} // B4 RCK
static void SR_OE_OUTPOT_ENABLE(void){ writePinLow(B5); GPIO_DELAY(); }     // B5 OE
//static void SR_OE_OUTPUT_DISABLE(void){ writePinHigh(B5); GPIO_DELAY(); }     // B5 OE

static void SR_SET_SCAN_COL( int colNum ){
	// 負論理にしたかったけど回路のダイオードの向きが逆なので仕方かなく正論理 _(:3 」∠ )_
	// シフトレジスタの0bitから15bitまでを列に割り当てる
	// 後ろの15列から詰める必要がある

	uint16_t col = 1 << (MATRIX_COLS - colNum -1); // colNumが1なら 0b0100 0000 0000 0000 colNumが2なら 0b0010 0000 0000 0000
	for( uint16_t i = 0; i < MATRIX_COLS; i++ ){
		if( col & 0b000000000001 ){ SR_SER_HIGH(); }
		else { SR_SER_LOW(); }
		col >>= 1;
		SR_CLOCK();
	}

//	// ↑ は動きとしては ↓ と一緒のはず
//	bool col[ MATRIX_COLS ] = { false }; col[ colNum ] = true;
//	for( uint16_t i = MATRIX_COLS-1; i >= 0; i-- ){
//		if( col[i] ){ SR_SER_HIGH(); }
//		else { SR_SER_LOW(); }
//		SR_CLOCK();
//	}
	SR_RCLOCK(); // ピンに出力
}

void matrix_init_custom(void) { // {{{
	// TODO: initialize hardware here
	//
	// GPIOをいじる関数
	//setPinInputHigh(pin); // Set pin as input with builtin pull-up resistor
	//setPinOutput(pin); // Set pin as output
	//writePinHigh(pin); // Set pin level as high, assuming it is an output
	//writePinLow(pin); // Set pin level as low, assuming it is an output
	//readPin(pin); // Returns the level of the pin

	// シフトレジスタの設定
	setPinInput(D4); setPinInput(F6); setPinInput(F7); setPinInput(B1);
	setPinInput(B3); setPinInput(B2); setPinInput(B6);
	setPinOutput(C6); setPinOutput(D7); setPinOutput(E6); setPinOutput(B4); setPinOutput(B5);
	SR_CLEAR(); SR_RCLOCK(); SR_OE_OUTPOT_ENABLE();
} // }}}

bool matrix_scan_custom(matrix_row_t current_matrix_row[]) {
	bool matrix_has_changed = false;
	// TODO: add matrix scanning routine here
	//
	// matrix_row_t型は一列にある行の最大数が収まる8bit、16bit、32bitのunsigned int型っぽい
	// どうもデータ形式がmatrix_row_t型の配列になっているっぽい
	//
	// * 列を設定してから行を読み取る
	// * 1行が1つの整数型に収まる感じでn列目はmatrix_row_t型の (n - MATRIX_COLS) bit目になる
	// * fan90ではシフトレジスタを使っており、キースキャンを独自に実装する必要がある
	for (uint16_t c = 0; c < MATRIX_COLS; c++) {
		SR_SET_SCAN_COL(c);                                  // シフトレジスタでc列だけHIGHにする 正論理
		for( uint8_t r = 0; r < MATRIX_ROWS; r++ ){          // c列のr行目を読み取る
			matrix_row_t last_row_value = current_matrix_row[r]; // 直前のc列r行目の状態を保存
			//current_matrix_row[r] |= readRowPin(r) ? 0 : (MATRIX_ROW_SHIFTER << c); // 負論理
			current_matrix_row[r] |= readRowPin(r) ? (MATRIX_ROW_SHIFTER << c) : 0; // 正論理
			matrix_has_changed |= (last_row_value != current_matrix_row[r]);
		}
		//GPIO_DELAY();
	}
	return matrix_has_changed;
}

