#ifndef __CARDS_MANAGEMENT_HEADER__
#define __CARDS_MANAGEMENT_HEADER__

#include <stdbool.h>
#include <stdio.h> 

/* Totally 52 cards, which includes
* Release 1: 10 cards per colour;
* Release 2: 4 Skip cards; 4 Draw One cards; 2 Wild cards; 2 Wild Draw Two cards*/
#define MAX_CARDS_NUM   52 
#define LINE_SIZE       1000         /*LINESIZE to read input */
#define MALLOC_FAIL     1
#define SUCCESS         0
#define PLAYERS_NUM     2
#define DEAL_CARDS_NUM  5

typedef enum playerType { HUMAN_PLAYER, COMPUTER } PlayerType;
typedef enum direction { CLOCKWISE, COUNTER_CLOCKWISE } Direction;
typedef enum color { RED, BLUE, GREEN, YELLOW } Color;
typedef enum card_name { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE } CardName;

/* Card struct */
typedef struct card {
    Color color;      /* Color code for card */
    CardName name;    /* Name code for card */
} Card;

/* Deck struct, which is a Linked-list */
typedef struct deck {
    Card card;            /* The current card this deck holds */
    struct deck* next;    /* Pointer to the next deck item */
} Deck;

/* Player struct */
typedef struct player {
    PlayerType type;            /* The player type*/
    int length;           /* The length of the deck on the player's hand */
    Deck* cards_on_hand;          /* Pointer to the player's deck on hand */
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
 *        This function is used to insert a new card to the head of the link. 
 * 
 * @param card The specific card which is inserted.
 * @return int   0 - Inserting is successful;
 *               1 - Inserting card is failed, since malloc memory fails.
 */
int insert_card(const Card card);

#endif // __CARDS_MANAGEMENT_HEADER__#pragma once