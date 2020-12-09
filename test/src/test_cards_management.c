#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "../../include/cards_management.h"
#include "../../include/game.h"
#include "../include/test.h"

void test_initialize_cards(void);
void test_deal_cards(void);
void test_remove_card_from_deck(void);
void test_remove_first_card_from_deck(void);

/*#################################### Test Functions ####################################*/
void test_cards_mgmt(void)
{
    write_log("--------------- Start Cards Management Module Test ---------------\n");
    test_initialize_cards();
    test_deal_cards();
    test_remove_card_from_deck();
    test_remove_first_card_from_deck();
    return;
}

void test_initialize_cards(void)
{
    int result = initialize_cards();
    int length = get_pile_length(g_draw_pile);
    if ((0 == result) && (length == MAX_CARDS_NUM)) {
        write_log("Test --- initialize_cards()......successful!\n");
    } else {
        write_log("Test --- initialize_cards()......failed!\n");
    }
    return;
}

void test_deal_cards(void)
{
    initialize_players();
    int result = deal_cards();
    int length = get_pile_length(g_draw_pile);
    if ((0 == result) && (length == (MAX_CARDS_NUM - DEAL_CARDS_NUM * PLAYERS_NUM))){
        write_log("Test --- deal_cards()......successful!\n");
    } else {
        write_log("Test --- deal_cards()......failed!\n");
    }

    return;
}

Deck_t* create_list_test(void)
{
    int i,j = 0;
    Deck_t* newNode, * temp;

    Deck_t* head = (Deck_t*)malloc(sizeof(Deck_t));
    if (head == NULL) {      /* If unable to allocate memory for head node*/
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
    
    printf("Test List Created Successfully.\n");
    return head;
}

void test_remove_card_from_deck(void)
{
    Deck_t* pile_test = create_list_test();
    bool card_1_exist, card_2_exist, card_3_exist = true;

    //Remove the card at the beginning of the list
    Card_t card_1 = {RED, ZERO};
    remove_card_from_deck(&pile_test, card_1);

    //Remove the card in the middile of the list
    Card_t card_2 = {RED, TWO};
    remove_card_from_deck(&pile_test, card_2);

    //Remove the card at end of the list
    Card_t card_3 = {YELLOW, NINE};
    remove_card_from_deck(&pile_test, card_3);

    card_1_exist = is_exist_card(pile_test, card_1);
    card_2_exist = is_exist_card(pile_test, card_2);
    card_3_exist = is_exist_card(pile_test, card_3);

    //case 1: Remove the card at the beginning of the list
    if (!is_exist_card(pile_test, card_1)) {
        write_log("Test --- remove_card_from_deck().Case 1......successful!\n");
    } else {
        write_log("Test --- remove_card_from_deck().Case 1......failed!\n");
    }

    //case 2: Remove the card in the middile of the list
    if (!is_exist_card(pile_test, card_2)) {
        write_log("Test --- remove_card_from_deck().Case 2......successful!\n");
    } else {
        write_log("Test --- remove_card_from_deck().Case 2......failed!\n");
    }

    //case 3: Remove the card at end of the list
    if (!is_exist_card(pile_test, card_3)) {
        write_log("Test --- remove_card_from_deck().Case 3......successful!\n");
    } else {
        write_log("Test --- remove_card_from_deck().Case 3......failed!\n");
    }

    return;
}

void test_remove_first_card_from_deck(void)
{
    Card_t card = {RED, ZERO};
    Deck_t* pile_test = create_list_test();
    remove_first_card_from_deck(&pile_test);
    if (!is_exist_card(pile_test, card)) {
        write_log("Test --- remove_first_card_from_deck().Case 1......successful!\n");
    } else {
        write_log("Test --- remove_first_card_from_deck().Case 1......failed!\n");
    }
}

