#include "../../src/cards_management.h"
#include "../../src/game.h"

int test_initialize_cards(void);
int test_deal_cards(void);
void test_discard_card(int test_case);
int test_draw_cards(void);

int main(void)
{
    int result = 0;

    printf("--------------- Start the Test ---------------\n");
    result = test_initialize_cards();
    result += test_deal_cards();
    for (int i = 0; i < 2; i++)
    {
        test_discard_card(i);
    }
    
    result += test_draw_cards();
    return result;
}
/*#################################### Test Functions ####################################*/
int test_initialize_cards(void)
{
    int result = initialize_cards();
    int length = get_pile_length(g_draw_pile);
    if ((0 == result) && (length == MAX_CARDS_NUM)) {
        printf("initialize_cards......successful!\n");
    }

    return result;
}

int test_deal_cards(void)
{
    initialize_players();
    int result = deal_cards();
    int length = get_pile_length(g_draw_pile);
    if ((0 == result)
        && (length == (MAX_CARDS_NUM - DEAL_CARDS_NUM * PLAYERS_NUM)))
    {
        printf("deal_cards......successful!\n");
    }

    printf(" Human Player Cards List: ");
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);
    printf("\n Computer Player Cards List:");
    display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);

    return result;
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
    if (initialize_game()) {
        printf(" Initialize game failed! \n");
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

    printf("\n************* Discard Card Test %d*************\n", test_case);
    printf("Before Discarding Card: \n");
    printf(" Player on turn is %s.\n", PLAYER_TYPE_STRING[g_player_on_turn]);
    printf(" The card on table: (%s, %s) \n", CARD_COLOR_STRING[g_card_on_table.color], CARD_NAME_STRING[g_card_on_table.name]);
    printf(" COMPUTER_PLAYER Cards List: ");
    display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);

    printf("\nAfter Discarding Card: \n");
    int ret = computer_discard_card();
    if (0 == ret)
    {
        printf("  Computer: discard cards successful.\n");
    }
    else if (1 == ret)
    {
        printf("  Computer: No playable card to discard, end of turn, game continues.\n");
    }
    printf("  COMPUTER_PLAYER Cards List: ");
    display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);
}

int test_draw_cards(void)
{
    g_card_on_table.color = BLUE;
    g_card_on_table.name = NINE;

    int result;
    printf("\n------- Draw Cards-------\n");
    printf("Before......");
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);
    result = draw_cards(2, HUMAN);

    printf("After.......");
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);
    printf("\nThe last card on the table: (%s, %s) \n", CARD_COLOR_STRING[g_card_on_table.color], CARD_NAME_STRING[g_card_on_table.name]);

    return result;
}