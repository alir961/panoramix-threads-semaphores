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
    data.max_portions = data.pot_size;
    data.mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(data.mutex, NULL);
    data.druid_sem = malloc(sizeof(sem_t));
    sem_init(data.druid_sem, 0, 0);

    data.villagers_sem = malloc(sizeof(sem_t));
    sem_init(data.villagers_sem, 0, 1);

    if ((data.nb_fights_left = malloc(sizeof(int) * data.nb_villagers)) ==
        NULL)
        exit(84);
    for (int id = 0; id < data.nb_villagers; id++) {
        data.nb_fights_left[id] = data.nb_fights;
    }
}

void error_handling(void)
{
    if (data.nb_villagers <= 0 || data.pot_size <= 0 ||
        data.nb_fights <= 0 || data.nb_refills <= 0)
        exit(84);
}

int main(int ac, char **av)
{
    pthread_t *druid = malloc(sizeof(pthread_t) * (data.nb_villagers + 1));
    pthread_t *villager = malloc(sizeof(pthread_t) * (data.nb_villagers + 1));

    if (ac != 5) {
        print_usage();
        return 84;
    }
    parser(av);
    error_handling();
    create_join_thread(druid, villager);
    free_all(druid, villager);
    return 0;
}
