#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/cards_management.h"

/* Global variables */
Deck_t *g_draw_pile = NULL;            /* Draw cards pile */
Deck_t *g_discard_pile = NULL;         /* discarded cards */
Player_t g_players[PLAYERS_NUM];       /* array of players */
Card_t g_card_on_table;                /* last played card on the table-discard pile */
PlayerType_e g_player_on_turn = HUMAN; /* The current player on turn */
PlayerType_e g_game_winner = PlayerTypeNum;    /* game winner*/

int initialize_cards(void);
void initialize_card_on_table(void);
int deal_cards(void);
int shuffle_cards(void);
int add_card_at_beginning(Deck_t** pp_head, Card_t card);
int add_card_at_end(Deck_t* p_head, Card_t card);
const Deck_t* remove_first_card_from_deck(Deck_t** pp_head);
bool remove_card_from_deck(Deck_t** ptr_head, Card_t card);
void display_cards_list(const Deck_t* p_list);
int get_pile_length(Deck_t* p_pile);
bool is_playable_card(Card_t card);
bool is_exist_card(Deck_t* p_pile, Card_t card);
void swap_cards(Card_t* p_a, Card_t* p_b);
Card_t draw_one_card(void);
void initialize_card_on_table(void);
void display_player_deck(PlayerType_e player);
CardType_e get_card_type(Card_t card);

/**
 * @brief Initializes all the cards status and put them in remaining deck iteratively.
 *        Memeory will be allocated to store all the cards informations.
 *        If it can't malloc at any point, we will free the deck and return FAIL.
 *        initialize discard_cards pointor to be NULL, which indicates no discard cards.
 * @return int    0 - Initialization is successful;
 *             != 0 - Initialization is failed, since malloc memory fails
 */

int initialize_cards(void)
{
    int i, j;
    Card_t card;
    int result = 0;

    g_draw_pile = (Deck_t*)malloc(sizeof(Deck_t));
    if (g_draw_pile == NULL){
        printf("Unable to allocate memory to initialize draw_pile.");
        return -1;
    }
    g_draw_pile->card.color = RED;    // Link data field with data
    g_draw_pile->card.name = ZERO;
    g_draw_pile->next = NULL;         // Link address field to NULL

    for (j = ONE; j <= DRAW_ONE; j++){
        card.color = RED;
        card.name = j;
        result += add_card_at_beginning(&g_draw_pile, card);
    }

    for (i = BLUE; i <= YELLOW; i++){
        for (j = ZERO; j <= DRAW_ONE; j++){
            card.color = i;
            card.name = j;
            result += add_card_at_beginning(&g_draw_pile, card);
        }
    }

    //Adds 2 wild cards
    card.color = ACTION;
    card.name = WILD;
    result += add_card_at_beginning(&g_draw_pile, card);
    result += add_card_at_beginning(&g_draw_pile, card);

    //Adds 2 wild draw two cards
    card.color = ACTION;
    card.name = WILD_DRAW_TWO;
    result += add_card_at_beginning(&g_draw_pile, card);
    result += add_card_at_beginning(&g_draw_pile, card);


    if (0 != shuffle_cards()){
        printf("Shuffle cards failed in initialization.");
    }

    g_discard_pile = (Deck_t*)malloc(sizeof(Deck_t));
    if (g_discard_pile == NULL){
        printf("Unable to allocate memory to initialize discard pile.");
        return -1;
    }
    g_discard_pile->next = NULL;

    return result;
}


/**
 * @brief Deals each player 5 cards during the game initialization
 *
 * @return int   0 - Successful;
 *               1 - Failed due to error in malloc;
 */
int deal_cards(void)
{
    int i, j;
    const Deck_t *dealt_card;
    int result = SUCCESS;

    for (i = 0; i < DEAL_CARDS_NUM; i++){
        for (j = 0; j < PLAYERS_NUM; j++){
            dealt_card = remove_first_card_from_deck(&g_draw_pile);
            result += add_card_at_beginning(&g_players[(PlayerType_e)j].cards_on_hand, dealt_card->card);
        }
    }

    return result;
}

/**
* @brief All the cards are managed in a linked list.
*        This function is used to add a new card at the beginning to the specific cards list.
*
* @param pp_head pointer to the pointer of the list head
* @param card The specific card which is to be added.
* @return int 0 - Successful;
*             1 - Failed due to error in malloc;
*/
int add_card_at_beginning(Deck_t **pp_head, Card_t card)
{
    Deck_t* new_card = (Deck_t*)malloc(sizeof(Deck_t));
    if (new_card == NULL){
        printf("Fail to malloc memory when insert the card.\n");
        return MALLOC_FAIL;
    }

    memcpy(&new_card->card, &card, sizeof(Card_t));

    new_card->next = *pp_head;
    *pp_head = new_card;

    return 0;
}

