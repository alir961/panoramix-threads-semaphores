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

void print_usage(void)
{
    my_putstr("USAGE: ./panoramix <nb_villagers> ");
    my_putstr("<pot_size> <nb_fights> <nb_refills>\n");
}

void free_all(pthread_t *druid, pthread_t *villager)
{
    pthread_mutex_destroy(&data.mutex);
    sem_destroy(&data.villagers_sem);
    sem_destroy(&data.druid_sem);
    free(data.nb_fights_left);
    free(druid);
    free(villager);
}

void create_join_thread(pthread_t *druid, pthread_t *villager)
{
    int id2 = 0;

    for (int id = 0; id < data.nb_villagers; id++) {
        if (pthread_create(&villager[id], NULL, villager_thread, (void *)id)) {
            printf("Error creating villager thread\n");
            exit(84);
        }
        id2 = id;
    }

    if (pthread_create(&druid, NULL, druid_thread, (void *)id2)) {
            printf("Error creating druid thread\n");
            exit(84);
    }

    for (int i = 0; i < data.nb_villagers; i++) {
        pthread_join(villager[i], NULL);
    }
    pthread_join(*druid, NULL);
}
