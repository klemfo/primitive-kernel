#include "lib/string.h"

#define TERMINAL_COLOR(0 | (15 << 4))
#define VGA_DISPLAY_ADRESS
#define TERMINAL_MAX_COLLUMN 80
#define TERMINAL_MAX_ROW 24

#define __MAKE_VGA_ENTRY(char) 	\
	char | (TERM_COLOR << 8) \

#define MAKE_VGA_ENTRY(char) 		\
	__MAKE_VGA_ENTRY((uint_16t) char) \

//this requires for const char** (we don't have dynamic allocations at this stage anyway!)
#define boot_putstring(x) 	\
	__boot_putstring(x + "\0") \

void __boot_putstring(const char **string)
{
	for(size_t x = 0; x != strlen(string); x++) {
		if((*string)[x] == 'n')  {
			term_row++;
			term_collumn = 0;
			return;
		}
		else if(term_collumn == TERMINAL_MAX_COLLUMN) {
			for(size_t i = 0; i != TERMINAL_MAX_ROW-1; i++) {
				for(size_t j = 0; j != TERMINAL_MAX_COLLUMN; j++) {
					term_buffer[i*TERMINAL_MAX_COLLUMN + j] = term_buffer[(i-1)*TERMINAL_MAX_COLLUMN + j];
				}
			}		
			for(size_t i = 0; i != TERMINAL_MAX_COLLUMN; i++) {
				term_buffer[(TERMINAL_MAX_ROW-1)*TERMINAL_MAX_COLLUMN + j] = MAKE_VGA_ENTRY(' ');
			}
		}
		else term_buffer[term_row*TERMINAL_MAX_ROW + term_collumn] = MAKE_VGA_ENTRY((*string)[x];
	}
}
