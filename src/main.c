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

    data.pot_mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(data.pot_mutex, NULL);

    data.pot_empty_cv = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(data.pot_empty_cv, NULL);

    data.pot_sem = malloc(sizeof(sem_t));
    sem_init(data.pot_sem, 0, data.pot_size);

    data.refill_mutex = malloc(sizeof(sem_t));
    sem_init(data.refill_mutex, 0, 1);
}

int main(int ac, char **av)
{
    if (ac != 5) {
        printUsage();
        return 84;
    }
    parser(av);

    pthread_t *thread = malloc(sizeof(pthread_t) * (data.nb_villagers + 2));

    if (pthread_create(&thread[data.nb_villagers], NULL, druid_function, NULL)) {
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

    pthread_mutex_destroy(&data.pot_mutex);
    pthread_cond_destroy(&data.pot_empty_cv);

    sem_destroy(&data.pot_sem);
    sem_destroy(&data.refill_mutex);

    free(thread);

    return 0;
}
