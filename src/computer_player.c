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
//
// input :
// - card on the table (for update and play)
// - if player "UNO"
// - card drawed from the deck

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cards_management.h"

#define MAX 40
#define hand_MAX 20
#define plarCardNumber 10

/* (not used for now) */
struct CARD record_array[MAX]; // array for recording all the cards
int record_size = 0, handcard_size = 0;

void record(struct CARD card)
{
    record_size++;
    record_array[record_size - 1] = card;
}

/* 
* @brief: function that find the most occurrence with the color 
* 
* @return CardColor the color with moset occurrence
*/
enum CardColor  find_most_color(struct DECK *cards_on_hand)
{
    int R_count = 0, G_count = 0, B_count = 0, Y_count = 0, most = 0, least = 0;
    struct DECK *temp;
    struct DECK *head = cards_on_hand;
    if (head == NULL)
    {
        printf("hand card is empty!");
        return 0;
    }
    temp = head;
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
        else
        {
            Y_count++;
        }
        temp = temp->next;
    }
    if (R_count > B_count && R_count > G_count && R_count > Y_count)
    {
        return RED;
    }
    else if (B_count > R_count && B_count > G_count && B_count > Y_count)
    {
        return BLUE;
    }
    else if (G_count > R_count && G_count > B_count && G_count > Y_count)
    {
        return GREEN;
    }
    else if (Y_count > R_count && Y_count > B_count && Y_count > G_count)
    {
        return YELLOW;
    }

    return 0;
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
* @return int the case number
*/


int pick_case(struct CARD card, struct DECK *hand_card)
{
    struct DECK *ptr1 = hand_card, *ptr2 = hand_card;
    int commonColor = 0, commonName = 0;
    while (ptr1 != NULL) {
        if (card.color == ptr1->card.color) {
            commonColor = 1;
        }
        ptr1 = ptr1->next;
    }
    while (ptr2 != NULL) {
        if (card.name == ptr2->card.name) {
            commonName = 1;
        }
        ptr2 = ptr2->next;
    }
    if (commonColor && commonName) {
        return 4;
    }
    else if (!commonColor && commonName) {
        return 3;
    }
    else if (commonColor && !commonName) {
        return 2;
    }
    else if (!commonColor && !commonName) {
        return 1;
    }
    return 0;
}

/*
* @brief: function that play card from handcard list
*
* @return void
*/
void play_card(struct CARD card, struct DECK **head)
{
    struct DECK *prev = *head;
    struct DECK *temp = *head;
    // head node
    if (temp != NULL && temp->card.name == card.name && temp->card.color == card.color)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->card.name == card.name && temp->card.color == card.color)
    {
        prev = temp;
        temp = temp->next;
    }
    // if not present
    if (temp == NULL)
        return;

    // delete
    prev->next = temp->next;

    free(temp);
}
/*
* @brief: function that check if a card exist in the handcard deck
*
* @return 1 exist, 0 not exist
*/

