#define BOOT_MEM_START (0x1000 + 4*1024)
#define BOOT_MEM_LENGHT 4*1024

int start_kernel(void)
{
	mem_segm_t *segm = (segm_t*) BOOT_MEM_START;
	segm = (segm_t*) probe_mem_best_fit(segm);
	init_boot_mem(segm);
}
