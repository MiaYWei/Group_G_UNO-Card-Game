#include "../include/console_print.h"

/**
 * @brief Set the console colour 
 *
 * @param attributes console screen buffer attributes info
 * @param color the expected color
 */
void set_console_colour(WORD* attributes, WORD color)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE handle_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle_stdout, &info);
    *attributes = info.wAttributes;
    SetConsoleTextAttribute(handle_stdout, color);
}

/**
 * @brief wraped print function for warning print. The color is red.
 *
 * @param string pointer to the specific string to print
 */
void print_warning(const char* string)
{
    WORD attributes = 0;
    set_console_colour(&attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
    printf("%s\n", string);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}

/**
 * @brief wraped print function for info print. The color is blue.
 *
 * @param string string pointer to the specific string to print
 */
void print_info(const char* string)
{
    WORD attributes = 0;
    set_console_colour(&attributes, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("%s\n", string);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}

/**
 * @brief wraped print function for info print. The color is blue.
 *
 * @param string string pointer to the specific string to print
 */
void print_winner(const char* string, const char* name)
{
    WORD attributes = 0;
    set_console_colour(&attributes, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    if (name == NULL){
        printf("%s\n", string);
    }
    else {
        printf("%s %s\n", string, name);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}