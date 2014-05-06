#define BOOT_MEM_START (0x1000 + 4*1024)
#define BOOT_MEM_LENGHT 4*1024

size_t term_row, term_collumn;
uint16_t *term_buffer;

int start_kernel(void)
{
	term_row, term_collumn = 0;
	term_buffer = (uint16_t*) VGA_MEM_ADRESS;
	putstring("Terminal enabled.");
	mem_segm_t *segm = (segm_t*) BOOT_MEM_START;
	segm = (segm_t*) probe_mem_best_fit(segm);
	init_boot_mem(segm);
}
