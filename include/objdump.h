/*
** EPITECH PROJECT, 2021
** malloc
** File description:
** malloc
*/

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>

#define HAS_RELOC       0x01
#define EXEC_P          0x02
#define HAS_SYMS        0x10
#define DYNAMIC         0x40
#define D_PAGED         0x100

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#include <elf.h>

typedef struct {
    void *data;
    void *strtable;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    size_t fsize;
} elf64;

typedef struct {
    void *data;
    void *strtable;
    Elf32_Ehdr *ehdr;
    Elf32_Shdr *shdr;
    size_t fsize;
} elf32;

typedef struct {
    void *data;
    void *strtable;
    elf32 *_elf32;
    elf64 *_elf64;
    size_t fsize;
} elfdata;

char *change_symbol(char *mydata, char *symbol, int x, int a);

void display_hexa(char *mydata, int x);

void display_end(int compt, char *symbol);

void display_contain32(int i, Elf32_Shdr *sh_table, FILE* fd);

void display_contain64(int i, Elf64_Shdr *sh_table, FILE* fd);

void display_part32(char *sh_str, FILE* fd, Elf32_Ehdr elf, Elf32_Shdr *sh_table);

void display_part64(char *sh_str, FILE* fd, Elf64_Ehdr elf, Elf64_Shdr *sh_table);

void launch32BIT(char *filename);

void launch64BIT(char *filename);

int display(elfdata *elf, char *filename);
    
elfdata *extract_file(char *filename);

uint32_t create_flags(elfdata *elf);

void dump_flags(uint32_t flags);

int check_magic(unsigned char const ident[EI_NIDENT]);

#endif
