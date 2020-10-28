
#include <stddef.h>  
#include <stdlib.h>   
#include <string.h>
#include "cards_management.h"

/* Global variables */
Deck* remaining_cards = NULL;               /* remaining cards to draw */
Deck* discard_cards = NULL;                 /* discarded cards */
Card current_card;                          /* last played card on the table */

int main (void)
{
    int result; 
    result = initialize_cards();
    if (0 == result) {
        printf("initialize_cards......successful!\n");
    }
    return result;
}

/**
 * @brief Initialize all the cards status and put them in remaining_pile iteratively.
 *        Memeory will be allocated to store all the cards informations.
 *        If it can't malloc at any point, we will free the deck and return FAIL.
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
 * @brief  Deletes the first card from the linked list, and make the next to first link as first.
 * 
 * @return const Deck* pointer which points to the deleted card
 */
const Deck *delete_card(void)
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