#ifndef __terminal_h__
#define __terminal_h__

#include "types.h"
#include "string.h"

static volatile word* const TERMINAL_BUFFER = (word *)0xB8000;
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

enum vga_color
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_GRAY = 7,
    VGA_COLOR_DARKGRAY = 8,
    VGA_COLOR_BRIGHTBLUE = 9,
    VGA_COLOR_BRIGHTGREEN = 10,
    VGA_COLOR_BRIGHTCYAN = 11,
    VGA_COLOR_BRIGHTRED = 12,
    VGA_COLOR_BRIGHTMAGENTA = 13,
    VGA_COLOR_YELLOW = 14,
    VGA_COLOR_WHITE = 15
};

size_t terminal_row;
size_t terminal_column;
byte terminal_color;

static inline byte vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline word vga_entry(unsigned char c, byte color)
{
    return (word) c | (word) color << 8;
}

static inline void terminal_clear(word entry)
{
    size_t x,y;

    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_GRAY, VGA_COLOR_BLUE);

    for (y = 0; y < VGA_HEIGHT; y++)
    {
        for (x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            TERMINAL_BUFFER[index] = entry;
        }
    }
}

static inline void terminal_put_vga_entry(word entry, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    TERMINAL_BUFFER[index] = entry;
}

static inline void terminal_scroll()
{
    size_t x,y;

    for (y = 1; y < VGA_HEIGHT; y++)
    {
        for (x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            const size_t prev_index = (y-1) * VGA_WIDTH + x;
            TERMINAL_BUFFER[prev_index] = TERMINAL_BUFFER[index];
        }
    }

    for (x = 0; x < VGA_WIDTH; x++)
    {
        const size_t index = (VGA_HEIGHT-1) * VGA_WIDTH + x;
        TERMINAL_BUFFER[index] = vga_entry(' ', terminal_color);
    }

    terminal_row--;
}

static inline void terminal_carriage_return()
{
    terminal_column = 0;
    terminal_row++;

    if (terminal_row >= VGA_HEIGHT)
        terminal_scroll();
}

static inline void terminal_put_char(unsigned char c)
{
    if (terminal_column >= VGA_WIDTH || terminal_row >= VGA_HEIGHT)
        return;

    terminal_put_vga_entry(vga_entry(c, terminal_color), terminal_column, terminal_row);
}

static inline void terminal_increment()
{
    if (terminal_column >= VGA_WIDTH)
        terminal_carriage_return();
    else
        terminal_column++;
}

static inline void terminal_write_char(unsigned char c)
{
    switch(c)
    {
        case '\n':
            terminal_carriage_return();
            break;
        default:
            terminal_put_char(c);
            terminal_increment();
            break;
    }
}

static inline void terminal_write_str(char* str)
{
    size_t len, i;
    len = strlen(str);

    for (i = 0; i < len; i++)
    {
        terminal_write_char(str[i]);
    }
}

#endif
