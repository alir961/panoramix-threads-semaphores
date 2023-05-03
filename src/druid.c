/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** druid
*/

#include "../inc/panoramix.h"

void *druid_thread(void *arg)
{
    int id = (int*) arg;
    int nb_villagers_left = data.nb_fights_left[id];
    printf("Druid: I'm ready... but sleepy...\n");
    while (1) {
        sem_wait(data.druid_sem);
        pthread_mutex_lock(data.mutex);
        if (data.nb_refills > 0 && data.pot_size == 0) {
            data.pot_size = data.max_portions;
            data.portions_left = data.max_portions - 1;
            data.nb_refills--;
            printf(REFILL(data.nb_refills));
            sem_post(data.villagers_sem);
        }
        pthread_mutex_unlock(data.mutex);
        if (data.nb_refills <= 0 || nb_villagers_left <= 0) {
            break;
        }
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
}
