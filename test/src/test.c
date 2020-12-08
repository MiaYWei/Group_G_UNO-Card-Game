#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdio.h>
#include "test.h"
#include "test_cards_management.h"
#include "test_game.h"

void init_log(void);

void main(void)
{
    init_log();

    test_cards_mgmt();
    test_game();
	
	return;
}

void init_log(void)
{
    FILE* output_file;
    char* output_file_name = ".\\test_log.txt";
    output_file = fopen(output_file_name, "w");
    if (output_file != NULL)
    {
        fclose(output_file);
    }
    else
    {
        printf("Can't open the log file.\n");
    }

    return;
}

void write_log(const char* string)
{
    FILE* output_file;
    char* output_file_name = ".\\test_log.txt";
    output_file = fopen(output_file_name, "a");
    if (output_file != NULL)
    {
        //fprintf(output_file, "this is a test %d\n", integer);
        fprintf(output_file, string);
        fclose(output_file);
    }
    else
    {
        printf("Can't open the log file.\n");
    }

    return;
}