/**
 * @brief Adds a new card at the end of the linked list.
 * 
 * @param p_head pointer to the list head
 * @param card  The specific card which is to be added. 
 * @return int 0 - Successful;
 *             1 - Failed due to error in malloc;
 */
int add_card_at_end(Deck_t *p_head, Card_t card)
{
    Deck_t *new_card = (Deck_t *)malloc(sizeof(Deck_t));
    if (new_card == NULL){
        printf("Unable to allocate memory.");
        return 1;
    }

    new_card->card.color = card.color;
    new_card->card.name = card.name;
    new_card->next = NULL;

    while (p_head != NULL && p_head->next != NULL){
        p_head = p_head->next;
    }

    if (p_head != NULL && p_head->next == NULL){
        p_head->next = new_card; /* Add the new node at end */
    }
    
    return 0;
}

/**
 * @brief remove the first card at the beginning of the card list
 * 
 * @param pp_head :pointer which points to the address of head of card list
 * @return const Deck_t* pointer type variable, which points to the removed card 
 */
const Deck_t *remove_first_card_from_deck(Deck_t **pp_head)
{
    Deck_t *to_delete;
    if (*pp_head == NULL){
        printf("List is already empty.");
        return NULL;
    }

    to_delete = *pp_head;
    *pp_head = (*pp_head)->next; // Mark the second element as first

    return to_delete;
}

/**
 * @brief Displays the detailed card infomation from the card list
 *
 * @param p_list The pointer which points to the beginning of the cards list
 */
void display_cards_list(const Deck_t *p_list)
{
    const Deck_t *temp_list_ptr = p_list;

    printf("[ ");

    while (temp_list_ptr != NULL){
        printf("(%s,%s) ", CARD_COLOR_STRING[temp_list_ptr->card.color], CARD_NAME_STRING[temp_list_ptr->card.name]);
        temp_list_ptr = temp_list_ptr->next;
    }

    printf(" ]\n");

    return;
}

/**
 * @brief Gets the length of a specific deck of cards
 * 
 * @param p_pile  pointer which points to the specific pile
 * @return int the length of the card list
 */
int get_pile_length(Deck_t *p_pile)
{
    int length = 0;
    Deck_t *temp_deck = p_pile;

    while (temp_deck != NULL){
        temp_deck = temp_deck->next;
        length++;
    }

    return length;
} 

/**
 * @brief Determines the card is playable or not by comparing the card with current card on table.
 *        If either the color or the name is same, then it's playable
 *
 * @param card The card which needs to be checked if it is playable or not
 * @return true The card is playable
 * @return false The card is not playable
 */
bool is_playable_card(Card_t card)
{
    if ((card.color == g_card_on_table.color) || (card.name == g_card_on_table.name)){
        return true;
    }
    return false;
}

/**
 * @brief Determines the card exist or not in the list
 *
 * @param p_pile  pointer which points to the specific pile
 * @param card The card which needs to be checked 
 * @return true The card exist
 * @return false The card does not exist
 */
bool is_exist_card(Deck_t* p_pile, Card_t card)
{
    bool is_exist = false;
    Deck_t* cur_element = p_pile;
    if (p_pile == NULL){
        printf("List is empty.\n");
        return false;
    }

    /* Iterate till last element until key is not found*/
    while (cur_element != NULL){
        if ((cur_element->card.color == card.color) && (cur_element->card.name == card.name)){
            return true;
        }
        cur_element = cur_element->next;
    }

    return false;
}

/**
 * @brief Swaps the position of card a and card b
 *
 * @param p_a pointer to card a;
 * @param p_b pointer to card b;
 */
void swap_cards(Card_t *p_a, Card_t *p_b)
{
    Card_t temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;

    return;
}

/**
 * @brief Returns the top card from the draw pile. Can be called by both Human
 * as well as computer player 
 * If there are no cards left in the draw pile, then it shuffles all the card from the discard pile and 
 * makes it as the new draw pile. 
 *
 * @return The drawn card
 */
