#include "../../include/human_player.h"
#include "../include/test.h"

void test_record_human_input(void);

int test_hunman_player(void)
{
    int result = 0;
    write_log("\n--------------- Start Test: Human Player Module ---------------\n\n");
    test_record_human_input();  
    write_log("\n--------------- End of Test: Human Player Module ---------------\n");

    return result;
}

void test_record_human_input(void)
{
    record_human_input();    

    return;
}


