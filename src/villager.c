/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** villager
*/

#include "../inc/panoramix.h"

bool drink_potion(int id)
{
    int nb_fights_left = data.nb_fights_left[id];

    pthread_mutex_lock(data.mutex);
    if (data.pot_size > 0) {
        data.pot_size--;
        nb_fights_left--;
        data.nb_fights_left[id] = nb_fights_left;
        data.portions_left--;
        printf(VILLAGER_ATTACK(id, nb_fights_left));
        pthread_mutex_unlock(data.mutex);
        return true;
    }
    return false;
}

bool villager_handling(int id)
{
    printf(VILLAGER_NEED(id, data.portions_left));

    while (data.nb_refills > 0) {
        if (drink_potion(id)) {
            return true;
        } else {
            printf("Villager %d: Hey Pano wake up! We need more potion.\n", id);
            sem_post(data.druid_sem);
            sem_wait(data.villagers_sem);
        }
    }
    return false;
}

void *villager_thread(void *arg)
{
    int id = (int*) arg;

    printf("Villager %d: Going into battle!\n", id);

    while (data.nb_fights_left[id] != 0) {
        if (!villager_handling(id))
            break;
    }
    printf("Villager %d: I'm going to sleep now.\n", id);
}
