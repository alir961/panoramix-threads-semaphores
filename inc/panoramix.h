/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** utils
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#pragma once

#define VILLAGER_NEED(id, portions_left) "Villager %d: I need a drink... \
I see %d servings left.\n", id, portions_left
#define ATTACK(id, nb_fight_left) "Villager %d: Take that roman scum! \
Only %d left.\n", id, nb_fight_left
#define REFILL(nb_refills) "Druid: Ah! Yes, yes. I'm awake! Working on it! \
Beware I can only make %d more refills after this one.\n", nb_refills

typedef struct datathread_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int *nb_fights_left;
    int nb_refills;
    int portions_left;
    int max_portions;
    bool refill_requested;
    pthread_mutex_t *mutex;
    sem_t *druid_sem;
    sem_t *villagers_sem;
} datathread_t;

extern datathread_t data;

int my_putstr(char const *str);
void print_usage(void);
void *druid_thread(void *arg);
void *villager_thread(void *arg);
void free_all(pthread_t *druid, pthread_t *villager);
void create_join_thread(pthread_t *druid, pthread_t *villager);
