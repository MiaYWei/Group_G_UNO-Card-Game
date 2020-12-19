#include <stdlib.h>
#include "../../include/cards_management.h"
#include "../../include/computer_player.h"
#include "../include/test.h"
#include "../include/test_game.h"
#include "../include/test_cards_management.h"
void test_computer_take_turn(void);

void test_computer_player(void)
{
    write_log("\n--------------- Start Test: Computer Player Module  ---------------\n");
    test_computer_take_turn();
    write_log("--------------- End of Test: Computer Player Module ---------------\n");
    return;
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
    struct CARD card1 = { RED, ONE }, card2 = { RED, FIVE }, card3 = { GREEN, FIVE }, card4 = { ACTION, WILD }, card5 = { GREEN, TWO }, card6 = { YELLOW, FOUR }, card7 = { RED, NINE }, card8 = { RED, SKIP }, card9 = {GREEN, DRAW_ONE};
    struct CARD testCard1 = { BLUE, SIX }, testCard2 = { GREEN , SEVEN }, testCard3 = { BLUE, FIVE }, testCard4 = { BLUE, ONE }, testCard5 = { GREEN, FOUR }, testWILD = { BLUE, WILD }, testDRAW = { BLUE, DRAW_ONE };

    /* define hand card list */
    struct DECK* hand_card_list = NULL, * played = NULL;
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
    int expected_ret, actual_ret = 0;
    if (initialize_game()) {
        write_log("Test --- computer_take_turn()......Initialize game failed! \n");
    }
    g_players[COMPUTER].cards_on_hand = build_test_list_for_computer();


    // function - test find_most_color
    actual_ret = test_find_most_color(&g_players[COMPUTER].cards_on_hand);
    expected_ret = 1;
    if (actual_ret == expected_ret) {
        write_log("Test-- - find_most_color().find the color with the most occurence......Successful!\n");;
    }
    else {
        write_log("Test-- - find_most_color().find the color with the most occurence......failed!\n");
        write_fail_log("The return value of find_most_color: %s  %s\n", actual_ret, "expected_ret");
    }

    // function - test ifexists
    Card_t card = { RED, ONE };
    actual_ret = test_ifexists(&g_players[COMPUTER].cards_on_hand, card, 1);
    expected_ret = 1;
    if (expected_ret == actual_ret) {
        write_log("Test-- - ifexsits.find if a card is existed in the list......Successful!\n");
    }
    else {
        write_log("Test-- - ifexsits.find if a card is existed in the list......failed!\n");
        write_fail_log("The return value of ifexists():\n", actual_ret, expected_ret);
    }


    // function - test find_largest_number
    actual_ret = test_find_largest_number(&g_players[COMPUTER].cards_on_hand, RED, NINE);
    expected_ret = 1;
    if (expected_ret == actual_ret) {
        write_log("Test-- - find_largest_number().find the largest number of a color in the list......Successful!\n");
    }
    else {
        write_log("Test-- - find_largest_number().find the largest number of a color in the list......failed!\n");
        write_fail_log("The return value of find_largest_number():\n", actual_ret, expected_ret);
    }


    // function - test find_occurence_of_number
    actual_ret = test_find_occurence_of_number(&g_players[COMPUTER].cards_on_hand, FIVE, 2);
    expected_ret = 1;
    if (expected_ret == actual_ret) {
        write_log("Test-- - find_largest_number().find the occurence of a number  in the list......Successful!\n");
    }
    else {
        write_log("Test-- - find_largest_number.()find the largest number of a color in the list......failed!\n");
        write_fail_log("The return value of find_largest_number():\n", actual_ret, expected_ret);
    }


    // function - test find_occurence_of_color
    expected_ret = 1;
    actual_ret = test_find_occurence_of_color(&g_players[COMPUTER].cards_on_hand, RED, 4);
    if (actual_ret == expected_ret) {
        write_log("Test-- - find_occurence_of_color().find the count of a color in the list......Successful!\n");
    }
    else {
        write_log("Test-- - find_occurence_of_color.find the count of a clolr in the list......failed!\n");
        write_fail_log("The return value of find_occurence_of_color():\n", actual_ret, expected_ret);
    }



    // function - test find_color_with_most_occurence
    expected_ret = 1;
    actual_ret = test_find_color_with_most_occurence(&g_players[COMPUTER].cards_on_hand, FIVE, RED);
    if (actual_ret == expected_ret) {
        write_log("Test-- - find_color_with_most_occurence.if multiple color have same number(). find the color with most occurence......Successful!\n");
    }
    else {
        write_log("Test-- - find_color_with_most_occurence.if multiple color have same number. find the color with most occurence......failed!\n");
        write_fail_log("The return value of find_color_with_most_occurence():\n", actual_ret, expected_ret);
    }

    //function - pick case CASE1
    expected_ret = 1;
     Card_t testCard1 = { BLUE, SIX };
    actual_ret = test_pick_case(&g_players[COMPUTER].cards_on_hand, testCard1, CASE1);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_case(). CASE1 No matched color and No matched number......Successful!\n");
    }
    else {
        write_log("Test-- - pick_case(). CASE1 No matched color and No matched number......failed!\n");
        write_fail_log("The return value of pick_case().CASE1:\n", actual_ret, expected_ret);
    }

    //function - pick case CASE2
    expected_ret = 1;
    Card_t testCard2 = { GREEN , SEVEN };
    actual_ret = test_pick_case(&g_players[COMPUTER].cards_on_hand, testCard2, CASE2);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_case(). CASE2 matched color and No matched number......Successful!\n");
    }
    else {
        write_log("Test-- - pick_case(). CASE2 matched color and No matched number......failed!\n");
        write_fail_log("The return value of pick_case().CASE2:\n", actual_ret, expected_ret);
    }

    //function - pick case CASE3
    expected_ret = 1;
    Card_t  testCard3 = { BLUE, FIVE };
    actual_ret = test_pick_case(&g_players[COMPUTER].cards_on_hand, testCard3, CASE3);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_case(). CASE3 NO matched color and matched number......Successful!\n");
    }
    else {
        write_log("Test-- - pick_case(). CASE3 NO matched color and matched number......failed!\n");
        write_fail_log("The return value of pick_case().CASE3:\n", actual_ret, expected_ret);
    }


    //function - pick case CASE4
    expected_ret = 1;
    Card_t  testCard5 = {  GREEN, FOUR };
    actual_ret = test_pick_case(&g_players[COMPUTER].cards_on_hand, testCard5, CASE4);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_case(). CASE4  matched color and matched number......Successful!\n");
    }
    else {
        write_log("Test-- - pick_case(). CASE4  matched color and matched number......failed!\n");
        write_fail_log("The return value of pick_case().CASE4:\n", actual_ret, expected_ret);
    }

    //function - pick card CASE1
    expected_ret = 1;
    Card_t  expectCard = { RED, WILD };
    actual_ret = test_pick_card(&g_players[COMPUTER].cards_on_hand, testCard1, expectCard);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_card(). CASE1  Play wild if there is no playable card......Successful!\n");
    }
    else {
        write_log("Test-- -  pick_card(). CASE1  Play wild if there is no playable card......failed!\n");
        write_fail_log("The return value of pick_card().CASE1:\n", actual_ret, expected_ret);
    }

    //function - pick card CASE1-1
    expected_ret = 1;
    //pop wild from list
    Card_t WILDCard = { ACTION, WILD };
    play_card(find_address(&g_players[COMPUTER].cards_on_hand, WILDCard), &g_players[COMPUTER].cards_on_hand);
    Card_t NULLcard = { INVALID_COLOR, INVALID_NAME };
    actual_ret = test_pick_card(&g_players[COMPUTER].cards_on_hand, testCard1, NULLcard);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_card(). CASE1-1  Play nothing there is no playable card and wild card......Successful!\n");
    }
    else {
        write_log("Test-- -  pick_card(). CASE1-1  Play nothing there is no playable card and wild card......failed!\n");
        write_fail_log("The return value of pick_card(). CASE 1-1:\n", actual_ret, expected_ret);
    }

    //function - pick card CASE2
    expected_ret = 1;
    Card_t expectCard2 = { GREEN, DRAW_ONE };
    actual_ret = test_pick_card(&g_players[COMPUTER].cards_on_hand, testCard2, expectCard2);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_card(). CASE2  Play matched action card if matched color > 2 ......Successful!\n");
    }
    else {
        write_log("Test-- -  pick_card(). CASE2  Play matched action card if matched color > 2......failed!\n");
        write_fail_log("The return value of pick_card(). CASE 2:\n", actual_ret, expected_ret);
    }


    //function - pick card CASE2-1
    expected_ret = 1;
    display_cards_list(g_players[COMPUTER].cards_on_hand);
    Card_t testCard6 = { YELLOW, THREE }; 
    Card_t expectCard3 = { YELLOW, FOUR };
    actual_ret = test_pick_card(&g_players[COMPUTER].cards_on_hand, testCard6, expectCard3);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_card(). CASE2-1  Play matched card with largest number if matched color < 2 ......Successful!\n");
    }
    else {
        write_log("Test-- -  pick_card(). CASE2-1 Play matched card with largest number if matched color < 2......failed!\n");
        write_fail_log("The return value of pick_card(). CASE 2-1:\n", actual_ret, expected_ret);
    }


    //function - pick card CASE3
    expected_ret = 1;
    display_cards_list(g_players[COMPUTER].cards_on_hand);
    Card_t testCard7 = { BLUE, FIVE };
    Card_t expectCard4 = { RED, FIVE };
    actual_ret = test_pick_card(&g_players[COMPUTER].cards_on_hand, testCard7, expectCard4);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_card(). CASE3 Play color you have the most with that number......Successful!\n");
    }
    else {
        write_log("Test-- -  pick_card(). CASE3 Play the number with most color you have with that number......failed!\n");
        write_fail_log("The return value of pick_card(). CASE 3:\n", actual_ret, expected_ret);
    }

    //function - pick card CASE4
    expected_ret = 1;
    display_cards_list(g_players[COMPUTER].cards_on_hand);
    Card_t testCard8 = { RED, FOUR };
    Card_t expectCard5 = { RED, NINE };
    actual_ret = test_pick_card(&g_players[COMPUTER].cards_on_hand, testCard8, expectCard5);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_card(). CASE4 play if input color = most_color......Successful!\n");
    }
    else {
        write_log("Test-- -  pick_card(). CASE4 play if input color = most_color......failed!\n");
        write_fail_log("The return value of pick_card(). CASE 4:\n", actual_ret, expected_ret);
    }

    //function - pick card CASE4
    expected_ret = 1;
    display_cards_list(g_players[COMPUTER].cards_on_hand);
    Card_t testCard9 = { YELLOW, FIVE };
    Card_t expectCard6 = { RED, FIVE };
    actual_ret = test_pick_card(&g_players[COMPUTER].cards_on_hand, testCard9, expectCard6);
    if (actual_ret == expected_ret) {
        write_log("Test-- - pick_card(). CASE4-1 find and play the most color with that number if input color! = most_color......Successful!\n");
    }
    else {
        write_log("Test-- -  pick_card(). CASE4-1 find and play the most color with that number if input color! = most_color......failed!\n");
        write_fail_log("The return value of pick_card(). CASE 4-1:\n", actual_ret, expected_ret);
    }


    //function computer_take_turn Case 1: no playable card to discard, end of turn, game continues.
    g_card_on_table.color = BLUE;
    g_card_on_table.name = EIGHT;
    g_player_on_turn = COMPUTER;

    expected_ret = 1;
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    g_draw_pile = create_test_list(YELLOW, FIVE, NINE);
    actual_ret = computer_take_turn();
    if (expected_ret == actual_ret) {
        write_log("Test-- - computer_take_turn().Case 1:No Playable Card Discarded, End Turn, Game Continues......Successful!\n");
    }
    else {
        write_log("Test-- - computer_take_turn().Case 1:No Playable Card Discarded, End Turn, Game Continues......failed!\n");
        write_fail_log("The return value of computer_take_turn():\n", actual_ret, expected_ret);
    }

    
    // function computer_take_turn Case 2: Computer: discard cards successful
    g_card_on_table.color = RED;
    g_card_on_table.name = TWO;
    g_player_on_turn = COMPUTER;

    expected_ret = 0;
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    actual_ret = computer_take_turn();
    if (expected_ret == actual_ret) {
        write_log("Test-- - computer_take_turn().Case 2:Playable Card Discarded, End Turn......Successful!\n");
    } 
    else {
        write_log("Test-- - computer_take_turn().Case 2:Playable Card Discarded, End Turn......failed!\n");
        write_fail_log("The return value of computer_take_turn():\n", actual_ret, expected_ret);
    }

    // function computer_take_turn Case 3: Not Computer Turn.
    g_player_on_turn = HUMAN;
    expected_ret = 2;
    actual_ret = computer_take_turn();
    if (expected_ret == actual_ret) {
        write_log("Test-- - computer_take_turn().Case 3:Invalid Player......Successful!\n");
    }
    else {
        write_log("Test-- - computer_take_turn().Case 3:Invalid Player......failed!\n");
        write_fail_log("The return value of computer_take_turn():\n", actual_ret, expected_ret);
    }

    return;
}





