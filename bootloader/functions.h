#pragma once
#include "types.h"

// Disk
bool disk_init(device_t *disk,uint8_t drive_number);
void disk_lba2chs(device_t *disk, uint32_t lba, uint16_t *cylinder, uint16_t *sector, uint16_t *head);
bool disk_read(device_t *disk, uint32_t lba, uint8_t sectors, void *data);

// x86
extern "C" void outb(uint16_t port, uint8_t value);
extern "C" uint8_t inb(uint16_t port);
extern "C" bool get_drive_params(uint8_t drive, uint8_t *drive_type, uint16_t *cylinders, uint16_t *sectors, uint16_t *heads);
extern "C" bool x86_reset_disk(uint8_t drive);
extern "C" bool x86_read_disk(uint8_t drive, uint16_t cylinder, uint16_t sector, uint16_t head, uint8_t count, void* data);
extern "C" bool x86_hs(uint8_t drive, uint16_t *sectors, uint8_t *heads);

// FAT
bool fat_read_boot_sector(device_t *disk);
bool fat_read_fat(device_t *disk);
bool fat_init(device_t *disk);
uint32_t fat_cluster2lba(uint32_t cluster);
fat_file_t *fat_open_entry(device_t *disk, fat_directory_entry_t* entry);
uint32_t fat_next_cluster(uint32_t current);
uint32_t fat_read(device_t *disk, fat_file_t *file, uint32_t count, void* data);
bool fat_read_entry(device_t *disk, fat_file_t *file, fat_directory_entry_t *directory_entry);
void fat_close(fat_file_t *file);
bool fat_find_file(device_t *disk, fat_file_t *file, const char *name, fat_directory_entry_t *entry);
fat_file_t *fat_open(device_t *disk, const char *path);

// Memory
void* memcpy(void* dst, void* src, uint16_t count);
void* memset(void* ptr, int value, uint16_t count);
bool memcmp(void* ptr1, void* ptr2, uint16_t count);

// Stage 2
void print_char(char c);
void print_string(char* string);
void print_string(const char* string);
void printk(uint8_t *format, ...);
extern "C" void main(uint16_t boot_drive);

// String
const char* strchr(const char* str, char chr);
char* strcpy(char* dst, const char* src);
unsigned strlen(const char* str);
bool islower(char chr);
char toupper(char chr);

// Ports
void insl(int port, void *addr, int cnt);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);