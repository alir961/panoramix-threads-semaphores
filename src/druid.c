/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** druid
*/

#include "../inc/panoramix.h"

void *druid_thread(void)
{
    printf("Druid: I'm ready... but sleepy...\n");
    while (1) {
        sem_wait(data.druid_sem);
        if (data.nb_refills > 0 && data.pot_size == 0) {
            data.portions_left = data.pot_size;
            data.nb_refills--;
            printf(REFILL(data.nb_refills));
            sem_post(data.villagers_sem);
        } else {
            break;
        }
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
}
