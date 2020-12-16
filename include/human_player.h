#ifndef __HUMAN_PLAYER_HEADER__
#define __HUMAN_PLAYER_HEADER__
#include "cards_management.h"
#include "return_types.h"

int request_card(PlayerType_e PlayerType, int no_of_cards);
void invalid_card_warning(void);
PlayerType_e determine_next_player(Card_t *previous_card, PlayerType_e current_player);
bool validate_card(const char *entered_value);
ret_type_e record_human_input();
void show_cards_assigned(Card_t assigned_card);
bool check_is_valid_card(Card_t *current_card);
bool is_human_card(Card_t* current_card);
void display_player_turn(PlayerType_e next_player);
int quit_game(void);
ret_type_e handle_human_turn(void);
ret_type_e human_process_normal_card(const char* user_input);

#endif // __HUMAN_PLAYER_HEADER__