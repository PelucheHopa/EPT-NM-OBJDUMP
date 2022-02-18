/*
** EPITECH PROJECT, 2021
** display
** File description:
** display
*/

#include "objdump.h"

char *change_symbol(char *mydata, char *symbol, int x, int a)
{
    if (mydata[x] >= 33 && mydata[x] <= 127) symbol[a] = mydata[x];
    else symbol[a] = '.';
    symbol[a + 1] = '\0';
    return (symbol);
}

void display_hexa(char *mydata, int x)
{
    if (x % 4 == 0) printf(" ");
    if (mydata[x] < 255 && mydata[x] >= 0) printf("%02x", mydata[x]);
    else printf("%02x", 256 + mydata[x]);
}

void display_end(int compt, char *symbol)
{
    for (; compt != 16; compt++) {
        printf("  ");
        if (compt % 4 == 0) printf(" ");
    }
    printf("  %s\n", symbol);
}

char *check_status(unsigned char const ident[EI_CLASS])
{
    if (ident == NULL) return ("");
    if (ident[EI_CLASS] == 1) return ("32");
    if (ident[EI_CLASS] == 2) return ("64");
    return ("");
}

int display(elfdata *elf, char *filename)
{
    uint32_t flags;
    char *bit = check_status(elf->_elf64->ehdr->e_ident);

    printf("\n%s:     file format elf%s-x86-%s\n", filename, bit, bit);
    flags = create_flags(elf); // voir plus bas
    printf("architecture: i386:x86-%s, flags 0x%08x:\n", bit, flags);
    dump_flags(flags);
    printf("\n");
    // e_entry est le point d'entrée du programme, la toute première instruction
    // On est en 64 bits, donc les addresses sont sur 16 octets, d'où %016lx
    printf("start address 0x%016lx\n\n", elf->_elf64->ehdr->e_entry);
    if (strcmp(bit, "32") == 0) return (32);
    if (strcmp(bit, "64") == 0) return (64);
    return (84);
}
