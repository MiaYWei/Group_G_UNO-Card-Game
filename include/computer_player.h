#ifndef __COMPUTER_PLAYER_HEADER__
#define __COMPUTER_PLAYER_HEADER__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../include/cards_management.h"

typedef enum casenumber { CASE1, CASE2, CASE3, CASE4 } casenumber_e;
typedef struct colorInfo {
    CardColor_e color;
    int count;
}colorInfo_t;

/*
* @brief: variadic function that returns the max of given numbers
*
* @param: number of args
* @return int the max value
*/
int get_max(int n, ...);

/*
* @brief: function that find the most occurrence with the color
*
* @param: pointer to the head of handcard list
* @return CardColor the color with moset occurrence
*/
CardColor_e  find_most_color(Deck_t** cards_on_hand);

/*
* @brief: function that find the largest number of given color
*
*
* @param pointer to the pointer to the head of handcard list, color that need to be checked
* @return CardName the largest number
*/
CardName_e find_largest_number(Deck_t** hand_card, CardColor_e input_card_color);

/*
* @brief: function that find the occruence of a number
*
* @param pointer to the pointer to the head of handcard list, number that needs to be checked
* @return int number count for occruence
*/
int find_occurence_of_number(Deck_t** hand_card, CardName_e input_card_number);

/*
* @brief: function that find the occruence of a color
*
* @param pointer to the pointer to the head of handcard list, color that needs to be checked
* @return int number count for occruence
*/
int find_occurence_of_color(Deck_t** hand_card, CardColor_e input_card_color);

/*
* @brief: function that find the most color occruence of a given number
*
*
* @param pointer to the pointer to the head of handcard list, name that need to be checked
* @return CardColor  most color occruence of a given number
*
*/
CardColor_e find_color_with_most_occurence(Deck_t** hand_card, CardName_e input_card_name);

/*
* @brief: function that get the matched color in the list for the given number
*
*
* @param pointer to the pointer to the head of handcard list, name that need to be checked
* @return CardColor  the matched color
*
*/
CardColor_e find_matched_color(Deck_t** hand_card, CardName_e card_name);

/*
* @brief: function that find address within the list of a given card
*
*
* @param pointer to the pointer to the head of handcard list, card that need to be checked
* @return DECK * the address of that card
*
*/
Deck_t* find_address(Deck_t** head, Card_t card);

/* function that choose the right card to draw */
/*
* @brief: function that choose the right card to draw
*          if player card # > 1
*           case 1 : no matched color and no matched number
*             - if have wild card, draw wild if wild card > with color with the most occurence
*             - if have skip, use skip
*             - if not have wild or skip, take card from pile
*            case 2 : have the matched color and no matched number
*             - choose the largest number on that color
*             - if matched color > 3, use match draw/draw2/skip card based on the color with the most occurence
*
*            case 3 : no matched color, but have matched number
*             - if have multiple, choose the color with the most occurence and corresponding action card
*             - if have only one, get rid of it
*
*            case 4 : have matched color and match number
*             - quickly get rid of matched numbers in the hand first.
*             - if occurence of
*
*         if player card # = 1
*            - use action card if possibile
*            - avoid play the last color that the player played
*
* @param Card that will be evaluated, pointer to the head of handcard list
* @return int the case number
*/
casenumber_e pick_case(Card_t card, Deck_t** hand_card);

/** @brief Pick the best card to discard from hand cards based on
 *         the newest card on the table.
 *
 *	@param card need to be evalued, reference to the header of the hand card list
 *  @return A best cooresponding card from hand cards
 */
Deck_t* pick_card(Card_t input_card, Deck_t** hand_card);

/*
* @brief: function that play card from handcard list
*
* @param card that will be played, pointer to the pointer to the head of handcard list
* @return 1 for successed, 0 for failed
*/
Deck_t* play_card(const Deck_t* card_address, Deck_t** head);

/*
* @brief: after play a card, computer will check if the drawed card is playable
*
* @param card color, hand card list
* @return 1 for successed, 0 for failed
*/
bool check_after_action(CardColor_e color, Deck_t** hand_card);

/**
 * @brief No playable card, computer player reuqests a new card
 *
 * @return int 0 - The new drawn card is playable;
 *             1 - The new drawn card is not playable, and be added to player cards on hand list;
 */
int computer_process_request_card(void);

/**
 * @brief Computer player discards a playable card, which include Skip and DRAW_ONE card.
 *
 */
void computer_process_playable_card(Deck_t* playable_card);

/**
 * @brief Logic to discard card for computer player,
 *        1.Firstly search for a playable card in the on hand cards list.
 *        2.If there is playable card, then remove the first playable card out of player's deck,
 *        update card_on_table global variable
 *        then place the discarded card into discard deck, and update player's deck length,
 *        3.If there is no playable card, draw a card from the draw pile and again check if it's playable.
 *        If yes, goto step 2. If no, end turn.
 *        4.Set winner if the last card is discarded from the player
 *
 * @return int   0 - Discarding card is successful, end of turn, game continues.
 *               1 - No playable card to discard, end of turn, game continues.
 *               2 - Invalid player.
 */
int computer_take_turn(void);

#endif //__COMPUTER_PLAYER_HEADER__