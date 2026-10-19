/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** panoramix
*/

#pragma once

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EXIT_ERROR 84

typedef struct datathread_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int servings_left;
    int active_villagers;
    int waiting_villagers;
    bool refill_requested;
    unsigned int fight_ms;
    pthread_mutex_t mutex;
    sem_t druid_sem;
    sem_t villagers_sem;
} datathread_t;

extern datathread_t data;

void print_usage(void);
bool parse_arguments(int ac, char **av);
void *druid_thread(void *arg);
void *villager_thread(void *arg);
int run_simulation(void);
