#define PAGE_SIZE 4*1024
#define LOG_2_PAGE_SIZE 12

typedef struct {
	uint64_t adress;
	uint16_t order;
	uint8_t flags;
}__attribute__((packed)) page_entry_t;
