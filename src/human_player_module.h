#ifndef __HUMAN_PLAYER_HEADER__
#define __HUMAN_PLAYER_HEADER__
#include "cards_management.h"
#include "return_types.h"

int request_card(PlayerType_e PlayerType, int no_of_cards);
void invalid_turn_warning(void);
const Deck_t *show_recent_card(Deck_t **pp_head);
PlayerType_e determine_next_player(struct CARD *previous_card, PlayerType_e current_player);
bool validate_card(char *entered_value);
ret_type_e record_human_input();
void show_cards_assigned(Card_t assigned_card);
bool check_is_valid_turn(Card_t *current_card);
void display_player_turn(PlayerType_e next_player);
int quit_game(void);
ret_type_e handle_human_turn(void);

#endif // __HUMAN_PLAYER_HEADER__