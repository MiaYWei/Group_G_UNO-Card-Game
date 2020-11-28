#include <stddef.h>  
#include <stdlib.h>   
#include <string.h>
#include "cards_management.h"
#include "game.h"

int initialize_game(void);

/**
 * @brief Starts a new game
 * 
 */
void start_new_game(void)
{
    bool is_confirmed = false;
    initialize_game();
    printf("Latest Discard Card is: (%s, %s).\n", CARD_COLOR_STRING[g_card_on_table.color], CARD_NAME_STRING[g_card_on_table.name]);
    printf("Human Player on hand card list: ");
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);
    printf("Computer Player on hand card list: ");
    display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);

    printf("Current Player is: %s.\n", PLAYER_TYPE_STRING[g_player_on_turn]);
    printf("Game is running.... You can enter 'q' or 'Q' to request quit the current game.\n");

    if (g_player_on_turn == HUMAN) {
        int key_Q = 81;  //ASCII code for "Q"                                   
        int key_q = 113;  //ASCII code for "q"    
        while (1) {
            if ((key_Q == _getch()) || (key_q == _getch())) {                 
                printf("Human Player request to quit the game.\n");
                if (!confirm_exit()) {
                    printf("Game is continuing...\n");
                }
            }
        }
    }
}

/**
 * @brief confirm if the player's exit or quit request
 * 
 * @return true exit is confirmed
 * @return false exit is cancelled
 */
bool confirm_exit(void)
{
    char char_choice[4] = { 0,0,0,0 };
    char exit_string[] = "Yes";

    printf("Exit Game?\n");
    printf("Please enter 'Yes' to confirm the Exit. Press any other key to cancel Exit.\n");
    scanf_s("%s", char_choice, 4);
    printf("Entered string is %s \n", char_choice);

    if (0 == strcmp(char_choice, exit_string)) {
        printf("Exit the game...\n");
        exit(0);
    } else {
        return false;
    }
}
/**
 * @brief Initializes game which includes initialize cards and initialize players
 *
 * @return int 0 - Initialization is successful;
 *             1 - Initialization is failed, since malloc memory fails
 */
int initialize_game(void)
{
    int result = initialize_cards();
    initialize_players();
    result += deal_cards();

    initialize_card_on_table();
    return result;
}