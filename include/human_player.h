#ifndef __HUMAN_PLAYER_HEADER__
#define __HUMAN_PLAYER_HEADER__
#include "cards_management.h"
#include "return_types.h"

ret_type_e handle_human_turn(void);
ret_type_e record_human_input(void);
Card_t map_user_input(const char* user_input);
CardType_e get_card_type(Card_t card);
int request_card(PlayerType_e PlayerType, int no_of_cards);
void invalid_card_warning(void);
void show_cards_assigned(Card_t assigned_card);
bool is_valid_card(Card_t current_card);
bool is_human_card(Card_t current_card);
ret_type_e human_process_card(const char* user_input);
ret_type_e human_process_end_turn_request(void);
ret_type_e human_process_new_card_request(void);
ret_type_e human_process_normal_card(Card_t human_card_choice);
ret_type_e human_process_skip_card(Card_t human_card_choice);
ret_type_e human_process_draw_one_card(Card_t human_card_choice);
ret_type_e human_process_wild_card(Card_t human_card_choice);
ret_type_e human_process_wild_draw_two_card(Card_t human_card_choice);
int quit_game(void);

#endif // __HUMAN_PLAYER_HEADER__