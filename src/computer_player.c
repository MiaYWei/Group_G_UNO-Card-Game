// computer algrithm for hard level computer
//
// features:
// - Count cards on the table, record all the played card                                               (x)
// - Quickly get rid of matched numbers in the hand.                                                    (x)
// - Keeping at most one Wild Card until the very end.                                                  (x)
// - use reverse card when you have no card to play                                                     (x)
// - Play series of similar color cards first, use draw 2 card,                                         (x)
//   skip card, or reverse card first based on the most color that computer has                         (x)
// - When playing a Wild Card +4, always change the color based on what the computer has the most       (x)
// - Try to keep at least one +2 card in your hand.         (x)                                         (x)
// - Play higher number cards first to get more points      (x)                                         (x)
// - Note the last card color when players have one card left and avoid to play it.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "../include/cards_management.h"
#include "../include/computer_player.h"
#include "../include/game.h"
#include "../include/console_print.h"

/*
* @brief: variadic function that returns the max of given numbers
*
* @param: number of args
* @return int the max value
*/
int get_max(int n, ...) {
    int max_value = INT_MIN;
    int temp;
    va_list list;
    va_start(list, n);

    for (int i = 0; i < n; i++){
        temp = va_arg(list, int);
        if (max_value < temp){
            max_value = temp;
        }
    }
    va_end(list);
    return max_value;
}

/*
* @brief: function that find the most occurrence with the color
*
* @param: pointer to the head of handcard list
* @return CardColor the color with moset occurrence
*/
CardColor_e  find_most_color(Deck_t** cards_on_hand)
{
    int R_count = 0, G_count = 0, B_count = 0, Y_count = 0, most = 0, least = 0;
    Deck_t* temp = *cards_on_hand;

    if (*cards_on_hand == NULL)
    {
        printf("hand card is empty!");
        return INVALID_COLOR;
    }
    while (temp != NULL)
    {
        if (temp->card.color == RED){
            R_count++;
        }
        else if (temp->card.color == BLUE){
            B_count++;
        }
        else if (temp->card.color == GREEN){
            G_count++;
        }
        else if (temp->card.color == YELLOW){
            Y_count++;
        }
        temp = temp->next;
    }
    if (get_max(4, R_count, G_count, B_count, Y_count) == R_count){
        return RED;
    }
    else if (get_max(4, R_count, G_count, B_count, Y_count) == B_count){
        return BLUE;
    }
    else if (get_max(4, R_count, G_count, B_count, Y_count) == G_count){
        return GREEN;
    }
    else if (get_max(4, R_count, G_count, B_count, Y_count) == Y_count){
        return YELLOW;
    }

    return INVALID_COLOR;
}

/*
* @brief: function that find the largest number of given color
*
*
* @param pointer to the pointer to the head of handcard list, color that need to be checked
* @return CardName the largest number
*/
CardName_e find_largest_number(Deck_t** handcard, CardColor_e inputCardColor)
{
    Deck_t* temp = *handcard;
    CardName_e Max = ZERO;

    // Check loop while head not equal to NULL
    while (temp != NULL) {
        // If max is less then head->data then
        // assign value of head->data to max
        // otherwise node point to next node.
        if ((temp->card.name != SKIP) && (temp->card.name != DRAW_ONE)
            && (temp->card.name != WILD_DRAW_TWO) && (temp->card.name != WILD)){
            Max = temp->card.name;
        }
        temp = temp->next;
    }

    return Max;
}

/*
* @brief: function that find the occruence of a number
*
* @param pointer to the pointer to the head of handcard list, number that needs to be checked
* @return int number count for occruence
*/
int find_occurence_of_number(Deck_t** hand_card, CardName_e input_card_number)
{
    Deck_t* temp = *hand_card;
    int count = 0;
    while (temp != NULL){
        if (temp->card.name == input_card_number){
            count++;
        }
        temp = temp->next;
    }
    return count;
}

/*
* @brief: function that find the occruence of a color
*
* @param pointer to the pointer to the head of handcard list, color that needs to be checked
* @return int number count for occruence
*/
int find_occurence_of_color(Deck_t** hand_card, CardColor_e input_card_color)
{
    Deck_t* temp = *hand_card;
    int count = 0;
    while (temp != NULL){
        if (temp->card.color == input_card_color){
            count++;
        }
        temp = temp->next;
    }
    return count;
}

