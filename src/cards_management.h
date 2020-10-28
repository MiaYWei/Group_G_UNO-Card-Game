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

typedef enum playerType { HUMAN_PLAYER, COMPUTER_PLAYER } PlayerType;
typedef enum direction { CLOCKWISE, COUNTER_CLOCKWISE } Direction;
typedef enum color { RED, BLUE, GREEN, YELLOW } Color;
typedef enum card_name { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE } CardName;


/* Card struct */
typedef struct card {
    Color color;               /* Color code for card */
    CardName name;             /* Name code for card */
} Card;

/* Deck struct, which is a Linked-list */
typedef struct deck {
    Card card;                  /* The current card this deck holds */
    struct deck* next;          /* Pointer to the next deck item */
} Deck;

/* Player struct */
typedef struct player {
    PlayerType type;            /* The player type*/
    int length;                 /* The length of the deck on the player's hand */
    Deck* cards_on_hand;        /* Pointer to the player's deck on hand */
} Player;

/**
 * @brief Initialize all the cards status and put them in remaining_pile iteratively.
 *        Memeory will be allocated to store all the cards informations.
 *        If it can't malloc at any point, we will free the deck and return FAIL.
 * @return int  0 - Initialization is successful;
 *             != 0 - Initialization is failed, since malloc memory fails
 */
int initialize_cards(void);

/**
 * @brief All the cards are managed in a linked list. 
 *        This function is used to add a new card to the head of the link. 
 * 
 * @param card The specific card which is inserted.
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int add_card_remaining_pile(const Card card);

/**
 * @brief  Deletes the first card from the linked list, and make the next to first link as first.
 * 
 * @return struct Deck* pointer which points to the deleted card
 */
const Deck *get_card_from_remaining_pile(void);

/**
 * @brief Displays the detailed card infomation from the card list 
 * 
 * @param list_ptr The pointer which points to the beginning of the cards list
 */
void display_cards_list(const Deck *list_ptr);

/**
 * @brief Checks the if there is still have available cads in the remianing pile.
 * 
 * @return true  remaining pile is empty
 * @return false remaining pile is not empty
 */
bool is_remaining_pile_empty(void);

/**
 * @brief Get the remaining pile length 
 * 
 * @return int the length of the remaining pile, 
 *         which means how many cards are available in the remaining pile.
 */
int get_remaining_pile_length(void);

/**
 * @brief Determins the card is playable or not by comparing the card with current card
 *        If the color or the name is same, then it's playable
 * @param card The card which needs to be checked is playable or not
 * @return true The card is playable
 * @return false The card is not playable
 */
bool is_playable_card(Card card);

/**
 * @brief Initialize players global variables
 * 
 */
void initialize_players(void);

/**
 * @brief Deals each player 5 cards at the start of the game setup
 * 
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int deal_cards(void);

/**
 * @brief Adds one card to the specific player's on hand cards list
 * 
 * @param card structure type varialble, includes card name and card color information 
 * @param player enum type varialble, which indicates the specific palyer type
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int add_card_on_hand(const Card card, PlayerType player);

/**
 * @brief Sorts the on hand cards for the specific player by
 *        placing all the playable card on the top of the player's deck.
 * 
 * @param sort_player emum type variable: The specific player needs to sort his/her on hand cards 
 * @return int SUCCESS - Successful;
 *             MALLOC_FAIL - Failed because of memory malloc fails 
 */
int sort_cards_on_hand(PlayerType sort_player);

/**
 * @brief Swaps the position of card a and card b
 *
 * @param a pointer to card a;
 * @param b pointer to card b;
 */
void swap_cards(Card* a, Card* b);


int test_initialize_cards(void);
int test_deal_cards(void);
int test_sort_cards_on_hand(void);
#endif // __CARDS_MANAGEMENT_HEADER__#pragma once