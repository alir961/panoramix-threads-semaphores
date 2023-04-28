/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** villager
*/

#include "../inc/villager.h"
#include "../inc/utils.h"

void* villager_thread(void *arg)
{
    datathread_t *data = (datathread_t*) arg;
    int id = data->id;
    int nb_fights = data->nb_fights;
    int nb_refills = data->nb_refills;
    int pot_size = data->pot_size;
    int *portions_left = data->portions_left;
    pthread_mutex_t *pot_mutex = data->pot_mutex;
    pthread_cond_t *pot_empty_cv = data->pot_empty_cv;
    sem_t *pot_sem = data->pot_sem;
    sem_t *refill_mutex = data->refill_mutex;
    
    printf("Villager %d: Going into battle!\n", id);
    for (int i = 0; i < nb_fights; i++) {
        sem_wait(pot_sem);
        if (*portions_left > 0) {
            (*portions_left)--;
            printf("Villager %d: I need a drink... I see %d servings left.\n", id, *portions_left);
            sem_post(pot_sem);
        } else {
            sem_wait(refill_mutex);
            if (nb_refills > 0) {
                printf("Villager %d: Hey Pano wake up! We need more potion.\n", id);
                nb_refills--;
                *portions_left = pot_size - 1;
            } else {
                printf("Villager %d: I'm going to sleep now.\n", id);
                sem_post(refill_mutex);
                sem_post(pot_sem);
                return NULL;
            }
            sem_post(refill_mutex);
            sem_post(pot_sem);
        }
        printf("Villager %d: Take that roman scum! Only %d fights left.\n", id, nb_fights - i - 1);
        usleep(rand() % 1000 + 1000);
    }
    return NULL;
}
