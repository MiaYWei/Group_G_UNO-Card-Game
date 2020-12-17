#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "../../include/cards_management.h"
#include "../../include/game.h"
#include "../include/test.h"

void test_initialize_cards(void);
void test_deal_cards(void);
void test_add_card_at_end(void);
void test_add_card_at_beginning(void);
void test_remove_card_from_deck(void);
void test_remove_first_card_from_deck(void);
void test_is_playable_card(void);

/*#################################### Test Functions ####################################*/
void test_cards_mgmt(void)
{
    write_log("--------------- Start Cards Management Module Test ---------------\n");
    test_initialize_cards();
    test_deal_cards();
    test_add_card_at_end();
    test_add_card_at_beginning();
    test_remove_card_from_deck();
    test_remove_first_card_from_deck();
    test_is_playable_card();

    return;
}

Deck_t* create_test_list(CardColor_e color, CardName_e name_from, CardName_e name_to)
{
    int i = 0;
    Deck_t* newNode, * temp;

    Deck_t* head = (Deck_t*)malloc(sizeof(Deck_t));
    if (head == NULL) {      /* If unable to allocate memory for head node*/
        printf("Unable to allocate memory.");
        return NULL;
    }
    head->card.color = color;    // Link data field with data
    head->card.name = ZERO;
    head->next = NULL;           // Link address field to NULL
    temp = head;

    /* Create n nodes and adds to linked list */
    for (i = name_from; i <= name_to; i++)
    {
        newNode = (Deck_t*)malloc(sizeof(Deck_t));
        if (newNode == NULL) { /* If memory is not allocated for newNode */
            printf("Unable to allocate memory.");
            break;
        }

        newNode->card.color = color;    // Link data field of newNode with data
        newNode->card.name = i;
        newNode->next = NULL; // Link address field of newNode with NULL

        temp->next = newNode; // Link previous node i.e. temp to the newNode
        temp = temp->next;
    }

    return head;
}

Deck_t* create_list_test(void)
{
    int i, j = 0;
    Deck_t* newNode, * temp;
    Deck_t* head = (Deck_t*)malloc(sizeof(Deck_t));
    if (head == NULL) {    
        printf("Unable to allocate memory.");
        return NULL;
    }

    head->card.color = RED;    // Link data field with data
    head->card.name = ZERO;
    head->next = NULL;        // Link address field to NULL
    temp = head;

    /* Create n nodes and adds to linked list */
    for (j = 1; j <= NINE; j++) {
        newNode = (Deck_t*)malloc(sizeof(Deck_t));
        if (newNode == NULL) { /* If memory is not allocated for newNode */
            printf("Unable to allocate memory.");
            break;
        }
        //printf("Enter the data of node %d: ", i);
        //scanf("%d", &data);
        newNode->card.color = RED;    // Link data field of newNode with data
        newNode->card.name = j;
        newNode->next = NULL; // Link address field of newNode with NULL

        temp->next = newNode; // Link previous node i.e. temp to the newNode
        temp = temp->next;
    }

    for (i = BLUE; i <= YELLOW; i++) {
        for (j = ZERO; j <= NINE; j++) {
            newNode = (Deck_t*)malloc(sizeof(Deck_t));
            if (newNode == NULL) { /* If memory is not allocated for newNode */
                printf("Unable to allocate memory.");
                break;
            }

            newNode->card.color = i;    // Link data field of newNode with data
            newNode->card.name = j;
            newNode->next = NULL; // Link address field of newNode with NULL

            temp->next = newNode; // Link previous node i.e. temp to the newNode
            temp = temp->next;
        }
    }
    return head;
}

void test_initialize_cards(void)
{
    int expected_ret = 0;
    int expected_length = MAX_CARDS_NUM;
    int actual_ret = initialize_cards();
    int actual_length = get_pile_length(g_draw_pile);
    if ((actual_ret == expected_ret) && (actual_length == expected_length)) {
        write_log("Test --- initialize_cards()......successful!\n");
    }
    else {
        write_log("Test --- initialize_cards()......failed!\n");
        write_fail_log("The return of initialize_cards():\n", actual_ret, expected_ret);
        write_fail_log("After initializing the cards, the draw pile length:\n", actual_length, expected_length);
    }
    return;
}

void test_deal_cards(void)
{
    int expected_ret = 0;
    int expected_length = MAX_CARDS_NUM - DEAL_CARDS_NUM * PLAYERS_NUM;

    initialize_players();
    int actual_ret = deal_cards();
    int actual_length = get_pile_length(g_draw_pile);
    if ((actual_ret == expected_ret) && (actual_length == expected_length)) {
        write_log("Test --- deal_cards()......successful!\n");
    }
    else {
        write_log("Test --- deal_cards()......failed!\n");
        write_fail_log("The return of deal_cards():\n", actual_ret, expected_ret);
        write_fail_log("After dealing cards, the draw pile length:\n", actual_length, expected_length);
    }

    return;
}

void test_add_card_at_end(void)
{
    Card_t new_card = { GREEN, SEVEN };
    Deck_t* pile_test = create_list_test();
    int pre_length = get_pile_length(pile_test);
    add_card_at_end(pile_test, new_card);
    int length = get_pile_length(pile_test);

    if (1 == (length - pre_length)) {
        write_log("Test --- add_card_at_end()......successful!\n");
    }
    else {
        write_log("Test --- add_card_at_end()......failed!\n");
    }

    return;
}

