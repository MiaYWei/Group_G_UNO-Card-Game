#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/cards_management.h"
#include "../include/human_player.h"
#include "../include/game.h"
#include "../include/console_print.h"

/* Global variables */
bool g_card_requested = false;

ret_type_e record_human_input(void);
Card_t map_user_input(const char* user_input);
int request_card(PlayerType_e PlayerType);
void invalid_card_warning(void);
bool is_human_card(Card_t current_card);
ret_type_e card_color_change_inquiry(CardColor_e* color_changed);
ret_type_e human_process_card(const char* user_input);
ret_type_e human_process_end_turn_request(void);
ret_type_e human_process_new_card_request(void);
ret_type_e human_process_normal_card(Card_t human_card_choice);
ret_type_e human_process_skip_card(Card_t human_card_choice);
ret_type_e human_process_draw_one_card(Card_t human_card_choice);
ret_type_e human_process_wild_card(Card_t human_card_choice, CardColor_e color_changed);
ret_type_e human_process_wild_draw_two_card(Card_t human_card_choice, CardColor_e color_changed);
int quit_game(void);

/**
 * @brief Function called when the human player requests a card during each turn
 * 
 * Assigns the top most card/cards in the draw pile to the user
 *
 * @param PlayerType - Indicates whether user requested is Human or Computer Player
 * @return int 0 - Successful;
 *             1 - Failed due to error in malloc;
 * 
 */
int request_card(PlayerType_e PlayerType)
{
    g_card_requested = true;
    Card_t card = draw_one_card();
    printf("The card from the draw pile is (%s,%s), it's added to Human player deck. \n", CARD_COLOR_STRING[card.color], CARD_NAME_STRING[card.name]);

    //Assigning the drawn card to the human player
    return add_card_at_end(g_players[HUMAN].cards_on_hand, card);
}

/**
 * @brief Throws a warning message if the card dropped by the user is invalid
 * 
 */
void invalid_card_warning(void)
{
    print_warning("!!Warning!! Invalid card - Please choose a valid card. \n");
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
    if (g_card_requested){
        g_card_requested = false;
        end_turn(HUMAN);
        return RET_SUCCESS;
    }
    else {
        print_warning("!!Warning!! Please draw a card('n' or 'N'), then you can end your turn.\n");
        return RET_FAILURE;
    }
}

/**
 * @brief human player discards a normal card 
 *
 * @param human_card_choice  the human player card choice
 * @return ret_type_e: RET_SUCCESS on successful;
 *                     RET_INVALID_CARD on invalid input
 *                     RET_NOT_PLAYABLE_CARD on not playable card
 */
ret_type_e human_process_normal_card(Card_t human_card_choice)
{   
    //If valid add the card to the discard_pile
    if (!is_playable_card(human_card_choice)){
        invalid_card_warning();
        return RET_NOT_PLAYABLE_CARD;
    }

    if (remove_card_from_deck(&g_players[HUMAN].cards_on_hand, human_card_choice)){
        add_card_discard_pile(human_card_choice);
        memcpy(&g_card_on_table, &human_card_choice, sizeof(Card_t));
        end_turn(HUMAN);
        g_card_requested = false;
        return RET_SUCCESS;
    }
    else{
        print_warning("!!Warning!! Remove Card Failed! \n");
        return RET_FAILURE;
    }
}

/**
 * @brief human player discards a action card - Draw one
 *
 * @param human_card_choice  the human player card choice
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_INVALID_CARD on invalid input
 */
ret_type_e human_process_draw_one_card(Card_t human_card_choice)
{
    int ret = RET_FAILURE;
    if (RET_SUCCESS == human_process_normal_card(human_card_choice)){
        //Next turn will be Human turn
        g_player_on_turn = HUMAN;
        ret = player_process_draw_one_card(HUMAN);
    }

    return ret;
}

/**
 * @brief human player discards a action card - Skip
 *
 * @param human_card_choice  the human player card choice
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_INVALID_CARD on invalid input
 */
