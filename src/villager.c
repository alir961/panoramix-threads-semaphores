/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** villager
*/

#include "../inc/panoramix.h"

void* villager_thread(void *arg)
{
    int id = (long)arg;

    printf("Villager %d: Going into battle!\n", id);
    for (int i = 0; i < data.nb_fights; i++) {
        sem_wait(data.pot_sem);
        if (data.portions_left > 0) {
            printf("Villager %d: I need a drink... I see %d servings left.\n", id, data.portions_left);
            sem_post(data.pot_sem);
            data.portions_left--;
        } else {
            sem_wait(data.refill_mutex);
            if (data.nb_refills > 0) {
                printf("Villager %d: Hey Pano wake up! We need more potion.\n", id);
                data.nb_refills--;
                data.portions_left = data.pot_size - 1;
            } if (data.nb_fights == 0) {
                printf("Villager %d: I'm going to sleep now.\n", id);
                sem_post(data.refill_mutex);
                sem_post(data.pot_sem);
                return NULL;
            }
            sem_post(data.refill_mutex);
            sem_post(data.pot_sem);
        }
        printf("Villager %d: Take that roman scum! Only %d fights left.\n", id, data.nb_fights - i - 1);
    }
    return NULL;
}
