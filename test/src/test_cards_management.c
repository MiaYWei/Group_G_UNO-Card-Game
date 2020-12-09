#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "../../include/cards_management.h"
#include "../../include/game.h"
#include "../include/test.h"

void test_initialize_cards(void);
void test_deal_cards(void);
void test_remove_cards(void);

/*#################################### Test Functions ####################################*/
void test_cards_mgmt(void)
{
    write_log("--------------- Start Card Management Module Test ---------------\n");
    test_initialize_cards();
    test_deal_cards();
    test_remove_cards();

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

Deck_t* create_list(void)
{
    int i,j = 0;
    Deck_t* newNode, * temp;

    Deck_t* head = (Deck_t*)malloc(sizeof(Deck_t));
    if (head == NULL) {      /* If unable to allocate memory for head node*/
        printf("Unable to allocate memory.");
        return NULL;
    }

    //printf("Enter the data of node 1: ");
    //scanf("%d", &data);
    head->card.color = RED;    // Link data field with data
    head->card.name = ZERO;
    head->next = NULL;        // Link address field to NULL
    temp = head;

    /* Create n nodes and adds to linked list */
    for (j = 1; j <= NINE; j++)
    {
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

    for (i = BLUE; i <= BLUE; i++)
    {
        for (j = ZERO; j <= NINE; j++)
        {
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
    
    printf("Linked List Created Successfully.\n");
    return head;
}

void test_remove_cards(void)
{
    Card_t card_1 = {RED, 0};
    Deck_t* pile_test = create_list();
    int result = 0;

    display_cards_list(pile_test);
    remove_card_from_deck(&pile_test, card_1);
    display_cards_list(pile_test);

    Card_t card_2 = {RED, 2};
    remove_card_from_deck(&pile_test, card_2);
    display_cards_list(pile_test);
}

        

