#include <stdlib.h>
#include "../../include/game.h"
#include "../../include/computer_player.h"
#include "../include/test.h"
#include "../include/test_game.h"
#include "../include/test_cards_management.h"

void append(Deck_t** head_ref, Card_t card);
Deck_t* build_test_list_for_computer();
void test_computer_take_turn(void);
void test_find_most_color(void);
void test_find_largest_number(void);
void test_find_occurence_of_number(void);
void test_find_occurence_of_color(void);
void test_find_color_with_most_occurence(void);
void test_pick_case(void);
void test_pick_card(void);
void test_process_playable_card(void);

void test_computer_player(void)
{
    write_log("\n--------------- Start Test: Computer Player Module  ---------------\n");
    test_computer_take_turn();
    test_find_most_color();
    test_find_largest_number();
    test_find_occurence_of_number();
    test_find_occurence_of_color();
    test_find_color_with_most_occurence();
    test_pick_case();
    test_pick_card();
    test_process_playable_card();
    write_log("--------------- End of Test: Computer Player Module ---------------\n");
    return;
}

void test_find_most_color(void)
{
    g_players[COMPUTER].cards_on_hand = build_test_list_for_computer();

    CardColor_e expected_ret = RED;
    CardColor_e actual_ret = find_most_color(&g_players[COMPUTER].cards_on_hand);

    // function - test find_most_color
    if (actual_ret == expected_ret) {
        write_log("Test-- - find_most_color().find the color with the most occurence......Successful!\n");;
    }
    else {
        write_log("Test-- - find_most_color().find the color with the most occurence......failed!\n");
        write_fail_log("The return value of find_most_color: \n", actual_ret, expected_ret);
    }

    return;
}

void test_find_largest_number(void)
{
    g_players[COMPUTER].cards_on_hand = build_test_list_for_computer();

    CardName_e expected_ret = NINE;
    CardColor_e actual_ret = find_largest_number(&g_players[COMPUTER].cards_on_hand, RED);

    if (expected_ret == actual_ret) {
        write_log("Test-- - find_largest_number().find the largest number of a color in the list......Successful!\n");
    }
    else {
        write_log("Test-- - find_largest_number().find the largest number of a color in the list......failed!\n");
        write_fail_log("The return value of find_largest_number():\n", actual_ret, expected_ret);
    }
}

void test_find_occurence_of_number(void)
{
    g_players[COMPUTER].cards_on_hand = build_test_list_for_computer();

    int expected_ret = 2, actual_ret;
    actual_ret = find_occurence_of_number(&g_players[COMPUTER].cards_on_hand, FIVE);
    if (expected_ret == actual_ret) {
        write_log("Test-- - find_occurence_of_number().find the occurence of a number  in the list......Successful!\n");
    }
    else {
        write_log("Test-- - find_occurence_of_number().find the largest number of a color in the list......failed!\n");
        write_fail_log("The return value of find_occurence_of_number():\n", actual_ret, expected_ret);
    }

}

void test_find_occurence_of_color(void)
{
    g_players[COMPUTER].cards_on_hand = build_test_list_for_computer();

    int expected_ret = 4, actual_ret;
    actual_ret = find_occurence_of_color(&g_players[COMPUTER].cards_on_hand, RED);
    if (expected_ret == actual_ret) {
        write_log("Test-- - find_occurence_of_color().find the occurence of a number  in the list......Successful!\n");
    }
    else {
        write_log("Test-- - find_occurence_of_color.()find the largest number of a color in the list......failed!\n");
        write_fail_log("The return value of find_occurence_of_color():\n", actual_ret, expected_ret);
    }

}

void test_find_color_with_most_occurence(void)
{
    g_players[COMPUTER].cards_on_hand = build_test_list_for_computer();

    CardColor_e expected_ret = RED, actual_ret;
    actual_ret = find_color_with_most_occurence(&g_players[COMPUTER].cards_on_hand, FIVE);
    if (actual_ret == expected_ret) {
        write_log("Test-- - find_color_with_most_occurence.if multiple color have same number(). find the color with most occurence......Successful!\n");
    }
    else {
        write_log("Test-- - find_color_with_most_occurence.if multiple color have same number. find the color with most occurence......failed!\n");
        write_fail_log("The return value of find_color_with_most_occurence():\n", actual_ret, expected_ret);
    }

}

