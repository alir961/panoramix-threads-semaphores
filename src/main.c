/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** main
*/
#include "../inc/utils.h"
#include "../inc/druid.h"
#include "../inc/villager.h"

void parser(char **av, datathread_t *data)
{
    data->nb_villagers = atoi(av[1]);
    data->pot_size = atoi(av[2]);
    data->nb_fights = atoi(av[3]);
    data->nb_refills = atoi(av[4]);

    data->portions_left = malloc(sizeof(int));
    *(data->portions_left) = data->pot_size;

    data->pot_mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(data->pot_mutex, NULL);

    data->pot_empty_cv = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(data->pot_empty_cv, NULL);

    data->pot_sem = malloc(sizeof(sem_t));
    sem_init(data->pot_sem, 0, data->pot_size);

    data->refill_mutex = malloc(sizeof(sem_t));
    sem_init(data->refill_mutex, 0, 1);

    data->villager_data = malloc(sizeof(datathread_t) * data->nb_villagers);

    for (int i = 0; i < data->nb_villagers; i++) {
        data->villager_data[i].id = i;
    }
}

int main(int ac, char **av)
{
    datathread_t data;

    if (ac != 5) {
        printUsage();
        return 84;
    }
    parser(av, &data);

    pthread_t druid_thread;
    pthread_t villagers_thread[data.nb_villagers];

    if (pthread_create(&druid_thread, NULL, druid_function, &data)) {
        printf("Error creating druid thread\n");
        return 84;
    }

    for (int i = 0; i < data.nb_villagers; i++) {
            data.villager_data[i].id = i;
        if (pthread_create(&villagers_thread[i], NULL, villager_thread, &data.villager_data[i])) {
            printf("Error creating villager thread\n");
            return 84;
        }
    }

    for (int i = 0; i < data.nb_villagers; i++) {
        pthread_join(villagers_thread[i], NULL);
    }
    pthread_join(druid_thread, NULL);

    pthread_mutex_destroy(&data.pot_mutex);
    pthread_cond_destroy(&data.pot_empty_cv);

    sem_destroy(&data.pot_sem);
    sem_destroy(&data.refill_mutex);

    free(&data.portions_left);
    free(&data.pot_mutex);
    free(&data.pot_empty_cv);
    free(&data.pot_sem);
    free(&data.refill_mutex);
    free(&data.villager_data);

    return 0;
}