ret_type_e human_process_skip_card(Card_t human_card_choice)
{
    if (RET_SUCCESS == human_process_normal_card(human_card_choice)){
        //Next turn will be Human turn
        g_player_on_turn = HUMAN;
        print_info("Human player dropped a Skip card, Computer player loses turn.\n");
        return RET_SUCCESS;
    }

    return RET_FAILURE;  
}

/**
 * @brief human player requests a new card
 *
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_FAILURE on failure
 */
ret_type_e human_process_new_card_request(void)
{
    if (g_card_requested){
        print_warning("!!Warning!! You've already requested a new card. Please discard card or end turn('e' or 'E') now. \n");
        return RET_FAILURE;
    }
    else{
        return request_card(HUMAN);
    }
}

/**
 * @brief Inquire a card color change when player discards a Wild card or Wild-Draw-Two card
 * 
 * @param color_changed pointer which points to choose the color to be changed
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_INVALID_INPUT on invalid input
 */
ret_type_e card_color_change_inquiry(CardColor_e* color_changed)
{
    char colornum = ' ';
    *color_changed = INVALID_COLOR;

    printf("Please enter your choice for the color changing. (R/B/G/Y)\n");
    scanf(" %c", &colornum);

    if (colornum == 'R'){
        *color_changed = RED;
    }
    else if (colornum == 'G'){
        *color_changed = GREEN;
    }
    else if (colornum == 'B'){
        *color_changed = BLUE;
    }
    else if (colornum == 'Y'){
        *color_changed = YELLOW;
    }
    else{
        print_warning("!!Warning!! Choose a valid color (R/B/G/Y) \n");
        return RET_INVALID_INPUT;
    }
    return RET_SUCCESS;
}

/**
 * @brief human player discards a  Wild action card
 *
 * @param human_card_choice  the human player card choice
 * @param color_changed human player chooses the color to be changed
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_INVALID_INPUT on invalid input
 *                     RET_INVALID_CARD on the card is unavailbe in player deck
 */
ret_type_e human_process_wild_card(Card_t human_card_choice, CardColor_e color_changed)
{
    remove_card_from_deck(&(g_players[HUMAN].cards_on_hand), human_card_choice);
    add_card_discard_pile(human_card_choice);
    //update the card on table
    g_card_on_table.color = color_changed;
    g_card_on_table.name = human_card_choice.name;

    //End turn
    end_turn(HUMAN);
    g_card_requested = false;
    return RET_SUCCESS;
}

/**
 * @brief human player discards a action card - Wild-Draw-Two
 *
 * @param human_card_choice  the human player card choice
 * @param color_changed human play choose the color to be changed
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_INVALID_CARD on invalid input
 */
ret_type_e human_process_wild_draw_two_card(Card_t human_card_choice, CardColor_e color_changed)
{
    int ret = RET_FAILURE;
    if (RET_SUCCESS == human_process_wild_card(human_card_choice, color_changed)){
        //Next turn will be Human turn
        g_player_on_turn = HUMAN;
        ret = player_process_wild_draw_two_card(HUMAN);
    }

    return ret;
}
/**
 * @brief  Function to map the human player input to Card type structure
 * 
 * @details Should be called only after validation of the user input
 * If user input is 3R, It will be mapped as follows
 *  card.color=Red, card.name=3
 *
 * @param user_input: pointer to the value entered by the human during his turn 
 * @return Card_t:  the mapped card name and color values
 *         
 */
