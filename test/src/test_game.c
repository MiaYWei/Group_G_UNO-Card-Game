#include <stdlib.h>
#include "../../include/cards_management.h"
#include "../../include/game.h"
#include "../include/test.h"
#include "../include/test_game.h"
#include "../include/test_cards_management.h"

void test_initialize_players(void);
void test_if_end_game(void);
void test_player_process_draw_one_card(void);
void test_player_process_wild_draw_two_card(void);
void test_handle_computer_turn(void);
void test_handle_human_turn(void);

void test_game(void)
{
    write_log("\n--------------- Start Test: Game Module ---------------\n\n");
    test_initialize_players();
    test_if_end_game();
    test_player_process_draw_one_card();
    test_player_process_wild_draw_two_card();
    test_handle_computer_turn();
    test_handle_human_turn();
    write_log("\n--------------- End of Test: Game Module ---------------\n");
    
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

void test_player_process_draw_one_card(void)
{
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    int length_before = get_pile_length(g_players[COMPUTER].cards_on_hand);
    player_process_draw_one_card(HUMAN);
    int length_after = get_pile_length(g_players[COMPUTER].cards_on_hand);
    int actual_diff = length_after - length_before;
    int expected_diff = 1;

    if (expected_diff == actual_diff) {
        write_log("Test-- - player_process_draw_one_card().......Successful!\n");
    }
    else {
        write_log("Test-- - player_process_draw_one_card()......failed!\n");
        write_fail_log(" The diff value of player_process_draw_one_card():\n", actual_diff, expected_diff);
    }

    return;
}

void test_player_process_wild_draw_two_card(void)
{
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    int length_before = get_pile_length(g_players[COMPUTER].cards_on_hand);
    player_process_wild_draw_two_card(HUMAN);
    int length_after = get_pile_length(g_players[COMPUTER].cards_on_hand);
    int actual_diff = length_after - length_before;
    int expected_diff = 2;

    if (expected_diff == actual_diff) {
        write_log("Test-- - player_process_wild_draw_two_card().......Successful!\n");
    }
    else {
        write_log("Test-- - player_process_wild_draw_two_card()......failed!\n");
        write_fail_log(" The diff value of player_process_wild_draw_two_card():\n", actual_diff, expected_diff);
    }

    return;
}

void test_handle_computer_turn(void)
{
    // Case 1: No playable card to discard, end of turn, game continues.
    g_card_on_table.color = BLUE;
    g_card_on_table.name = EIGHT;
    g_player_on_turn = COMPUTER;

    PlayerType_e expected = HUMAN;
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);
    g_draw_pile = create_test_list(YELLOW, FIVE, NINE);

    handle_computer_turn();
    PlayerType_e actual = g_player_on_turn;
    if (expected == actual) {
        write_log("Test-- - handle_computer_turn().Case 1:No Playable Card Discarded, End Turn.......Successful!\n");
    }
    else {
        write_log("Test-- - handle_computer_turn().Case 1:Playable Card Discarded, End Turn......failed!\n");
        write_fail_log(" The test value of handle_computer_turn():\n", actual, expected);
    }

    //Case 2: Playable card Discarded, End Turn
    g_card_on_table.color = RED;
    g_card_on_table.name = TWO;
    g_player_on_turn = COMPUTER;
    g_players[COMPUTER].cards_on_hand = create_test_list(RED, ONE, FOUR);

    expected = HUMAN;

    handle_computer_turn();
    actual = g_player_on_turn;
    if (expected == actual) {
        write_log("Test-- - handle_computer_turn().Case 2:Playable Card Discarded, End Turn.......Successful!\n");
    }
    else {
        write_log("Test-- - handle_computer_turn().Case 2:Playable Card Discarded, End Turn......failed!\n");
        write_fail_log(" The test value of handle_computer_turn():\n", actual, expected);
    }

    // Case 3: Not Computer Turn.
    g_player_on_turn = HUMAN;
    expected = HUMAN;
    handle_computer_turn();
    actual = g_player_on_turn;
    if (expected == actual) {
        write_log("Test-- - handle_computer_turn().Case 3:Invalid Player.......Successful!\n");
    }
    else {
        write_log("Test-- - handle_computer_turn().Case 3:Invalid Player......failed!\n");
        write_fail_log(" The test value of handle_computer_turn():\n", actual, expected);
    }

    return;
}

void test_handle_human_turn(void)
{
    return;
}