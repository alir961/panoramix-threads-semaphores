/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** druid
*/

#include "../inc/panoramix.h"

/* Called with the mutex held: refill the pot and wake every waiting villager */
static void refill_pot(void)
{
    data.servings_left = data.pot_size;
    data.nb_refills--;
    data.refill_requested = false;
    printf("Druid: Ah! Yes, yes. I'm awake! Working on it! Beware I can "
        "only make %d more refills after this one.\n", data.nb_refills);
    for (; data.waiting_villagers > 0; data.waiting_villagers--)
        sem_post(&data.villagers_sem);
}

void *druid_thread(void *arg)
{
    bool done = false;

    (void)arg;
    printf("Druid: I'm ready... but sleepy...\n");
    while (!done) {
        sem_wait(&data.druid_sem);
        pthread_mutex_lock(&data.mutex);
        if (data.refill_requested && data.nb_refills > 0)
            refill_pot();
        done = data.nb_refills == 0 || data.active_villagers == 0;
        pthread_mutex_unlock(&data.mutex);
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    return NULL;
}