void test_pick_case(void) {

    g_players[COMPUTER].cards_on_hand = build_test_list_for_computer();
    casenumber_e  expected_ret, actual_ret;

    //CASE 1
    Card_t testCard1;
    testCard1.color = BLUE;
    testCard1.name = SIX; 
    expected_ret = CASE1;
    actual_ret = pick_case(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_case().CASE1 No matched color and No matched number......Successful!\n");
    }
    else {
        write_log("Test-- - pick_case().CASE1 No matched color and No matched number......failed!\n");
        write_fail_log("The return value of pick_case().CASE1:\n", actual_ret, expected_ret);
    }

    //CASE 2
    testCard1.color = GREEN ;
    testCard1.name = SEVEN;
    expected_ret = CASE2;
    actual_ret = pick_case(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_case().CASE2 matched color and No matched number......Successful!\n");
    }
    else {
        write_log("Test-- - pick_case().CASE2 matched color and No matched number......failed!\n");
        write_fail_log("The return value of pick_case().CASE2:\n", actual_ret, expected_ret);
    }

    //CASE 3
    testCard1.color = BLUE;
    testCard1.name = FIVE;
    expected_ret = CASE3;
    actual_ret = pick_case(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_case().CASE3 NO matched color and matched number......Successful!\n");
    }
    else {
        write_log("Test-- - pick_case().CASE3 NO matched color and matched number......failed!\n");
        write_fail_log("The return value of pick_case().CASE3:\n", actual_ret, expected_ret);
    }

    //CASE 4
    testCard1.color = GREEN;
    testCard1.name = FOUR;
    expected_ret = CASE4;
    actual_ret = pick_case(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_case().CASE4 matched color and matched number......Successful!\n");
    }
    else {
        write_log("Test-- - pick_case().CASE4 matched color and matched number......failed!\n");
        write_fail_log("The return value of pick_case().CASE3:\n", actual_ret, expected_ret);
    }
}

void test_pick_card(void) {

    Card_t expected_ret, testCard1;
    Deck_t* actual_ret;
    g_players[COMPUTER].cards_on_hand = build_test_list_for_computer();



    //CASE1 PLAY WILD
    expected_ret.color = RED;
    expected_ret.name = WILD;
    testCard1.color = BLUE;
    testCard1.name = SIX;
    actual_ret = pick_card(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret->card.name == expected_ret.name && actual_ret->card.color == expected_ret.color) {
        write_log("Test-- - pick_card().CASE1 Play wild if there is no playable card......Successful!\n");
    }
    else {
        write_log("Test-- -  pick_card().CASE1 Play wild if there is no playable card......failed!\n");
 
    }

    //CASE 1-1 NO WILD 
    Card_t WILDCard = { ACTION, WILD };
    //pop WILD from test list
    play_card(find_address(&g_players[COMPUTER].cards_on_hand, WILDCard), &g_players[COMPUTER].cards_on_hand);
    expected_ret.color = INVALID_COLOR;
    expected_ret.name = INVALID_NAME;
    actual_ret = pick_card(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret == NULL) {
        write_log("Test-- - pick_card().CASE1-1 Play nothing there is no playable card and no wild card......Successful!\n");
    }
    else {
        write_log("Test-- - pick_card().CASE1-1 Play nothing there is no playable card and wild card......failed!\n");
    }

    //CASE2 
    expected_ret.color = GREEN;
    expected_ret.name = DRAW_ONE;
    testCard1.color = GREEN;
    testCard1.name = SEVEN;
    actual_ret = pick_card(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret->card.name == expected_ret.name && actual_ret->card.color == expected_ret.color) {
        write_log("Test-- - pick_card().CASE2 Play matched action card if matched color > 2......Successful!\n");
    }
    else {
        write_log("Test-- - pick_card().CASE2 Play matched action card if matched color > 2......failed!\n");
    }



    //CASE3    
    expected_ret.color = RED;
    expected_ret.name = FIVE;
    testCard1.color = BLUE;
    testCard1.name = FIVE;
    actual_ret = pick_card(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret->card.name == expected_ret.name && actual_ret->card.color == expected_ret.color) {
        write_log("Test-- - pick_card().CASE3 Play color you have the most with that number......Successful!\n");
    }
    else {
        write_log("Test-- - pick_card().CASE3 Play color you have the most with that number......failed!\n");
    }
    

    //CASE4 
    expected_ret.color = RED;
    expected_ret.name = FOUR;
    testCard1.color = RED;
    testCard1.name = SKIP;
    actual_ret = pick_card(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret->card.color == expected_ret.color) {
        write_log("Test-- - pick_card().CASE4 play if input color = most_color......Successful!\n");
    }
    else {
        write_log("Test-- - pick_card().CASE4 play if input color = most_colorr......failed!\n");
    }

    //CASE4-1
    expected_ret.color = RED;
    expected_ret.name = FIVE;
    testCard1.color = YELLOW;
    testCard1.name = FIVE;
    actual_ret = pick_card(testCard1, &g_players[COMPUTER].cards_on_hand);
    if (actual_ret->card.name == expected_ret.name && actual_ret->card.color == expected_ret.color) {
        write_log("Test-- - pick_card().CASE4-1 find and play the most color with that number if input color! = most_color......Successful!\n");
    }
    else {
        write_log("Test-- - pick_card().CASE4-1 find and play the most color with that number if input color! = most_colo......failed!\n");
    }
}

