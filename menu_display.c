#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <windows.h>
#include <windef.h>
#include <winnt.h>
#include <winbase.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
void startScreen()
{
    printf("***************************************************************\n");
    printf("*                                                             *\n");
    printf("*                 UNO EXPRESS                                 *\n");
    printf("*                                                             *\n");
    printf("*                  group   G                                  *\n");
    printf("*                                                             *\n");
    printf("***************************************************************\n");

}

void start()
{
    printf("Game Started\n");
    printf("press any key..");

    fflush(stdin); // option ONE to clean stdin
    getchar(); 
}
void rules()
{
    printf("UNO EXPRESS RULES: \n\n");
    printf("Object of the game \n");
    printf("************************\n");
    printf("Be the first player to get rid of all of your cards in each round and score points for the cards your opponents are left holding.Points in rounds accumulate and the first player to reach 250 points wins.\n\n");
    printf("Play the game\n ");

    printf("************************\n");
    printf("1. Each player draws a card; the player that draws the highest number deals (count any card with a symbol as zero). \n");
    printf("2. The dealer shuffles and deals each player 5 cards.\n");
    printf("3. On your turn, you must match a card from your hand to the card on the top of the DISCARD pile, either bynumber, color or symbol.\n\n");
    printf("Cards\n");
    printf("************************\n");
    printf("Draw One card - When you play this card, the next player must draw 1 card and miss their turn. This card may only be played on a matching color or on another Draw One card. \n");
    printf("Wild card - When you play this card, you get to choose the color that continues play (any color including the color in play before the Wild card was laid down).\n");
    printf("Wild Draw 2 card - When you play this card, you get to choose the color that continues play PLUS the next player must draw 2 cards from the DRAW pile and lose their turn.\n");
    printf("Skip card - When you play this card, the next player is “skipped” (loses their turn). This card may only be played on a matching color or on another Skip card. \n\n");
    printf("Win the game\n");
    printf("************************\n");
    printf("When you play your next-to-last card, you must yell “UNO” (meaning “one”) to indicate that you have only one card left. If you don’t yell “UNO” and you are caught before the next player begins their turn, you must,draw two cards.Once a player has no cards left, the round is over. Points are scored (see SCORING) and play starts over again.If the last card played in a round is a Wild Draw Two card, the next player must draw the 2 cards. These cards are counted when the points are totaled. If no player is out of cards by the time the DRAW pile is depleted, the DISCARD pile is reshuffled and play continues.Scoring\n");
    printf("\n\n");
    printf("press any key to go back to menu...");
    

    fflush(stdin); // option ONE to clean stdin
        getchar(); 
}
void score_board(){
    printf("this is score board\n");
        printf("press any key to go back to menu...");
    fflush(stdin); // option ONE to clean stdin
        getchar(); 

}

void main_menu()
{
        
    while(1){
        
        char char_choice[3];
        int int_choice = 0;
        system("cls"); //clear screen
        startScreen();
        printf("\n");
        printf("UNO EXPRESS -- Main Menu: \n\n");
        printf("1. Start new game\n");
        printf("2. Game rules\n");
        printf("3. Score Board \n");
        printf("4. EXIT GAME\n\n");
        printf("enter your choice\n");
        scanf("%s", char_choice);
        int_choice = atoi(char_choice);
        switch (int_choice)
        {
            case 1:
                start();
            
                break;
            case 2:
                rules();
                break;
            case 3:
                score_board();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Wrong choice. Enter Again");
                break;
        }
    }
}

int main(void){

main_menu();
    return 0;
    
}