#include <stdlib.h>
#include "../../include/cards_management.h"
#include "../../include/game.h"
#include "../include/test.h"
#include "../include/test_game.h"
#include "../include/test_cards_management.h"

void test_initialize_players(void);
void test_if_end_game(void);

void test_game(void)
{
    write_log("\n--------------- Start Game Module Test ---------------\n");
    test_initialize_players();
    test_if_end_game();
    
    return;
}

void test_initialize_players(void)
{
    PlayerType_e expected_1st_player_type = HUMAN;
    PlayerType_e expected_2nd_player_type = COMPUTER;
    Deck_t *expected_player_card_list = NULL;

    initialize_players();

    if ((g_players[0].type == expected_1st_player_type) && (g_players[1].type == expected_2nd_player_type)) {
        write_log("Test-- - test_initialize_players().Case 1:Player Type......Successful!\n");
    }
    else {
        write_log("Test-- - test_initialize_players().Case 1:Player Type.......failed!\n");
        write_fail_log(" The player type value in test_initialize_players():\n", g_players[0].type, expected_1st_player_type);
    }

    if ((g_players[0].cards_on_hand == expected_player_card_list) && (g_players[1].cards_on_hand == expected_player_card_list)) {
        write_log("Test-- - test_initialize_players().Case 2:Player Card List Pointer......Successful!\n");
    }
    else {
        write_log("Test-- - test_initialize_players().Case 2:Player Card List Pointer.......failed!\n");
        write_log(" The player card list pointer value in test_initialize_players(): The expected pointer is Null. But the actual pointer is not NULL\n");
    }

    return;
}

void test_if_end_game(void)
{
    //Case 1: Not End game
    bool expected_ret = false;
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    bool actual_ret = if_end_game(COMPUTER);
    if (expected_ret == actual_ret) {
        write_log("Test-- - if_end_game().Case 1:Not End Game......Successful!\n");
    }
    else {
        write_log("Test-- - if_end_game().Case 1:Not End Game......failed!\n");
        write_fail_log(" The return value of if_end_game():\n", actual_ret, expected_ret);
    }

    //Case 2: End game
    expected_ret = true;
    g_players[COMPUTER].cards_on_hand = NULL;
    actual_ret = if_end_game(COMPUTER);
    if (expected_ret == actual_ret) {
        write_log("Test-- - if_end_game().Case 2:End Game......Successful!\n");
    }
    else {
        write_log("Test-- - if_end_game().Case 2:End Game......failed!\n");
        write_fail_log(" The return value of if_end_game():\n", actual_ret, expected_ret);
    }

    return;
}
