
#include <stddef.h>  
#include <stdlib.h>   
#include <string.h>
#include "cards_management.h"

/* Global variables */
Deck* remaining_cards = NULL;               /* remaining cards to draw */
Deck* discard_cards = NULL;                 /* discarded cards */
Card current_card;                          /* last played card on the table */
Player players[PLAYERS_NUM];                /* array of players */                      

int main (void)
{
    int result; 
    int length;
    result = initialize_cards();
    length = get_remaining_pile_length();
    if ((0 == result) && (length == MAX_CARDS_NUM)) {
        printf("initialize_cards......successful!\n");
    }

    initialize_players();

    result += deal_cards();
    length = get_remaining_pile_length();
    if ((0 == result) 
        && (length == (MAX_CARDS_NUM - DEAL_CARDS_NUM * PLAYERS_NUM))
        && (players[0].length == DEAL_CARDS_NUM) 
        && (players[1].length == DEAL_CARDS_NUM)) {
        printf("deal_cards......successful!\n");
    }

    return result;
}

/**
 * @brief Initialize all the cards status and put them in remaining_pile iteratively.
 *        Memeory will be allocated to store all the cards informations.
 *        If it can't malloc at any point, we will free the deck and return FAIL.
 *        initialize discard_cards pointor to be NULL, which indicates no discard cards.
 * @return int  0 - Initialization is successful;
 *             != 0 - Initialization is failed, since malloc memory fails
 */
int initialize_cards(void)
{
    int i, j;
    Card card;
    int result = 0;

    for (i = RED; i <= YELLOW; i++) {
        for (j = ZERO; j <= NINE; j++) {
            card.color = i;
            card.name = j;
            result += insert_card(card);
        }
    }
    
    discard_cards = NULL;
    return result;
}

/**
 * @brief All the cards are managed in a linked list. 
 *        This function is used to insert a new card to the head of the link. 
 * 
 * @param card The specific card which is inserted.
 * @return int   0 - Inserting is successful;
 *               1 - Inserting card is failed, since malloc memory fails.
 */
int insert_card(const Card card) 
{
    Deck* cards_link = (Deck*)malloc(sizeof(Deck));
    if (cards_link == NULL) {
        printf("Fail to malloc memory when insert the card.\n");
        return MALLOC_FAIL;
    }

    memcpy(&cards_link->card, &card, sizeof(Card));

    cards_link->next = remaining_cards;
    remaining_cards = cards_link;

    return SUCCESS;
}

/**
 * @brief  Gets the first card from the linked list, and make the next to first link as first.
 * 
 * @return const Deck* pointer which points to the deleted card
 */
const Deck *get_card_from_remaining_pile(void)
{
    Deck* temp_deck = remaining_cards;
    remaining_cards = remaining_cards->next; 
    return temp_deck;  
}

/**
 * @brief Checks the if there is still have available cads in the remianing pile.
 * 
 * @return true  remaining pile is empty
 * @return false remaining pile is not empty
 */
bool is_remaining_pile_empty() 
{
    return remaining_cards == NULL;
}

/**
 * @brief Get the remaining pile length 
 * 
 * @return int the length of the remaining pile, 
 *         which means how many cards are available in the remaining pile.
 */
int get_remaining_pile_length(void)
{
    int length = 0;
    Deck* temp_pile = remaining_cards;

    while (temp_pile != NULL){
        temp_pile = temp_pile->next;
        length++;
    }

    return length;
}

/**
 * @brief Determins the card is playable or not by comparing the card with current card
 *        If the color or the name is same, then it's playable
 * @param card The card which needs to be checked is playable or not
 * @return true The card is playable
 * @return false The card is not playable
 */
bool is_playable_card(Card card)
{
    bool result = false;

    if ((card.color == current_card.color) || (card.name == current_card.name)) {
        result = true;
    }

    return result;
}

/**
 * @brief Initialize players global variables
 * 
 */
void initialize_players(void)
{
    for (int i = 0; i < PLAYERS_NUM; i++) {
        players[i].type = (PlayerType)i;
        players[i].length = 0;
        players[i].cards_on_hand = NULL;
    }
}

/**
 * @brief Deals each player 5 cards at the start of the game setup
 *        Use current_position and next player to deal card to players in order
 * 
 * @return int   0 - Inserting is successful;
 *               1 - Inserting card is failed, since malloc memory fails.
 */
int deal_cards(void)
{   
    int i, j;
    const Deck* dealt_card;
    
    for (i = 0; i < DEAL_CARDS_NUM; i++)
    {
        for (j = 0; j < PLAYERS_NUM; j++)
        {
            dealt_card = get_card_from_remaining_pile();
            players[j].cards_on_hand = malloc(sizeof(Deck));
            if (players[j].cards_on_hand == NULL) {
                printf("Fail to malloc memory when insert the card.\n");
                return MALLOC_FAIL;
            }

            memcpy(&players[j].cards_on_hand->card, &dealt_card->card, sizeof(Card));
            players[j].cards_on_hand->next = NULL;
            players[j].length++;
        }
    }

    return SUCCESS;
}