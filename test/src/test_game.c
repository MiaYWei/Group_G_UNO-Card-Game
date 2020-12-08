#include "../../src/cards_management.h"
#include "test.h"
#include "test_game.h"

void test_game(void)
{
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


