#include "../src/human_player_module.h"

void test_record_human_input(void);
int main(void)
{
    int result = 0;

    printf("--------------- Start the Test ---------------\n");  
    test_record_human_input();  
    return result;
}

void test_record_human_input(void)
{
 record_human_input();    
}


