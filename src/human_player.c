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

ret_type_e record_human_input(void);
Card_t map_user_input(const char* user_input);
CardType_e get_card_type(Card_t card);
int request_card(PlayerType_e PlayerType, int no_of_cards);
void invalid_card_warning(void);
void show_cards_assigned(Card_t assigned_card);
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
        printf("!!Warning!! Please draw a card before you can end your turn.\n");
        display_player_deck(HUMAN);
    }

    return ret;
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
    //Check if the card is from the human player deck
    if (!is_human_card(human_card_choice))
    {
        printf("!!Warning!! Please select a card from your deck! \n");
        invalid_card_warning();
        return RET_INVALID_CARD;
    }

    //If valid add the card to the discard_pile
    if (!is_playable_card(human_card_choice))
    {
        invalid_card_warning();
        return RET_NOT_PLAYABLE_CARD;
    }

    remove_card_from_deck(&g_players[HUMAN].cards_on_hand, human_card_choice);
    add_card_at_end(g_discard_pile, human_card_choice);
    memcpy(&g_card_on_table, &human_card_choice, sizeof(Card_t));
    end_turn(HUMAN);
    g_card_requested = false;
    return RET_SUCCESS;
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
    if (RET_SUCCESS == human_process_normal_card(human_card_choice))
    {
        //Next turn will be Human turn
        g_player_on_turn = HUMAN;
        ret = player_process_draw_one_card(HUMAN);
        printf("%s discarded a Draw-One card, COMPUTER player will lose turn.\n", g_human_player_name);
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
    if (RET_SUCCESS == human_process_normal_card(human_card_choice))
    {
        //Next turn will be Human turn
        g_player_on_turn = HUMAN;
        printf("%s discarded a Skip card, COMPUTER player will lose turn.\n", g_human_player_name);
        return RET_SUCCESS;
    }

    return RET_FAILURE;  
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

    if (colornum == 'R') {
        *color_changed = RED;
    }
    else if (colornum == 'G') {
        *color_changed = GREEN;
    }
    else if (colornum == 'B') {
        *color_changed = BLUE;
    }
    else if (colornum == 'Y') {
        *color_changed = YELLOW;
    }
    else
    {
        printf("!!Warning!! Choose a valid color (R/B/G/Y) \n");
        return RET_INVALID_INPUT;
    }
    return RET_SUCCESS;
}

/**
 * @brief human player discards a action card - Wild
 *
 * @param human_card_choice  the human player card choice
 * @param color_changed human play choose the color to be changed
 * @return ret_type_e: RET_SUCCESS on success;
 *                     RET_INVALID_INPUT on invalid input
 *                     RET_INVALID_CARD on the card is unavailbe in player deck
 */
ret_type_e human_process_wild_card(Card_t human_card_choice, CardColor_e color_changed)
{
    //If valid add the card to the discard_pile
    if (!is_human_card(human_card_choice))
    {
        printf("!!Warning!! Please select a card from your deck! \n");
        return RET_INVALID_CARD;
    }

    remove_card_from_deck(&(g_players[HUMAN].cards_on_hand), human_card_choice);
    add_card_at_end(g_discard_pile, human_card_choice);

    //update g_card_on_table
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
    if (RET_SUCCESS == human_process_wild_card(human_card_choice, color_changed))
    {
        //Next turn will be Human turn
        g_player_on_turn = HUMAN;
        ret = player_process_wild_draw_two_card(HUMAN);
        printf("%s discarded a Wild-Draw-Twe card, COMPUTER player will lose turn.\n", g_human_player_name);
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
 * @brief Get the card type by card info
 *
 * @param card The specific card info
 * @return CardType_e the mapped card type.
 *
 */
CardType_e get_card_type(Card_t card)
{
    CardType_e card_type = INVALID_TYPE;
    switch (card.name)
    {
        case ZERO:
        case TWO:
        case THREE:
        case FOUR:
        case FIVE:
        case SIX:
        case SEVEN:
        case EIGHT:
        case NINE:
            card_type = NORMAL;
            break;
        case SKIP:
        case DRAW_ONE:
        case WILD:
        case WILD_DRAW_TWO:
            card_type = card.name - 9;
            break;
        default:
            break;
    }

    return card_type;
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
    else
    {
        return human_process_card(user_input);
    }

    return RET_FAILURE;
}

/**
 * @brief human player discards a card
 *
 * @param human_card_choice  the human player card choice
 * @return ret_type_e: RET_SUCCESS on successful;
 *                     RET_INVALID_INPUT on invalid input
 */
ret_type_e human_process_card(const char* user_input)
{
    CardColor_e color_changed;

    Card_t human_card_choice = map_user_input(user_input);
    if ((human_card_choice.color == INVALID_COLOR) || (human_card_choice.name == INVALID_NAME))
    {
        return RET_INVALID_INPUT;
    }

    CardType_e card_type = get_card_type(human_card_choice);
    switch (card_type)
    {
        case NORMAL:
            return human_process_normal_card(human_card_choice);
        case SKIP_T:
            return human_process_skip_card(human_card_choice);
        case DRAW_ONE_T:
            return human_process_draw_one_card(human_card_choice);
        case WILD_T:
            if (RET_SUCCESS == card_color_change_inquiry(&color_changed)) {
                return human_process_wild_card(human_card_choice, color_changed);
            } else {
                return RET_INVALID_INPUT;
            }
        case WILD_DRAW_TWO_T:
            if (RET_SUCCESS == card_color_change_inquiry(&color_changed)) {
                return human_process_wild_draw_two_card(human_card_choice, color_changed);
            }
            else {
                return RET_INVALID_INPUT;
            }
        case INVALID_TYPE:
        default:
            return RET_FAILURE;
    }
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
