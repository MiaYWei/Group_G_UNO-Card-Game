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

#define hand_MAX 20
#define plarCardNumber 10

///* (not used for now) */
//struct CARD record_array[MAX]; // array for recording all the cards
//int record_size = 0, handcard_size = 0;
//
//void record(struct CARD card)
//{
//    record_size++;
//    record_array[record_size - 1] = card;
//}

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

    for (int i = 0; i < n; i++) {
        temp = va_arg(list, int);
        if (max_value < temp) {
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
        return 0;
    }
    while (temp != NULL)
    {
        if (temp->card.color == RED)
        {
            R_count++;
        }
        else if (temp->card.color == BLUE)
        {
            B_count++;
        }
        else if (temp->card.color == GREEN)
        {
            G_count++;
        }
        else if (temp->card.color == YELLOW)
        {
            Y_count++;
        }
        temp = temp->next;
    }
    if (get_max(4, R_count, G_count, B_count, Y_count) == R_count)
    {
        return RED;
    }
    else if (get_max(4, R_count, G_count, B_count, Y_count) == B_count)
    {
        return BLUE;
    }
    else if (get_max(4, R_count, G_count, B_count, Y_count) == G_count)
    {
        return GREEN;
    }
    else if (get_max(4, R_count, G_count, B_count, Y_count) == Y_count)
    {
        return YELLOW;
    }

    return 0;
}

