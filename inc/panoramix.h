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

typedef struct datathread_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int *nb_fights_left;
    int nb_refills;
    int portions_left;
    pthread_mutex_t *mutex;
    sem_t *druid_sem;
    sem_t *villagers_sem;
} datathread_t;

extern datathread_t data;

int my_putstr(char const *str);
void printUsage();
void *druid_thread();
void *villager_thread(void *arg);
void free_all(pthread_t *thread);
void create_join_thread(pthread_t *thread);
