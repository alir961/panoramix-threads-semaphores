/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** utils
*/

#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int my_putstr(char const *str);
void printUsage();

typedef struct datathread_t datathread_t;

typedef struct datathread_t {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int *portions_left;
    pthread_mutex_t *pot_mutex;
    pthread_cond_t *pot_empty_cv;
    sem_t *pot_sem;
    sem_t *refill_mutex;
    int id;
    datathread_t *villager_data;
} datathread_t;
