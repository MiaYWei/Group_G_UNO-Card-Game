#define _CRT_SECURE_NO_WARNINGS
#include "../../src/cards_management.h"
#include "../../src/game.h"

void test_initialize_cards(void);
void test_deal_cards(void);
void test_discard_card(int test_case);
void init_log(void);
void write_log(const char* string);

int main(void)
{
    init_log();
    write_log("--------------- Start the Test ---------------\n", 0);
    test_initialize_cards();
    test_deal_cards();
    for (int i = 0; i < 2; i++)
    {
        test_discard_card(i);
    }
    
    return 0;
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

void write_log(const char*string)
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

/*#################################### Test Functions ####################################*/
void test_initialize_cards(void)
{
    int result = initialize_cards();
    int length = get_pile_length(g_draw_pile);
    if ((0 == result) && (length == MAX_CARDS_NUM)) {
        write_log("Test initialize_cards()......successful!\n");
    }
    else
    {
        write_log("Test initialize_cards()......failed!\n");
    }

    return;
}

void test_deal_cards(void)
{
    initialize_players();
    int result = deal_cards();
    int length = get_pile_length(g_draw_pile);
    if ((0 == result)
        && (length == (MAX_CARDS_NUM - DEAL_CARDS_NUM * PLAYERS_NUM)))
    {
        write_log("Test deal_cards()......successful!\n");
    }
    else
    {
        write_log("Test deal_cards()......failed!\n");
    }

    return;
}

void no_card_discarded(void)
{
    g_card_on_table.color = RED;
    g_card_on_table.name = EIGHT;
    g_player_on_turn = COMPUTER;
}

void card_discarded_from_one_hand_list(void)
{
    g_card_on_table.color = RED;
    g_card_on_table.name = NINE;
    g_player_on_turn = COMPUTER;
}

void test_discard_card(int test_case)
{
    if (initialize_game()) 
    {
        write_log(" Initialize game failed! \n");
    }

    switch (test_case)
    {
        case (1):
            no_card_discarded();
            break;
        case (2):
            card_discarded_from_one_hand_list();
            break;
        default:
            break;
    }

    write_log("\n************* Discard Card Test *************\n");
    printf("Before Discarding Card: \n");
    printf(" Player on turn is %s.\n", PLAYER_TYPE_STRING[g_player_on_turn]);
    printf(" The card on table: (%s, %s) \n", CARD_COLOR_STRING[g_card_on_table.color], CARD_NAME_STRING[g_card_on_table.name]);
    printf(" COMPUTER_PLAYER Cards List: ");
    display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);

    printf("\nAfter Discarding Card: \n");
    int ret = computer_take_turn();
    if (0 == ret)
    {
        write_log("  Computer: discard cards successful.\n");
    }
    else if (1 == ret)
    {
        write_log("  Computer: No playable card to discard, end of turn, game continues.\n");
    }
    printf("  COMPUTER_PLAYER Cards List: ");
    display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);
}