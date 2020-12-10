#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>  
#include <stdlib.h>   
#include <string.h>
#include "../include/cards_management.h"
#include "../include/human_player_module.h"
#include "../include/game.h"

#define PLAYERS_NAME_LENGTH  20

bool g_end_game = false;
char g_human_player_name[PLAYERS_NAME_LENGTH] = "HumanPlayer";

void start_new_game(void);
bool confirm_exit(void);
int initialize_game(void);
void end_turn(PlayerType_e player);
bool if_end_game(PlayerType_e player);
void handle_computer_turn(void);
void player_name_inquiry(void);

/**
 * @brief Starts a new game
 * 
 */
void start_new_game(void)
{
    player_name_inquiry();

    if (0 != initialize_game())
    {
        printf("Initialize game failed.\n ");
        return;
    }

    printf("\nGame begins now...\n");
    printf("Human Player Deck: ");
    display_cards_list((const Deck_t*)g_players[HUMAN].cards_on_hand);
    //For Testing only
    //printf("Computer Player Deck: ");
    //display_cards_list((const Deck_t*)g_players[COMPUTER].cards_on_hand);
    printf("\n\n");

    while (1)
    {
        printf("Card on the table now: (%s, %s).\n", CARD_COLOR_STRING[g_card_on_table.color], CARD_NAME_STRING[g_card_on_table.name]);
        printf("Current player is %s.\n", PLAYER_TYPE_STRING[g_player_on_turn]);
        if (g_player_on_turn == HUMAN) 
        {
            handle_human_turn();
        }
        else
        {
            handle_computer_turn();
        }

        if (g_end_game)
        {
            printf("Game over. The winner is %s", PLAYER_TYPE_STRING[g_game_winner]);
            if (g_game_winner == HUMAN) 
            {
                printf(": %s", g_human_player_name);
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
    char char_choice[4] = {0,0,0,0};
    char exit_string[] = "Yes";

    printf("Exit Game?\n");
    printf("Please enter 'Yes' to confirm the Exit. Press any other key to cancel Exit.\n");
    scanf("%s", char_choice);
    printf("Entered choice is %s \n", char_choice);

    if (0 == strcmp(char_choice, exit_string)) 
    {
        printf("Exit the game...\n");
        exit(0);
    } 
    else 
    {
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

    if (if_end_game(player))
    {
        g_end_game = true;
        g_game_winner = player;
    } 
    else 
    {
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
    if (0 == get_pile_length(g_players[player].cards_on_hand)) 
    {
        ret = true;
    }
    return ret;
}

/**
 * @brief This function handles the functionality to support computer player's turn 
 * 
 */
void handle_computer_turn(void)
{
    int ret = computer_take_turn();
    if ((0 == ret) || (1 == ret))
    {
        end_turn(COMPUTER);
    }
    else
    {
        printf("Error: Not Computer's turn now.\n");
    }

    return;
}

/**
 * @brief Logic to discard card for computer player,
 *        1.Firstly search for a  playable card in the on hand cards list.
 *        2.If there is playable card, then remove the first playable card out of player's deck,
 *        update card_on_table global variable
 *        then place the discarded card into discard deck, and update player's deck length,
 *        3.If there is no playable card, draw a card from the draw pile and again check if it's playable.
 *        If yes, goto step 2. If no, end turn.
 *        4.Set winner if the last card is discarded from the player
 *
 * @return int   0 - Discarding card is successful, end of turn, game continues.
 *               1 - No playable card to discard, end of turn, game continues.
 *               2 - Invalid player.
 */
int computer_take_turn(void)
{
    int result = 0;
    Card_t draw_card;
    const Deck_t* playable_card;

    if (g_player_on_turn != COMPUTER)
    {
        return 2;
    }

    playable_card = find_playable_card(COMPUTER);
    if (NULL == playable_card)
    { /* If no playable card on hand */
        draw_card = draw_one_card();
        printf("Conputer draws a new card from the draw pile \n");
        printf("No playable card on hand, drawing a new card from deck (%s,%s).\n", CARD_COLOR_STRING[draw_card.color], CARD_NAME_STRING[draw_card.name]);//TODO Remove this line after testing
        if (is_playable_card(draw_card))
        {
            memcpy(&g_card_on_table, &draw_card, sizeof(Card_t));
            add_card_at_end(g_discard_pile, g_card_on_table);
            result = 0;
        }
        else
        {          
            add_card_at_end(g_players[COMPUTER].cards_on_hand, draw_card);
            result = 1;
        }
    }
    else
    {   /*If there is playable card, then remove the first playable card from on hand cards list*/
        Deck_t* discard_card = remove_first_playable_card(&g_players[COMPUTER].cards_on_hand);
        printf("Computer Drops..(%s, %s)\n", CARD_COLOR_STRING[discard_card->card.color], CARD_NAME_STRING[discard_card->card.name]);
        memcpy(&g_card_on_table, &discard_card->card, sizeof(Card_t));      
        add_card_at_end(g_discard_pile, g_card_on_table);
        result = 0;
    }

    return result;
}
