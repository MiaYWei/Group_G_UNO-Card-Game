
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
    int result = 0; 

    printf("--------------- Start the Game ---------------\n");
    result = test_initialize_cards();
    result += test_deal_cards();
    result += test_sort_cards_on_hand();
    return result;
}

/**
 * @brief initialize game which includes initialize cards and initialize players
 * 
 * @return int 0 - Initialization is successful;
 *             1 - Initialization is failed, since malloc memory fails
 */
int initialize_game(void)
{
    int result = initialize_cards();
    initialize_players();
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
            result += add_card_remaining_pile(card);
        }
    }
    
    discard_cards = NULL;
    return result;
}

/**
 * @brief All the cards are managed in a linked list. 
 *        This function is used to add a new card to the head of the link. 
 * 
 * @param card The specific card which is inserted.
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int add_card_remaining_pile(const Card card) 
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
 * @brief Displays the detailed card infomation from the card list 
 * 
 * @param list_ptr The pointer which points to the beginning of the cards list
 */
void display_cards_list(const Deck *list_ptr) 
{
    const Deck *temp_list_ptr;
    temp_list_ptr = list_ptr;

    printf("[ ");

    while(temp_list_ptr != NULL) {
        printf("(%d,%d) ", temp_list_ptr->card.color, temp_list_ptr->card.name);
        temp_list_ptr = temp_list_ptr->next;
    }
        
    printf(" ]");
}

/**
 * @brief Checks the if there is still have available cads in the remianing pile.
 * 
 * @return true  remaining pile is empty
 * @return false remaining pile is not empty
 */
bool is_remaining_pile_empty(void) 
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
    if ((card.color == current_card.color) || (card.name == current_card.name)) {
        return true;
    }

    return false;
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

    return;
}

/**
 * @brief Deals each player 5 cards at the start of the game setup
 * 
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int deal_cards(void)
{   
    int i, j;
    const Deck* dealt_card;
    int result = SUCCESS;
    
    for (i = 0; i < DEAL_CARDS_NUM; i++) {
        for (j = 0; j < PLAYERS_NUM; j++) {
            dealt_card = get_card_from_remaining_pile();
            result += add_card_on_hand(dealt_card->card, (PlayerType)j);
            players[j].length++;
        }
    }

    return result;
}

/**
 * @brief Adds one card to the specific player's on hand cards list
 * 
 * @param card structure type varialble, includes card name and card color information 
 * @param player enum type varialble, which indicates the specific palyer type
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int add_card_on_hand(const Card card, PlayerType player) 
{
    Deck* cards_link = (Deck*)malloc(sizeof(Deck));
    if (cards_link == NULL) {
        printf("Fail to malloc memory when insert the card.\n");
        return MALLOC_FAIL;
    }

    memcpy(&cards_link->card, &card, sizeof(Card));

    cards_link->next = players[player].cards_on_hand;
    players[player].cards_on_hand = cards_link;

    return SUCCESS;
}

/**
 * @brief Sorts the on hand cards for the specific player by
 *        placing all the playable card on the top of the player's deck.
 * 
 * @param sort_player emum type variable: The specific player needs to sort his/her on hand cards 
 * @return int SUCCESS - Successful;
 *             MALLOC_FAIL - Failed because of memory malloc fails 
 */
int sort_cards_on_hand(PlayerType sort_player)
{
    int i;
    int length = players[sort_player].length;
    int index = 0;

    /*Copy the cards from the current player's hand into array*/
    Deck* current = malloc(sizeof(Deck));
    if (current == NULL) {
        printf("Fail to malloc memory when sort the on hand cards.\n");
        return MALLOC_FAIL;
    } 
    current = players[sort_player].cards_on_hand;

    Card* sorted_cards = malloc(sizeof(Card) * length);
    if (sorted_cards == NULL) {
        printf("Fail to malloc memory when sort the on hand cards.\n");
        free (current);
        return MALLOC_FAIL;
    }

    for (i = 0; i < length; i++) 
    {
        sorted_cards[i].color = current->card.color;
        sorted_cards[i].name = current->card.name;
        current = current->next;
    }

    /* Place all the playable cards on the top of the player's deck*/
    for (i = 0; i < length; i++) {
        if (is_playable_card(sorted_cards[i])) {
            swap_cards(&sorted_cards[i], &sorted_cards[index]);
            index++;
        }
    }

    /*Copy the sorted cards to player's on hand deck*/
    current = players[sort_player].cards_on_hand;

    for (i = 0; i < length; i++) {
        current->card = sorted_cards[i];
        current = current->next;
    }

    free (current);
    free (sorted_cards);
    return SUCCESS;
}

/**
 * @brief Swaps the position of card a and card b
 *
 * @param a pointer to card a;
 * @param b pointer to card b;
 */
void swap_cards(Card* a, Card* b)
{
    Card temp = *a;
    *a = *b;
    *b = temp;
}


/*#################################### Test Functions ####################################*/
int test_initialize_cards(void)
{
    int result = initialize_cards();
    int length = get_remaining_pile_length();
    if ((0 == result) && (length == MAX_CARDS_NUM)) {
        printf("initialize_cards......successful!\n");
    }

    return result;
}

int test_deal_cards(void)
{
    initialize_players();
    int result = deal_cards();
    int length = get_remaining_pile_length();
    if ((0 == result) 
        && (length == (MAX_CARDS_NUM - DEAL_CARDS_NUM * PLAYERS_NUM))
        && (players[0].length == DEAL_CARDS_NUM) 
        && (players[1].length == DEAL_CARDS_NUM)) {
        printf("deal_cards......successful!\n");
    }

    printf(" Human Player Cards List: ");
    display_cards_list(players[HUMAN_PLAYER].cards_on_hand);
    printf("\n Computer Player Cards List:");
    display_cards_list(players[COMPUTER_PLAYER].cards_on_hand);

    return result;
}

int test_sort_cards_on_hand(void)
{   
    int result;
    current_card.color = RED;
    current_card.name = FIVE;

    result = sort_cards_on_hand(HUMAN_PLAYER);
    result += sort_cards_on_hand(COMPUTER_PLAYER);

    printf("\n\n-------After sorting on hand cards-------");
    printf("\n The last card on the table: (%d, %d) ", current_card.color, current_card.name);
    printf("\n Human Player Cards List: ");
    display_cards_list(players[HUMAN_PLAYER].cards_on_hand);
    printf("\n Computer Player Cards List: ");
    display_cards_list(players[COMPUTER_PLAYER].cards_on_hand);

    return result;
}