/*********************** test functions ********************************/
int test_find_most_color(Deck_t* head) {
    CardColor_e color = find_most_color(&head);

    if (color == RED) {
        return 1;
    }
    return 0;
}

int test_pick_case(Deck_t** head, Card_t card, casenumber_e expected) {
    casenumber_e result = pick_case(card, head);
    
    if (result == expected) {
        return 1;
    }
    return 0;
}

int test_ifexists(Deck_t** head, Card_t card, int n) {
    int result;
    result = ifexists(head, card.name, card.color);
    if (result == n) {
        return 1;
    }
    return 0;
}

int test_find_largest_number(Deck_t** handcard, CardColor_e color, CardName_e name) {
    CardName_e Max = find_largest_number(handcard, color);
    if (Max == name) {
        return 1;
    }
    return 0;
}

int test_find_occurence_of_number(Deck_t** handcard, CardName_e inputCardNumber, int n) {
    int occurence = 0;
    occurence = find_occurence_of_number(handcard, inputCardNumber);
    if (occurence == n) {
        return 1;
    }
    return 0;
}

int test_find_occurence_of_color(Deck_t** handcard, CardColor_e inputCardColor, int n) {
    int occurence = 0;
    occurence = find_occurence_of_color(handcard, inputCardColor);
    if (occurence == n) {
        return 1;
    }
    return 0;
}

int test_find_color_with_most_occurence(Deck_t** handcard, CardName_e inputCardNumber, CardColor_e Final_color) {
    CardColor_e color;
    color = find_color_with_most_occurence(handcard, inputCardNumber);
    if (color == Final_color) {
        return 1;
    }
    return 0;
}

int test_pick_card(Deck_t** handcard, Card_t inputCard, Card_t expectCard) {
    Deck_t* result = pick_card(inputCard, handcard);
    

    if (result == NULL) {
        if (expectCard.color == INVALID_COLOR) {

            return 1;
        }
    }
    else if (result->card.name == expectCard.name && result->card.color == expectCard.color) {
        return 1;
    }
    else {
    };
    return 0;

}