/*
* @brief: function that find the most color occruence of a given number
*
*
* @param pointer to the pointer to the head of handcard list, name that need to be checked
* @return CardColor  most color occruence of a given number
*
*/
CardColor_e find_color_with_most_occurence(Deck_t** hand_card, CardName_e input_card_name)
{
    Deck_t* temp = *hand_card;
    CardColor_e most_color_with_number = INVALID_COLOR;
    struct colorInfo colors[4];
    int i = 0,max = INT_MIN;

    while (temp != NULL){
        if (temp->card.name == input_card_name){
            colors[i].color = temp->card.color;
            colors[i].count = find_occurence_of_color(hand_card, temp->card.color);
            i = i + 1;
        }
        temp = temp->next;
    }
    for (int n = 0; n < i; n++) {
        if (colors[n].count > max) {
            max = colors->count;
            most_color_with_number = colors[n].color;
        }
    }
    return most_color_with_number;
}

/*
* @brief: function that get the matched color in the list for the given number
*
*
* @param pointer to the pointer to the head of handcard list, name that need to be checked
* @return CardColor  the matched color
*
*/
CardColor_e find_matched_color(Deck_t** hand_card, CardName_e card_name)
{
    Deck_t* temp = *hand_card;
    while (temp != NULL) {
        if (temp->card.name == card_name) {
            return temp->card.color;
        }
        temp = temp->next;
    }
    return -1;
}

/*
* @brief: function that find address within the list of a given card
*
*
* @param pointer to the pointer to the head of handcard list, card that need to be checked
* @return DECK * the address of that card
*
*/
Deck_t* find_address(Deck_t** head, Card_t card) 
{
    Deck_t* temp = *head;
    if (card.name == WILD){
        while (temp != NULL){
            if (temp->card.name == WILD){
                return temp;
            }
            temp = temp->next;
        }
    }
    else if (card.name == WILD_DRAW_TWO){
        while (temp != NULL){
            if (temp->card.name == WILD_DRAW_TWO){
                return temp;
            }
            temp = temp->next;
        }
    }
    else {
        while (temp != NULL) {
            if (temp->card.name == card.name && temp->card.color == card.color){
                return temp;
            }
            temp = temp->next;
        }
    }

    return temp;
}

/* function that choose the right card to draw */
/*
* @brief: function that choose the right card to draw
*          if player card # > 1
*           case 1 : no matched color and no matched number
*             - if have wild card, draw wild if wild card > with color with the most occurence
*             - if have skip, use skip
*             - if not have wild or skip, take card from pile
*            case 2 : have the matched color and no matched number
*             - choose the largest number on that color
*             - if matched color > 3, use match draw/draw2/skip card based on the color with the most occurence
*
*            case 3 : no matched color, but have matched number
*             - if have multiple, choose the color with the most occurence and corresponding action card
*             - if have only one, get rid of it
*
*            case 4 : have matched color and match number
*             - quickly get rid of matched numbers in the hand first.
*             - if occurence of
*
*         if player card # = 1
*            - use action card if possibile
*            - avoid play the last color that the player played
*
* @param Card that will be evaluated, pointer to the head of handcard list
* @return int the case number
*/
casenumber_e pick_case(Card_t card, Deck_t** hand_card)
{
    Deck_t* ptr1 = *hand_card, * ptr2 = *hand_card;
    int commonColor = 0, commonName = 0;
    while (ptr1 != NULL){
        if (ptr1->card.color == card.color){
            commonColor = 1;
        }
        ptr1 = ptr1->next;
    }

    while (ptr2 != NULL){
        if (ptr2->card.name == card.name){
            commonName = 1;
        }
        ptr2 = ptr2->next;
    }
    if (commonColor && commonName){
        return CASE4;
    }
    else if (!commonColor && commonName){
        return CASE3;
    }
    else if (commonColor && !commonName){
        return CASE2;
    }
    else if (!commonColor && !commonName){
        return CASE1;
    }
    else{
        return INVALID_CASE;
    }
}

