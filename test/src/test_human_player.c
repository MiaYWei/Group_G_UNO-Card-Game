#include "../../include/human_player.h"
#include "../include/test.h"
#include "../include/test_cards_management.h"

void test_get_card_type(void);
void test_human_process_normal_card(void);
void test_human_process_skip_card(void);
void test_human_process_draw_one_card(void);
void test_human_process_wild_card(void);
void test_human_process_wild_draw_two_card(void);

int test_hunman_player(void)
{
    int result = 0;
    write_log("\n--------------- Start Test: Human Player Module ---------------\n");
    test_get_card_type();
    test_human_process_normal_card();
    test_human_process_skip_card();
    test_human_process_draw_one_card();
    test_human_process_wild_card();
    test_human_process_wild_draw_two_card();

    write_log("--------------- End of Test: Human Player Module ---------------\n");

    return result;
}

void test_get_card_type(void)
{
    // Case 1: Normal Card Type
    Card_t test_card = { GREEN, FIVE };
    CardType_e expected_type = NORMAL;
    CardType_e actual_type = get_card_type(test_card);
    if (expected_type == actual_type) {
        write_log("Test--- get_card_type().Case 1:Normal Card Type......Successful!\n");
    }
    else {
        write_log("Test--- get_card_type().Case 1:Normal Card Type......failed!\n");
        write_fail_log("The return value of get_card_type():\n", actual_type, expected_type);
    }

    // Case 2: Skip Card Type
    test_card.name = SKIP;
    expected_type = SKIP_T;
    actual_type = get_card_type(test_card);
    if (expected_type == actual_type) {
        write_log("Test--- get_card_type().Case 2:Skip Card Type......Successful!\n");
    }
    else {
        write_log("Test--- get_card_type().Case 2:Skip Card Type......failed!\n");
        write_fail_log("The return value of get_card_type():\n", actual_type, expected_type);
    }

    // Case 3: Draw-One Card Type
    test_card.name = DRAW_ONE;
    expected_type = DRAW_ONE_T;
    actual_type = get_card_type(test_card);
    if (expected_type == actual_type) {
        write_log("Test--- get_card_type().Case 3:Draw-One Card Type......Successful!\n");
    }
    else {
        write_log("Test--- get_card_type().Case 3:Draw-One Card Type......failed!\n");
        write_fail_log("The return value of get_card_type():\n", actual_type, expected_type);
    }

    // Case 4: Wild Card Type
    test_card.name = WILD;
    expected_type = WILD_T;
    actual_type = get_card_type(test_card);
    if (expected_type == actual_type) {
        write_log("Test--- get_card_type().Case 4:Wild Card Type......Successful!\n");
    }
    else {
        write_log("Test--- get_card_type().Case 4:Wild Card Type......failed!\n");
        write_fail_log("The return value of get_card_type():\n", actual_type, expected_type);
    }

    // Case 5: Wild-Draw-Two Card Type
    test_card.name = WILD_DRAW_TWO;
    expected_type = WILD_DRAW_TWO_T;
    actual_type = get_card_type(test_card);
    if (expected_type == actual_type) {
        write_log("Test--- get_card_type().Case 5:Wild-Draw-Two Card Type......Successful!\n");
    }
    else {
        write_log("Test--- get_card_type().Case 5:Wild-Draw-Two Card Type......failed!\n");
        write_fail_log("The return value of get_card_type():\n", actual_type, expected_type);
    }

    // Case 6: Wild-Draw-Two Card Type
    test_card.name = INVALID_NAME;
    expected_type = INVALID_TYPE;
    actual_type = get_card_type(test_card);
    if (expected_type == actual_type) {
        write_log("Test--- get_card_type().Case 6:Invalid Card Type......Successful!\n");
    }
    else {
        write_log("Test--- get_card_type().Case 6:Invalid Card Type......failed!\n");
        write_fail_log("The return value of get_card_type():\n", actual_type, expected_type);
    }
        
    return;
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

    // Case 1: Human Player Discards a Skip Card failed test: Invalid or Not Playable Card
    Card_t human_card_choice = { YELLOW, SKIP };
    ret_type_e expected_ret = RET_FAILURE;
    ret_type_e actual_ret = human_process_skip_card(human_card_choice);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_skip_card().Case 1:Inalid or Not Playable Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_skip_card().Case 1:Invalid or Not Playable Card......failed!\n");
        write_fail_log("The return value of human_process_skip_card():\n", actual_ret, expected_ret);
    }

    // Case 2: Human Player Discards a Skip Card Successfully
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

    // Case 1: Human player Discards a Draw-One Card failed test: Invalid or Not Playable Card
    Card_t human_card_choice = { YELLOW, DRAW_ONE };
    ret_type_e expected_ret = RET_FAILURE;
    ret_type_e actual_ret = human_process_draw_one_card(human_card_choice);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_draw_one_card().Case 1:Invalid or Not Playable Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_draw_one_card().Case 1:Invalid or Not Playable Card......failed!\n");
        write_fail_log("The return value of human_process_draw_one_card():\n", actual_ret, expected_ret);
    }

    // Case 2: Human Player Discards a Draw-One Card Successfully
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

