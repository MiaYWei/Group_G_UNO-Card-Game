#ifndef __COMPUTER_PLAYER_HEADER__
#define __COMPUTER_PLAYER_HEADER__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../include/cards_management.h"

typedef enum casenumber { CASE1, CASE2, CASE3, CASE4, INVALID_CASE } casenumber_e;
typedef struct colorInfo {
    CardColor_e color;
    int count;
}colorInfo_t;


int get_max(int n, ...);
CardColor_e  find_most_color(Deck_t** cards_on_hand);
CardName_e find_largest_number(Deck_t** hand_card, CardColor_e input_card_color);
int find_occurence_of_number(Deck_t** hand_card, CardName_e input_card_number);
int find_occurence_of_color(Deck_t** hand_card, CardColor_e input_card_color);
CardColor_e find_color_with_most_occurence(Deck_t** hand_card, CardName_e input_card_name);
CardColor_e find_matched_color(Deck_t** hand_card, CardName_e card_name);
Deck_t* find_address(Deck_t** head, Card_t card);
casenumber_e pick_case(Card_t card, Deck_t** hand_card);
Deck_t* pick_card(Card_t input_card, Deck_t** hand_card);
Deck_t* play_card(const Deck_t* card_address, Deck_t** head);
bool check_after_action(CardColor_e color, Deck_t** hand_card);
int computer_process_request_card(void);
void computer_process_playable_card(Deck_t* playable_card);
int computer_take_turn(void);
void process_playable_card(Card_t card);
#endif //__COMPUTER_PLAYER_HEADER__