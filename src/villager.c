/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** villager
*/

#include "../inc/panoramix.h"

/*
** Called with the mutex held. Returns with it held.
** The mutex is released while waiting, so the druid can take it to refill.
*/
static bool wait_for_refill(intptr_t id)
{
    if (data.nb_refills == 0)
        return false;
    if (!data.refill_requested) {
        printf("Villager %ld: Hey Pano wake up! We need more potion.\n", id);
        data.refill_requested = true;
        sem_post(&data.druid_sem);
    }
    data.waiting_villagers++;
    pthread_mutex_unlock(&data.mutex);
    sem_wait(&data.villagers_sem);
    pthread_mutex_lock(&data.mutex);
    return true;
}

/* Returns false when the pot is empty for good */
static bool drink(intptr_t id, int *fights_left)
{
    pthread_mutex_lock(&data.mutex);
    printf("Villager %ld: I need a drink... I see %d servings left.\n",
        id, data.servings_left);
    while (data.servings_left == 0) {
        if (!wait_for_refill(id)) {
            pthread_mutex_unlock(&data.mutex);
            return false;
        }
    }
    data.servings_left--;
    (*fights_left)--;
    printf("Villager %ld: Take that roman scum! Only %d left.\n",
        id, *fights_left);
    pthread_mutex_unlock(&data.mutex);
    return true;
}

void *villager_thread(void *arg)
{
    intptr_t id = (intptr_t)arg;
    int fights_left = data.nb_fights;

    printf("Villager %ld: Going into battle!\n", id);
    while (fights_left > 0 && drink(id, &fights_left))
        usleep(data.fight_ms * 1000);
    printf("Villager %ld: I'm going to sleep now.\n", id);
    pthread_mutex_lock(&data.mutex);
    data.active_villagers--;
    if (data.active_villagers == 0)
        sem_post(&data.druid_sem);
    pthread_mutex_unlock(&data.mutex);
    return NULL;
}