void test_human_process_wild_card(void)
{
    Card_t human_card_choice = { ACTION, WILD };
    g_players[HUMAN].cards_on_hand = create_test_list(RED, ONE, FIVE);

    // Case 1: Human player Discards a Draw-One Card failed test: Invalid Card
    ret_type_e expected_ret = RET_INVALID_CARD;
    ret_type_e actual_ret = human_process_wild_card(human_card_choice, BLUE);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_wild_card().Case 1:Invalid Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_wild_card().Case 1:Invalid Card......failed!\n");
        write_fail_log("The return value of human_process_wild_card():\n", actual_ret, expected_ret);
    }

    // Case 2: Human Player Discards a Draw-One Card Successfully 
    add_card_at_end(g_players[HUMAN].cards_on_hand, human_card_choice);
    expected_ret = RET_SUCCESS;
    actual_ret = human_process_wild_card(human_card_choice, BLUE);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_wild_card().Case 2:Human Player Discard a Wild Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_wild_card().Case 2:Human Player Discard a Wild Card......failed!\n");
        write_fail_log("The return value of human_process_wild_card():\n", actual_ret, expected_ret);
    }

    return;
}

void test_human_process_wild_draw_two_card(void)
{
    g_players[HUMAN].cards_on_hand = create_test_list(RED, ONE, FIVE);
    Card_t human_card_choice = { ACTION, WILD_DRAW_TWO };

    // Case 1: Human player Discards a Draw-One Card failed test: Invalid Card
    ret_type_e expected_ret = RET_FAILURE;
    ret_type_e actual_ret = human_process_wild_draw_two_card(human_card_choice, GREEN);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_wild_draw_two_card().Case 1:Invalid Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_wild_draw_two_card().Case 1:Invalid Card......failed!\n");
        write_fail_log("The return value of human_process_wild_draw_two_card():\n", actual_ret, expected_ret);
    }

    // Case 2: Human Player Discards a Draw-One Card Successfully 
    add_card_at_end(g_players[HUMAN].cards_on_hand, human_card_choice);
    expected_ret = RET_SUCCESS;
    actual_ret = human_process_wild_draw_two_card(human_card_choice, GREEN);
    if (expected_ret == actual_ret) {
        write_log("Test--- human_process_wild_draw_two_card().Case 2:Human Player Discard a Wild-Draw-Two Card......Successful!\n");
    }
    else {
        write_log("Test--- human_process_wild_draw_two_card().Case 2:Human Player Discard a Wild-Draw-Two Card......failed!\n");
        write_fail_log("The return value of human_process_wild_draw_two_card():\n", actual_ret, expected_ret);
    }

    return;
}
