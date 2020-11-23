#include <stddef.h>  
#include <stdlib.h>   
#include <string.h>
#include "cards_management.h"

/**
 * @brief Initializes game which includes initialize cards and initialize players
 *
 * @return int 0 - Initialization is successful;
 *             1 - Initialization is failed, since malloc memory fails
 */
int initialize_game(void)
{
    int result;

    result = initialize_cards();
    initialize_players();
    result += deal_cards();

    return result;
}

/**
 * @brief Initializes players global variables
 *
 */
void initialize_players(void)
{
    for (int i = 0; i < PLAYERS_NUM; i++) {
        players[i].type = (enum PlayerType)i;
        players[i].count = 0;
        players[i].cards_on_hand = NULL;
    }

    return;
}

/**
 * @brief Initializes all the cards status and put them in remaining deck iteratively.
 *        Memeory will be allocated to store all the cards informations.
 *        If it can't malloc at any point, we will free the deck and return FAIL.
 *        initialize discard_cards pointor to be NULL, which indicates no discard cards.
 * @return int  0 - Initialization is successful;
 *             != 0 - Initialization is failed, since malloc memory fails
 */
int initialize_cards(void)
{
    int i, j;
    struct CARD card;
    int result = 0;
    
    draw_pile = (struct DECK*)malloc(sizeof(struct DECK));
    if (draw_pile == NULL) {      
        printf("Unable to allocate memory to initizlize draw_pile.");
        return -1;
    }

    for (i = RED; i <= YELLOW; i++) {
        for (j = ZERO; j <= NINE; j++) {
            card.color = i;
            card.name = j;
            result += add_card_at_beginning(&draw_pile, card);
        }
    }

    discard_pile = (struct DECK*)malloc(sizeof(struct DECK));
    if (discard_pile == NULL) {      
        printf("Unable to allocate memory to initizlize discard pile.");
        return -1;
    }

    return result;
}

/**
 * @brief Deals each player 5 cards at the start of the game setup
 *
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int deal_cards(void)
{
    int i, j;
    struct DECK* dealt_card;
    int result = SUCCESS;

    for (i = 0; i < DEAL_CARDS_NUM; i++) {
        for (j = 0; j < PLAYERS_NUM; j++) {
            dealt_card = remove_first_card_at_beginning(&draw_pile);
            result += add_card_at_beginning(&players[(enum PlayerType)j].cards_on_hand, dealt_card->card);
            players[j].count++;
        }
    }

    return result;
}

/**
 * @brief All the cards are managed in a linked list.
 *        This function is used to add a new card to the remaining cards deck list.
 *
 * @param card The specific card which is added.
 * @return int   0 - Successful;
 *               1 - Failed, since malloc memory fails.
 */
int add_card_at_beginning(struct DECK** head, struct CARD card)
{
    struct DECK* new_card = (struct DECK*)malloc(sizeof(struct DECK));
    if (new_card == NULL) {
        printf("Fail to malloc memory when insert the card.\n");
        return MALLOC_FAIL;
    }

    memcpy(&new_card->card, &card, sizeof(struct CARD));

    new_card->next = *head;
    *head = new_card;

    return 0;
}

/**
 * @brief Creates a new node and adds it at the end of the linked list.
 *
 * @param[in/out] head: pointer which points to the head of the linked list.
 * @param[in] data: int type variable which the data of the new node
 */
int add_card_at_end(struct DECK* head, struct CARD card)
{
    struct DECK* new_card = (struct DECK*)malloc(sizeof(struct DECK));
    if (new_card == NULL) {
        printf("Unable to allocate memory.");
        return -1;
    }

    new_card->card.color = card.color;
    new_card->card.name = card.name;
    new_card->next = NULL;

    while (head != NULL && head->next != NULL) {
        head = head->next;
    }

    head->next = new_card;  /* Add the new node at end */

    //printf("Card (%d, %d) added at end of list successfully.\n", card.color, card.name);
    return 0;
}

