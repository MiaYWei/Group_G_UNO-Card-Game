#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdio.h>
#include "test.h"
#include "test_cards_management.h"
#include "test_game.h"
#include "../../src/cards_management.h"

Deck_t* g_draw_pile_test = NULL;            /* Draw cards pile */
Deck_t* g_discard_pile_test = NULL;         /* discarded cards */

void init_log(void);

void main(void)
{
    init_log();
    init_test();
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

int init_test(void)
{
    int i, j;
    Card_t card;
    int result = 0;

    for (i = RED; i <= YELLOW; i++)
    {
        for (j = ZERO; j <= TWO; j++)
        {
            card.color = i;
            card.name = j;
            result += add_card_at_beginning(&g_draw_pile_test, card);
        }
    }

    g_discard_pile_test = (Deck_t*)malloc(sizeof(Deck_t));
    if (g_discard_pile_test == NULL)
    {
        printf("Unable to allocate memory to initialize discard pile.");
        return -1;
    }
    g_discard_pile_test->next = NULL;

    return result;
}