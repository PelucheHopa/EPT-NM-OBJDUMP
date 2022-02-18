/*
** EPITECH PROJECT, 2021
** 32
** File description:
** 32
*/

#include "objdump.h"

void display_contain32(int i, Elf32_Shdr *sh_table, FILE* fd)
{
    char *mydata = malloc(sh_table[i].sh_size);
    char *symbol = malloc(sizeof(char) * (17));
    int a = 0;
    int compt = 0;

    fseek(fd, sh_table[i].sh_offset, SEEK_SET);
    fread(mydata, 1, sh_table[i].sh_size, fd);
    for (int x = 0; x != sh_table[i].sh_size; x++, a++, compt++) {
        if (x % 16 == 0) {
            if (x != 0) printf("  %s\n", symbol);
            else printf("\n");
            printf(" %06x", sh_table[i].sh_addr + x);
            a = 0;
            compt = 0;
        }
        display_hexa(mydata, x);
        symbol = change_symbol(mydata, symbol, x, a);
    }
    display_end(compt, symbol);
    free(mydata);
    free(symbol);
}

void display_part32(char *sh_str, FILE* fd, Elf32_Ehdr elf, Elf32_Shdr *sh_table)
{
    for (int i = 1; i < elf.e_shnum; i++) {
        printf("Contenu de la section %s :", sh_str + sh_table[i].sh_name);
        display_contain32(i, sh_table, fd);
        if (!strcmp(".gnu.build.attributes", (sh_str + sh_table[i].sh_name))) return;
    }
}

void InitSection32(FILE* fd, Elf32_Ehdr elf, Elf32_Shdr *sh_table)
{
    char* buff = NULL;

    buff = malloc(sh_table[elf.e_shstrndx].sh_size);
    if (buff != NULL) {
        fseek(fd, sh_table[elf.e_shstrndx].sh_offset, SEEK_SET);
        fread(buff, 1, sh_table[elf.e_shstrndx].sh_size, fd);
    }
    else exit(84);
    display_part32(buff, fd, elf, sh_table);
}

void launch32BIT(char *filename)
{
    FILE* fp = NULL; //Pointer used to access current file
    Elf32_Ehdr elf_header; //Elf header
    Elf32_Shdr* sh_table; //Elf symbol table

    fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_SET);
    fread(&elf_header, 1, sizeof(Elf64_Ehdr), fp);
    sh_table = malloc(elf_header.e_shentsize*elf_header.e_shnum);
    fseek(fp, elf_header.e_shoff, SEEK_SET);
    fread(sh_table, 1, elf_header.e_shentsize*elf_header.e_shnum, fp);
    InitSection32(fp, elf_header, sh_table);
    fclose(fp);
}
