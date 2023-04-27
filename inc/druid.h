/*
** EPITECH PROJECT, 2023
** B-CCP-400-LYN-4-1-panoramix-ali.raad
** File description:
** druid
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *druid_function(void *arg);

typedef struct {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int *portions_left;
    pthread_mutex_t *pot_mutex;
    pthread_cond_t *pot_empty_cv;
} datathread_t;
