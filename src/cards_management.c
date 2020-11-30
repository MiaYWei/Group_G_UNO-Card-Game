#include <stddef.h>  
#include <stdlib.h>   
#include <string.h>
#include "cards_management.h"

/* Global variables */
Deck_t* g_draw_pile = NULL;                     /* remaining cards to draw */
Deck_t* g_discard_pile = NULL;                  /* discarded cards */
Player_t g_players[PLAYERS_NUM];                /* array of players */
Card_t g_card_on_table;                         /* last played card on the table-discard pile */
PlayerType_e g_player_on_turn = HUMAN;          /* The current player on turn */
PlayerType_e g_game_winner = HUMAN;             /* game winner*/

int initialize_game(void);
void initialize_players(void);
int initialize_cards(void);
int deal_cards(void);
int add_card_at_beginning(Deck_t** pp_head, Card_t card);
int add_card_at_end(Deck_t* p_head, Card_t card);
const Deck_t* remove_first_card_at_beginning(Deck_t** pp_head);
const Deck_t* find_playable_card(PlayerType_e player);
void display_cards_list(const Deck_t *p_list);
int get_pile_length(Deck_t* p_pile);
bool is_playable_card(Card_t card);
int sort_cards_on_hand(PlayerType_e sort_player);
void swap_cards(Card_t* p_a, Card_t* p_b);
Deck_t *remove_first_playable_card(Deck_t** pp_head);
int discard_card(PlayerType_e player, int* p_post_condition);
int draw_cards(int num_draw_cards, PlayerType_e player);
Card_t draw_one_card(void);
PlayerType_e get_game_winner(void);

/**
 * @brief Initializes players global variables
 *
 */
void initialize_players(void)
{
    for (int i = 0; i < PLAYERS_NUM; i++) {
        g_players[i].type = (PlayerType_e)i;
        g_players[i].count = 0;
        g_players[i].cards_on_hand = NULL;
    }

    return;
}

/**
 * @brief Initializes all the cards status and put them in remaining deck iteratively.
 *        Memeory will be allocated to store all the cards informations.
 *        If it can't malloc at any point, we will free the deck and return FAIL.
 *        initialize discard_cards pointor to be NULL, which indicates no discard cards.
 * @return int  0 - Initialization is successful;
 *             != 0 - Initialization is failed, since malloc memory fails
 */
int initialize_cards(void)
{
    int i, j;
    Card_t card;
    int result = 0;
    
    g_draw_pile = (Deck_t*)malloc(sizeof(Deck_t));
    if (g_draw_pile == NULL) {      
        printf("Unable to allocate memory to initizlize draw_pile.");
        return -1;
    }

    for (i = RED; i <= YELLOW; i++) {
        for (j = ZERO; j <= NINE; j++) {
            card.color = i;
            card.name = j;
            result += add_card_at_beginning(&g_draw_pile, card);
        }
    }

    g_discard_pile = (Deck_t*)malloc(sizeof(Deck_t));
    if (g_discard_pile == NULL) {      
        printf("Unable to allocate memory to initizlize discard pile.");
        return -1;
    }

    return result;
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
    const Deck_t* dealt_card;
    int result = SUCCESS;

    for (i = 0; i < DEAL_CARDS_NUM; i++) {
        for (j = 0; j < PLAYERS_NUM; j++) {
            dealt_card = remove_first_card_at_beginning(&g_draw_pile);
            result += add_card_at_beginning(&g_players[(PlayerType_e)j].cards_on_hand, dealt_card->card);
            g_players[j].count++;
        }
    }

    return result;
}

/**
 * @brief All the cards are managed in a linked list.
 *        This function is used to add a new card to the specific cards list.
 * 
 * @param pp_head pointer to the pointer of the list head
 * @param card The specific card which is added.
 * @return int 0 - Successful;
 *             1 - Failed, since malloc memory fails.
 */
