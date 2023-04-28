/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** druid
*/

#include "../inc/druid.h"
#include "../inc/utils.h"

void *druid_function(void *arg)
{
    datathread_t *data = (datathread_t*) arg;
    int nb_fights = data->nb_fights;
    int nb_refills = data->nb_refills;
    int pot_size = data->pot_size;
    int *portions_left = data->portions_left;
    pthread_mutex_t *pot_mutex = data->pot_mutex;
    pthread_cond_t *pot_empty_cv = data->pot_empty_cv;
    
    printf("Druid: I’m ready... but sleepy...\n");
    int portions_to_fill = pot_size;
    int i;
    for (i = 0; i < nb_refills; i++) {
        pthread_mutex_lock(pot_mutex);
        while (*portions_left > 0) {
            pthread_cond_wait(pot_empty_cv, pot_mutex);
        }
        *portions_left = portions_to_fill;
        pthread_mutex_unlock(pot_mutex);
        pthread_cond_signal(pot_empty_cv);
        printf("Druid: Ah! Yes, yes, I’m awake! Working on it! ");
        printf("Beware I can only make %d more refills after this one.\n", nb_refills - i - 1);
        portions_to_fill = (*portions_left > pot_size) ? pot_size : *portions_left;
    }
    if (*portions_left == 0)
        printf("Druid: I’m out of viscum. I’m going back to... zZz\n");
    return NULL;
}
