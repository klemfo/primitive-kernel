#define BOOT_MEM_START (0x1000 + 4*1024)
#define BOOT_MEM_LENGHT 4*1024

int start_kernel(void)
{
	segm_t *segm = (segm_t*) BOOT_MEM_START;
	segm = (segm_t*) mem_boot_probe_besti_fit(segm); //will the cast work?
}