int add_card_at_beginning(Deck_t** pp_head, Card_t card)
{
    Deck_t* new_card = (Deck_t*)malloc(sizeof(Deck_t));
    if (new_card == NULL) {
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
 * @param card  The specific card which is added. 
 * @return int 0 - Successful;
 *             1 - Failed, since malloc memory fails.
 */
int add_card_at_end(Deck_t* p_head, Card_t card)
{
    Deck_t* new_card = (Deck_t*)malloc(sizeof(Deck_t));
    if (new_card == NULL) {
        printf("Unable to allocate memory.");
        return -1;
    }

    new_card->card.color = card.color;
    new_card->card.name = card.name;
    new_card->next = NULL;

    while (p_head != NULL && p_head->next != NULL) {
        p_head = p_head->next;
    }

    p_head->next = new_card;  /* Add the new node at end */

    //printf("Card (%d, %d) added at end of list successfully.\n", card.color, card.name);
    return 0;
}

/**
 * @brief remove the first card at the beginning of the card list
 * 
 * @param pp_head :pointer which points to the address of head of card list
 * @return const Deck_t* pointer type variable, which points to the removed card 
 */
const Deck_t* remove_first_card_at_beginning(Deck_t** pp_head)
{
    Deck_t* to_delete;
    if (*pp_head == NULL) {
        printf("List is already empty.");
        return NULL;
    }

    to_delete = *pp_head;
    *pp_head = (*pp_head)->next; // Mark the second element as first 
    //free(to_delete);       // No need to free the memory occupied by first element, will return it later.

    return to_delete;
}

/**
 * @brief Finds a playable cards from player on hand card list,
 *        which should be has the same color or same name comparing with the on tabe card
 *
 * @param player        enum type variable which indicates the player type
 * @return const Deck_t*  pointer type variable, which points to the playable card.
 */
const Deck_t* find_playable_card(PlayerType_e player)
{
    Deck_t* current = g_players[player].cards_on_hand;
    if (current == NULL) {
        return NULL;
    }

    while (!is_playable_card(current->card)) {
        if (current->next == NULL) {       /*if it is last node*/
            return NULL;
        }
        else {
            current = current->next;
        }
    }

    return current;
}

/**
 * @brief Displays the detailed card infomation from the card list
 *
 * @param p_list The pointer which points to the beginning of the cards list
 */
void display_cards_list(const Deck_t *p_list)
{
    const Deck_t* temp_list_ptr;
    temp_list_ptr = p_list;

    printf("[ ");

    while (temp_list_ptr != NULL) {
        printf("(%s,%s) ", CARD_COLOR_STRING[temp_list_ptr->card.color], CARD_NAME_STRING[temp_list_ptr->card.name]);
        temp_list_ptr = temp_list_ptr->next;
    }

    printf(" ]\n");
}

/**
 * @brief Gets the listed cards pile length
 * 
 * @param p_pile  pointer which points to the specific pile
 * @return int the length of the card list
 */
int get_pile_length(Deck_t* p_pile)
{
    int length = 0;
    Deck_t* temp_deck = p_pile;

    while (temp_deck != NULL) {
        temp_deck = temp_deck->next;
        length++;
    }

    return length;
}
    
/**
 * @brief Determins the card is playable or not by comparing the card with current card on tables.
 *        If either the color or the name is same, then it's playable
 *
 * @param card The card which needs to be checked is playable or not
 * @return true The card is playable
 * @return false The card is not playable
 */
bool is_playable_card(Card_t card)
{
    if ((card.color == g_card_on_table.color) || (card.name == g_card_on_table.name)) {
        return true;
    }

    return false;
}

/**
 * @brief Sorts the on hand cards for the specific player by
 *        placing the playable card on the top of the player's deck.
 *
 * @param sort_player enum type variable: The specific player needs to sort his/her on hand cards
 * @return int SUCCESS - Successful;
 *             MALLOC_FAIL - Failed because of memory malloc fails
 */
int sort_cards_on_hand(PlayerType_e sort_player)
{
    int i;
    int length = g_players[sort_player].count;
    int index = 0;

    /*Copy the cards from the current player's hand into array*/
    Deck_t* current = malloc(sizeof(Deck_t));
    if (current == NULL) {
        printf("Fail to malloc memory when sort the on hand cards.\n");
        return MALLOC_FAIL;
    }
    current = g_players[sort_player].cards_on_hand;

    Card_t* sorted_cards = malloc(sizeof(Card_t) * length);
    if (sorted_cards == NULL) {
        printf("Fail to malloc memory when sort the on hand cards.\n");
        free(current);
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
    current = g_players[sort_player].cards_on_hand;

    for (i = 0; i < length; i++) {
        current->card = sorted_cards[i];
        current = current->next;
    }

    free(current);
    free(sorted_cards);
    return SUCCESS;
}

/**
 * @brief Swaps the position of card a and card b
 *
 * @param p_a pointer to card a;
 * @param p_b pointer to card b;
 */
void swap_cards(Card_t* p_a, Card_t* p_b)
{
    Card_t temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;
}

/**
 * @brief remove the fist playable card from the card list
 * 
 * @param pp_head : pointer which points to pointer of the list head of
 * @return Deck_t* pointer which points to the removed the card
 */
Deck_t *remove_first_playable_card(Deck_t** pp_head)
{
    Deck_t* prev = NULL;
    Deck_t* cur = *pp_head;
    Card_t removed_card;

    if (*pp_head == NULL) {
        printf("List is already empty.\n");
        return NULL;
    }

    /* Check if head node contains key */
    while ((*pp_head != NULL) 
           && (((*pp_head)->card.color == g_card_on_table.color) 
               || ((*pp_head)->card.name == g_card_on_table.name))) {
        removed_card.color = (*pp_head)->card.color;
        removed_card.name = (*pp_head)->card.name;
        prev = *pp_head;          // Get reference of head node
        *pp_head = (*pp_head)->next; // Adjust head node link        
        //free(prev);            // Delete prev since it contains reference to head node
        printf("Successfully deleted the first palyable card (%s, %s) at beginning. \n", CARD_COLOR_STRING[removed_card.color], CARD_NAME_STRING[removed_card.name]);
        return prev;              // No need to delete further
    }

    /* For each node in the list */
    while (cur != NULL) {
        if ((cur->card.color == g_card_on_table.color) || (cur->card.name == g_card_on_table.name)) {         // Current node contains key
            if (prev != NULL) {
                prev->next = cur->next; // Adjust links for previous node
            }
            //free(cur);                  // Delete current node
            printf("Successfully deleted the first palyable card (%s, %s) in the middile. \n", CARD_COLOR_STRING[cur->card.color], CARD_NAME_STRING[cur->card.name]);
            return cur;
        }

        prev = cur;
        cur = cur->next;
    }

    return NULL;
}

/**
 * @brief The player discards a card,
 *        Firstly to search a playable card in the on hand cards list.
 *        If there is playable card, then cut the first playable card out of player's deck,
 *        update card_on_table globle variable
 *        then place the discarded card into discard deck, and update player's deck length,
 *        setup winner if the last card is discarded from the player
 *
 * @param[in] player enum type variable: The specific player who discards his/her on hand card
 * @param[out] p_post_condition pointer which points to int type variables
 *               0 - Discarding card is successful, end of turn, game continues.
 *               1 - Discarding card is successful, end of game, the current player wins the game.
 *               2 - No playable card to discard, end of turn, game continues.
 *               3 - Invalid player.
 * @return int   0 - Successful;
 *               1 - Failed
 */
int discard_card(PlayerType_e player, int* p_post_condition)
{
    int result = 1;
    Card_t draw_card;
    const Deck_t* playable_card;
    int post_condition;
             
    if (g_player_on_turn != player) {
        post_condition = 3;
        *p_post_condition = post_condition;
        return 1;
    }
    
    playable_card = find_playable_card(player);
    
    if (NULL == playable_card) { /* If no playable card on hand */
        draw_card = draw_one_card();
        printf("No playable card on hand, draw a new card (%s,%s).\n", CARD_COLOR_STRING[draw_card.color], CARD_NAME_STRING[draw_card.name]);
        if (is_playable_card(draw_card)) {
            memcpy(&g_card_on_table, &draw_card, sizeof(Card_t));
            result = add_card_at_end(g_discard_pile, g_card_on_table);
            post_condition = 0;
        } else {
            result += add_card_at_end(g_players[player].cards_on_hand, draw_card);
            post_condition = 2;
        }
    } else { /*If there is playable card, then remove the first playable card from on hand cards list*/
        Deck_t* discard_card = remove_first_playable_card(&g_players[player].cards_on_hand);
        memcpy(&g_card_on_table, &discard_card->card, sizeof(Card_t));
        printf("discard card on table is (%s, %s)\n", CARD_COLOR_STRING[discard_card->card.color], CARD_NAME_STRING[discard_card->card.name]);
        result = add_card_at_end(g_discard_pile, g_card_on_table);
        g_players[player].count--;
        post_condition = 0;
    }

    if (g_players[player].count == 0) {
        g_game_winner = player;
        post_condition = 1;
    }

    *p_post_condition = post_condition;
    return result;
}

/**
 * @brief Draws the requested number of cards from the remaining deck for the current player
 *        If there is no cards left in the remaining deck, then place all the cards from discard deck
 *        into the remaining deck.
 *
 * @param num_draw_cards number of draw cards
 * @param player enum type variable: The specific player who draws the cards
 * @return int   0 - Successful;
 *               1 - Failed.
 */
int draw_cards(int num_draw_cards, PlayerType_e player)
{
    int i;
    const Deck_t* draw_card;
    const Deck_t* temp_deck;
    int result = 1;

    for (i = 0; i < num_draw_cards; i++)
    {
        if (g_draw_pile == NULL)
        {
            while (g_discard_pile != NULL) {
                temp_deck = remove_first_card_at_beginning(&g_discard_pile);
                result += add_card_at_end(g_draw_pile, temp_deck->card);
            }
        }

        draw_card = remove_first_card_at_beginning(&g_draw_pile);
        result = add_card_at_beginning(&g_players[player].cards_on_hand, draw_card->card);
    }

    return result;
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
    const Deck_t* draw_deck;
    const Deck_t* temp_deck;
    int result = 1;

    if (g_draw_pile == NULL)
    {
        while (g_discard_pile != NULL) {
            temp_deck = remove_first_card_at_beginning(&g_discard_pile);
            result += add_card_at_end(g_draw_pile, temp_deck->card);
        }
    }

    draw_deck = remove_first_card_at_beginning(&g_draw_pile);
    return draw_deck->card;
}

/**
 * @brief Gets the winner of the game
 *
 * @return PlayerType_e The winner of the game
 */
PlayerType_e get_game_winner(void)
{
    return g_game_winner;
}

/**
 * @brief initialize the global varibale g_card_on_table, which indicates the latest discard card on table. 
 *        This function is called when start a new game.
 * 
 */
void initialize_card_on_table(void)
{
    Card_t draw_card = draw_one_card();
    memcpy(&g_card_on_table, &draw_card, sizeof(Card_t));
}
