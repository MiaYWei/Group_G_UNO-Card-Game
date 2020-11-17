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

enum PlayerType { HUMAN, COMPUTER};
enum Direction { CLOCKWISE, COUNTER_CLOCKWISE };
enum CardColor { RED, BLUE, GREEN, YELLOW };
enum CardName { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };
enum CardPile { DRAW, DISCARD, HUMAN_PLAYER, COMPUTER_PLAYER };

/* Card struct */
struct CARD {
    enum CardColor color;               /* Color code for card */
    enum CardName name;                 /* Name code for card */
                                        /* Release2: action*/
};

/* Deck struct, which is a Linked-list */
struct DECK {
    struct CARD card;                  /* The current card this deck holds */
    struct DECK* next;                 /* Pointer to the next deck item */
};

/* Player struct */
struct Player {
    enum PlayerType type;            /* The player type*/
    int count;                      /* The length of the deck on the player's hand */  
    struct DECK* cards_on_hand;      /* Pointer to the player's deck on hand */
};

/* Global variables */
struct DECK* draw_pile = NULL;                     /* remaining cards to draw */
struct DECK* discard_pile = NULL;                  /* discarded cards */
struct Player players[PLAYERS_NUM];                /* array of players */
struct CARD card_on_table;                         /* last played card on the table */
enum PlayerType player_on_turn = HUMAN;            /* The current player on turn */
enum PlayerType game_winner = HUMAN;               /* game winner*/

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
 * @brief All the cards are managed in a linked list. 
 *        This function is used to add a new card to the remaining cards deck list. 
 * 
 * @param card The specific card which is added.
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int add_card_at_beginning(struct DECK** head, struct CARD card);

/**
 * @brief Creates a new node and adds it at the end of the linked list.
 *
 * @param[in/out] head: pointer which points to the head of the linked list.
 * @param[in] data: int type variable which the data of the new node
 */
int add_card_at_end(struct DECK* head, struct CARD card);

/**
 * @brief remove the first card st the beginning of the card list
 * 
 * @param head :poinetr which points to the address of head of card list
 * @return struct DECK* ointer type variable, which points to the removed card 
 */
struct DECK* remove_first_card_at_beginning(struct DECK** head);

/**
 * @brief Finds a playable cards from player on hand card list, 
 *        which should be has the same color or same name comparing with the on tabe card 
 * 
 * @param player        enum type variable which indicates the player type
 * @return const Deck*  pointer type variable, which points to the playable card.
 */
struct DECK* find_playable_card(enum PlayerType player);

/**
 * @brief Displays the detailed card infomation from the card list 
 * 
 * @param list_ptr The pointer which points to the beginning of the cards list
 */
void display_cards_list(struct DECK *list_ptr);

/**
 * @brief Gets the listed cards pile length 
 * 
 * @return int the length of the listed cards pile, 
 *         which means how many cards are available in the specific pile.
 */
int get_pile_length(struct DECK* deck_ptr);

/**
 * @brief Checks the if there is still have available cads in the specific pile.
 * 
 * @param pile the specific type of pile
 * @return true the pile is empty
 * @return false  the pile is not empty
 */
bool is_pile_empty(enum CardPile pile);

/**
 * @brief Determins the card is playable or not by comparing the card with current card.
 *        If the color or the name is same, then it's playable
 * 
 * @param card The card which needs to be checked is playable or not
 * @return true The card is playable
 * @return false The card is not playable
 */
bool is_playable_card(struct CARD card);

/**
 * @brief Sorts the on hand cards for the specific player by
 *        placing the playable card on the top of the player's deck.
 * 
 * @param sort_player emum type variable: The specific player needs to sort his/her on hand cards 
 * @return int SUCCESS - Successful;
 *             MALLOC_FAIL - Failed because of memory malloc fails 
 */
int sort_cards_on_hand(enum PlayerType sort_player);

/**
 * @brief Swaps the position of card a and card b
 *
 * @param a pointer to card a;
 * @param b pointer to card b;
 */
void swap_cards(struct CARD* a, struct CARD* b);

/**
 * @brief remove the fist playable card in the card list
 * 
 * @param head : pointer which points to the head of the list
 * @param card : the latest discard card on table
 * @return struct DECK* pointer which points to the removed the card
 */
struct DECK *remove_first_playable_card(struct DECK** head);

/**
 * @brief The player discards a card, 
 *        Firstly to search a playable card in the on hand cards list.
 *        If there is playable card, then cut the first playable card out of player's deck 
 *        then place the discarded card into diacard deck, and update player's deck length, 
 *        setup winner if the last card is discarded from the player
 * 
 * @param player enum type variable: The specific player who discards his/her on hand card
 * @param ptr_post_condition pointer which points to int   
 *               0 - Discarding card is successful, end of turn, game continues. 
 *               1 - Discarding card is successful, end of game, the current player wins the game.
 *               2 - No playable card to discard, end of turn, game continues.
 *               3 - Invalid player type.
 * @return int   0 - Successful;
 *               1 - Failed
 */
int discard_card(enum PlayerType player, int* ptr_post_condition);

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
int draw_cards(int num_draw_cards, enum PlayerType player);

/**
 * @brief Draws one cards from the remaining deck for the current player
 *        If there is no cards left in the remaining deck, then place all the cards from discard deck
 *        into the remaining deck, then get it.
 * 
 * @param player enum type variable: The specific player who draws the card
 * @return Card  the drew card
 */
struct CARD draw_one_card(enum PlayerType player);

/**
 * @brief Gets the game winner
 * 
 * @return PlayerType The winner of the game
 */
enum PlayerType get_game_winner(void);

int test_initialize_cards(void);
int test_deal_cards(void);
int test_sort_cards_on_hand(void);
int test_discard_card(int test_case);
int test_draw_cards(void);
#endif // __CARDS_MANAGEMENT_HEADER__#pragma once