int ifexists(struct DECK **handcard, enum CardName inputCardName, enum CardColor inputCardColor)
{
    struct DECK *ptr = *handcard;
    while (ptr->next != NULL)
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
* @return CardName the largest number
*/

enum CardName find_largest_number(struct DECK **handcard, enum CardColor inputCardColor)
{
    struct DECK *temp = *handcard;
    enum CardName Max = ZERO;


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
* @return int number count for occruence
*/

int find_occurence_of_number(struct DECK **handcard, enum CardName inputCardNumber)
{
    struct DECK *temp = *handcard;
    int count = 0;
    while (temp != NULL)
    {
        if (temp->card.name == inputCardNumber)
        {
            count++;
        }
        temp = temp->next;
    }
    free(temp);
    return count;
}

/*
* @brief: function that find the most color occruence of a given number
*
* @return CardColor  most color occruence of a given number
*
*/

enum CardColor find_color_with_most_occurence(struct DECK **handcard, enum CardName inputCardNumber)
{
    struct DECK *temp = *handcard;
    int R_count=0, B_count=0, Y_count=0, G_count=0;
    while (temp != NULL)
    {
        if (temp->card.name == inputCardNumber)
        {
            if (temp->card.color == RED)
            {
                R_count++;
            }
            else if (temp->card.color == BLUE)
            {
                B_count++;
            }
            else if (temp->card.color == YELLOW)
            {
                Y_count++;
            }
            else
            {
                G_count++;
            }
        }
        temp = temp->next;

    }
    if (R_count > B_count && R_count > G_count && R_count > Y_count)
    {
        return RED;
    }
    else if (B_count > R_count && B_count > G_count && B_count > Y_count)
    {
        return BLUE;
    }
    else if (G_count > R_count && G_count > B_count && G_count > Y_count)
    {
        return GREEN;
    }
    else if (Y_count > R_count && Y_count > B_count && Y_count > G_count)
    {
        return YELLOW;
    }
    return 0;
 }


/*
* @brief: function that add one card at the end of the handcard list 
*
* @return void
*
*/
void push(struct DECK** head, struct CARD card) {
    struct DECK* newNode = (struct DECK*)malloc(sizeof(struct DECK));
    struct DECK* last = *head;

    newNode->card = card;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = newNode;
    return;
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

void pick_action(struct CARD inputCard, struct DECK *hand_card)
{
    int wildCount= 0, colorCount=0, numberCount=0;
    char most_color;
    char choosed_color;
    struct CARD playCard, DrawCard;
    struct DECK *temp = hand_card;
    int caseNum = pick_case(inputCard, hand_card);
    most_color = find_most_color(hand_card);
    switch (caseNum)
    {
    case 1:
        /* no matched color or number, check if wild is > */
        while (temp->next != NULL)
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
            choosed_color = most_color;
            playCard.name = WILD;
            playCard.color = choosed_color;
            play_card(playCard, &hand_card);
        }
        else
        {
            if (inputCard.name == WILD)
            {
                // draw_cards(4, COMPUTER_PLAYER); 
            }
            else if (inputCard.name == FDRAW2)
            {
                // draw_cards(2, COMPUTER_PLAYER);
            }
            else
            {
                DrawCard = draw_one_card();
                push(&hand_card, DrawCard);
            }
        }
        break;
    case 2:
        /* check if occurence of the color > 2, play DRAW/DRAW2 if true*/
        colorCount = 0;
        while (temp->next != NULL)
        {
            if (inputCard.color == temp->card.color)
            {
                colorCount++;
            }
            temp = temp->next;
        }
        if (colorCount > 2 && ifexists(&hand_card, FDRAW, inputCard.color))
        {
            playCard.name = FDRAW;
            playCard.color = inputCard.color;
            play_card(playCard, &hand_card);
        }
        else if (colorCount > 2 && ifexists(&hand_card, FDRAW2, inputCard.color))
        {
            playCard.name = FDRAW2;
            playCard.color = inputCard.color;
            play_card(playCard, &hand_card);
        }
        else
        {
            enum CardName Max = find_largest_number(&hand_card, inputCard.color);
            playCard.name = Max;
            playCard.color = inputCard.color;
            play_card(playCard, &hand_card);
        }
        break;
    case 3:
        /* no matched color, but have matched number */
        numberCount = find_occurence_of_number(&hand_card, inputCard.name);
        if (numberCount == 1)
        {
            playCard.name = inputCard.name;
            playCard.color = inputCard.color;
            play_card(playCard, &hand_card);
        }
        else
        {
            playCard.color = find_color_with_most_occurence(&hand_card,inputCard.name);
            playCard.name = inputCard.name;
            play_card(playCard, &hand_card);
        }
        break;
    case 4:
        /* have matched color, and have matched number */
        
        if(inputCard.color == find_most_color(hand_card)){
            playCard.name = find_largest_number(&hand_card, inputCard.color);
            playCard.color = inputCard.color;
            play_card(playCard, &hand_card);
        }else{
            playCard.color = find_color_with_most_occurence(&hand_card,inputCard.name);
            playCard.name = inputCard.name;
            play_card(playCard, &hand_card);
        }
        break;
    default:
        printf("entered default!\n");
        break;
    }
}


/*********************** test functions ********************************/

int test_find_most_color(struct DECK* head) {
    enum CardColor color;
    color = find_most_color(head);

    if (color == RED) {
        return 1;
    }
    return 0;
}

int test_pick_case(struct DECK* head, struct CARD card, int n) {
    int CaseNumber;

    CaseNumber = pick_case(card, head);
    if (CaseNumber == n) {
        return 1;
    }
    return 0;
}

int test_ifexists(struct DECK** head, struct CARD card, int n) {
    int result;
    result = ifexists(head, card.name, card.color);
    if (result == n) {
        return 1;
    }
    return 0;
}

int test_find_largest_number(struct DECK** handcard, enum CardColor color,enum CardName name) {
    enum CardName Max;
    Max = find_largest_number(handcard, color);  
    if (Max == name) {
        return 1;
    }
    return 0;
}

int test_find_occurence_of_number(struct DECK** handcard, enum CardName inputCardNumber, int n) {
    int occurence = 0;
    occurence = find_occurence_of_number(handcard, inputCardNumber);
    if (occurence == n) {
        return 1;
    }
    return 0;

}

int test_find_color_with_most_occurence(struct DECK** handcard, enum CardName inputCardNumber, enum CardColor Final_color) {
    enum CardColor color;
    color = find_color_with_most_occurence(handcard, TWO);
    if (color == Final_color) {
        return 1;
    }
    return 0;
}

#if 0
int main()
{

    /* define cards*/
    struct CARD card1 = { RED, ONE }, card2 = { RED, TWO }, card3 = { GREEN, FIVE }, card4 = { BLACK, WILD }, card5 = { GREEN, TWO }, card6 = { YELLOW, FOUR }, card7 = { RED, EIGHT };
    struct CARD testCard1 = { BLUE, SIX }, testCard2 = { GREEN , SEVEN }, testCard3 = { BLUE, FIVE }, testCard4 = { RED,FOUR };
    /* define hand card list */
    struct DECK * hand_card_list = NULL;
    push(&hand_card_list, card1);
    push(&hand_card_list, card2);
    push(&hand_card_list, card3);
    push(&hand_card_list, card4);
    push(&hand_card_list, card5);
    push(&hand_card_list, card6);
    push(&hand_card_list, card7);
    display_cards_list(hand_card_list);

    printf("\n\n");
    printf("****************** function test *******************\n");
    if (test_find_most_color(hand_card_list)) {
        printf("find_most_color Passed !\n");
    }
 
    if (test_pick_case(hand_card_list, testCard1, 1)) {
        printf("pick_case CASE 1 Passed ! \n");
    }
    if (test_pick_case(hand_card_list, testCard2, 2)) {
        printf("pick_case CASE 2 Passed ! \n");
    }
    if (test_pick_case(hand_card_list, testCard3, 3)) {
        printf("pick_case CASE 3 Passed ! \n");
    }
    if (test_pick_case(hand_card_list, testCard4, 4)) {
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

    if (test_find_occurence_of_number(&hand_card_list, TWO, 2)) {
        printf("find_occurence_of_number Passed ! \n");
    }

    if (test_find_color_with_most_occurence(&hand_card_list, TWO, RED)) {
        printf("find_color_with_most_occurence Passed ! \n");
    }

    initialize_cards();
    printf("\n\n");
    printf("****************** Pick_Case test *******************\n");
    printf("CASE 1: NO MATCH COLOR/NUMBER \n");
    display_cards_list(hand_card_list);
    pick_action(testCard1, hand_card_list);
    display_cards_list(hand_card_list);
}
#endif