Card_t map_user_input(const char* user_input)
{
    int i = 0;
    int m = sizeof(USER_INPUT_COLOR) / sizeof(USER_INPUT_COLOR[0]);
    int n = sizeof(USER_INPUT_NAME) / sizeof(USER_INPUT_NAME[0]);
    
    Card_t invalid_card = { INVALID_COLOR, INVALID_NAME };
    Card_t card = { INVALID_COLOR, INVALID_NAME };

    if (user_input == NULL){
        return invalid_card;
    }

    //maps the card color
    for (i = 0; i < m; i++){
        if (user_input[0] == USER_INPUT_COLOR[i]){
            card.color = i;
            break;
        }
    }

    //maps the card name only if the card color is valid.
    for (i = 0; i < n; i++){
        if (user_input[1] == USER_INPUT_NAME[i]){
            card.name = i;
            break;
        }
    }
    
    return card;
}

/**
 * @brief Records the Human player input during his turn and performs appropriate functions  
 * 
 * @details This function is called each time during the human player's turn to process the input given. 
 * Keyboard Input from Human 
 *        Q/q - Exit game
 *        n/N - Requests card 
 *        E/e - End Turn
 *        Other- Map to appropriate card Info
 * 
 * * @return ret_type_e: RET_SUCCESS on success;
 *                       RET_INVALID_INPUT on invalid input;
 *                       RET_FAILURE on failure
 */
ret_type_e record_human_input(void)
{
    char user_input[10]; 
    printf("Please enter your choice \n");
    scanf("%s", user_input);

    if (user_input[0] == 'q' || user_input[0] == 'Q'){
        if (confirm_exit()){
            quit_game();
        }
    }
    else if (user_input[0] == 'n' || user_input[0] == 'N'){
        return human_process_new_card_request();
    }
    else if (user_input[0] == 'e' || user_input[0] == 'E'){
        return human_process_end_turn_request();
    }
    else{
        return human_process_card(user_input);
    }

    return RET_FAILURE;
}

/**
 * @brief Function to handle the discarded card by the human player
 *
 * @param human_card_choice  the human player card choice
 * @return ret_type_e: RET_SUCCESS on successful;
 *                     RET_INVALID_INPUT on invalid input
 */
ret_type_e human_process_card(const char* user_input)
{
    ret_type_e ret = RET_FAILURE;
    CardColor_e color_changed;
    Card_t human_card_choice = map_user_input(user_input);
    printf("You selected: (%s, %s).\n", CARD_COLOR_STRING[human_card_choice.color], CARD_NAME_STRING[human_card_choice.name]);
    if ((human_card_choice.color == INVALID_COLOR) || (human_card_choice.name == INVALID_NAME)){
        print_warning("!!Warning!! Invalid Input - Please enter a valid choice. \n");            
        return RET_INVALID_INPUT;
    }

    CardType_e card_type = get_card_type(human_card_choice);
    //Check if the card is from the human player deck
    if (!is_human_card(human_card_choice)){
        print_warning("!!Warning!! Please select a card from your deck! \n");
        return RET_INVALID_CARD;
    }

    switch (card_type){
        case NORMAL:
            return human_process_normal_card(human_card_choice);
        case SKIP_T:
            return human_process_skip_card(human_card_choice);
        case DRAW_ONE_T:
            return human_process_draw_one_card(human_card_choice);
        case WILD_T:
            while (ret != RET_SUCCESS){
                ret = card_color_change_inquiry(&color_changed);
            }
            return human_process_wild_card(human_card_choice, color_changed);
        case WILD_DRAW_TWO_T:
            while (ret != RET_SUCCESS) {
                ret = card_color_change_inquiry(&color_changed);
            }
            return human_process_wild_draw_two_card(human_card_choice, color_changed);
        case INVALID_TYPE:
        default:
            return RET_FAILURE;
    }
}

/**
 * @brief Checks if the card dropped by human player during his turn actually belongs to his deck of cards
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

    while (temp != NULL){
        if (temp->card.color == current_card.color && temp->card.name == current_card.name){
            return true;
        }

        temp = temp->next;
    }

    return false;
}

/**
 * @brief Ends the Game as requested by the human player
 * 
 * @return int 0 - To quit the game
 */
int quit_game(void)
{
    print_info("HUMAN player requested to quit the current. Exiting the game..");
    exit(0);
}
