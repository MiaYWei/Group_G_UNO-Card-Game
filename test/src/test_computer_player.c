#include <stdlib.h>
#include "../../include/cards_management.h"
#include "../../include/computer_player.h"
#include "../include/test.h"
#include "../include/test_game.h"
#include "../include/test_cards_management.h"

void test_computer_take_turn(void);

void test_computer_player(void)
{
    write_log("\n--------------- Start Computer Player Module Test ---------------\n");
    test_computer_take_turn();
    
    return;
}

void test_computer_take_turn(void)
{
    int expected_ret, actual_ret = 0;
    if (initialize_game()) {
        write_log("Test --- computer_take_turn()......Initialize game failed! \n");
    }

    // Case 1: No playable card to discard, end of turn, game continues.
    g_card_on_table.color = BLUE;
    g_card_on_table.name = EIGHT;
    g_player_on_turn = COMPUTER;

    expected_ret = 1;
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    g_draw_pile = create_test_list(YELLOW, FIVE, NINE);
    actual_ret = computer_take_turn();
    if (expected_ret == actual_ret) {
        write_log("Test-- - computer_take_turn().Case 1......Successful!\n");
    } 
    else {
        write_log("Test-- - computer_take_turn().Case 1......failed!\n");
        write_fail_log("The return value of computer_take_turn():\n", actual_ret, expected_ret);
    }
    
    // Case 2: Computer: discard cards successful
    g_card_on_table.color = RED;
    g_card_on_table.name = TWO;
    g_player_on_turn = COMPUTER;

    expected_ret = 0;
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    actual_ret = computer_take_turn();
    if (expected_ret == actual_ret) {
        write_log("Test-- - computer_take_turn().Case 2......Successful!\n");
    } 
    else {
        write_log("Test-- - computer_take_turn().Case 2......failed!\n");
        write_fail_log("The return value of computer_take_turn():\n", actual_ret, expected_ret);
    }

    // Case 3: Not Computer Turn.
    g_player_on_turn = HUMAN;
    expected_ret = 2;
    actual_ret = computer_take_turn();
    if (expected_ret == actual_ret) {
        write_log("Test-- - computer_take_turn().Case 3......Successful!\n");
    }
    else {
        write_log("Test-- - computer_take_turn().Case 3......failed!\n");
        write_fail_log("The return value of computer_take_turn():\n", actual_ret, expected_ret);
    }

    return;
}