/** @brief Pick the best card to discard from hand cards based on
 *         the newest card on the table.
 *         if it is an action card:
 *              - if it is a draw/draw2 card and number of the card of the color of that draw/draw2 card < 2,
 *                use wild card if possible to change to color
 *              - if it is a wild card, play the corresponding color
 *              - if do not have the corresponding color, draw card
 *         if opponent player has more than one card # > 1:
 *          case 1 : no matched color and no matched number
 *              - if have more than one wild card, play wild card with color with the most occurence
 *              - if have skip, use skip card
 *              - if don't have wild or skip, draw card from pile
 *          case 2 : have the matched color and no matched number
 *              - choose the largest number on that color to make opponent lose more point
 *              - if matched color > 2, use match draw/draw2/skip card based on the color with
 *                the most occurence
 *              - if card on table is Draw/Draw2, draw card 
 *          case 3 : no matched color, but have matched number
 *              - if have multiple matched number, choose the color with the most occurence
 *                or corresponding action card
 *              - if have only one matched number with different card, get rid of it
 *          case 4 : have both matched color and match number
 *              - Quickly get rid of matched numbers in the hand.
 *
 *          if opponent player has one card left:
 *              - use action card if possibile
 *              - avoid play the last color that the player played
 *
 *  @return A best cooresponding card from hand cards, or call an action (draw card)
 */
Deck_t* pick_card(Card_t input_card, Deck_t** hand_card)
{
    int color_count = 0, number_count = 0;
    CardColor_e most_color;
    Deck_t* play_card = NULL;
    Card_t playable_card;
    Deck_t* temp = *hand_card;
    Card_t wild_card = { ACTION, WILD };
    Card_t wild_draw_two_card = { ACTION, WILD_DRAW_TWO };
    Card_t case2_card = { input_card.color, DRAW_ONE };

    casenumber_e caseNum = pick_case(input_card, hand_card);
    most_color = find_most_color(hand_card);

    switch (caseNum){
        case CASE1: /* no matched color or number, check if wild or wild-draw-two*/
            if (is_exist_card(*hand_card, wild_card) == 1){
                play_card = find_address(hand_card, wild_card);
                play_card->card.color = most_color;
                return play_card;
            }
            else if (is_exist_card(*hand_card, wild_draw_two_card) == 1){
                play_card = find_address(hand_card, wild_draw_two_card);
                play_card->card.color = most_color;
                return play_card;
            }
            else{
                return NULL;
            }
        case CASE2: /* check if occurence of the color > 2, play DRAW if true*/
            while (temp != NULL){
                if (input_card.color == temp->card.color)
                {
                    color_count++;
                }
                temp = temp->next;
            }
            if (color_count > 2 && is_exist_card(*hand_card, case2_card)){
                playable_card.name = DRAW_ONE;
            }
            else{
                CardName_e Max = find_largest_number(hand_card, input_card.color);
                playable_card.name = Max;
            }
            playable_card.color = input_card.color;
            play_card = find_address(hand_card, playable_card);
            return play_card;
        case CASE3: /* no matched color, but have matched number */
            number_count = find_occurence_of_number(hand_card, input_card.name);
            if (number_count == 1){
                playable_card.color = find_matched_color(hand_card, input_card.name);
            }
            else{
                playable_card.color = find_color_with_most_occurence(hand_card, input_card.name);
            }
            playable_card.name = input_card.name;
            play_card = find_address(hand_card, playable_card);
            return play_card;
        case CASE4: /* have matched color, and have matched number */
            if (input_card.color == find_most_color(hand_card)){
                playable_card.name = find_largest_number(hand_card, input_card.color);
                playable_card.color = input_card.color;
            }
            else{
                playable_card.color = find_color_with_most_occurence(hand_card, input_card.name);
                playable_card.name = input_card.name;
            }
            play_card = find_address(hand_card, playable_card);
            return play_card;
        default:
            printf("entered default!\n");
            break;
    }

    return play_card;
}

/*
* @brief: after play a card, computer will check if the drawed card is playable
*
* @param card color, hand card list 
* @return 1 for successed, 0 for failed
*/
bool check_after_action(CardColor_e color, Deck_t** hand_card) 
{
    if (find_occurence_of_color(hand_card, color) != 0){
        return true;
    }
    else{
        return false;
    }
}

