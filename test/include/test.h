#ifndef __TEST_HEADER__
#define __TEST_HEADER__

#include "../../include/cards_management.h"

extern Deck_t* g_draw_pile_test;                     /* remaining cards to draw */
extern Deck_t* g_discard_pile_test;                  /* discarded cards */

void write_log(const char* string);
void write_fail_log(const char* string, int actual, int expected);
int init_test(void);
#endif //__TEST_HEADER__