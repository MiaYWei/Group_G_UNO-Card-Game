#ifndef __GAME_HEADER__
#define __GAME_HEADER__

#include <stdbool.h>
#include "../include/return_types.h"
#include "../include/cards_management.h"

#define PLAYERS_NAME_LENGTH  20

extern bool g_end_game;
extern char g_human_player_name[PLAYERS_NAME_LENGTH];

int initialize_game(void);
void initialize_players(void);
void start_new_game(void);
void player_name_inquiry(void);
bool confirm_exit(void);
void end_turn(PlayerType_e player);
bool if_end_game(PlayerType_e player);
void handle_computer_turn(void);
ret_type_e handle_human_turn(void);
int player_process_draw_one_card(PlayerType_e player);
int player_process_wild_draw_two_card(PlayerType_e player);

#endif //__GAME_HEADER__