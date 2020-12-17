#ifndef __GAME_HEADER__
#define __GAME_HEADER__

#include <stdbool.h>
#include "../include/return_types.h"
#include "../include/cards_management.h"

#define PLAYERS_NAME_LENGTH  20

extern bool g_end_game;
extern char g_human_player_name[PLAYERS_NAME_LENGTH];
/**
 * @brief Initializes game which includes initialize cards and initialize players
 *
 * @return int 0 - Initialization is successful;
 *             1 - Initialization is failed, since malloc memory fails
 */
int initialize_game(void);

/**
 * @brief Requests Human player's name
 *
 */
void player_name_inquiry(void);

/**
 * @brief Initializes players global variables
 *
 */
void initialize_players(void);

/**
 * @brief Starts a new game
 *
 */
void start_new_game(void);

/**
 * @brief confirm if the player's exit or quit request
 * 
 * @return true exit is confirmed
 * @return false exit is cancelled
 */
bool confirm_exit(void);

/**
 * @brief Ends the player turn as requested
 *
 * @param player - Indicates whether user requested is Human or Computer Player
 */
void end_turn(PlayerType_e player);

/**
 * @brief check if meet the condition to end the game
 *
 * @param player Player who is going to be updated as a game player.
 * @return true game ends
 * @return false game doesn't end
 */
bool if_end_game(PlayerType_e player);

/**
 * @brief his function handles the functionality to support computer player's turn
 *
 */
void handle_computer_turn(void);

/**
 * @brief This function handles the functionality to support human player's turn
 *
 */
ret_type_e handle_human_turn(void);

/**
 * @brief Draw a new card and add it to the next player's cards on hand list.
 *
 * @param player  The player who discards a draw-one card.
 * @return int 0 - Successful;
 *             1 - Failed due to error in malloc;
 */
int player_process_draw_one_card(PlayerType_e player);

/**
 * @brief Draw two new cards and add them to the next player's cards on hand list.
 *
 * @param player  The player who discards a wild-draw-two card.
 * @return int 0 - Successful;
 *             1 - Failed due to error in malloc;
 */
int player_process_wild_draw_two_card(PlayerType_e player);

#endif // __GAME_HEADER__#pragma once