/**
 * @brief remove the first card st the beginning of the card list
 * 
 * @param head :poinetr which points to the address of head of card list
 * @return struct DECK* ointer type variable, which points to the removed card 
 */
struct DECK* remove_first_card_at_beginning(struct DECK** head)
{
    struct DECK* to_delete;
    if (*head == NULL) {
        printf("List is already empty.");
        return NULL;
    }

    to_delete = *head;
    *head = (*head)->next; // Mark the second element as first 
    //free(to_delete);       // No need to free the memory occupied by first element, will return it later.

    return to_delete;
}

/**
 * @brief Finds a playable cards from player on hand card list,
 *        which should be has the same color or same name comparing with the on tabe card
 *
 * @param player        enum type variable which indicates the player type
 * @return const DECK*  pointer type variable, which points to the playable card.
 */
struct DECK* find_playable_card(enum PlayerType player)
{
    struct DECK* current = players[player].cards_on_hand;
    if (current == NULL) {
        return NULL;
    }

    while (!is_playable_card(current->card)) {
        if (current->next == NULL) {       /*if it is last node*/
            return NULL;
        }
        else {
            current = current->next;
        }
    }

    return current;
}

/**
 * @brief Displays the detailed card infomation from the card list
 *
 * @param list_ptr The pointer which points to the beginning of the cards list
 */
void display_cards_list(struct DECK* list_ptr)
{
    const struct DECK* temp_list_ptr;
    temp_list_ptr = list_ptr;

    printf("[ ");

    while (temp_list_ptr != NULL) {
        printf("(%d,%d) ", temp_list_ptr->card.color, temp_list_ptr->card.name);
        temp_list_ptr = temp_list_ptr->next;
    }

    printf(" ]\n");
}

/**
 * @brief Gets the listed cards pile length
 *
 * @return int the length of the listed cards pile,
 *         which means how many cards are available in the specific pile.
 */
int get_pile_length(struct DECK* deck_ptr)
{
    int length = 0;
    struct DECK* temp_deck = deck_ptr;

    while (temp_deck != NULL) {
        temp_deck = temp_deck->next;
        length++;
    }

    return length;
}

/**
 * @brief Checks the if there is still have available cads in the specific pile.
 * 
 * @param pile the specific type of pile
 * @return true the pile is empty
 * @return false  the pile is not empty
 */
bool is_pile_empty(enum CardPile pile)
{
    bool is_empty = false;
    
    switch (pile)
    {
        case(DRAW):
            is_empty = draw_pile == NULL? true: false;
            break;
        case(DISCARD):
            is_empty = discard_pile == NULL? true: false;
            break;
        case(HUMAN_PLAYER):
            is_empty = players[0].cards_on_hand == NULL? true: false;
            break;
        case(COMPUTER_PLAYER):
            is_empty = players[1].cards_on_hand == NULL? true: false;
            break;
        default:
            printf("Invalid pile number.\n");
            break;
    }

    return is_empty;
}
    
/**
 * @brief Determins the card is playable or not by comparing the card with current card.
 *        If the color or the name is same, then it's playable
 *
 * @param card The card which needs to be checked is playable or not
 * @return true The card is playable
 * @return false The card is not playable
 */
bool is_playable_card(struct CARD card)
{
    if ((card.color == card_on_table.color) || (card.name == card_on_table.name)) {
        return true;
    }

    return false;
}

/**
 * @brief Sorts the on hand cards for the specific player by
 *        placing the playable card on the top of the player's deck.
 *
 * @param sort_player enum type variable: The specific player needs to sort his/her on hand cards
 * @return int SUCCESS - Successful;
 *             MALLOC_FAIL - Failed because of memory malloc fails
 */
