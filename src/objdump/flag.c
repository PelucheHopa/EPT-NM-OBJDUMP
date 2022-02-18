/*
** EPITECH PROJECT, 2021
** flag
** File description:
** flag
*/

#include "objdump.h"

static const struct {
    int num;
    char *name;
} flag_names[5] = {
    {HAS_RELOC, "HAS_RELOC"},
    {EXEC_P, "EXEC_P"},
    {HAS_SYMS, "HAS_SYMS"},
    {DYNAMIC, "DYNAMIC"},
    {D_PAGED, "D_PAGED"}
};

static char *get_name(int num)
{
    for (int i = 0; i < 5; i++) {
        if (num == flag_names[i].num) {
            return flag_names[i].name;
        }
    }
    return "UNKNOWN";
}

void dump_flags(uint32_t flags)
{
    bool first = true;

    for (int i = 1; i <= 0x100; i *= 2)
        if ((flags & i) != 0) {
            if (first) {
                printf("%s", get_name(i));
                first = false;
            } else printf(", %s", get_name(i));
        }
}

uint32_t create_flags(elfdata *elf)
{
    uint32_t flags = 0;
    const char *shname;

    flags |= elf->_elf64->ehdr->e_type == ET_EXEC ? (unsigned) EXEC_P : 0;
    flags |= elf->_elf64->ehdr->e_type == ET_DYN ? (unsigned) DYNAMIC : 0;
    flags |= elf->_elf64->ehdr->e_type == ET_REL ? (unsigned) HAS_RELOC : 0;
    flags |= (elf->_elf64->ehdr->e_phnum ? (unsigned) D_PAGED : 0);
    if (elf->strtable != NULL) {
        for (int i = 0; i < elf->_elf64->ehdr->e_shnum; i++) {
            // On accède au nom de la section.
            shname = elf->_elf64->strtable + elf->_elf64->shdr[i].sh_name;
            if (strcmp(shname, ".dynsym") == 0 || strcmp(shname, ".symtab") == 0) {
                flags |= (unsigned) HAS_SYMS;
                break;
            }
        }
    }
    return flags;
}

int check_magic(unsigned char const ident[EI_NIDENT])
{
    if (ident == NULL) return 0;
    if (ident[EI_MAG0] == ELFMAG0 && ident[EI_MAG1] == ELFMAG1
        && ident[EI_MAG2] == ELFMAG2 && ident[EI_MAG3] == ELFMAG3)
        return 1;
    return 0;
}
