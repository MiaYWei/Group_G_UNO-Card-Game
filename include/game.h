#ifndef __GAME_HEADER__
#define __GAME_HEADER__

extern bool g_end_game;
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
 * @brief Requests Human player's name
 *
 */
void player_name_inquiry(void);

#endif // __GAME_HEADER__#pragma once