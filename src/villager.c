/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** villager
*/

#include "../inc/panoramix.h"

bool drink_potion(intptr_t id)
{
    intptr_t nb_fights_left = data.nb_fights_left[id];

    if (data.pot_size > 0) {
        data.pot_size--;
        nb_fights_left--;
        data.nb_fights_left[id] = nb_fights_left;
        data.portions_left--;
        printf(ATTACK(id, nb_fights_left));
        pthread_mutex_unlock(data.mutex);
        return true;
    }
    pthread_mutex_unlock(data.mutex);
    return false;
}

bool villager_handling(intptr_t id)
{
    pthread_mutex_lock(data.mutex);
    printf(VILLAGER_NEED(id, data.portions_left));
    if (drink_potion(id))
        return true;
    if (!data.refill_requested && data.nb_refills != 0) {
        printf("Villager %ld: Hey Pano wake up! We need more potion.\n", id);
        data.refill_requested = true;
        sem_post(data.druid_sem);
        sem_wait(data.villagers_sem);
        if (drink_potion(id)) {
            pthread_mutex_unlock(data.mutex);
            return true;
        }
    }
    return false;
}

void *villager_thread(void *arg)
{
    intptr_t id = (intptr_t) arg;

    printf("Villager %ld: Going into battle!\n", id);

    while (data.nb_fights_left[id] > 0) {
        if (!villager_handling(id))
            break;
        sleep(1);
    }
    data.nb_fights_left[id] = 0;
    sem_post(data.druid_sem);
    printf("Villager %ld: I'm going to sleep now.\n", id);
    return NULL;
}