void test_process_playable_card(void)
{
    Card_t test_card;
    int expected_diff, before_lenth, after_lenth, actual_diff;
    PlayerType_e expected_player, actual_player;
    g_players[COMPUTER].cards_on_hand = build_test_list_for_computer();

    //Case 1 WILD card change turn 
    test_card.color = ACTION;
    test_card.name = WILD;
    expected_player = HUMAN;
    process_playable_card(test_card);
    actual_player =  g_player_on_turn;

    if (expected_player == actual_player) {
        write_log("Test-- - process_playable_card().Drop WILD......Successful!\n");;
    }
    else {
        write_log("Test-- - process_playable_card().Drop WILD.......failed!\n");
        write_fail_log("The return value of process_playable_card().Drop WILD: %s  %s\n", actual_player, expected_player);
    }

    //Case 2:  WILD draw2 add 2 card & change turn
    test_card.color = ACTION;
    test_card.name = WILD_DRAW_TWO;
    expected_diff = 2;
    expected_player = COMPUTER;
    before_lenth = get_pile_length(g_players[HUMAN].cards_on_hand);
    process_playable_card(test_card);
    after_lenth = get_pile_length(g_players[HUMAN].cards_on_hand);
    actual_diff = after_lenth - before_lenth;
    actual_player = g_player_on_turn;
    if (actual_diff == expected_diff && expected_player == actual_player) {
        write_log("Test-- - process_playable_card().Drop WILD DRAW TWO......Successful!\n");;
    }
    else {
        write_log("Test-- - Process_playable_card().Drop WILD DRAW TWO.....failed!\n");
        write_fail_log("The return value of process_playable_card().Drop WILD: %s  %s\n", actual_diff, expected_diff);
    }



    //Case 3 SKIP change turn 
    test_card.color = YELLOW;
    test_card.name = SKIP;
    process_playable_card(test_card);
    expected_player = COMPUTER;
    actual_player = g_player_on_turn;
    if (expected_player == actual_player) {
        write_log("Test-- - process_playable_card().Drop SKIP......Successful!\n");;
    }
    else {
        write_log("Test-- - process_playable_card().Drop SKIP.......failed!\n");
        write_fail_log("The return value of process_playable_card().Drop SKIP: %s  %s\n", actual_diff, expected_diff);
    }



    //Case 4 Draw_one add 1 card & change turn:  
    test_card.color = GREEN;
    test_card.name = DRAW_ONE;
    expected_diff = 1;
    expected_player = COMPUTER;
    before_lenth = get_pile_length(g_players[HUMAN].cards_on_hand);
    process_playable_card(test_card);
    after_lenth = get_pile_length(g_players[HUMAN].cards_on_hand);
    actual_diff = after_lenth - before_lenth;
    actual_player = g_player_on_turn;
    if (actual_diff == expected_diff && expected_player == actual_player) {
        write_log("Test-- - process_playable_card().Drop DRAW ONE......Successful!\n");;
    }
    else {
        write_log("Test-- - Process_playable_card().Drop DRAW ONE.....failed!\n");
        write_fail_log("The return value of process_playable_card().Drop DRAW ONE  : %s  %s\n", actual_diff, expected_diff);
    }

}




void append(Deck_t** head_ref, Card_t card) {
    /* 1. allocate node */

    Deck_t* new_card = (Deck_t*)malloc(sizeof(Deck_t));
    struct DECK* last = *head_ref;  /* used in step 5*/

    /* 2. put in the data  */
    new_card->card.color = card.color;
    new_card->card.name = card.name;
    new_card->next = NULL;


    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = new_card;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_card;
    return;
}

Deck_t* build_test_list_for_computer() {
    /* define cards*/
    struct CARD card1 = { RED, ONE }, card2 = { RED, FIVE }, card3 = { GREEN, FIVE }, card4 = { ACTION, WILD }, card5 = { GREEN, TWO }, card6 = { YELLOW, FOUR }, card7 = { RED, NINE }, card8 = { RED, SKIP }, card9 = { GREEN, DRAW_ONE };
    /* define hand card list */
    struct DECK* hand_card_list = NULL;
    struct DECK* ptr = NULL;
    append(&hand_card_list, card1);
    append(&hand_card_list, card2);
    append(&hand_card_list, card3);
    append(&hand_card_list, card4);
    append(&hand_card_list, card5);
    append(&hand_card_list, card6);
    append(&hand_card_list, card7);
    append(&hand_card_list, card8);
    append(&hand_card_list, card9);
    display_cards_list(hand_card_list);

    return hand_card_list;
}

void test_computer_take_turn(void)
{
    if (initialize_game()) {
        write_log("Test --- computer_take_turn()......Initialize game failed! \n");
    }
     return;
}

