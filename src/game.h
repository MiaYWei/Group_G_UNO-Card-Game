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
 * @brief Update the winner of the game
 * 
 * @param player Player who is going to be updated as a game player.
 * @return true set the specific player as winner successsful
 * @return false set the specific player as winner failed
 */
bool update_game_winner(PlayerType_e player);

/**
 * @brief his function handles the functionality to support computer player's turn
 *
 */
void handle_computer_turn(void);

/**
 * @brief The computer player discards a card,
 *        Firstly to search a playable card in the on hand cards list.
 *        If there is playable card, then cut the first playable card out of player's deck,
 *        update card_on_table globle variable
 *        then place the discarded card into discard deck, and update player's deck length,
 *        setup winner if the last card is discarded from the player
 *
 * @return int   0 - Discarding card is successful, end of turn, game continues.
 *               1 - No playable card to discard, end of turn, game continues.
 *               2 - Invalid player.
 */
int computer_take_turn(void);

#endif // __GAME_HEADER__#pragma once