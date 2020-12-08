#define _CRT_SECURE_NO_WARNINGS
#include "../../src/cards_management.h"
#include "../../src/game.h"
#include "test.h"

void test_initialize_cards(void);
void test_deal_cards(void);

/*#################################### Test Functions ####################################*/
void test_cards_mgmt(void)
{
    write_log("--------------- Start Card Management Module Test ---------------\n");
    test_initialize_cards();
    test_deal_cards();

    return;
}

void test_initialize_cards(void)
{
    int result = initialize_cards();
    int length = get_pile_length(g_draw_pile);
    if ((0 == result) && (length == MAX_CARDS_NUM)) {
        write_log("Test --- initialize_cards()......successful!\n");
    }
    else
    {
        write_log("Test --- initialize_cards()......failed!\n");
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
        write_log("Test --- deal_cards()......successful!\n");
    }
    else
    {
        write_log("Test --- deal_cards()......failed!\n");
    }

    return;
}

