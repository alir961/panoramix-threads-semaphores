/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** main
*/

#include "../inc/panoramix.h"

datathread_t data;

int main(int ac, char **av)
{
    if (!parse_arguments(ac, av)) {
        print_usage();
        return EXIT_ERROR;
    }
    return run_simulation();
}