int sort_cards_on_hand(enum PlayerType sort_player)
{
    int i;
    int length = players[sort_player].count;
    int index = 0;

    /*Copy the cards from the current player's hand into array*/
    struct DECK* current = malloc(sizeof(struct DECK));
    if (current == NULL) {
        printf("Fail to malloc memory when sort the on hand cards.\n");
        return MALLOC_FAIL;
    }
    current = players[sort_player].cards_on_hand;

    struct CARD* sorted_cards = malloc(sizeof(struct CARD) * length);
    if (sorted_cards == NULL) {
        printf("Fail to malloc memory when sort the on hand cards.\n");
        free(current);
        return MALLOC_FAIL;
    }

    for (i = 0; i < length; i++)
    {
        sorted_cards[i].color = current->card.color;
        sorted_cards[i].name = current->card.name;
        current = current->next;
    }

    /* Place all the playable cards on the top of the player's deck*/
    for (i = 0; i < length; i++) {
        if (is_playable_card(sorted_cards[i])) {
            swap_cards(&sorted_cards[i], &sorted_cards[index]);
            index++;
        }
    }

    /*Copy the sorted cards to player's on hand deck*/
    current = players[sort_player].cards_on_hand;

    for (i = 0; i < length; i++) {
        current->card = sorted_cards[i];
        current = current->next;
    }

    free(current);
    free(sorted_cards);
    return SUCCESS;
}

/**
 * @brief Swaps the position of card a and card b
 *
 * @param a pointer to card a;
 * @param b pointer to card b;
 */
