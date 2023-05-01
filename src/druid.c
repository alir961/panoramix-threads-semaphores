/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** druid
*/

#include "../inc/panoramix.h"

void *druid_thread()
{
    printf("Druid: I'm ready... but sleepy...\n");
    while (1) {
        sem_wait(data.druid_sem);
        if (data.nb_refills == 0)
            break;
        if (data.pot_size == 0) {
            data.nb_refills--;
            data.portions_left = data.pot_size;
            printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only make %d more refills after this one.\n", data.nb_refills);
            sem_post(data.villagers_sem);
            if (data.nb_refills == 0)
                break;
        }
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
}
