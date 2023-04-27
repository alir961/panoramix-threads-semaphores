/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** main
*/
#include "../inc/utils.h"
#include "../inc/druid.h"

void parser(char **av, datathread_t *data)
{
    int nb_villagers = atoi(av[1]);
    int pot_size = atoi(av[2]);
    int nb_fights = atoi(av[3]);
    int nb_refills = atoi(av[4]);
    int portions_left = pot_size;
    pthread_mutex_t pot_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t pot_empty_cv = PTHREAD_COND_INITIALIZER;
    
    data->nb_villagers = nb_villagers;
    data->pot_size = pot_size;
    data->nb_fights = nb_fights;
    data->nb_refills = nb_refills;
    data->portions_left = &portions_left;
    data->pot_mutex = &pot_mutex;
    data->pot_empty_cv = &pot_empty_cv;
}

int main(int ac, char **av)
{
    datathread_t data;
    pthread_t druid_thread;
    
    if (ac != 5) {
        printUsage();
        return 84;
    }
    parser(av, &data);

    if (pthread_create(&druid_thread, NULL, druid_function, &data)) {
        printf("Error creating druid thread\n");
        return 84;
    }
    
    pthread_mutex_destroy(data.pot_mutex);
    pthread_cond_destroy(data.pot_empty_cv);
    return 0;
}
