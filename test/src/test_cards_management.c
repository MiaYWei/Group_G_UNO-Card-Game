#include "../../src/cards_management.h"

int main(void)
{
    int result = 0;

    printf("--------------- Start the Test ---------------\n");
    //result = test_initialize_cards();
    //result += test_deal_cards();
    //result += test_sort_cards_on_hand();
    result += test_discard_card();
    //result += test_draw_cards();
    return result;
}

/*#################################### Test Functions ####################################*/
int test_initialize_cards(void);
int test_deal_cards(void);
int test_sort_cards_on_hand(void);
void test_discard_card(int test_case);
int test_draw_cards(void);

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
        && (length == (MAX_CARDS_NUM - DEAL_CARDS_NUM * PLAYERS_NUM))
        && (g_players[0].count == DEAL_CARDS_NUM)
        && (g_players[1].count == DEAL_CARDS_NUM)) {
        printf("deal_cards......successful!\n");
    }

    printf(" Human Player Cards List: ");
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);
    printf("\n Computer Player Cards List:");
    display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);

    return result;
}

int test_sort_cards_on_hand(void)
{
    int result;
    g_card_on_table.color = RED;
    g_card_on_table.name = FIVE;

    result = sort_cards_on_hand(HUMAN);
    result += sort_cards_on_hand(COMPUTER);

    printf("\n\n-------Sorts on hand cards-------");
    printf("\n The last card on the table: (%d, %d) \n", g_card_on_table.color, g_card_on_table.name);
    printf("\n Human Player Cards List: ");
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);
    printf("\n Computer Player Cards List: ");
    display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);

    return result;
}

void no_card_discarded(void)
{
    g_card_on_table.color = RED;
    g_card_on_table.name = EIGHT;
    g_player_on_turn = HUMAN;
}

void card_discarded_from_one_hand_list(void)
{
    g_card_on_table.color = RED;
    g_card_on_table.name = NINE;
    g_player_on_turn = HUMAN;
}

void test_discard_card(int test_case)
{
    int discard_post_condition = -1;

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
    printf(" Player on turn is %d. (HUMAN_PLAYER = 0; COMPUTER_PLAYER = 1)\n", g_player_on_turn);
    printf(" The card on table: (%d, %d) \n", g_card_on_table.color, g_card_on_table.name);
    printf(" HUMAN_PLAYER Cards List: ");
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);
    printf(" COMPUTER_PLAYER Cards List: ");
    display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);

    printf("\nAfter Discarding Card: \n");
    if (0 == discard_card(HUMAN, &discard_post_condition)) {
        printf("  HUMAN_PLAYER discard cards successful with post condition of %d. \n", discard_post_condition);
    }
    else {
        printf("  HUMAN_PLAYER discard cards failed with post condition of %d. \n", discard_post_condition);
    }
    printf("  HUMAN_PLAYER Cards List: ");
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);

    if (0 == discard_card(COMPUTER, &discard_post_condition)) {
        printf("\n  COMPUTER_PLAYER discards card successful with post condition of %d. \n", discard_post_condition);
    }
    else {
        printf("\n  COMPUTER_PLAYER discards card failed with post condition of %d. \n", discard_post_condition);
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
    printf("\nThe last card on the table: (%d, %d) \n", g_card_on_table.color, g_card_on_table.name);
    printf("Then sort card.......");
    result += sort_cards_on_hand(HUMAN);
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);

    return result;
}
