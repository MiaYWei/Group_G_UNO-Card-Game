#ifndef __CARDS_MANAGEMENT_HEADER__
#define __CARDS_MANAGEMENT_HEADER__

#include <stdbool.h>
#include <stdio.h> 

/* Totally 52 cards, which includes
* Release 1: 10 cards per colour;
* Release 2: 4 Skip cards; 4 Draw One cards; 2 Wild cards; 2 Wild Draw Two cards*/
#define MAX_CARDS_NUM   40
#define LINE_SIZE       1000         /*LINESIZE to read input */
#define MALLOC_FAIL     1
#define SUCCESS         0
#define PLAYERS_NUM     2
#define DEAL_CARDS_NUM  5

typedef enum PlayerType { HUMAN, COMPUTER, PlayerTypeNum} PlayerType_e;
typedef enum Direction { CLOCKWISE, COUNTER_CLOCKWISE } Direction_e;
typedef enum CardColor { RED, BLUE, GREEN, YELLOW, BLACK } CardColor_e;
typedef enum CardName { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, FDRAW, FDRAW2, WILD, SKIP } CardName_e;
typedef enum CardPile { DRAW, DISCARD, HUMAN_PLAYER, COMPUTER_PLAYER } CardPile_e;

static const char* PLAYER_TYPE_STRING[] = { "HUMAN", "COMPUTER" };
static const char* CARD_NAME_STRING[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "FDRAW", "FDRAW2", "WILD" ,"SKIP"};
static const char* CARD_COLOR_STRING[] = { "RED", "BLUE", "GREEN", "YELLOW", "BLACK" };

static const char* CARD_VALUES [] = {   "0R", "1R", "2R","3R", "4R", "5R","6R", "7R", "8R","9R",
                                        "0Y", "1Y", "2Y","3Y", "4Y", "5Y","6Y", "7Y", "8Y","9Y",
                                        "0B", "1B", "2B","3B", "4B", "5B","6B", "7B", "8B","9B",
                                        "0G", "1G", "2G","3G", "4G", "5G","6G", "7G", "8G","9G" };

/* Card struct */
typedef struct CARD {
    CardColor_e color;               /* Color code for card */
    CardName_e name;                 /* Name code for card */
} Card_t;

/* Deck struct, which is a Linked-list */
typedef struct DECK {
    Card_t card;                  /* The current card this deck holds */
    struct DECK* next;                 /* Pointer to the next deck item */
} Deck_t;

/* Player struct */
typedef struct Player {
    PlayerType_e type;            /* The player type*/
    Deck_t* cards_on_hand;      /* Pointer to the player's deck on hand */
} Player_t;

/* Global variables */
extern Deck_t* g_draw_pile;                     /* remaining cards to draw */
extern Deck_t* g_discard_pile;                  /* discarded cards */
extern Player_t g_players[PLAYERS_NUM];         /* array of players */
extern Card_t g_card_on_table;                  /* last played card on the table */
extern PlayerType_e g_player_on_turn;           /* The current player on turn */
extern PlayerType_e g_game_winner;              /* game winner*/

/**
 * @brief Initializes game which includes initialize cards and initialize players
 * 
 * @return int 0 - Initialization is successful;
 *             1 - Initialization is failed, since malloc memory fails
 */
int initialize_game(void);

/**
 * @brief Initializes players global variables
 * 
 */
void initialize_players(void);

/**
 * @brief Initializes all the cards status and put them in remaining deck iteratively.
 *        Memeory will be allocated to store all the cards informations.
 *        If it can't malloc at any point, we will free the deck and return FAIL.
 * @return int  0 - Initialization is successful;
 *             != 0 - Initialization is failed, since malloc memory fails
 */
int initialize_cards(void);

/**
 * @brief Deals each player 5 cards at the start of the game setup
 * 
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int deal_cards(void);

/**
 * @brief Finds a playable cards from player on hand card list,
 *        which should be has the same color or same name comparing with the on tabe card
 *
 * @param player        enum type variable which indicates the player type
 * @return const Deck_t*  pointer type variable, which points to the playable card.
 */
const Deck_t* find_playable_card(PlayerType_e player);

/**
 * @brief Displays the detailed card infomation from the card list 
 * 
 * @param p_list The pointer which points to the beginning of the cards list
 */
void display_cards_list(const Deck_t *p_list);

/**
 * @brief Gets the listed cards pile length
 * 
 * @param p_pile  pointer which points to the specific pile
 * @return int the length of the card list
 */
int get_pile_length(Deck_t* p_pile);

/**
 * @brief Determins the card is playable or not by comparing the card with current card on tables.
 *        If either the color or the name is same, then it's playable
 *
 * @param card The card which needs to be checked is playable or not
 * @return true The card is playable
 * @return false The card is not playable
 */
bool is_playable_card(Card_t card);

/**
 * @brief remove the fist playable card from the card list
 * 
 * @param pp_head : pointer which points to pointer of the list head of
 * @return Deck_t* pointer which points to the removed the card
 */
Deck_t *remove_first_playable_card(Deck_t** pp_head);

/**
 * @brief Draws the requested number of cards from the remaining deck for the current player
 *        If there is no cards left in the remaining deck, then place all the cards from discard deck
 *        into the remaining deck.
 *
 * @param num_draw_cards number of draw cards
 * @param player emum type variable: The specific playe who draws the cards
 * @return int   0 - Successful;
 *               1 - Failed.
 */
int draw_cards(int num_draw_cards, PlayerType_e player);

/**
 * @brief Draws one cards from the remaining deck for the current player
 *        If there is no cards left in the remaining deck, then place all the cards from discard deck
 *        into the remaining deck, then get it.
 * 
 * @return Card  the drew card
 */
Card_t draw_one_card(void);

/**
 * @brief initialize the global varibale g_card_on_table, which indicates the latest discard card on table.
 *        This function is called when start a new game.
 *
 */
void initialize_card_on_table(void);

/**
* @brief All the cards are managed in a linked list.
*        This function is used to add a new card to the specific cards list.
*
* @param pp_head pointer to the pointer of the list head
* @param card The specific card which is added.
* @return int 0 - Successful;
*             1 - Failed, since malloc memory fails.
*/
int add_card_at_beginning(Deck_t** pp_head, Card_t card);

/**
 * @brief Adds a new card at the end of the linked list.
 * 
 * 
 * @param p_head pointer to the list head
 * @param card  The specific card which is added. 
 * @return int 0 - Successful;
 *             1 - Failed, since malloc memory fails.
 */
int add_card_at_end(Deck_t *p_head, Card_t card);

/**
 * @brief Remove a particular card from the given deck
 * Can be used to discard a particular card - during each turn
 * Works for both the computer as well as human deck of cards
 *
 * @param pp_head Pointer to the head of the deck from which card has to be removed
 * @param card Card to be removed
 * @return true If the card is been removed successfully
 * @return false If the removing of card fails
 */
bool remove_card_from_deck(Deck_t** ptr_head, const Card_t card);

/**
 * @brief Checks if the specific card exist in the list or not
 *
 * @param list the head of the list
 * @param card  the specific card to be checked
 * @return true  The card is in the list
 * @return false The card is not in the list
 */
bool is_card_exist_in_list(const Deck_t* p_list, Card_t card);

/**
 * @brief Displays player's current list of cards
 *
 * @param player Player whose card list has to be displayed
 */
void display_player_deck(PlayerType_e player);

#endif // __CARDS_MANAGEMENT_HEADER__#pragma once