#include "../include/console_print.h"

void set_console_colour(WORD* attributes, WORD color)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, color);
}

void reset_console_colour(WORD attributes)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}

void print_warning(const char* string)
{
    WORD attributes = 0;
    set_console_colour(&attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
    printf("%s\n", string);
    reset_console_colour(attributes);
}

void print_info(const char* string)
{
    WORD attributes = 0;
    set_console_colour(&attributes, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("%s\n", string);
    reset_console_colour(attributes);
}