void test_add_card_at_beginning(void)
{
    Card_t new_card = { GREEN, SEVEN };
    Deck_t* pile_test = create_list_test();
    int pre_length = get_pile_length(pile_test);
    add_card_at_beginning(&pile_test, new_card);
    int length = get_pile_length(pile_test);
    const Deck_t* card_removed = remove_first_card_from_deck(&pile_test);

    if ((1 == (length - pre_length)) && (card_removed->card.color == new_card.color) && (card_removed->card.name == new_card.name)) {
        write_log("Test --- add_card_at_beginning()......successful!\n");
    }
    else {
        write_log("Test --- add_card_at_beginning()......failed!\n");
    }

    return;
}

void test_remove_card_from_deck(void)
{
    Deck_t* pile_test = create_list_test();
    bool card_exist_actual = true;
    //case 1: Remove the card at the beginning of the list
    Card_t card_1 = { RED, ZERO };
    remove_card_from_deck(&pile_test, card_1);
    card_exist_actual = is_exist_card(pile_test, card_1);

    if (card_exist_actual == false) {
        write_log("Test --- remove_card_from_deck().Case 1:Remove Card at Beginning of List......successful!\n");
    }
    else {
        write_log("Test --- remove_card_from_deck().Case 1:Remove Card at Beginning of List......failed!\n");
        write_fail_log("After removing card from deck, check if the card is still existing in the deck:\n", card_exist_actual, false);
    }

    //case 2: Remove the card in the middile of the list
    Card_t card_2 = { RED, TWO };
    remove_card_from_deck(&pile_test, card_2);
    card_exist_actual = is_exist_card(pile_test, card_2);

    if (card_exist_actual == false) {
        write_log("Test --- remove_card_from_deck().Case 2:Remove Card in Middle of List......successful!\n");
    }
    else {
        write_log("Test --- remove_card_from_deck().Case 2:Remove Card in Middle of List......failed!\n");
        write_fail_log("After removing card from deck, check if the card is still existing in the deck:\n", card_exist_actual, false);
    }

    //case 3: Remove the card at end of the list
    Card_t card_3 = { YELLOW, NINE };
    remove_card_from_deck(&pile_test, card_3);
    card_exist_actual = is_exist_card(pile_test, card_3);

    if (card_exist_actual == false) {
        write_log("Test --- remove_card_from_deck().Case 3:Remove Card at End of List......successful!\n");
    }
    else {
        write_log("Test --- remove_card_from_deck().Case 3:Remove Card at End of List......failed!\n");
        write_fail_log("After removing card from deck, check if the card is still existing in the deck:\n", card_exist_actual, false);
    }

    return;
}

void test_remove_first_card_from_deck(void)
{
    const Deck_t* card_removed;
    Deck_t* pile_test = NULL;

    // Case 1: Empty list
    card_removed = remove_first_card_from_deck(&pile_test);
    if (card_removed == NULL) {
        write_log("Test --- remove_first_card_from_deck().Case 1:Empty List......successful!\n");
    } 
    else {
        write_log("Test --- remove_first_card_from_deck().Case 1:Empty List......failed!\n");
        write_fail_log("After removing the first card from deck, the expected removed card color:\n", card_removed->card.color, INVALID_COLOR);
        write_fail_log("After removing the first card from deck, the expected removed card name:\n", card_removed->card.name, INVALID_NAME);
    }

    // Case 2: Not empty list
    Card_t expected_card = { RED, ZERO };
    bool expected_ret = false;
    pile_test = create_list_test();
    card_removed = remove_first_card_from_deck(&pile_test);
    bool card_exist_actual = is_exist_card(pile_test, expected_card);
    if ((card_exist_actual == expected_ret) && (card_removed->card.color == expected_card.color) && (card_removed->card.name == expected_card.name)) {
        write_log("Test --- remove_first_card_from_deck().Case 2:Not Empty List......successful!\n");
    } 
    else {
        write_log("Test --- remove_first_card_from_deck().Case 2:Not Empty List......failed!\n");
        write_log(" After removing the first card from deck: \n");
        write_fail_log("  check if the card is still existing in the deck:\n", card_exist_actual, false);
        write_fail_log("  the expected removed card color:\n", card_removed->card.color, expected_card.color);
        write_fail_log("  the expected removed card name:\n", card_removed->card.name, expected_card.name);
    }

    return;
}

void test_is_playable_card(void)
{
    //Case 1: Playable
    bool expected_return = true;
    g_card_on_table.color = YELLOW;
    g_card_on_table.name = FIVE;

    Card_t test_card = { RED, FIVE };
    bool actual_return = is_playable_card(test_card);

    if (actual_return == expected_return) {
        write_log("Test --- test_is_playable_card().Case 1:Playable Card......successful!\n");
    }
    else {
        write_log("Test --- test_is_playable_card().Case 1:Playable Card......failed!\n");
        write_fail_log("The return value of is_playable_card():\n", actual_return, expected_return);
    }


    //Case 2: Not-Playable
    expected_return = false;
    g_card_on_table.color = YELLOW;
    g_card_on_table.name = FIVE;

    test_card.name = ZERO;
    actual_return = is_playable_card(test_card);

    if (actual_return == expected_return) {
        write_log("Test --- test_is_playable_card().Case 2:Not Playable Card......successful!\n");
    }
    else {
        write_log("Test --- test_is_playable_card().Case 2:Not Playable Card......failed!\n");
        write_fail_log("The return value of is_playable_card():\n", actual_return, expected_return);
    }
    
    return;
}