#ifndef __CARDS_MANAGEMENT_HEADER__
#define __CARDS_MANAGEMENT_HEADER__

#include <stdbool.h>
#include <stdio.h> 

/* Totally 52 cards, which includes
* Release 1: 10 cards in each colour;
* Release 2: 4 Skip cards; 4 Draw One cards; 2 Wild cards; 2 Wild Draw Two cards*/
#define MAX_CARDS_NUM   52
#define MALLOC_FAIL     1
#define SUCCESS         0
#define PLAYERS_NUM     2
#define DEAL_CARDS_NUM  5

typedef enum { HUMAN, COMPUTER, PlayerTypeNum } PlayerType_e;
typedef enum { NORMAL, SKIP_T, DRAW_ONE_T, WILD_T, WILD_DRAW_TWO_T, INVALID_TYPE } CardType_e;
typedef enum { RED, BLUE, GREEN, YELLOW, ACTION, INVALID_COLOR } CardColor_e;
typedef enum { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, SKIP, DRAW_ONE, WILD, WILD_DRAW_TWO, INVALID_NAME } CardName_e;

static const char* PLAYER_TYPE_STRING[] = { "HUMAN", "COMPUTER", "INVALID"};
static const char* CARD_NAME_STRING[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Skip", "Draw-One", "Wild", "Wild-Draw-Two", "Invalid" };
static const char* CARD_COLOR_STRING[] = { "Red", "Blue", "Green", "Yellow", "Action", "Invalid" };

static const int USER_INPUT_COLOR[] = { 'R', 'B', 'G', 'Y', 'A'};
static const int USER_INPUT_NAME[] = { '0', '1', '2', '3', '4', '5', '6' ,'7', '8', '9', 'S', 'O', 'W', 'T'};

/* Card struct */
typedef struct CARD {
    CardColor_e color;               /* Color code for the card */
    CardName_e name;                 /* Name code for the card */
} Card_t;

/* Deck struct, which is a Linked-list */
typedef struct DECK {
    Card_t card;                       /* The current card this deck holds */
    struct DECK* next;                 /* Pointer to the next deck item */
} Deck_t;

/* Player struct */
typedef struct Player {
    PlayerType_e type;            /* The player type*/
    Deck_t* cards_on_hand;       /* Pointer to the player's deck on hand */
} Player_t;

/* Global variables */
extern Deck_t* g_draw_pile;                     /* remaining cards to draw */
extern Deck_t* g_discard_pile;                  /* discarded cards */
extern Player_t g_players[PLAYERS_NUM];         /* array of players */
extern Card_t g_card_on_table;                  /* last played card on the table */
extern PlayerType_e g_player_on_turn;           /* The current player on turn */
extern PlayerType_e g_game_winner;              /* game winner*/

int initialize_cards(void);
void initialize_card_on_table(void);
int deal_cards(void);
int shuffle_cards(void);
int add_card_at_beginning(Deck_t** pp_head, Card_t card);
int add_card_at_end(Deck_t* p_head, Card_t card);
const Deck_t* remove_first_card_from_deck(Deck_t** pp_head);
bool remove_card_from_deck(Deck_t** ptr_head, Card_t card);
void display_cards_list(const Deck_t *p_list);
int get_pile_length(Deck_t* p_pile);
bool is_playable_card(Card_t card);
bool is_exist_card(Deck_t* p_pile, Card_t card);
void swap_cards(Card_t* p_a, Card_t* p_b);
Card_t draw_one_card(void);
void initialize_card_on_table(void);
void display_player_deck(PlayerType_e player);
CardType_e get_card_type(Card_t card);

#endif //__CARDS_MANAGEMENT_HEADER__