void swap_cards(struct CARD* a, struct CARD* b)
{
    struct CARD temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief remove the fist playable card in the card list
 * 
 * @param head : pointer which points to the head of the list
 * @return struct DECK* pointer which points to the removed the card
 */
struct DECK *remove_first_playable_card(struct DECK** head)
{
    struct DECK* prev = NULL;
    struct DECK* cur = *head;
    struct CARD removed_card;

    if (*head == NULL) {
        printf("List is already empty.\n");
        return NULL;
    }

    /* Check if head node contains key */
    while ((*head != NULL) 
           && (((*head)->card.color == card_on_table.color) 
               || ((*head)->card.name == card_on_table.name))) {
        removed_card.color = (*head)->card.color;
        removed_card.name = (*head)->card.name;
        prev = *head;          // Get reference of head node
        *head = (*head)->next; // Adjust head node link        
        //free(prev);            // Delete prev since it contains reference to head node
        printf("Successfully deleted the first palyable card (%d, %d) at beginning. \n", removed_card.color, removed_card.name);
        return prev;              // No need to delete further
    }

    /* For each node in the list */
    while (cur != NULL) {
        if ((cur->card.color == card_on_table.color) || (cur->card.name == card_on_table.name)) {         // Current node contains key
            if (prev != NULL) {
                prev->next = cur->next; // Adjust links for previous node
            }
            //free(cur);                  // Delete current node
            printf("Successfully deleted the first palyable card (%d, %d) in the middile. \n", cur->card.color, cur->card.name);
            return cur;
        }

        prev = cur;
        cur = cur->next;
    }

    return NULL;
}

/**
 * @brief The player discards a card,
 *        Firstly to search a playable card in the on hand cards list.
 *        If there is playable card, then cut the first playable card out of player's deck,
 *        update card_on_table globle variable
 *        then place the discarded card into discard deck, and update player's deck length,
 *        setup winner if the last card is discarded from the player
 *
 * @param[in] player enum type variable: The specific player who discards his/her on hand card
 * @param[out] ptr_post_condition pointer which points to int
 *               0 - Discarding card is successful, end of turn, game continues.
 *               1 - Discarding card is successful, end of game, the current player wins the game.
 *               2 - No playable card to discard, end of turn, game continues.
 *               3 - Invalid player.
 * @return int   0 - Successful;
 *               1 - Failed
 */
int discard_card(enum PlayerType player, int* ptr_post_condition)
{
    int result = 1;
    struct CARD draw_card;
    struct DECK* playable_card;
    int post_condition;
             
    if (player_on_turn != player) {
        post_condition = 3;
        *ptr_post_condition = post_condition;
        return 1;
    }
    
    playable_card = find_playable_card(player);
    
    if (NULL == playable_card) { /* If no playable card on hand */
        draw_card = draw_one_card(player);
        printf("No playable card on hand, draw a new card (%d,%d).\n", draw_card.color, draw_card.name);
        if (is_playable_card(draw_card)) {
            memcpy(&card_on_table, &draw_card, sizeof(struct CARD));
            result = add_card_at_end(discard_pile, card_on_table);
            post_condition = 0;
        } else {
            result += add_card_at_end(players[player].cards_on_hand, draw_card);
            post_condition = 2;
        }
    } else { /*If there is playable card, then remove the first playable card from on hand cards list*/
        struct DECK* discard_card = remove_first_playable_card(&players[player].cards_on_hand);
        memcpy(&card_on_table, &discard_card->card, sizeof(struct CARD));
        printf("discard card on table is (%d, %d)\n", discard_card->card.color, discard_card->card.name);
        result = add_card_at_end(discard_pile, card_on_table);
        players[player].count--;
        post_condition = 0;
    }

    if (players[player].count == 0) {
        game_winner = player;
        post_condition = 1;
    }

    *ptr_post_condition = post_condition;
    return result;
}

/**
 * @brief Draws the requested number of cards from the remaining deck for the current player
 *        If there is no cards left in the remaining deck, then place all the cards from discard deck
 *        into the remaining deck.
 *
 * @param num_draw_cards number of draw cards
 * @param player enum type variable: The specific player who draws the cards
 * @return int   0 - Successful;
 *               1 - Failed.
 */
int draw_cards(int num_draw_cards, enum PlayerType player)
{
    int i;
    const struct DECK* draw_card;
    const struct DECK* temp_deck;
    int result = 1;

    for (i = 0; i < num_draw_cards; i++)
    {
        if (draw_pile == NULL)
        {
            while (discard_pile != NULL) {
                temp_deck = remove_first_card_at_beginning(&discard_pile);
                result += add_card_at_end(draw_pile, temp_deck->card);
            }
        }

        draw_card = remove_first_card_at_beginning(&draw_pile);
        result = add_card_at_beginning(&players[player].cards_on_hand, draw_card->card);
    }

    return result;
}

/**
 * @brief Draws one cards from the remaining deck for the current player
 *        If there is no cards left in the remaining deck, then place all the cards from discard deck
 *        into the remaining deck, then get it.
 *
 * @param player enum type variable: The specific player who draws the card
 * @return Card  the drew card
 */
struct CARD draw_one_card(enum PlayerType player)
{
    const struct DECK* draw_deck;
    const struct DECK* temp_deck;
    int result = 1;

    if (draw_pile == NULL)
    {
        while (discard_pile != NULL) {
            temp_deck = remove_first_card_at_beginning(&discard_pile);
            result += add_card_at_end(draw_pile, temp_deck->card);
        }
    }

    draw_deck = remove_first_card_at_beginning(&draw_pile);
    return draw_deck->card;
}

/**
 * @brief Gets the game winner
 *
 * @return PlayerType The winner of the game
 */
enum PlayerType get_game_winner(void)
{
    return game_winner;
}

/*#################################### Test Functions ####################################*/
int test_initialize_cards(void)
{
    int result = initialize_cards();
    int length = get_pile_length(draw_pile);
    if ((0 == result) && (length == MAX_CARDS_NUM)) {
        printf("initialize_cards......successful!\n");
    }

    return result;
}

int test_deal_cards(void)
{
    initialize_players();
    int result = deal_cards();
    int length = get_pile_length(draw_pile);
    if ((0 == result)
        && (length == (MAX_CARDS_NUM - DEAL_CARDS_NUM * PLAYERS_NUM))
        && (players[0].count == DEAL_CARDS_NUM)
        && (players[1].count == DEAL_CARDS_NUM)) {
        printf("deal_cards......successful!\n");
    }

    printf(" Human Player Cards List: ");
    display_cards_list(players[HUMAN].cards_on_hand);
    printf("\n Computer Player Cards List:");
    display_cards_list(players[COMPUTER].cards_on_hand);

    return result;
}

int test_sort_cards_on_hand(void)
{
    int result;
    card_on_table.color = RED;
    card_on_table.name = FIVE;

    result = sort_cards_on_hand(HUMAN);
    result += sort_cards_on_hand(COMPUTER);

    printf("\n\n-------Sorts on hand cards-------");
    printf("\n The last card on the table: (%d, %d) \n", card_on_table.color, card_on_table.name);
    printf("\n Human Player Cards List: ");
    display_cards_list(players[HUMAN].cards_on_hand);
    printf("\n Computer Player Cards List: ");
    display_cards_list(players[COMPUTER].cards_on_hand);

    return result;
}

void no_card_discarded(void)
{
    card_on_table.color = RED;
    card_on_table.name = EIGHT;
    player_on_turn = HUMAN;
}

void card_discarded_from_one_hand_list(void)
{
    card_on_table.color = RED;
    card_on_table.name = NINE;
    player_on_turn = HUMAN;
}

int test_discard_card(int test_case)
{
    int result;
    int discard_post_condition = -1;

    if (initialize_game()) {
        printf(" Initialize game failed! \n");
    }
    
    switch (test_case)
    {
        case (1):
            no_card_discarded();
            break;
        case (2):
            card_discarded_from_one_hand_list();
            break;
        default:
            break;
    }
    
    printf("\n************* Discard Card Test %d*************\n", test_case);
    printf("Before Discarding Card: \n");
    printf(" Player on turn is %d. (HUMAN_PLAYER = 0; COMPUTER_PLAYER = 1)\n", player_on_turn);
    printf(" The card on table: (%d, %d) \n", card_on_table.color, card_on_table.name);
    printf(" HUMAN_PLAYER Cards List: ");
    display_cards_list(players[HUMAN].cards_on_hand);
    printf(" COMPUTER_PLAYER Cards List: ");
    display_cards_list(players[COMPUTER].cards_on_hand);

    printf("\nAfter Discarding Card: \n");
    if (0 == discard_card(HUMAN, &discard_post_condition)) {
        printf("  HUMAN_PLAYER discard cards successful with post condition of %d. \n", discard_post_condition);  
    } else {
        printf("  HUMAN_PLAYER discard cards failed with post condition of %d. \n", discard_post_condition);
    }
    printf("  HUMAN_PLAYER Cards List: ");
    display_cards_list(players[HUMAN].cards_on_hand);

    if (0 == discard_card(COMPUTER, &discard_post_condition)) {
        printf("\n  COMPUTER_PLAYER discards card successful with post condition of %d. \n", discard_post_condition);  
    } else {
        printf("\n  COMPUTER_PLAYER discards card failed with post condition of %d. \n", discard_post_condition);
    }
    printf("  COMPUTER_PLAYER Cards List: ");
    display_cards_list(players[COMPUTER].cards_on_hand);

    return result;
}

int test_draw_cards(void)
{
    card_on_table.color = BLUE;
    card_on_table.name = NINE;

    int result;
    printf("\n------- Draw Cards-------\n");
    printf("Before......");
    display_cards_list(players[HUMAN].cards_on_hand);
    result = draw_cards(2, HUMAN);

    printf("After.......");
    display_cards_list(players[HUMAN].cards_on_hand);
    printf("\nThe last card on the table: (%d, %d) \n", card_on_table.color, card_on_table.name);
    printf("Then sort card.......");
    result += sort_cards_on_hand(HUMAN);
    display_cards_list(players[HUMAN].cards_on_hand);

    return result;
}


int main(void)
{
    int result = 0;

    printf("--------------- Start the Test ---------------\n");
    //result = test_initialize_cards();
    //result += test_deal_cards();
    //result += test_sort_cards_on_hand();
    for (int i = 0; i< 2; i++)
    {
        result += test_discard_card(i);
    }
    //result += test_draw_cards();
    return result;
}