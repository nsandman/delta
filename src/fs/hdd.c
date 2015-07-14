extern void read_lba_sector(uint32_t lba, uint8_t num, uint64_t addr);

// Abstract disk interface. In the future, we will make a 
// decision about what protocol to use here. For now, it's
// always ATA LBA.
void readsector(uint32_t lba, uint8_t num, uint64_t addr) {
	read_lba_sector(lba, num, addr);
}