/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** druid
*/

#include "../inc/panoramix.h"

void *druid_function()
{
    printf("Druid: I’m ready... but sleepy...\n");
    int portions_to_fill = data.pot_size;
    int i;
    for (i = 0; i < data.nb_refills; i++) {
        pthread_mutex_lock(data.pot_mutex);
        while (data.portions_left > 0)
         {
            pthread_cond_wait(data.pot_empty_cv, data.pot_mutex);
        }
        data.portions_left = portions_to_fill;
        pthread_mutex_unlock(data.pot_mutex);
        pthread_cond_signal(data.pot_empty_cv);
        printf("Druid: Ah! Yes, yes, I’m awake! Working on it! ");
        printf("Beware I can only make %d more refills after this one.\n", data.nb_refills - i - 1);
        portions_to_fill = (data.portions_left > data.pot_size) ? data.pot_size : data.portions_left;
    }
    if (data.portions_left == 0)
        printf("Druid: I’m out of viscum. I’m going back to... zZz\n");
    return NULL;
}
