
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


#define LINESIZE 1000         /**< LINESIZE to read input */
#define MAX_CARDS_NUM 108

typedef enum playerType{PLAYER, COMPUTER, COMPUTER1, COMPUTER2} Type;
typedef enum direction {CLOCKWISE, COUNTER_CLOCKWISE} Direction;
typedef enum color {RED, BLUE, GREEN, YELLOW, BLACK} Color;
typedef enum card_name {ZERO, ONE, TWO, THREE, FOUR, FIVE,
    SIX, SEVEN, EIGHT, NINE, SKIP, REVERSE, PLUS, WILD} CardName;

/**
 * Card struct.
 */
typedef struct card {
    Color color;      /**< Color code for card */
    CardName name;    /**< Name code for card */
} Card;

/**
 * Deck struct.
 * Linked-list 
 */
typedef struct deck {
    Card card;            /**< The current card this deck holds */
    struct deck * next;   /**< Pointer to the next deck item */
} Deck;

typedef struct player{
    int length;           /**< The length of the deck on the player's hand */
    int score;            /**< Current score */
    Deck *cards;          /**< Pointer to the player's deck on hand */
    Type type;            /**< The current card this deck holds */
}Player;

Player *players;
Card current_card;        /**< last played card on table */
Deck *remaining_pile;     /**< remaining cards to draw */
Deck *discard_pile;       /**< discarded cards */
int currentPosition;      /**< index of current player in turn */
int numPlayers = 2;           /**< number of players */

char *card_name[15] = {"0","1","2","3","4","5","6","7","8","9","Skip",
                       "Reverse", "Plus","Wild"};
char *color[5] = {"Red","Blue","Green","Yellow","Black"};

void free_deck(Deck* d) {
  // Recursively free the deck
  if (d != NULL) {
    free_deck(d->next);
    free(d);
  }
}

int create_cards(int rule){
    // Create all the cards and put them in remaining_pile iteratively
    // If it can't malloc at any point, we will free the deck and return 1
    Card card;
    card.color = RED;
    card.name = ZERO;
    remaining_pile = malloc(sizeof(Deck));
    if (remaining_pile == NULL)
      return 1;
    remaining_pile->card = card;
    remaining_pile->next = malloc(sizeof(Deck));
    Deck *current = remaining_pile->next;
    if (current == NULL) {
      free(remaining_pile);
      return 1;
    }
    for (int i=BLUE;i<=YELLOW ; i++) {
        card.color = i;
        card.name = ZERO;
        current->card = card;
        current->next = malloc(sizeof(Deck));
        current = current->next;
        if (current == NULL) {
          free_deck(remaining_pile);
          return 1;
        }
    }
    for (int i=RED;i<=YELLOW; i++) {
        for (int j=ONE;j<WILD; j++) {
            for (int k = 0; k<= 1; k++) {
                card.color = i;
                card.name = j;
                current->card = card;
                current->next = malloc(sizeof(Deck));
                current = current->next;
                if (current == NULL) {
                  free_deck(remaining_pile);
                  return 1;
                }
            }
        }
    }
    for (int i=PLUS; i<=WILD;i++) {
        for (int j=0; j<4; j++) {
            //If the last element is assigned, make sure that there is no memory spaces assigned to the next deck of the last element of the whole cards
            // Set the last elements's next deck to null
            if(j==3 && i == WILD){
                card.color = BLACK;
                card.name = i;
                current->card = card;
                current->next=NULL;
            }
            else {
                card.color = BLACK;
                card.name = i;
                current->card = card;
                current->next = malloc(sizeof(Deck));
                current = current->next;
                if (current == NULL) {
                  free_deck(remaining_pile);
                  return 1;
                }
            }
        }
    }
    return 0;
}

void swap(Card *a, Card *b) {
    Card temp = *a;
    *a = *b;
    *b = temp;
}

int shuffle(int length) {
    // reset seed
    srand(time(NULL));
    // copy the cards in remaining pile into a Card array
    Deck *current = remaining_pile;
    Card *array = malloc(sizeof(Card)*length);
    if (array==NULL) {
      free_deck(remaining_pile);
      return 1;
    }
    for (int i=0; i<length; i++) {
        array[i] = current->card;
        current = current->next;
    }
    
    // loop through the cards array and swap them randomly, using Fisher-Yates shuffle
    for (int i=0; i<length; i++) {
        // find a random index to swap with the current one
        int random_index = rand() % (length-i) +i;
        swap(&array[random_index],&array[i]);
    }

    // Put cards in array back to the remaining pile in the shuffled order
    current = remaining_pile;
    for (int i=0; i<length-1; i++) {
        current->card = array[i];
        current = current->next;
    }
    //To make sure that there is no memory spaces assigned to the next deck of the last element of the whole cards
    // Set the last elements's next deck to null
    current->card = array[length-1];
    current->next = NULL;
    free(array);
    return 0;
}

