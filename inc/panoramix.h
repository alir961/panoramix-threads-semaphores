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

#pragma once

typedef struct datathread_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int portions_left;
    int id;
    pthread_mutex_t *pot_mutex;
    pthread_cond_t *pot_empty_cv;
    sem_t *pot_sem;
    sem_t *refill_mutex;
} datathread_t;

extern datathread_t data;

int my_putstr(char const *str);
void printUsage();
void *druid_function();
void *villager_thread(void *arg);
