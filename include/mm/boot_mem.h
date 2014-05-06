#define ACPI_GOOD_ENTRY 1
#define MEM_TYPE_FREE 1

typedef struct {
  uint64_t base;
  uint64_t lenght;
  uint16_t type;
}__attribute__((packed)) mem_segm_t;