void print_card_name(Card a) {
    printf("%s %s\n",card_name[a.name], color[a.color]);
}

void sort(int length) {
  // Copy the cards in the current player's hand into array
  Deck *current = players[currentPosition].cards;
  Card *array = malloc(sizeof(Card)*length);
  for (int i=0; i<length; i++) {
      array[i] = current->card;
      current = current->next;
  }
 }

void drawCard(int numDraw, int currentPosition){
    // Make the current player draw the given number of cards 1 by 1
    for (int i =0; i<numDraw; i++) {
        if(remaining_pile==NULL){
          // If there is no card left in remaining_pile
          // Take all the cards from discard_pile, put them in remaining_pile
          remaining_pile = discard_pile;
          discard_pile = NULL;
          int pile_len = 0;
          Deck *current = remaining_pile;
          while (current != NULL) {
              pile_len++;
              current = current->next;
          }
          // shuffle again
          shuffle(pile_len);
        }
        Deck *current = malloc(sizeof(Deck));
        current->card = remaining_pile->card;
        current->next = players[currentPosition].cards;
        players[currentPosition].cards = current;
        current = remaining_pile;
        remaining_pile = remaining_pile->next;
        free(current);
        players[currentPosition].length++;
    }
    // after drawing, sort the deck again
    sort(players[currentPosition].length);
}

void next_player() {
    
  currentPosition = (currentPosition + 1) % numPlayers;
}

void dealCard(){
  // Deal 5 cards to each player, 1 by 1
  // Use currentPosition and next player to deal card to players in order
  for(int j = 0; j < 5;j++) {
    for (int i = 0; i < numPlayers; i++) {
      if (j==0) {
        players[currentPosition].length++;
        Deck temp = *remaining_pile;
        Deck *current = remaining_pile;
        remaining_pile = remaining_pile->next;
        free(current);
        players[currentPosition].cards = malloc(sizeof(Deck));
        players[currentPosition].cards->card = temp.card;
        players[currentPosition].cards->next = NULL;
        next_player();
      } else {
        drawCard(1,i);
        next_player();
      }
    }
  }
}


int set_up() {
  // Let all players draw 1 card and put it into the bottom of remaining_pile
  discard_pile = NULL;
  Deck *last = remaining_pile;
  while (last->next != NULL) {
    last = last->next;
  }
  for (int i = 0; i < numPlayers; i++) {
    players[i].cards = malloc(sizeof(Deck));
    if (players[i].cards == NULL) {
      for (int j=0; j<i; j++) {
        free_deck(players[j].cards);
      }
      free_deck(remaining_pile);
      return 1;
    }
    players[i].cards->card = remaining_pile->card;
    Deck *previous = remaining_pile;
    remaining_pile = remaining_pile->next;
    previous->next = NULL;
    players[i].cards->next = NULL;
    last->next = previous;
    last = last->next;
  }
  dealCard();
  return 0;
}

int create_players(int num){
  // Allocate an array of players in the heap
  // Number of players is from user input
  numPlayers = num;
  players = malloc(sizeof(Player) * numPlayers);
  if (players == NULL) {
    free_deck(remaining_pile);
    return 1;
  }
  for (int i = 0; i < numPlayers; i++) {
        players[i].length = 0;
        players[i].score = 0;
        
    }
  return set_up();
}


int main() {
  /*//This code to make the random number in the computer will be different, not return to the default
  //So that we could have different array while running the code
  time_t current_time = time(NULL);
  srand(current_time);*/

  create_cards(0);
  shuffle(108);
  create_players(numPlayers);
  int c = 0;
  Deck *current = remaining_pile;
  current_card = remaining_pile->card;
  /*while (current !=NULL) {
    print_card_name(current->card);
    c = c+1;
    current = current->next;
  }
  printf("%d",c);*/
  remaining_pile = remaining_pile->next;
  free(current);
  discard_pile = malloc(sizeof(Deck));
  discard_pile->card = current_card;
  discard_pile->next = NULL;
  printf("Card on table is: ");
  print_card_name(current_card);
  printf("-----------------------------------");
  
  drawCard(1,0);

  for(int i =0; i<numPlayers; i++){
    printf("\nPlayer %d's cards: \n", i);
    printf("------------------\n");
    Deck *current = players[i].cards;
    while (current!=NULL) {
      print_card_name(current->card);
      current = current->next;
    }
    printf("-----------------------------------");
  }
}
