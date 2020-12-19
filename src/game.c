#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>  
#include <stdlib.h>   
#include <string.h>
#include "../include/game.h"
#include "../include/computer_player.h"
#include "../include/human_player.h"
#include "../include/console_print.h"

bool g_end_game = false;
char g_human_player_name[PLAYERS_NAME_LENGTH] = "HumanPlayer";

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

/**
 * @brief Starts a new game
 * 
 */
void start_new_game(void)
{
    player_name_inquiry();

    if (0 != initialize_game()){
        printf("Initialize game failed.\n ");
        return;
    }

    printf("\nGame begins now...\n");
    printf("\n\n");

    while (true){
        printf("Card on the table now: (%s,%s).\n", CARD_COLOR_STRING[g_card_on_table.color], CARD_NAME_STRING[g_card_on_table.name]);
        printf("Current player is ");
        print_info(PLAYER_TYPE_STRING[g_player_on_turn]);

        if (g_player_on_turn == HUMAN){
            handle_human_turn();
        }
        else{
            handle_computer_turn();
        }

        if (g_end_game){
            if (g_game_winner == COMPUTER) {
                print_winner("Game over. The winner is COMPUTER player ", NULL);
            }
            else {
                print_winner("Game over. The winner is HUMAN player:", PLAYER_TYPE_STRING[g_game_winner]);
            }

            printf("\n");
            return;
        }
    }

    return;
}

/**
 * @brief Requests Human player's name
 *
 */
void player_name_inquiry(void)
{
    char choice[PLAYERS_NAME_LENGTH] = {0};
    printf("Please enter your name:");
    scanf("%s", choice);
    memcpy(g_human_player_name, choice, sizeof(choice));
    return;
}

/**
 * @brief Confirm if the player wants to exit
 * 
 * @return true exit is confirmed
 * @return false exit is cancelled
 */
bool confirm_exit(void)
{
    char char_choice[10] = {0,0,0,0};
    char exit_string[] = "Yes";

    print_info("Exit Game?");
    print_info("Please enter 'Yes' to confirm the Exit. Press any other key to cancel Exit. \n");

    scanf("%s", char_choice);
    printf("Entered choice is %s \n", char_choice);

    if (0 == strcmp(char_choice, exit_string)){
        printf("Exit the game...\n");
        exit(0);
    } 
    else{
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

    printf("Hi %s! Let's start a new game.\n", g_human_player_name);
    return result;
}

/**
 * @brief Initializes players global variables
 *
 */
void initialize_players(void)
{
    for (int i = 0; i < PLAYERS_NUM; i++){
        g_players[i].type = (PlayerType_e)i;
        g_players[i].cards_on_hand = NULL;
    }

    return;
}

/**
 * @brief Ends the player turn 
 *
 * @param player - Indicates whether user requested is Human or Computer Player
 */
void end_turn(PlayerType_e player)
{
    PlayerType_e next_turn_type = (player + 1) % PLAYERS_NUM;
    printf("%s Turn ended...\n\n", PLAYER_TYPE_STRING[player]);
    printf(". \n");
    printf(". \n");

    if (if_end_game(player)){
        g_end_game = true;
        g_game_winner = player;   
    } 
    else{
        g_player_on_turn = next_turn_type;
    }
    
    return;
}

/**
 * @brief check if meet the condition to end the game
 * 
 * @param player Player who is going to be updated as a game player.
 * @return true game ends
 * @return false game doesn't end
 */
bool if_end_game(PlayerType_e player)
{
    bool ret = false;
    if (0 == get_pile_length(g_players[player].cards_on_hand)){
        ret = true;
    }
    return ret;
}

/**
 * @brief This function handles the functionality to support human player's turn
 *
 */
ret_type_e handle_human_turn(void)
{
    display_player_deck(HUMAN);
    return record_human_input();
}

/**
 * @brief This function handles the functionality to support computer player's turn
 *
 */
void handle_computer_turn(void)
{
    computer_take_turn();
}

/**
 * @brief Draw a new card and add it to the next player's cards on hand list.
 *
 * @param player  The player who discards a draw-one card.
 * @return int 0 - Successful;
 *             1 - Failed due to error in malloc;
 */
int player_process_draw_one_card(PlayerType_e player)
{
    PlayerType_e be_applied_player = (player + 1) % PLAYERS_NUM;
    Card_t draw_card = draw_one_card();
    int ret = add_card_at_end(g_players[be_applied_player].cards_on_hand, draw_card);
    if (player == HUMAN) {
        print_info("HUMAN discarded a Draw-One card, COMPUTER loses turn, and a new card is added to COMPUTER card list.\n");
    }
    else {
        print_info("COMPUTER discarded a Draw-One card, HUMAN loses turn, and a new card is added to HUMAN card list.\n");
    }

    return ret;
}

/**
 * @brief Draw two new cards and add them to the next player's cards on hand list.
 *
 * @param player  The player who discards a wild-draw-two card.
 * @return int 0 - Successful;
 *             1 - Failed due to error in malloc;
 */
int player_process_wild_draw_two_card(PlayerType_e player)
{
    PlayerType_e be_applied_player = (player + 1) % PLAYERS_NUM;

    Card_t draw_card = draw_one_card();
    int ret = add_card_at_end(g_players[be_applied_player].cards_on_hand, draw_card);

    draw_card = draw_one_card();
    ret += add_card_at_end(g_players[be_applied_player].cards_on_hand, draw_card);

    if (player == HUMAN) {
        print_info("HUMAN discarded a Wild-Draw-Two card, COMPUTER loses turn, and two new cards are added to COMPUTER card list.\n");
    }
    else {
        print_info("COMPUTER discarded a Wild-Draw-Two card, HUMAN loses turn, and two new cards are added to HUMAN card list.\n");
    }
  
    return ret;
}