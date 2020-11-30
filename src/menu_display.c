#include "cards_management.h"
#include "game.h"

void start_screen(void)
{
    printf("***************************************************************\n");
    printf("*                                                             *\n");
    printf("*           WELCOME To UNO EXPRESS CARD GAME                  *\n");
    printf("*                                                             *\n");
    printf("*               SYSC5709 Project Group G                      *\n");
    printf("*                                                             *\n");
    printf("***************************************************************\n");

    printf("\n");
    printf("Main Menu: \n\n");
    printf("1. Start New Game\n");
    printf("2. Game Rules\n");
    printf("3. Exit Game\n\n");
    printf("4. Score Board (Release 2)\n"); 
    printf("Enter your choice:\n");
}

void display_rules(void)
{
    char choice[5] = { 0 };

    printf("\nRULES of UNO EXPRESS CARD GAME: \n");
    printf("************************************************************************\n");
    printf("Normal Cards: \n\n");
    printf(" 10 Blue cards - 0 to 9\n");
    printf(" 10 Green cards - 0 to 9\n");
    printf(" 10 Red cards - 0 to 9\n");
    printf(" 10 Yellow cards - 0 to 9\n\n");  

    printf("Action Cards (Release 2): \n\n");
    printf(" 4 Draw One cards - 1 each in blue, green, red and yellow.\n");
    printf("   Draw One card - When you play this card, the next player must draw 1 card and miss their turn. This card may only be played on a matching color. \n");
    printf(" 4 Skip cards - 1 each in blue, green, red and yellow.\n");
    printf("   Skip card - When you play this card, the next player is skipped (loses their turn). This card may only be played on a matching color. \n"); 
    printf(" 2 Wild cards.\n");
    printf("   Wild card - When you play this card, you get to choose the color that continues play (any color including the color in play before the Wild card was laid down).\n");
    printf(" 2 Wild Draw Two cards.\n");
    printf("   Wild Draw TWO card - When you play this card, you get to choose the color that continues play PLUS the next player must draw 2 cards from the DRAW pile and lose their turn.\n\n");
    printf("************************************************************************\n");
    
    printf("Objective of the Game \n");
    printf(" Be the first player to get rid of all of your cards in each turn.\n\n");
    printf("************************************************************************\n");
    printf("Play the Game\n");
    printf(" 1. Human player starts the game. \n");
    printf(" 2. The program deals each player 5 cards when start a new game.\n");
    printf(" 3. On your turn, you must match a card from your hand to the card on the top of the DISCARD pile, either by number, color or symbol.\n");
    printf("    EXAMPLE: If the card on the top of the DISCARD pile is a blue 7, the player must put down a blue card OR any color 7.\n\n");
    //printf(" Alternatively, the player can put down a Wild card(See FUNCTIONS OF ACTION CARDS");
    printf("************************************************************************\n");
    printf("Win the Game\n");
    printf(" Once a player has no cards left, the game is over. The specific player is the winner of the game.\n");
    printf(" If no player is out of cards by the time the DRAW pile is depleted, the DISCARD pile is reshuffled and play continues.\n");
    printf("\n\npress any key to go back to menu...");
    scanf_s("%s", choice, 1);
}

void display_score_board(void)
{
    char choice[5] = { 0 };
    printf("Will release in Release 2\n");
    printf("Press any key to go back to menu...");
    scanf_s("%s", choice, 1);
}

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
                display_rules();
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