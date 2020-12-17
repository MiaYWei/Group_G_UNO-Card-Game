#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/cards_management.h"
#include "../include/human_player.h"
#include "../include/game.h"

/* Global variables */
bool g_card_requested = false;

int request_card(PlayerType_e PlayerType, int no_of_cards);
void invalid_card_warning(void);
Card_t map_user_input(const char* user_input);
ret_type_e record_human_input(void);
void show_cards_assigned(Card_t assigned_card);
bool is_valid_card(Card_t current_card);
bool is_human_card(Card_t current_card);
int quit_game(void);
bool is_wild_card(const char* user_input);
bool is_skip_card(const char* user_input);
ret_type_e human_process_end_turn_request(void);
ret_type_e human_process_new_card_request(void);
ret_type_e human_process_action_wild_card(void);
ret_type_e human_process_skip_card(const char* user_input);
ret_type_e human_process_normal_card(const char* user_input);

/**
 * @brief Function called when the human player requests a card during each turn/
 *  Draw1/ Draw2 
 * Assigns the top most card/cards in the draw pile to the user
 *
 * @param PlayerType - Indicates whether user requested is Human or Computer Player
 * @param no_of_cards - Indicates the number of cards requested  
 */
int request_card(PlayerType_e PlayerType, int no_of_cards)
{
    Card_t card;
    int result;
    g_card_requested = true;
    card = draw_one_card();
    show_cards_assigned(card);
    //Assigning the drawn card to the human player
    result = add_card_at_end(g_players[HUMAN].cards_on_hand, card);
    return result;
}
/**
 * @brief Throws a warning message if the card dropped by the user is invalid
 * 
 */
void invalid_card_warning(void)
{
    printf("!!Warning!! Invalid card - Please choose a valid card \n");
    display_player_deck(HUMAN);

    return;
}

 /**
  * @brief  human player processes end turn request
  *
  * @return ret_type_e: RET_SUCCESS on success; 
  *                     RET_FAILURE on fail
  */
ret_type_e human_process_end_turn_request(void)
{
    ret_type_e ret = RET_FAILURE;

    if (g_card_requested)
    {
        g_card_requested = false;
        end_turn(HUMAN);
        ret = RET_SUCCESS;
    }
    else
    {
        printf("!!Warning!! Please draw a card before you can end your turn \n");
        display_player_deck(HUMAN);
    }

    return ret;
}

/**
 * @brief human player discards a normal card 
 *
 * @param user_input pointer to the user input
 * @return ret_type_e: RET_SUCCESS on successful;
 *                     RET_INVALID_CARD on invalid input
 */
ret_type_e human_process_normal_card(const char* user_input)
{
    //To be added if the format of user input is different
    Card_t human_card_choice = map_user_input(user_input);

    //Check if the card is from the human player deck
    if (!is_human_card(human_card_choice))
    {
        printf("!!Warning!! Please select a card from your deck! \n");
        invalid_card_warning();
        return RET_INVALID_CARD;
    }

    //If valid add the card to the discard_pile
    if (is_valid_card(human_card_choice))
    {
        remove_card_from_deck(&(g_players[HUMAN].cards_on_hand), human_card_choice);
        add_card_at_end(g_discard_pile, human_card_choice);
        memcpy(&g_card_on_table, &human_card_choice, sizeof(Card_t));
        end_turn(HUMAN);
        g_card_requested = false;
        return RET_SUCCESS;
    }
    else
    {
        invalid_card_warning();
        return RET_INVALID_CARD;
    }
}

/**
 * @brief human player requests a new card
 *
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_FAILURE on fail
 */
ret_type_e human_process_new_card_request(void)
{
    if (g_card_requested)
    {
        printf("!!Warning!! You've already drawn a card from the pile. Please discard card or end turn now \n");
        return RET_FAILURE;
    }
    else
    {
        return request_card(HUMAN, 1);
    }
}

/**
 * @brief human player discards a action card - Wild
 *
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_INVALID_CARD on invalid input
 */
ret_type_e human_process_action_wild_card(void)
{
    CardColor_e color_changed = 0;
    char colornum = ' ';
    Card_t updated_card = { ACTION, WILD };

    printf("Please enter your choice for the color changing. (R/B/G/Y)\n");
    scanf(" %c", &colornum);

    if (colornum == 'R') {
        color_changed = RED;
    }
    else if (colornum == 'G') {
        color_changed = GREEN;
    }
    else if (colornum == 'B') {
        color_changed = BLUE;
    }
    else if (colornum == 'Y') {
        color_changed = YELLOW;
    }
    else
    {
        printf("!!Warning!! Choose a valid color (R/B/G/Y) \n");
        return RET_INVALID_CARD;
    }

    //If valid add the card to the discard_pile
    if (!is_human_card(updated_card))
    {
        printf("!!Warning!! Please select a card from your deck! \n");
        return RET_INVALID_CARD;
    }

    remove_card_from_deck(&(g_players[HUMAN].cards_on_hand), updated_card);
    add_card_at_end(g_discard_pile, updated_card);

    //update g_card_on_table
    g_card_on_table.color = color_changed;
    g_card_on_table.name = WILD;

    //End turn
    end_turn(HUMAN);
    g_card_requested = false;
    return RET_SUCCESS;
}

/**
 * @brief human player discards a action card - Skip
 *
 * @param user_input pointer to the user input
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_INVALID_CARD on invalid input
 */
