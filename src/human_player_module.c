#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cards_management.h"
#include "human_player_module.h"
#include "game.h"

/* Global variables */
bool g_card_requested = false;
bool is_action_card = false;

int request_card(PlayerType_e PlayerType, int no_of_cards);
void invalid_turn_warning(void);
PlayerType_e determine_next_player(struct CARD *previous_card, PlayerType_e current_player); //Release 2
bool validate_card(char *entered_value);
Card_t map_user_input(char *input);
Card_t *pick_card_from_deck(Deck_t **pp_head, Card_t *card_to_be_matched); //Can be included in Card management
ret_type_e record_human_input(void);
void show_cards_assigned(Card_t assigned_card);
bool check_is_valid_turn(Card_t *current_card);
bool is_human_card(Card_t *current_card);
void display_player_turn(PlayerType_e next_player);
int quit_game(void);
ret_type_e handle_human_turn(void);

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
void invalid_turn_warning(void)
{
    printf("!!Warning!! Invalid card - Please choose a valid card \n");
    display_player_deck(HUMAN);
}

/**
 * @brief Validates if the input entered during the human player's turn by
 * comparing it with the predefined card values array
 * 
 * @param entered_value Value entered by the human player
 * @return true - Entered value is right
 * @return false - Value does not match the card values defined previously
 */
bool validate_card(char *entered_value)
{
    int size = sizeof CARD_VALUES / sizeof *CARD_VALUES;

    int i = 0;
    while (i < size)
    {
        if (0 != strcmp(CARD_VALUES[i], entered_value)) //strcmp returns 0, if both strings are identical (equal)
        {
            i++;
        }
        else
        {
            return true;
        }
    }
    return false;
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
    ret_type_e ret = RET_FAILURE;
    printf("Please enter your choice \n");
    scanf("%s", user_input);

    if (user_input[0] == 'q' || user_input[0] == 'Q')
    {
        quit_game();
    }
    else if (user_input[0] == 'n' || user_input[0] == 'N')
    {
        if (g_card_requested)
        {
            printf("!!Warning!! You've already drawn a card from the pile. Please discard card or end turn now \n");
        }
        else
        {
            request_card(HUMAN, 1);
        }
    }
    else if (user_input[0] == 'e' || user_input[0] == 'E')
    {
        if (g_card_requested)
        {
            g_card_requested = false;
            end_turn(HUMAN);
            return RET_SUCCESS;
        }
        else
        {
            printf("!!Warning!! Please draw a card before you can end your turn \n");
            display_player_deck(HUMAN);
        }
    }
    else
    {
        if (validate_card(user_input))
        {
            //To be added if the format of user input is different
            Card_t human_card_choice = map_user_input(user_input);

            //Check if the card is from the human player deck
            if (!is_human_card(&human_card_choice))
            {
                printf("!!Warning!! Please select a card from your deck! \n");
                return RET_INVALID_CARD;
            }

            //If valid add the card to the discard_pile
            if (check_is_valid_turn(&human_card_choice))
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
                invalid_turn_warning();
            }
        }
        else
        {
            invalid_turn_warning();
        }
    }
    return ret;
}

/**
 * @brief Function to map the human player input to Card type structure
 * Should be called only after validation of the user input
 * 
 * If user input is 3R, It will be mapped as follows
 *  card.color=Red, card.name=3
 * 
 * @param input Value entered by the human during his turn
 * 
 * @return Card_t the mapped card name and color values
 *         NULL If the input is invalid
 */
Card_t map_user_input(char *input)
{
    Card_t temp_card = {ColorNum, NameNum};

    if (input[0] == 'R')
    {
        temp_card.color = RED;
    }
    else if (input[0] == 'G')
    {
        temp_card.color = GREEN;
    }
    else if (input[0] == 'B')
    {
        temp_card.color = BLUE;
    }
    else if (input[0] == 'Y')
    {
        temp_card.color = YELLOW;
    }

    //To map the number part of the User input to the card name field
    temp_card.name = input[1] - '0';
    return temp_card;
}

//TODO Remove this function if unused
/**
 * @brief Function picks a particular card from the current human deck of cards
 * Called when a particular card has to be selected for removing from a deck
 * Frees the menory allocated to he temporary selected drop card input parameter
 * Note: Function  must be called only if the card to be selected is VALID
 * 
 * @param pp_head :Pointer which points to the address of head of card list in the Deck
 * @param card_to_be_matched :Card which has to be matched from the deck
 * 
 * @return Card_t* Card that has been matched with the given card value
 *         NULL - Returns NULL if the given card does not match with any of the cards in the deck
 */
Card_t *pick_card_from_deck(Deck_t **pp_head, Card_t *card_to_be_matched)
{
    Deck_t *temp = *pp_head;
    while (temp->next != NULL)
    {
        if (temp->card.color == card_to_be_matched->color && temp->card.name == card_to_be_matched->name)
        {
            return &temp->card;
        }
        temp = temp->next;
    }
    //free(card_to_be_matched); //Check if it can be freed here
    return NULL;
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
bool is_human_card(Card_t *current_card)
{

    bool is_valid = false;

    Deck_t *temp = g_players[HUMAN].cards_on_hand;

    while (temp!= NULL)
    {

        if (temp->card.color == current_card->color && temp->card.name == current_card->name)
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
bool check_is_valid_turn(Card_t *current_card)
{
    bool is_valid = false;
    if ((g_card_on_table.color == current_card->color) || (g_card_on_table.name == current_card->name))
    {
        is_valid = true;
    }
    return is_valid;
}

/**
 * @brief Determines next player based on the previous card dropped on the discard pile
 *
 * @param previous_card - Last dropped card on the pile
 * @param current_player - Indicates the current player who dropped the card  
 */

PlayerType_e determine_next_player(struct CARD *previous_card, PlayerType_e current_player)
{
    PlayerType_e next_player;
    if (current_player == 0 && !is_action_card)
    {
        next_player = COMPUTER;
        //call function to execute the computer's turn
    }
    else if (current_player == 1 && !is_action_card)
    {
        next_player = HUMAN;
        handle_human_turn();
    }
    else
    {
        /* Action card functionality in Release 2 */
    }
    return next_player;
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
 * @brief Displays whose turn it is- Human/Computer to play on the terminal
 *
 * @param next_player - Player to take turn next *  
 */
void display_player_turn(PlayerType_e next_player)
{
    printf("%s Player's Turn now", PLAYER_TYPE_STRING[next_player]);
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

//Release 2
//Write for computer?

/**
 * @brief Records the action_color when the previous card is Draw2/Wild card
 *
 * @param color - Color that is received from human player
 * 
 * 
 * @return- Correct enum representaion of the defined colors
 */
/*
enum CardColor action_color(char color)
{
}
*/
/**
 * @brief Function called when card dropped on the pile is Wild card
 *
 * @param PlayerType - Indicates whether the card is played by Human or Computer Player
 */
/*
void wild_card(PlayerType_e type)
{
}

*/
