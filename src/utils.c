/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** utils
*/

#include "../inc/panoramix.h"

int my_putstr(char const *str)
{
    int a = 0;

    while (str[a] != '\0') {
        write(1, &str[a], 1);
        a++;
    }
}

void printUsage()
{
    my_putstr("USAGE: ./panoramix <nb_villagers> ");
    my_putstr("<pot_size> <nb_fights> <nb_refills>\n");
}
