/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** main
*/
#include "../inc/panoramix.h"

datathread_t data;

void parser(char **av)
{
    data.nb_villagers = atoi(av[1]);
    data.pot_size = atoi(av[2]);
    data.nb_fights = atoi(av[3]);
    data.nb_refills = atoi(av[4]);

    data.portions_left = data.pot_size;

    data.mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(data.mutex, NULL);

    data.druid_sem = malloc(sizeof(sem_t));
    sem_init(data.druid_sem, 0, 0);

    data.villagers_sem = malloc(sizeof(sem_t));
    sem_init(data.villagers_sem, 0, 0);

    data.nb_fights_left = malloc(sizeof(int) * data.nb_villagers);
    for (int i = 0; i < data.nb_villagers; i++) {
        data.nb_fights_left[i] = data.nb_fights;
    }
}

int main(int ac, char **av)
{
    pthread_t *thread = malloc(sizeof(pthread_t) * (data.nb_villagers + 1));
    
    if (ac != 5) {
        printUsage();
        return 84;
    }
    parser(av);
    create_join_thread(thread);
    free_all(thread);
    return 0;
}
