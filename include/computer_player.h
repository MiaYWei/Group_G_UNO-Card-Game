#ifndef __COMPUTER_HEADER__
#define __COMPUTER_HEADER__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define hand_MAX 20
#define plarCardNumber 10
typedef enum casenumber { CASE1, CASE2, CASE3, CASE4 } casenumber_e;

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
enum CardColor  find_most_color(struct DECK** cards_on_hand);

/*
* @brief: function that check if a card exist in the handcard deck
*
*
* @param: pointer to the pointer to the head of handcard list, card that needs to be checked
* @return 1 exist, 0 not exist
*/
int ifexists(struct DECK** handcard, enum CardNumber inputCardName, enum CardColor inputCardColor);

/*
* @brief: function that find the largest number of given color
*
*
* @param pointer to the pointer to the head of handcard list, color that need to be checked
* @return CardName the largest number
*/
enum CardName find_largest_number(struct DECK** handcard, enum CardColor inputCardColor);

/*
* @brief: function that find the occruence of a number
*
* @param pointer to the pointer to the head of handcard list, number that needs to be checked
* @return int number count for occruence
*/
int find_occurence_of_number(struct DECK** handcard, enum CardName inputCardNumber);


/*
* @brief: function that find the occruence of a color
*
* @param pointer to the pointer to the head of handcard list, color that needs to be checked
* @return int number count for occruence
*/
int find_occurence_of_color(struct DECK** handcard, enum CardColor inputCardcolor);

/*
* @brief: function that find the most color occruence of a given number
*
*
* @param pointer to the pointer to the head of handcard list, name that need to be checked
* @return CardColor  most color occruence of a given number
*
*/
enum CardColor find_color_with_most_occurence(struct DECK** handcard, enum CardName inputCardNumber);

/*
* @brief: function that get the matched color in the list for the given number
*
*
* @param pointer to the pointer to the head of handcard list, name that need to be checked
* @return CardColor  the matched color
*
*/
enum CardColor find_matched_color(struct DECK** handcard, enum CardName number);


/*
* @brief: function that find address within the list of a given card
*
*
* @param pointer to the pointer to the head of handcard list, card that need to be checked
* @return DECK * the address of that card
*
*/
struct DECK* find_address(struct DECK** head, struct CARD CARD);

/*
* @brief: function that play card from handcard list
*
* @param card that will be played, pointer to the pointer to the head of handcard list
* @return 1 for successed, 0 for failed
*/
struct DECK * play_card(struct CARD* card, struct DECK** head);


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
enum casenumber pick_case(struct CARD card, struct DECK** hand_card);

/** @brief Pick the best card to discard from hand cards based on
 *         the newest card on the table.
 *
 *	@param card need to be evalued, reference to the header of the hand card list
 *  @return A best cooresponding card from hand cards
 */

struct CARD * pick_card(struct CARD inputCard, struct DECK** hand_card);

#endif