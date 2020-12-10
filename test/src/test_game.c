#include <stdlib.h>
#include "../../include/cards_management.h"
#include "../../include/game.h"
#include "../include/test.h"
#include "../include/test_game.h"

void test_computer_take_turn(void);

void test_game(void)
{
    write_log("\n--------------- Start Game Module Test ---------------\n");
    test_computer_take_turn();
    
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

void test_computer_take_turn(void)
{
    int expected_ret = 0;
    if (initialize_game()) {
        write_log("Test --- computer_take_turn()......Initialize game failed! \n");
    }

    // No playable card to discard, end of turn, game continues.
    g_card_on_table.color = BLUE;
    g_card_on_table.name = EIGHT;
    g_player_on_turn = COMPUTER;

    expected_ret = 1;
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    g_draw_pile = create_test_list(YELLOW, FIVE, NINE);
    if (expected_ret == computer_take_turn()) {
        write_log("Test-- - computer_take_turn().Case 1......Successful!\n");
    } 
    else {
        write_log("Test-- - computer_take_turn().Case 1......failed!\n");
    }
    
    // Computer: discard cards successful
    g_card_on_table.color = RED;
    g_card_on_table.name = TWO;
    g_player_on_turn = COMPUTER;

    expected_ret = 0;
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    if (expected_ret == computer_take_turn()) {
        write_log("Test-- - computer_take_turn().Case 2......Successful!\n");
    } 
    else {
        write_log("Test-- - computer_take_turn().Case 2......failed!\n");
    }

    // Not Computer Turn.
    g_player_on_turn = HUMAN;
    expected_ret = 2;
    if (expected_ret == computer_take_turn()) {
        write_log("Test-- - computer_take_turn().Case 3......Successful!\n");
    }
    else {
        write_log("Test-- - computer_take_turn().Case 3......failed!\n");
    }

    return;
}


