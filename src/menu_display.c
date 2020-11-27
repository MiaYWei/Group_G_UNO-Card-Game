#include "cards_management.h"
#include "game.h"

void start_screen(void)
{
    printf("***************************************************************\n");
    printf("*                                                             *\n");
    printf("*                 UNO EXPRESS Card Game                       *\n");
    printf("*                                                             *\n");
    printf("*                       Group G                               *\n");
    printf("*                                                             *\n");
    printf("***************************************************************\n");

    printf("\n");
    printf("Main Menu: \n\n");
    printf("1. Start New Game\n");
    printf("2. Game Rules\n");
    printf("3. Exit Game\n\n");
    //printf("4. Score Board \n");  - Release 2
    printf("Enter your choice\n");
}

void rules(void)
{
    char choice[5] = { 0 };

    printf("UNO EXPRESS RULES: \n\n");
    printf("Objective of the Game \n");
    printf("************************\n");
    printf("Be the first player to get rid of all of your cards in each round.\n\n");
    printf("Play the Game\n");

    printf("************************\n");
    printf("1. Human player starts the game. \n");
    printf("2. The program deals each player 5 cards when start a new game.\n");
    printf("3. On your turn, you must match a card from your hand to the card on the top of the DISCARD pile, either by number, color or symbol.\n\n");
    /*printf("Action Cards (Release 2)\n");
    printf("************************\n");
    printf("Draw One card - When you play this card, the next player must draw 1 card and miss their turn. This card may only be played on a matching color or on another Draw One card. \n");
    printf("Wild card - When you play this card, you get to choose the color that continues play (any color including the color in play before the Wild card was laid down).\n");
    printf("Wild Draw 2 card - When you play this card, you get to choose the color that continues play PLUS the next player must draw 2 cards from the DRAW pile and lose their turn.\n");
    printf("Skip card - When you play this card, the next player is skipped (loses their turn). This card may only be played on a matching color or on another Skip card. \n\n");*/
    printf("Win the Game\n");
    printf("************************\n");
    printf("Once a player has no cards left, the game is over. If no player is out of cards by the time the DRAW pile is depleted, the DISCARD pile is reshuffled and play continues.\n");
    printf("\n\n");
    printf("press any key to go back to menu...");
    scanf_s("%s", choice, 1);
}

//void score_board()
//{
//    char choice[5] = { 0 };
//    printf("this is score board\n");
//    printf("press any key to go back to menu...");
//    scanf_s("%s", choice, 1);
//}

void main_menu(void)
{   
    int int_choice;

    while(1){    
        system("cls"); //clear screen
        start_screen();
        scanf_s("%d", &int_choice);
        switch (int_choice) {
            case 1:
                start_new_game();
                return;
            case 2:
                rules();
                break;
            case 3:
                confirm_exit();
                break;
            /* case 4:                 - Release 2
                score_board();
                break;*/
            default:
                printf("Wrong choice. Enter Again");
                break;
        }
    }
}

int main(void) {
    main_menu();
    return 0;
}