#include <stdlib.h>
#include "../../include/game.h"
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

void test_computer_take_turn(void)
{
    int expected_ret, actual_ret = 0;
    if (initialize_game()) {
        write_log("Test --- computer_take_turn()......Initialize game failed! \n");
    }

    // Case 1: No playable card to discard, end of turn, game continues.
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
    
    // Case 2: Computer: discard cards successful
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

    // Case 3: Not Computer Turn.
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

#if 0
/*********************** test functions ********************************/
int test_find_most_color(Deck_t* head) {
    CardColor_e color = find_most_color(&head);

    if (color == RED) {
        return 1;
    }
    return 0;
}

int test_pick_case(Deck_t** head, Card_t card, int n) {
    int CaseNumber;

    CaseNumber = pick_case(card, head);
    if (CaseNumber == n) {
        return 1;
    }
    return 0;
}

int test_find_largest_number(Deck_t** handcard, CardColor_e color, CardName_e name) {
    CardName_e Max;
    Max = find_largest_number(handcard, color);
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



int main()
{

    /* define cards*/
    struct CARD card1 = { RED, ONE }, card2 = { RED, FIVE }, card3 = { GREEN, FIVE }, card4 = { BLACK, WILD }, card5 = { GREEN, TWO }, card6 = { YELLOW, FOUR }, card7 = { RED, NINE };
    struct CARD testCard1 = { BLUE, SIX }, testCard2 = { GREEN , SEVEN }, testCard3 = { BLUE, FIVE }, testCard4 = { BLUE, ONE }, testCard5 = { GREEN, FOUR }, testWILD = { BLUE, WILD }, testDRAW = { BLUE, DRAWONE };

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
    display_cards_list(hand_card_list);
    /* ptr = find_address(&hand_card_list, card4);
     printf("card is (%s,%s) \n", CARD_COLOR_STRING[ptr->card.color], CARD_NAME_STRING[ptr->card.name]);
     played = play_card(ptr, &hand_card_list);
     played->card.color = RED;
     printf("card is (%s,%s) \n", CARD_COLOR_STRING[ptr->card.color], CARD_NAME_STRING[ptr->card.name]);
     display_cards_list(hand_card_list);*/

     /*rintf("\n\n");
     printf("****************** function test *******************\n");
     if (test_find_most_color(&hand_card_list)) {
         printf("find_most_color Passed !\n");
     }

     if (test_pick_case(&hand_card_list, testCard1, CASE1)) {
         printf("pick_case CASE 1 Passed ! \n");
     }
     if (test_pick_case(&hand_card_list, testCard2, CASE2)) {
         printf("pick_case CASE 2 Passed ! \n");
     }
     if (test_pick_case(&hand_card_list, testCard3, CASE3)) {
         printf("pick_case CASE 3 Passed ! \n");
     }
     if (test_pick_case(&hand_card_list, testCard5, CASE4)) {
         printf("pick_case CASE 4 Passed ! \n");
     }

     if (test_find_largest_number(&hand_card_list, RED, EIGHT)) {
         printf("find_largest_number TEST1 Passed ! \n");
     }
     if (test_find_largest_number(&hand_card_list, GREEN, FIVE)) {
         printf("find_largest_number TEST2 Passed ! \n");
     }

     if (test_find_occurence_of_number(&hand_card_list, FIVE, 2)) {
         printf("find_occurence_of_number Passed ! \n");
     }

     if (test_find_occurence_of_color(&hand_card_list, RED, 3)) {
         printf("find_occurence_of_color Passed ! \n");
     }

     if (test_find_color_with_most_occurence(&hand_card_list, FIVE, RED)) {
         printf("find_color_with_most_occurence Passed ! \n");
     }

     initialize_cards();*/
    printf("\n\n");
    printf("****************** Pick_action test *******************\n");
    /* PASSED
    printf("CASE 1: NO MATCH COLOR/NUMBER && WILD > 1 \n");
    display_cards_list(hand_card_list);
    printf("DRAW WILD \n");

    played = play_card(pick_card(testCard1, &hand_card_list), &hand_card_list);
    printf("card is (%s,%s) \n", CARD_COLOR_STRING[played->card.color], CARD_NAME_STRING[played->card.name]);
    display_cards_list(hand_card_list); */

    //PASSED
    //printf("CASE 1: NO MATCH COLOR/NUMBER && WILD <= 1 \n");
    //display_cards_list(hand_card_list);
    //play_card(pick_card(testWILD, &hand_card_list), &hand_card_list);
    //display_cards_list(hand_card_list);

    //PASSED
    //printf("\n\n");
    //printf("CASE 2: MATCH COLOR, no matche number \n");
    //display_cards_list(hand_card_list);
    //printf("input Card [GREEN , 7], play [GREEN, 5] \n");
    //play_card(pick_card(testCard2, &hand_card_list), &hand_card_list);
    //display_cards_list(hand_card_list);

    //PASSED
    //printf("\n\n");
    //printf("CASE 3: No MATCH COLOR, match number \n");
    //display_cards_list(hand_card_list);
    //printf("input Card [BLUE, 5], play [GREEN, 5] \n");
    //play_card(pick_card(testCard3, &hand_card_list), &hand_card_list);
    //display_cards_list(hand_card_list);

    //PASSED
    //printf("\n\n");
    //printf("CASE 4:   MATCH COLOR, MATCH NUMBER  \n");
    //display_cards_list(hand_card_list);
    //printf("input Card [GREEN,4], play [YELLOW, 4] \n");
    //play_card(pick_card(testCard5, &hand_card_list), &hand_card_list);
    //display_cards_list(hand_card_list);
}

#endif