Card_t draw_one_card(void)
{
    const Deck_t *draw_deck;
    const Deck_t *temp_deck;
    int result = 1;

    if (g_draw_pile == NULL){
        while (g_discard_pile != NULL)
        {
            temp_deck = remove_first_card_from_deck(&g_discard_pile);
            result += add_card_at_end(g_draw_pile, temp_deck->card);
        }
    }

    draw_deck = remove_first_card_from_deck(&g_draw_pile);
    return draw_deck->card;
}

/**
 * @brief Recursively free the given deck
 * @param d deck to be freed
 */
void free_deck(Deck_t* d){
    // Recursively free the deck
    if (d != NULL){
        free_deck(d->next);
        free(d);
    }
}

/**
 * @brief shuffles the cards in draw pile
 * @return int   0 - Successful;
 *               1 - Failed.
 */
int shuffle_cards(void) 
{
    int length = MAX_CARDS_NUM;
    int i;
    // reset seed
    srand((unsigned int)time(NULL));
    // copy the cards in remaining pile into a Card array
    Deck_t* current = g_draw_pile;
    Card_t* array = malloc(sizeof(Card_t) * length);
    if (array == NULL){
        free_deck(g_draw_pile);
        return 1;
    }
    for (i = 0; i < length; i++){
        array[i] = current->card;
        current = current->next;
    }

    // loop through the cards array and swap them randomly, using Fisher-Yates shuffle
    for (i = 0; i < length; i++){
        // find a random index to swap with the current one
        int random_index = rand() % (length - i) + i;
        swap_cards(&array[random_index], &array[i]);
    }

    // Put cards in array back to the remaining pile in the shuffled order
    current = g_draw_pile;
    for (i = 0; i < length - 1; i++){
        current->card = array[i];
        current = current->next;
    }
    //To make sure that there is no memory spaces assigned to the next deck of the last element of the whole cards
    // Set the last elements's next deck to null
    current->card = array[length - 1];
    current->next = NULL;

    free(array);
    return 0;
}

/**
 * @brief initialize the global varibale g_card_on_table, which indicates the latest card in the discard pile 
 *        This function is called when we start a new game.
 * 
 */
void initialize_card_on_table(void)
{
    CardType_e card_type = INVALID_TYPE;
    Card_t draw_card;

    while (card_type != NORMAL)
    {
        draw_card = draw_one_card();
        card_type = get_card_type(draw_card);
        add_card_at_end(g_discard_pile, draw_card);
    }

    memcpy(&g_card_on_table, &draw_card, sizeof(Card_t));

    return;
}

/**
 * @brief Remove a particular card from the given deck
 * Can be used to discard a particular card - during each turn
 * Works for both the computer as well as human deck of cards 
 * 
 * @param pp_head Pointer to the head of the deck from which card has to be removed
 * @param card Card to be removed
 * @return true If the card has been removed successfully
 * @return false If the removing of card fails
 */
bool remove_card_from_deck(Deck_t** pp_head, Card_t card)
{
    Deck_t* temp = *pp_head;
    Deck_t* prev = *pp_head;

    // If head node itself holds the key or multiple occurrences of key
    while ((temp != NULL) && (temp->card.name == card.name) && (temp->card.color == card.color)){
        *pp_head = temp->next; // Changed head
        free(temp);             // free old head
        return true;
    }

    // To delete key if it's not present in head 
    // Search for the key to be deleted, keep track of the previous node as we need to change 'prev->next'
    while ((temp != NULL) && ((temp->card.name != card.name) || (temp->card.color != card.color))){
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL){
        return false;
    }

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp); // Free memory
    return true;
}

/**
 * @brief Displays player's current list of cards
 *
 * @param player Player whose card list has to be displayed
 */
void display_player_deck(PlayerType_e player)
{
    printf("%s Player Deck", PLAYER_TYPE_STRING[player]);
    display_cards_list(g_players[player].cards_on_hand);

    return;
}

/**
 * @brief Get the card type by card info
 *
 * @param card The specific card info
 * @return CardType_e the mapped card type.
 *
 */
CardType_e get_card_type(Card_t card)
{
    CardType_e card_type = INVALID_TYPE;
    switch (card.name){
        case ZERO:
        case ONE:
        case TWO:
        case THREE:
        case FOUR:
        case FIVE:
        case SIX:
        case SEVEN:
        case EIGHT:
        case NINE:
            card_type = NORMAL;
            break;
        case SKIP:
        case DRAW_ONE:
        case WILD:
        case WILD_DRAW_TWO:
            card_type = card.name - 9;
            break;
        default:
            break;
    }

    return card_type;
}