/*
* @brief: function that check if a card exist in the handcard deck
*
*
* @param: pointer to the pointer to the head of handcard list, card that needs to be checked
* @return 1 exist, 0 not exist
*/
int ifexists(Deck_t** handcard, CardName_e inputCardName, CardColor_e inputCardColor)
{
    Deck_t* ptr = *handcard;
    while (ptr != NULL)
    {
        if (ptr->card.name == inputCardName && ptr->card.color == inputCardColor)
        {
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
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
    while (temp != NULL)
    {

        // If max is less then head->data then
        // assign value of head->data to max
        // otherwise node point to next node.
        if (temp->card.color == inputCardColor && Max < temp->card.name)
        {
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
int find_occurence_of_number(Deck_t** handcard, CardName_e inputCardNumber)
{
    Deck_t* temp = *handcard;
    int count = 0;
    while (temp != NULL)
    {
        if (temp->card.name == inputCardNumber)
        {
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
int find_occurence_of_color(Deck_t** handcard, CardColor_e inputCardcolor)
{
    Deck_t* temp = *handcard;
    int count = 0;
    while (temp != NULL)
    {
        if (temp->card.color == inputCardcolor)
        {
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
CardColor_e find_color_with_most_occurence(Deck_t** handcard, CardName_e inputCardNumber)
{
    Deck_t* temp = *handcard;
    CardColor_e most_color_with_number;
    struct colorInfo colors[4];
    int i = 0, max = INT_MIN;

    while (temp != NULL)
    {
        if (temp->card.name == inputCardNumber)
        {
            colors[i].color = temp->card.color;
            colors[i].count = find_occurence_of_color(handcard, temp->card.color);
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
CardColor_e find_matched_color(Deck_t** handcard, CardName_e number) {
    Deck_t* temp = *handcard;

    while (temp != NULL) {
        if (temp->card.name == number) {
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
Deck_t* find_address(Deck_t** head, Card_t CARD) {
    Deck_t* temp = *head;
    if (CARD.name == WILD) {
        while (temp != NULL) {
            if (temp->card.name == WILD) {
                return temp;
            }
            temp = temp->next;
        }
    }
    else {
        while (temp != NULL) {
            if (temp->card.name == CARD.name && temp->card.color == CARD.color) {
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
    Deck_t* ptr1 = *hand_card, * ptr2 = *hand_card, * ptr3 = *hand_card;
    int commonColor = 0, commonName = 0;
    if (card.name == WILD) {
        while (ptr3 != NULL) {
            if (ptr3->card.color == card.color) {
                return CASE2;
            }
            ptr3 = ptr3->next;
        }
        return CASE1;

    }
    while (ptr1 != NULL) {
        if (ptr1->card.color == card.color) {
            commonColor = 1;
        }
        ptr1 = ptr1->next;
    }

    while (ptr2 != NULL) {
        if (ptr2->card.name == card.name) {
            commonName = 1;
        }
        ptr2 = ptr2->next;
    }
    if (commonColor && commonName) {
        return CASE4;
    }
    else if (!commonColor && commonName) {
        return CASE3;
    }
    else if (commonColor && !commonName) {
        return CASE2;
    }
    else if (!commonColor && !commonName) {
        return CASE1;
    }
    free(ptr1);
    free(ptr2);
    free(ptr3);
    return 0;
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
Deck_t* pick_card(Card_t inputCard, Deck_t** hand_card)
{
    int wildCount = 0, colorCount = 0, numberCount = 0;
    CardColor_e most_color;
    Deck_t* playCard = NULL, * NULLCARD = NULL;
    Card_t playableCard;

    Deck_t* temp = *hand_card;
    enum casenumber caseNum = pick_case(inputCard, hand_card);
    most_color = find_most_color(hand_card);
    //if (temp->next->next = NULL) {
    //    playableCard.name = WILD;
    //    playCard = find_address(hand_card, playableCard);
    //    playCard->card.color = most_color;
    //}
    switch (caseNum)
    {
    case CASE1:
        /* no matched color or number, check if wild is > */
        while (temp != NULL)
        {
            if (temp->card.name == WILD)
            {
                wildCount++;
            }
            temp = temp->next;
        }

        /* if wild card >1, play the WILD with color with the most occurence */
        if (wildCount > 1)
        {

            playableCard.name = WILD;
            playCard = find_address(hand_card, playableCard);
            playCard->card.color = most_color;

            return playCard;
        }
        else
        {

            return NULL;
        }
        break;
    case CASE2:
        /* check if occurence of the color > 2, play DRAW if true*/
        colorCount = 0;
        while (temp != NULL)
        {
            if (inputCard.color == temp->card.color)
            {
                colorCount++;
            }
            temp = temp->next;
        }
        if (colorCount > 2 && ifexists(hand_card, DRAW_ONE, inputCard.color))
        {
            playableCard.name = DRAW_ONE;
            playableCard.color = inputCard.color;
            playCard = find_address(hand_card, playableCard);
            return playCard;
        }
        else
        {
            CardName_e Max = find_largest_number(hand_card, inputCard.color);
            playableCard.name = Max;
            playableCard.color = inputCard.color;
            playCard = find_address(hand_card, playableCard);
            return playCard;
        }
        break;
    case CASE3:
        /* no matched color, but have matched number */
        numberCount = find_occurence_of_number(hand_card, inputCard.name);
        if (numberCount == 1)
        {

            playableCard.name = inputCard.name;
            playableCard.color = find_matched_color(hand_card, inputCard.name);
            playCard = find_address(hand_card, playableCard);
            return playCard;

        }
        else
        {
            playableCard.color = find_color_with_most_occurence(hand_card, inputCard.name);
            playableCard.name = inputCard.name;
            playCard = find_address(hand_card, playableCard);
            return playCard;
        }
        break;
    case CASE4:
        /* have matched color, and have matched number */

        if (inputCard.color == find_most_color(hand_card)) {
            playableCard.name = find_largest_number(hand_card, inputCard.color);
            playableCard.color = inputCard.color;
            playCard = find_address(hand_card, playableCard);
            return playCard;
        }
        else {
            playableCard.color = find_color_with_most_occurence(hand_card, inputCard.name);
            playableCard.name = inputCard.name;
            playCard = find_address(hand_card, playableCard);
            return playCard;
        }
        break;
    default:
        printf("entered default!\n");
        break;
    }

    return playCard;
}

/*
* @brief: function that play card from handcard list
*
* @param card that will be played, pointer to the pointer to the head of handcard list
* @return 1 for successed, 0 for failed
*/
Deck_t* play_card(const Deck_t* cardAddress, Deck_t** head)
{
    Deck_t* temp = *head;
    Deck_t* prev = *head;
    if (*head == NULL)
    {
        printf("List is already empty.\n");
        return NULL;
    }

    if (cardAddress == NULL) {
        printf("Drawed One card \n");
        return NULL;
    }

    if (cardAddress->card.name == WILD) {
        // head node
        while ((temp != NULL) && (temp->card.name == WILD))
        {
            *head = temp->next;

            return temp;
        }
        /* For each node in the list */
        while ((temp != NULL) && ((temp->card.name != WILD)))
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return NULL;
        prev->next = temp->next;
        //printf("Successfully deleted WILD card (%s, %s). \n", CARD_COLOR_STRING[temp->card.color], CARD_NAME_STRING[temp->card.name]);
        return temp;

    }
    else {
        // head node
        while ((temp != NULL) && (temp->card.name == cardAddress->card.name) && (temp->card.color == cardAddress->card.color))
        {

            *head = temp->next;

            return temp;
        }
        /* For each node in the list */
        while ((temp != NULL) && ((temp->card.name != cardAddress->card.name) || (temp->card.color != cardAddress->card.color)))
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return NULL;
        prev->next = temp->next;
        printf("Successfully deleted  card (%s, %s). \n", CARD_COLOR_STRING[temp->card.color], CARD_NAME_STRING[temp->card.name]);
        return temp;

    }
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
    //For test only
    //printf("Computer dect: ");
    //display_player_deck(COMPUTER);
    playable_card = pick_card(g_card_on_table, &g_players[COMPUTER].cards_on_hand);

    if (playable_card == NULL)
    { /* If no playable card on hand */
        draw_card = draw_one_card();

        printf("Computer draws a new card from the draw pile \n");
        //printf("No playable card on hand, drawing a new card from deck (%s,%s).\n", CARD_COLOR_STRING[draw_card.color], CARD_NAME_STRING[draw_card.name]);//TODO Remove this line after testing
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
        Deck_t* discard_card = play_card(playable_card, &g_players[COMPUTER].cards_on_hand);
        printf("Computer Drops..(%s, %s)\n", CARD_COLOR_STRING[discard_card->card.color], CARD_NAME_STRING[discard_card->card.name]);
        memcpy(&g_card_on_table, &discard_card->card, sizeof(Card_t));
        add_card_at_end(g_discard_pile, g_card_on_table);
        result = 0;
    }

    if (g_players[COMPUTER].cards_on_hand->next == NULL) {
        printf("Computer Palyer: UNO !!!\n");
    }

    return result;
}

/*********************** test functions ********************************/
int test_find_most_color(Deck_t* head) {
    CardColor_e color = find_most_color(&head);

    if (color == RED) {
        return 1;
    }
    return 0;
}

int test_pick_case(Deck_t** head, Card_t card, int n) {
    int CaseNumber;

    CaseNumber = pick_case(card, head);
    if (CaseNumber == n) {
        return 1;
    }
    return 0;
}

int test_ifexists(Deck_t** head, Card_t card, int n) {
    int result;
    result = ifexists(head, card.name, card.color);
    if (result == n) {
        return 1;
    }
    return 0;
}

int test_find_largest_number(Deck_t** handcard, CardColor_e color, CardName_e name) {
    CardName_e Max;
    Max = find_largest_number(handcard, color);
    if (Max == name) {
        return 1;
    }
    return 0;
}

int test_find_occurence_of_number(Deck_t** handcard, CardName_e inputCardNumber, int n) {
    int occurence = 0;
    occurence = find_occurence_of_number(handcard, inputCardNumber);
    if (occurence == n) {
        return 1;
    }
    return 0;
}

int test_find_occurence_of_color(Deck_t** handcard, CardColor_e inputCardColor, int n) {
    int occurence = 0;
    occurence = find_occurence_of_color(handcard, inputCardColor);
    if (occurence == n) {
        return 1;
    }
    return 0;
}

int test_find_color_with_most_occurence(Deck_t** handcard, CardName_e inputCardNumber, CardColor_e Final_color) {
    CardColor_e color;
    color = find_color_with_most_occurence(handcard, inputCardNumber);
    if (color == Final_color) {
        return 1;
    }
    return 0;
}
void append(Deck_t** head_ref, Card_t card) {
    /* 1. allocate node */

    Deck_t* new_card = (Deck_t*)malloc(sizeof(Deck_t));
    struct DECK* last = *head_ref;  /* used in step 5*/

    /* 2. put in the data  */
    new_card->card.color = card.color;
    new_card->card.name = card.name;
    new_card->next = NULL;


    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = new_card;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_card;
    return;
}


#if 0
int main()
{

    /* define cards*/
    struct CARD card1 = { RED, ONE }, card2 = { RED, FIVE }, card3 = { GREEN, FIVE }, card4 = { BLACK, WILD }, card5 = { GREEN, TWO }, card6 = { YELLOW, FOUR }, card7 = { RED, NINE };
    struct CARD testCard1 = { BLUE, SIX }, testCard2 = { GREEN , SEVEN }, testCard3 = { BLUE, FIVE }, testCard4 = { BLUE, ONE }, testCard5 = { GREEN, FOUR }, testWILD = { BLUE, WILD }, testDRAW = { BLUE, DRAWONE };

    /* define hand card list */
    struct DECK* hand_card_list = NULL, * played = NULL;
    struct DECK* ptr = NULL;
    append(&hand_card_list, card1);
    append(&hand_card_list, card2);
    append(&hand_card_list, card3);
    append(&hand_card_list, card4);
    append(&hand_card_list, card5);
    append(&hand_card_list, card6);
    append(&hand_card_list, card7);
    display_cards_list(hand_card_list);
    /* ptr = find_address(&hand_card_list, card4);
     printf("card is (%s,%s) \n", CARD_COLOR_STRING[ptr->card.color], CARD_NAME_STRING[ptr->card.name]);
     played = play_card(ptr, &hand_card_list);
     played->card.color = RED;
     printf("card is (%s,%s) \n", CARD_COLOR_STRING[ptr->card.color], CARD_NAME_STRING[ptr->card.name]);
     display_cards_list(hand_card_list);*/

     /*rintf("\n\n");
     printf("****************** function test *******************\n");
     if (test_find_most_color(&hand_card_list)) {
         printf("find_most_color Passed !\n");
     }

     if (test_pick_case(&hand_card_list, testCard1, CASE1)) {
         printf("pick_case CASE 1 Passed ! \n");
     }
     if (test_pick_case(&hand_card_list, testCard2, CASE2)) {
         printf("pick_case CASE 2 Passed ! \n");
     }
     if (test_pick_case(&hand_card_list, testCard3, CASE3)) {
         printf("pick_case CASE 3 Passed ! \n");
     }
     if (test_pick_case(&hand_card_list, testCard5, CASE4)) {
         printf("pick_case CASE 4 Passed ! \n");
     }

     if (test_ifexists(&hand_card_list, card1, 1)) {
         printf("ifexists EXIST Passed ! \n");
     }
     if (test_ifexists(&hand_card_list, testCard1, 0)) {
         printf("ifexists NOT EXIST Passed ! \n");
     }

     if (test_find_largest_number(&hand_card_list, RED, EIGHT)) {
         printf("find_largest_number TEST1 Passed ! \n");
     }
     if (test_find_largest_number(&hand_card_list, GREEN, FIVE)) {
         printf("find_largest_number TEST2 Passed ! \n");
     }

     if (test_find_occurence_of_number(&hand_card_list, FIVE, 2)) {
         printf("find_occurence_of_number Passed ! \n");
     }

     if (test_find_occurence_of_color(&hand_card_list, RED, 3)) {
         printf("find_occurence_of_color Passed ! \n");
     }

     if (test_find_color_with_most_occurence(&hand_card_list, FIVE, RED)) {
         printf("find_color_with_most_occurence Passed ! \n");
     }

     initialize_cards();*/
    printf("\n\n");
    printf("****************** Pick_action test *******************\n");
    /* PASSED
    printf("CASE 1: NO MATCH COLOR/NUMBER && WILD > 1 \n");
    display_cards_list(hand_card_list);
    printf("DRAW WILD \n");

    played = play_card(pick_card(testCard1, &hand_card_list), &hand_card_list);
    printf("card is (%s,%s) \n", CARD_COLOR_STRING[played->card.color], CARD_NAME_STRING[played->card.name]);
    display_cards_list(hand_card_list); */

    //PASSED
    //printf("CASE 1: NO MATCH COLOR/NUMBER && WILD <= 1 \n");
    //display_cards_list(hand_card_list);
    //play_card(pick_card(testWILD, &hand_card_list), &hand_card_list);
    //display_cards_list(hand_card_list);

    //PASSED
    //printf("\n\n");
    //printf("CASE 2: MATCH COLOR, no matche number \n");
    //display_cards_list(hand_card_list);
    //printf("input Card [GREEN , 7], play [GREEN, 5] \n");
    //play_card(pick_card(testCard2, &hand_card_list), &hand_card_list);
    //display_cards_list(hand_card_list);

    //PASSED
    //printf("\n\n");
    //printf("CASE 3: No MATCH COLOR, match number \n");
    //display_cards_list(hand_card_list);
    //printf("input Card [BLUE, 5], play [GREEN, 5] \n");
    //play_card(pick_card(testCard3, &hand_card_list), &hand_card_list);
    //display_cards_list(hand_card_list);

    //PASSED
    //printf("\n\n");
    //printf("CASE 4:   MATCH COLOR, MATCH NUMBER  \n");
    //display_cards_list(hand_card_list);
    //printf("input Card [GREEN,4], play [YELLOW, 4] \n");
    //play_card(pick_card(testCard5, &hand_card_list), &hand_card_list);
    //display_cards_list(hand_card_list);
}

#endif