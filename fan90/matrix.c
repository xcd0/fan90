
// https://docs.qmk.fm/#/custom_matrix
// https://github.com/qmk/qmk_firmware/blob/ece14278efe5168ef20298984bff4b1d5eb43e4b/quantum/matrix_common.c#L108
// https://synapse.kyoto/glossary/74hc595/page001.html
int row_pins[] = { F6,F7,B1,B3,B2,B6 };
void SR_CLEAR(){ writePinLow(D6); writePinHigh(D6); }
void SR_CLOCK(){ writePinHigh(D7); writePinLow(D7); }
void SR_RCLOCK(){ writePinHigh(D8); writePinLow(D8); }

void matrix_init_custom(void) {
	// TODO: initialize hardware here

	// initialize matrix state: all keys off
	for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
		raw_matrix[i] = 0;
		matrix[i]     = 0;
	}

	debounce_init(MATRIX_ROWS);

	matrix_init_quantum();
	
	//setPinInputHigh(pin); // Set pin as input with builtin pull-up resistor
	//setPinOutput(pin); // Set pin as output
	//writePinHigh(pin); // Set pin level as high, assuming it is an output
	//writePinLow(pin); // Set pin level as low, assuming it is an output
	//readPin(pin); // Returns the level of the pin

	int input[7] = {D4,B6,B2,B3,B1,F7,F6};
	int output[5] = {D5,D6,D7,D8,D9};

	for(int i = 1; i <= 7; i++){
		setPinInputHigh(i); // Set pin as input with builtin pull-up resistor
	}
	for(int i = 1; i <= 5; i++){
		setPinOutput(i); // Set pin as output
	}

	// シフトレジスタの設定
	SR_CLEAR();
	writePinHigh(D8); // RCLK
	
	
	//writePinHigh(pin); // Set pin level as high, assuming it is an output
	//writePinLow(pin); // Set pin level as low, assuming it is an output
}
static void read_row( matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];
changed |= read_cols_on_row(raw_matrix, current_row);


}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
	bool matrix_has_changed = false;

	// TODO: add matrix scanning routine here

	//writePinHigh(pin); // Set pin level as high, assuming it is an output
	//writePinLow(pin); // Set pin level as low, assuming it is an output
	//readPin(pin); // Returns the level of the pin

	return matrix_has_changed;
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t last_row_value = current_matrix[current_row];
    current_matrix[current_row] = 0;

    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        pin_t pin = direct_pins[current_row][col_index];
        if (pin != NO_PIN) {
            current_matrix[current_row] |= readPin(pin) ? 0 : (MATRIX_ROW_SHIFTER << col_index);
        }
    }

    return (last_row_value != current_matrix[current_row]);
}
static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    matrix_io_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    // Unselect col
    unselect_col(current_col);

    return matrix_changed;
}

/*
 * pro micro pin
 * | pin | name       | use            | io  |
 * | --- | ---        | ---            | --- |
 * | 1   | TX0/D3     | -              | -   |
 * | 2   | RX1/D2     | -              | -   |
 * | 3   | GND        | GND            | -   |
 * | 4   | GND        | GND            | -   |
 * | 5   | D2/        | -              | -   |
 * | 6   | D3/        | -              | -   |
 * | 7   | D4/        | software reset | i   |
 * | 8   | D5/        | SER            | o   |
 * | 9   | D6/        | SCK            | o   |
 * | 10  | D7/        | SCL            | o   |
 * | 11  | D8/        | RCK            | o   |
 * | 12  | D9/        | OE             | o   |
 * | 13  | B6/10/D10  | row05          | i   |
 * | 14  | B2/16/MOSI | row04          | i   |
 * | 15  | B3/14/MISO | row03          | i   |
 * | 16  | B1/15/SCK  | row02          | i   |
 * | 17  | F7/A0      | row01          | i   |
 * | 18  | F6/A1      | row00          | i   |
 * | 19  | F5/A2      | -              | -   |
 * | 20  | F4/A3      | -              | -   |
 * | 21  | VCC        | VCC            | -   |
 * | 22  | RESET      | hardware reset | i   |
 * | 23  | GND        | GND            | -   |
 * | 24  | VCC        | -              | -   |
 *
 *
 *
 */


/*
 *https://docs.qmk.fm/#/custom_matrix

matrix_row_t matrix_get_row(uint8_t row) {
    // TODO: return the requested row data
}

void matrix_print(void) {
    // TODO: use print() to dump the current matrix state to console
}

void matrix_init(void) {
    // TODO: initialize hardware and global matrix state here

    // Unless hardware debouncing - Init the configured debounce routine
    debounce_init(MATRIX_ROWS);

    // This *must* be called for correct keyboard behavior
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    bool matrix_has_changed = false;

    // TODO: add matrix scanning routine here

    // Unless hardware debouncing - use the configured debounce routine
    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    // This *must* be called for correct keyboard behavior
    matrix_scan_quantum();

    return matrix_has_changed;
}

また、次のコールバックのデフォルトも提供します。

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

*/
#include "matrix.h"
#include "debounce.h"
#include "wait.h"
#include "print.h"
#include "debug.h"

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 30
#endif

/* matrix state(1:on, 0:off) */
matrix_row_t raw_matrix[MATRIX_ROWS];
matrix_row_t matrix[MATRIX_ROWS];

#ifdef MATRIX_MASKED
extern const matrix_row_t matrix_mask[];
#endif

// user-defined overridable functions

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

// helper functions

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) {
    // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
    // switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}

// Deprecated.
bool matrix_is_modified(void) {
    if (debounce_active()) return false;
    return true;
}

#if (MATRIX_COLS <= 8)
#    define print_matrix_header() print("\nr/c 01234567\n")
#    define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))
#    define matrix_bitpop(row) bitpop(matrix_get_row(row))
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse16(matrix_get_row(row))
#    define matrix_bitpop(row) bitpop16(matrix_get_row(row))
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse32(matrix_get_row(row))
#    define matrix_bitpop(row) bitpop32(matrix_get_row(row))
#endif

void matrix_print(void) {
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row);
        print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += matrix_bitpop(i);
    }
    return count;
}

__attribute__((weak)) void matrix_io_delay(void) { wait_us(MATRIX_IO_DELAY); }

// CUSTOM MATRIX 'LITE'
__attribute__((weak)) void matrix_init_custom(void) {}

__attribute__((weak)) bool matrix_scan_custom(matrix_row_t current_matrix[]) { return true; }

__attribute__((weak)) void matrix_init(void) {
    matrix_init_custom();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

__attribute__((weak)) uint8_t matrix_scan(void) {
    bool changed = matrix_scan_custom(raw_matrix);

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();
    return changed;
}
