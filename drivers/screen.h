#include "ports.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80 
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void memory_copy(char *source, 
    char *dest, 
    int nbytes) {
    int i;
    
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}


void int_to_ascii(int n, 
    char str[]) {
    int i, sign;
    if ((sign = n) < 0) 
        n = -n;

    i = 0;

    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) 
        str[i++] = '-';

    str[i] = '\0';
}


int print_char(char c, int row, int col, char attr);


void kprint_at(char *message, 
    int row, 
    int col) {
    int offset = get_cursor_offset();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
    int i = 0;

    while (message[i] != 0) {
        offset = print_char(message[i++], row, col, WHITE_ON_BLACK);

        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}


int get_offset(int col, int row) { return 2 * (row * MAX_ROWS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }

// If 'col' and 'row' are negative, we will print at current cursor location
// Returns the offset of the next character
// Sets the video cursor to the returned offset
int print_char(char c, 
    int row, 
    int col, 
    char attr) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    int offset;

    if (col >= 0 && row >= 0) 
        offset = get_offset(col, row);
    else 
        offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            memory_copy(get_offset(0, i) + VIDEO_ADDRESS,
                        get_offset(0, i-1) + VIDEO_ADDRESS,
                        MAX_COLS * 2);

        /* Blank last line */
        char *last_line = get_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS;

        for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);

    return offset;
}


int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    return offset * 2; /* Position * size of character cell */
}


void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}


void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    char *screen = VIDEO_ADDRESS;

    for (int i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }

    set_cursor_offset(get_offset(0, 0));
}
