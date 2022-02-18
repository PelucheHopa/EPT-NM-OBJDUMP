/*
** EPITECH PROJECT, 2021
** test
** File description:
** etst
*/

#include "objdump.h"

int main(int ac, char **av)
{
    if (ac != 2) return (84);

    elfdata *elf = extract_file(av[1]);
    int bit = 0;

    bit = display(elf, av[1]);
    if (bit == 84) {
        free(elf);
        exit(84);
    }
    if (bit == 32) launch32BIT(av[1]);
    if (bit == 64) launch64BIT(av[1]);
    return (0);
}