ret_type_e human_process_skip_card(const char* user_input)
{
    Card_t card = map_user_input(user_input);
    if ((card.color == INVALID_COLOR) || (card.name == INVALID_NAME))
    {
        return RET_INVALID_INPUT;
    }

    if (!is_human_card(card))
    {
        printf("Entered Card is [%s, %s]! \n", CARD_COLOR_STRING[card.color], CARD_NAME_STRING[card.name]);
        printf("!!Warning!! Please select a card from your deck! \n");
        return RET_INVALID_CARD;
    }

    //If the card is valid, then add the card to the discard_pile
    remove_card_from_deck(&(g_players[HUMAN].cards_on_hand), card);
    add_card_at_end(g_discard_pile, card);

    //update g_card_on_table
    g_card_on_table.color = card.color;
    g_card_on_table.name = card.name;

    //End turn
    end_turn(HUMAN);
    g_card_requested = false;

    //Next turn will be Human turn
    g_player_on_turn = HUMAN;
    return RET_SUCCESS;
}

/**
 * @brief Check if the card discarded by player is an action card
 *
 * @param user_input pointer to the user input
 * @return true on a wild action card discarding request; otherwise is false.
 *                     
 */
bool is_wild_card(const char* user_input)
{
    return (user_input[0] == 'a' || user_input[0] == 'A') && (user_input[1] == 'w' || user_input[1] == 'W');
}

/**
 * @brief Check if the card discarded by player is a skip card
 *
 * @param user_input pointer to the user input
 * @return true on a skip action card discarding request; otherwise is false.
 *
 */
bool is_skip_card(const char* user_input)
{
    for (int i = 0; i < 4; i++)
    {
        if (user_input[0] == USER_INPUT_COLOR[i])
        {
            if (user_input[1] == 'S')
            {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Function to map the human player input to Card type structure
 * Should be called only after validation of the user input
 *
 * If user input is 3R, It will be mapped as follows
 *  card.color=Red, card.name=3
 *
 * @param user_input: pointer to the value entered by the human during his turn
 *
 * @return Card_t the mapped card name and color values
 *         
 */
Card_t map_user_input(const char* user_input)
{
    int i = 0;
    int m = sizeof(USER_INPUT_COLOR) / sizeof(USER_INPUT_COLOR[0]);
    int n = sizeof(USER_INPUT_NAME) / sizeof(USER_INPUT_NAME[0]);
    
    Card_t invalid_card = { INVALID_COLOR, INVALID_NAME };
    Card_t card = { INVALID_COLOR, INVALID_NAME };

    //maps the card color
    for (i = 0; i < m; i++)
    {
        if (user_input[0] == USER_INPUT_COLOR[i])
        {
            card.color = i;
            break;
        }
    }

    if (card.color == INVALID_COLOR)
    {
        return invalid_card;
    }

    //maps the card name only if the card color is valid.
    for (i = 0; i < n; i++)
    {
        if (user_input[1] == USER_INPUT_NAME[i])
        {
            card.name = i;
            break;
        }
    }

    if (card.name == INVALID_NAME)
    {
        return invalid_card;
    }
    
    return card;
}

/**
 * @brief Records the Human player input during his turn and performs appropriate functions 
 * Called each time when it's the human player's turn 
 * Keyboard Input from Human 
 *        Q/q - Exit game
 *        n/N - Requests card 
 *        E/e - End Turn
 *        Other- Map to appropriate Card Info
 */
ret_type_e record_human_input(void)
{
    char user_input[10]; //TODO Modify the array size later
    printf("Please enter your choice \n");
    scanf("%s", user_input);

    if (user_input[0] == 'q' || user_input[0] == 'Q')
    {
        quit_game();
    }
    else if (user_input[0] == 'n' || user_input[0] == 'N')
    {
        return human_process_new_card_request();
    }
    else if (user_input[0] == 'e' || user_input[0] == 'E')
    {
        return human_process_end_turn_request();
    }
    else if (is_wild_card(user_input))
    {
        return human_process_action_wild_card();
    }
    else if (is_skip_card(user_input))
    {
        return human_process_skip_card(user_input);
    }
    else
    {
        return human_process_normal_card(user_input);
    }

    return RET_SUCCESS;
}

/**
 * @brief Displays the card assigned to the human player on the console during Request card/
 * Draw1 and Draw2 scenarios
 * 
 * @param assigned_card Card that has been added newly to the player's deck
 */
void show_cards_assigned(Card_t assigned_card)
{
    printf("The card from the draw pile is (%s,%s) \n", CARD_COLOR_STRING[assigned_card.color], CARD_NAME_STRING[assigned_card.name]);
    display_player_deck(HUMAN);
    return;
}

/**
 * @brief Checks if the card dropped by human player during his turn actually belongs to him
 *
 * @param current_card - Current card dropped by the human player
 *
 * @return- True if the card is valid
 *          False if the card is invalid
 */
bool is_human_card(Card_t current_card)
{
    bool is_valid = false;
    Deck_t* temp = g_players[HUMAN].cards_on_hand;

    while (temp != NULL)
    {
        if (temp->card.color == current_card.color && temp->card.name == current_card.name)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

/**
 * @brief Checks if the card dropped by human player during his turn is valid
 * 
 * @param current_card - Current card dropped by the human player
 * 
 * @return- True if the card is valid
 *          False if the card is invalid
 */
bool is_valid_card(Card_t current_card)
{
    if ((g_card_on_table.color == current_card.color) || (g_card_on_table.name == current_card.name))
    {
        return true;
    }

    return false;
}

/**
 * @brief This function handles the functionality to support human player's turn
 * 
 */
ret_type_e handle_human_turn(void)
{
    display_player_deck(HUMAN);
    ret_type_e ret = record_human_input();

    return ret;
}

/**
 * @brief Ends the Game as requested by the human player 
 *
 * @param PlayerType - Indicates whether user requested is Human or Computer Player
* ~
 */
int quit_game(void)
{
    printf("Exiting the game..");
    exit(0);
}
