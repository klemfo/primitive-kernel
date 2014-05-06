#define ACPI_GOOD_ENTRY 1
#define MEM_TYPE_FREE 1

typedef struct {//should go in header
  uint64_t base; //assume 64 bit support
  uint64_t lenght;
  uint16_t type;
}__attribute__((packed)) mem_segm_t;
int64_t probe_mem_best_fit(mem_segm_t *segm)
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
