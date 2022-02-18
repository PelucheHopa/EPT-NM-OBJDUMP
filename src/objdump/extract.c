/*
** EPITECH PROJECT, 2021
** extract
** File description:
** extract
*/

#include "objdump.h"

elfdata *extract_file(char *filename)
{
    elfdata *e = malloc(sizeof(elfdata));
    struct stat st;
    int fd;

    e->_elf64 = malloc(sizeof(elf64));
    e->_elf32 = malloc(sizeof(elf32));
    if (lstat(filename, &st) == -1) { // On vérifie l'existence du fichier
        printf("'%s': no such file\n", filename);
        return 0;
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 0;
    }
    // On charge le contenu du fd dans e->data,

    e->data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (e->data == MAP_FAILED) // Le chargement a échoué
        return 0;
    e->fsize = st.st_size;
    // L'Ehdr est au tout début du fichier, autant juste cast la data en Elf64_Ehdr
    e->_elf64->ehdr = (Elf64_Ehdr *)e->data;
    if (!check_magic((e->_elf64->ehdr->e_ident))) {
        printf("%s: File format not recognized\n", filename);
        exit (84);
    }
// Le Shdr est situé à l'offset indiqué par le champ e_shoff de l'Ehdr
    e->_elf64->shdr = (Elf64_Shdr *)((uint8_t *)e->data + e->_elf64->ehdr->e_shoff);
    // Voir ci-dessous
    e->_elf64->strtable = (char *)e->data + e->_elf64->shdr[e->_elf64->ehdr->e_shstrndx].sh_offset;
    close(fd); // on a plus besoin du file descriptor, autant le fermer
    return (e);
}
