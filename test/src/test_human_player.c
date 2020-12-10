#include "../../include/human_player_module.h"
#include "../include/test.h"

void test_record_human_input(void);

int test_hunman_player(void)
{
    int result = 0;
    write_log("\n--------------- Start Human Player Module Test ---------------\n");
    test_record_human_input();  
    return result;
}

void test_record_human_input(void)
{
    record_human_input();    

    return;
}


