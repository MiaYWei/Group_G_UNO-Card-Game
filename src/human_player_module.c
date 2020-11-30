#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cards_management.h"
#include "human_player_module.h"

/* Global variables */
bool g_card_requested = false;
bool is_action_card = false;
Player_t *human_player;

int request_card(PlayerType_e PlayerType, int no_of_cards);
void invalid_turn_warning();
const Deck_t *show_recent_card(Deck_t **pp_head);
PlayerType_e determine_next_player(struct CARD *previous_card, PlayerType_e current_player);
bool validate_card(char *entered_value);
Card_t *map_user_input(char *input);
Card_t *pick_card_from_deck(Deck_t **pp_head, Card_t *card_to_be_matched); //Can be included in Card management
error_e remove_card_from_deck(Deck_t **pp_head, Card_t *card_to_be_removed); //Can be included in Card management
error_e record_human_input();
void show_cards_assigned(Card_t assigned_card); 
bool check_is_valid_turn(Card_t *previous_card, Card_t *current_card);
void display_player_deck(Player_t *player);
void display_player_turn(PlayerType_e next_player);
void end_turn(PlayerType_e type);
int quit_game();
error_e handle_human_turn();

//Write for computer as well?
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
    result = add_card_at_end(human_player->cards_on_hand, card);
    return result;
}
/**
 * @brief Throws a warning message if the card dropped by the user is invalid
 * 
 */
void invalid_turn_warning()
{
    printf("!!Warning!! Invalid card - Please choose a valid card \n");
    display_player_deck(human_player);
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

    for (int i = 0; i < size; ++i)
    {
        if (!strcmp(CARD_VALUES[i], entered_value))
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Records the Human player input during his turn and performs appropriate functions 
 * Called each time when it's the human player's turn 
 * Keyboard Input from Human 
 *        Q/q - Exit game
 *        R/r - Requests card 
 *        E/e - End Turn
 *        Other- Map to appropriate Card Info
 */

error_e record_human_input()
{
    char user_input[2];
    printf("Please enter your choice \n");
    scanf("%s", user_input);

    if (user_input[0] == 'q' || user_input[0] == 'Q')
    {
        quit_game();
    }
    else if (user_input[0] == 'r' || user_input[0] == 'R')
    {
        request_card(HUMAN, 1);
    }

    else if (user_input[0] == 'e' || user_input[0] == 'E')
    {
        if (g_card_requested)
        {
            end_turn(g_player_on_turn);
        }
        else
        {
            printf("Please draw a card before you can end your turn");
            display_player_deck(human_player);
        }
    }
    else
    {
        if (validate_card(user_input))
        {
            //To be added if the format of user input is different
            Card_t *human_card_choice = map_user_input(user_input);
            //If valid add the card to the discard_pile
            if (check_is_valid_turn(&g_card_on_table, human_card_choice))
            {
                Deck_t **pp_head = &(human_player->cards_on_hand);

                Card_t *to_remove_card = pick_card_from_deck(pp_head, human_card_choice);

                if (to_remove_card != NULL)
                {
                    ERR_RET(remove_card_from_deck(pp_head, human_card_choice));
                    add_card_at_end(g_discard_pile, *to_remove_card);
                }
            }
        }
        else
        {
            invalid_turn_warning();
        }
    }
    return ERR_SUCCESS;
}
/**
 * @brief Remove a particular card from the given deck
 * Can be used to discard a particular card - during each turn
 * Works for both the computer as well as human deck of cards
 * 
 * @param pp_head 
 * @param card_to_be_removed 
 * @return error_e 
 */
error_e remove_card_from_deck(Deck_t **pp_head, Card_t *card_to_be_removed)
{
    Deck_t *to_delete = *pp_head;
    Deck_t *prev = *pp_head;
    if (*pp_head == NULL)
    {
        printf("List is already empty.");
        return ERR_EMPTY_LIST;
    }
    while (to_delete->next != NULL)
    {
        if (to_delete->card.color == card_to_be_removed->color && to_delete->card.name == card_to_be_removed->name)
        {
            prev->next = to_delete->next;
            free(&(to_delete->card));
            return true;
        }
        to_delete = to_delete->next;
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
 * @param input Value entered by the human during his turn
 * 
 * @return Card_t* Contains the mapped card name and color values
 * If Card_t is NULL it means the input is an invalid one
 */
Card_t *map_user_input(char *input)
{

    Card_t *temp_card = (Card_t *)malloc(sizeof(Card_t));
    temp_card = NULL;

    if (input[0] == 'R')
    {
        temp_card->color = RED;
    }
    else if (input[0] == 'G')
    {
        temp_card->color = GREEN;
    }
    else if (input[0] == 'B')
    {
        temp_card->color = BLUE;
    }

    else if (input[0] == 'Y')
    {
        temp_card->color = YELLOW;
    }
    else
    {
        return temp_card;
    }
    //To map the number part of the User input to the card name field
    temp_card->name = input[0] - '0';
    return temp_card;
}
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
    free(card_to_be_matched); //Check if it can be freed here
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
    printf("The card from the draw pile is %d%d \n", assigned_card.color, assigned_card.name);
    display_player_deck(human_player);
    return;
}

/**
 * @brief Checks if the card dropped by human player during his turn is valid
 *
 * @param previous_card - Card that was dropped previously in the pile
 * @param current_card - Current card dropped by the human player
 * 
 * @return- True if the card is invaid
 *          False if the card is valid
 */
bool check_is_valid_turn(Card_t *previous_card, Card_t *current_card)
{
    bool is_valid = false;
    if (g_discard_pile == NULL)
    {
    }
    if ((previous_card->color == current_card->color) || (previous_card->name == current_card->name))
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
error_e handle_human_turn()
{
    display_player_deck(human_player);
    record_human_input(); //TODO: Handle error here
    return ERR_SUCCESS;
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
 * @brief Displays player's current list of cards
 * 
 * @param player Player whose card list has to be displayed
 */
void display_player_deck(Player_t *player)
{
    display_cards_list(player->cards_on_hand);
}

/**
 * @brief Ends the player turn as requested
 * 
 * @param player - Indicates whether user requested is Human or Computer Player
 */
void end_turn(PlayerType_e type)
{
    printf("Turn ended...\n");
    printf("Computer's Turn now \n");
    //Call computer function to handle its turn
}

/**
 * @brief Ends the Game as requested by the human player 
 *
 * @param PlayerType - Indicates whether user requested is Human or Computer Player
* ~
 */
int quit_game()
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
