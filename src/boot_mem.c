#include "mm/boot_mem.h"
#include "mm/page.h"
#include "lib/math.h"

mem_segm_t probe_mem_best_fit(mem_segm_t *segm)
{
	uint32_t next_entry = 0;
	uint64_t best_segment = 0;
	int signature, bytes = 0;
	do {
		__asm__ __volatile__ ("int  $0x15" 
				: "=a"(signature), "=c"(bytes), "=b"(next_entry)
				: "a"(0xE820), "b"(contID), "c"(24), "d"(0x534D4150), "D"(buffer));
		if (signature != 0x534D4150) return NULL;
		if (!(bytes > 20 && segm->ACPI & ACPI_GOOD_ENTRY == 0) &&
		segm->type == MEM_TYPE_FREE && segm->lenght > (mem_segm_t*) best_segment) best_segment = segm->base;
	} while (next_entry != 0);
  	return best_segment;
}

uint64_t allocate_boot_mem(boot_mem_list_t *mem_list, uint8_t size)
{
	uint8_t order = math_binary_log(size) - LOG_2_PAGE_SIZE;
	if(page_order) __allocate_boot_mem(mem_list, order);
}

uint64_t __allocate_boot_mem(boot_mem_list_t *mem_list, uint8_t order)
{
	boot_mem_list_t *best_fit;
	while(mem_list) {
		if(mem_list->flags & RESERVED_FLAG != 1) {
			if(mem_list->order == order) goto found;
			else if(mem_list->order > order && mem_list->order < best_fit->order) best_fit = mem_list;
		}
		mem_list = mem_list->next;
	}

	/*
	 *	-> [||||||||||||||||||O] ->
	 *	-> [||||||||] -> [||||||||O] ->
	 *	-> [|||||||| -> [||||] -> [||||O] -> 
	 */
	if(best_fit) mem_list = best_fit; //stupid?
	else return NULL; //not enough memory.
	for(size_t i = mem_list->order; i != order - 1; i--) {
		mem_list *tmp = mem_list->next;
		mem_list->next = (boot_mem_list_t*)(mem_list + (mem_list - mem_list->next)/2);
		mem_list = mem_list->next;
		mem_list->order = i;
		mem_list->next = tmp;
	}
	mem_list->flags |= RESERVED_FLAG;
	found:
	return (uint64_t) mem_list;
}

void free_boot_mem(boot_mem_list_t *mem_list, uint64_t adress)
{
	((boot_mem_list_t*) adress)->flags &= ~RESERVED_FLAG;
}

boot_mem_list_t *init_boot_mem(segm_t *segm)
{
	boot_mem_list_t *mem = (boot_mem_list_t*) segm->lenght;
	mem->order = math_binary_log(segm->lenght);
	mem->flags = 0;
	return mem:
}
