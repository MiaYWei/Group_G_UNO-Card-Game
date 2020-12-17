#include "../../include/human_player.h"
#include "../include/test.h"
#include "../include/test_cards_management.h"

void test_human_process_normal_card(void);
void test_human_process_skip_card(void);
void test_human_process_draw_one_card(void);

int test_hunman_player(void)
{
    int result = 0;
    write_log("\n--------------- Start Test: Human Player Module ---------------\n");
    test_human_process_normal_card();
    test_human_process_skip_card();
    test_human_process_draw_one_card();
    write_log("--------------- End of Test: Human Player Module ---------------\n");

    return result;
}

void test_human_process_normal_card(void)
{
    g_players[HUMAN].cards_on_hand = create_test_list(RED, ONE, FOUR);

    // Case 1: The human card choice is unavailable in human player deck
    Card_t human_card_choice = { YELLOW, ONE };
    ret_type_e expected_ret = RET_INVALID_CARD;
    ret_type_e actual_ret = human_process_normal_card(human_card_choice);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_normal_card().Case 1:Invalid Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_normal_card().Case 1:Invalid Card......failed!\n");
        write_fail_log("The return value of human_process_normal_card():\n", actual_ret, expected_ret);
    }

    // Case 2: The human card choice is in human player deck, but not playable.
    human_card_choice.color = RED;
    human_card_choice.name = ONE;
    g_card_on_table.color = BLUE;
    g_card_on_table.name = TWO;
    expected_ret = RET_NOT_PLAYABLE_CARD;
    actual_ret = human_process_normal_card(human_card_choice);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_normal_card().Case 2:Valid Card, but Not Playable......Successful!\n");
    }
    else {
        write_log("Test--- human_process_normal_card().Case 2:Valid Card, but Not Playable......failed!\n");
        write_fail_log("The return value of human_process_normal_card():\n", actual_ret, expected_ret);
    }

    // Case 3: Human player discards a normal card successfully.
    human_card_choice.color = RED;
    human_card_choice.name = ONE;
    g_card_on_table.color = BLUE;
    g_card_on_table.name = ONE;
    expected_ret = RET_SUCCESS;
    actual_ret = human_process_normal_card(human_card_choice);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_normal_card().Case 3:Human Player Discard a Normal Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_normal_card().Case 3:Human Player Discard a Normal Card......failed!\n");
        write_fail_log("The return value of human_process_normal_card():\n", actual_ret, expected_ret);
    }

    return;
}

void test_human_process_skip_card(void)
{
    g_players[HUMAN].cards_on_hand = create_test_list(RED, ONE, SKIP);

    // Case 1: Human player Discards a Skip Card failed test
    Card_t human_card_choice = { YELLOW, SKIP };
    ret_type_e expected_ret = RET_FAILURE;
    ret_type_e actual_ret = human_process_skip_card(human_card_choice);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_skip_card().Case 1:Valid or Not Playable Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_skip_card().Case 1:Valid or Not Playable Card......failed!\n");
        write_fail_log("The return value of human_process_skip_card():\n", actual_ret, expected_ret);
    }

    // Case 2: Human player Discards a Skip Card successfully test
    g_card_on_table.color = RED;
    g_card_on_table.name = SEVEN;
    human_card_choice.color = RED;
    expected_ret = RET_SUCCESS;
    actual_ret = human_process_skip_card(human_card_choice);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_skip_card().Case 2:Human Player Discard a Skip Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_skip_card().Case 2:Human Player Discard a Skip Card......failed!\n");
        write_fail_log("The return value of human_process_skip_card():\n", actual_ret, expected_ret);
    }

    return;
}

void test_human_process_draw_one_card(void)
{
    g_players[HUMAN].cards_on_hand = create_test_list(RED, ONE, DRAW_ONE);

    // Case 1: Human player Discards a Draw-One Card failed test
    Card_t human_card_choice = { YELLOW, DRAW_ONE };
    ret_type_e expected_ret = RET_FAILURE;
    ret_type_e actual_ret = human_process_draw_one_card(human_card_choice);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_draw_one_card().Case 1:Valid or Not Playable Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_draw_one_card().Case 1:Valid or Not Playable Card......failed!\n");
        write_fail_log("The return value of human_process_draw_one_card():\n", actual_ret, expected_ret);
    }

    // Case 2: Human player Discards a Draw-One Card successfully test
    g_card_on_table.color = RED;
    g_card_on_table.name = SEVEN;
    human_card_choice.color = RED;
    expected_ret = RET_SUCCESS;
    actual_ret = human_process_draw_one_card(human_card_choice);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_draw_one_card().Case 2:Human Player Discard a Draw-One Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_draw_one_card().Case 2:Human Player Discard a Draw-One Card......failed!\n");
        write_fail_log("The return value of human_process_draw_one_card():\n", actual_ret, expected_ret);
    }

    return;
}