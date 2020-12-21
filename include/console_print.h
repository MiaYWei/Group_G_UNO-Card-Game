#ifndef __CONSOLE_PRINT_HEADER__
#define __CONSOLE_PRINT_HEADER__

#include <windows.h>
#include <stdio.h>

void print_warning(const char* string);
void print_info(const char* string);
void print_winner(const char* string, const char* name);

#endif //__CONSOLE_PRINT_HEADER__