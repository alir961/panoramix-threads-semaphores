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

void printUsage(void)
{
    my_putstr("USAGE: ./panoramix <nb_villagers> ");
    my_putstr("<pot_size> <nb_fights> <nb_refills>\n");
}

void free_all(pthread_t *thread)
{
    pthread_mutex_destroy(&data.mutex);
    sem_destroy(&data.villagers_sem);
    sem_destroy(&data.druid_sem);
    free(data.nb_fights_left);
    free(thread);
}

void create_join_thread(pthread_t *thread)
{
    if (pthread_create(&thread[data.nb_villagers], NULL, druid_thread, NULL)) {
        printf("Error creating druid thread\n");
        return 84;
    }
    for (int i = 0; i < data.nb_villagers; i++) {
        if (pthread_create(&thread[i], NULL, villager_thread, (void *)i)) {
            printf("Error creating villager thread\n");
            return 84;
        }
    }
    for (int i = 0; i < data.nb_villagers; i++) {
        pthread_join(thread[i], NULL);
    }
}
