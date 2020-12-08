#include <stdlib.h>
#include "cards_management.h"
#include "game.h"

void start_screen(void)
{
    printf("***********************************************************************\n");
    printf("*                                                                     *\n");
    printf("*               WELCOME To UNO EXPRESS CARD GAME                      *\n");
    printf("*                                                                     *\n");
    printf("*                   SYSC5709 Project Group G                          *\n");
    printf("*                                                                     *\n");
    printf("***********************************************************************\n");

    printf("\n");
    printf("Main Menu: \n\n");
    printf("1. Game Rules\n");
    printf("2. Start New Game\n");
    printf("3. Exit Game\n");
    // printf("4. Score Board (Release 2)\n\n"); 
    printf("Enter your choice:\n");
}

void display_rules(void)
{
    char choice[5] = {0};

    printf("************************************************************************\n");
    printf("*                                                                      *\n");
    printf("*                           GAME RULES                                 *\n");
    printf("*                                                                      *\n");
    printf("************************************************************************\n");
    printf("************************************************************************\n\n");
    printf(" Normal Cards: \n");
    printf("  10 Blue cards - 0 to 9\n");
    printf("  10 Green cards - 0 to 9\n");
    printf("  10 Red cards - 0 to 9\n");
    printf("  10 Yellow cards - 0 to 9\n\n");  

    printf(" Action Cards (Release 2): \n");
    printf("  4 Draw One cards - 1 each in blue, green, red and yellow.\n");
    printf("  4 Skip cards - 1 each in blue, green, red and yellow.\n");
    printf("  2 Wild cards.\n");
    printf("  2 Wild Draw Two cards.\n\n");
    printf("************************************************************************\n\n");
    printf(" Objective of the Game \n");
    printf("  Be the first player to get rid of all of your cards.\n\n");
    printf("************************************************************************\n\n");
    printf(" Let's Play\n");
    printf("  1. Human player starts the game. \n");
    printf("  2. The program deals each player 5 cards while starting a new game.\n");
    printf("  3. On your turn, you must match a card from your hand to the card on the top of the DISCARD pile, either by number, color or symbol.\n");
    printf("    EXAMPLE: If the card on the top of the DISCARD pile is a blue 7, the player must put down a blue card OR 7 in any color.\n\n");
    //printf(" Alternatively, the player can put down a Wild card(See FUNCTIONS OF ACTION CARDS");
    printf("************************************************************************\n\n");
    // printf(" Win the Game\n");
    printf("  Once a player has no cards left, the game is over. The player who exhausts all of his cards quickly is the winner of the game.\n");
    printf("  If no player is out of cards by the time the DRAW pile is depleted, the DISCARD pile is reshuffled and set as the draw pile. \n\n");
    printf("************************************************************************\n\n");

    printf(" Inputs to play the game\n");
    printf("  To request a card from the Draw pile, Press N or n. \n");
    printf("  To end turn, Press E or e. \n");
    printf("  To discard a card - Say you want to discard(RED,3), Press R3.\n");
    printf("  To quit the game, Press Q or q.\n\n");
    printf("************************************************************************\n\n");

    printf(" Functions of Action Cards (Release 2)\n");
    printf("  Draw One card - When you play this card, the next player must draw 1 card and miss their turn. This card may only be played on a matching color. \n");
    printf("  Skip card - When you play this card, the next player is skipped (loses their turn). This card may only be played on a matching color. \n");
    printf("  Wild card - When you play this card, you get to choose the color that continues play (any color including the color in play before the Wild card was laid down).\n");
    printf("  Wild Draw TWO card - When you play this card, you get to choose the color that continues play PLUS the next player must draw 2 cards from the DRAW pile and lose their turn.\n\n");
    printf("************************************************************************\n\n");

    printf("\nPress any key to go back to Main Menu...");
    scanf("%s", choice);    
}

void display_score_board(void)
{
    char choice[5] = { 0 };
    printf("Will be available in Release 2\n");
    printf("Press any key to go back to Main Menu...");
    scanf("%s", choice);
}

void invalid_choice(void)
{
    char choice[5] = {0,0,0,0,0};
    printf("Wrong choice. Press any key to go back to Main Menu...\n");
    scanf("%s", choice);
}

void main_menu(void)
{   
    int int_choice;

    while(1)
    {    
        system("clear"); //clear screen      
        start_screen();
        scanf("%d", &int_choice);
        switch (int_choice) {
            case 1:
                display_rules();
                break;
            case 2:
                start_new_game();
                return;
            case 3:
                confirm_exit();
                break;
            //case 4:                 //Release 2
            //    display_score_board();
            //    break;
            default:
                invalid_choice();
                break;
        }
    }
}

int main(void) 
{
    char choice[5] = {0};
    main_menu();
    printf("Press any key to exit console display...\n");
    scanf("%s", choice);

    return 0;
}