/*
* @brief: function that play card from handcard list
*
* @param card address, reference to the hand card list
* @return 1 for successed, 0 for failed
*/
Deck_t* play_card(const Deck_t* card_address, Deck_t** head)
{
    Deck_t* temp = *head;
    Deck_t* prev = *head;
    if (*head == NULL){
        printf("List is already empty.\n");
        return NULL;
    }

    if (card_address == NULL){
        printf("Drawed One card \n");
        return NULL;
    }

    if (card_address->card.name == WILD){
        while ((temp != NULL) && (temp->card.name == WILD)){
            *head = temp->next;
            return temp;
        }
        /* For each node in the list */
        while ((temp != NULL) && ((temp->card.name != WILD))){
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            return NULL;
        }
        prev->next = temp->next;
        return temp;
    }
    else{
        // head node
        while ((temp != NULL) && (temp->card.name == card_address->card.name) && (temp->card.color == card_address->card.color)){
            *head = temp->next;
            return temp;
        }
        /* For each node in the list */
        while ((temp != NULL) && ((temp->card.name != card_address->card.name) || (temp->card.color != card_address->card.color))){
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) {
            return NULL;
        }
        prev->next = temp->next;
        return temp;
    }
}

/**
 * @brief Computer player discards a playable card
 *
 * @param card the card to be process by computer
 */
void process_playable_card(Card_t card)
{
    Card_t original_card;
    memcpy(&g_card_on_table, &card, sizeof(Card_t));
    
    if ((card.name == WILD) || (card.name == WILD_DRAW_TWO))
    {
        original_card.color = ACTION;
        original_card.name = card.name;
        printf("COMPUTER dropped..(%s,%s). ", CARD_COLOR_STRING[ACTION], CARD_NAME_STRING[card.name]);
        printf("Color changed to %s\n", CARD_COLOR_STRING[card.color]);
        add_card_at_end(g_discard_pile, original_card);
    }
    else{
        printf("COMPUTER dropped..(%s,%s)\n", CARD_COLOR_STRING[card.color], CARD_NAME_STRING[card.name]);
        add_card_at_end(g_discard_pile, g_card_on_table);
    }
    
    end_turn(COMPUTER);
    if (card.name == SKIP) {
        print_info("COMPUTER discarded a Skip card, HUMAN will lose turn.\n");
        g_player_on_turn = COMPUTER;
    }
    else if (card.name == DRAW_ONE) {
        g_player_on_turn = COMPUTER;
        player_process_draw_one_card(COMPUTER);
    }
    else if (card.name == WILD_DRAW_TWO) {
        g_player_on_turn = COMPUTER;
        player_process_wild_draw_two_card(COMPUTER);
    }
    return;
}

/**
 * @brief Computer requests a new card when it has no playable card on hand
 *
 * @return int 0 - The new drawn card is playable;
 *             1 - The new drawn card is not playable, and be added to player cards on hand list;
 */
int computer_process_request_card(void)
{
    int result = -1;
    Card_t draw_card = draw_one_card();
    printf("COMPUTER draws a new card from the pile. \n");
    if (is_playable_card(draw_card)) {
        process_playable_card(draw_card);
        result = 0;
    }
    else {
        add_card_at_end(g_players[COMPUTER].cards_on_hand, draw_card);
        end_turn(COMPUTER);
        result = 1;
    }

    return result;
}

/**
 * @brief Computer player discards a playable card
 *
 * @param   reference to the playable card in th list, reference to hand card list
 * 
 */
void computer_process_playable_card(Deck_t* playable_card)
{
    Deck_t* discard_card = play_card(playable_card, &g_players[COMPUTER].cards_on_hand);
    process_playable_card(discard_card->card);

    return;
}

/**
 * @brief Logic to discard card for computer player,
 *        1.Firstly search for a playable card in the on hand cards list.
 *        2.If there is playable card, then remove the first playable card out of player's deck,
 *        update card_on_table global variable
 *        then place the discarded card into discard deck, and update player's deck length,
 *        3.If there is no playable card, draw a card from the draw pile and again check if it's playable.
 *        If yes, goto step 2. If no, end turn.
 *        4.Set winner if the last card is discarded from the player
 *
 * @return int   0 - Discarding card is successful, end of turn, game continues.
 *               1 - No playable card to discard, end of turn, game continues.
 */
int computer_take_turn(void)
{
    int result = 0;
    Deck_t* playable_card;

    playable_card = pick_card(g_card_on_table, &g_players[COMPUTER].cards_on_hand);

    if (g_players[COMPUTER].cards_on_hand->next == NULL){
        printf("Computer Palyer: UNO !!!\n");
    }

    if (playable_card == NULL){ /* If no playable card on hand */
        return computer_process_request_card();  
    }
    else{   /*If there is playable card, then remove playable card from on hand cards list*/
        computer_process_playable_card(playable_card);
        return 0;
    }

    return result;
}