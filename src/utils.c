/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** argument parsing and thread lifecycle
*/

#include <errno.h>
#include <limits.h>
#include "../inc/panoramix.h"

void print_usage(void)
{
    printf("USAGE: ./panoramix <nb_villagers> <pot_size> "
        "<nb_fights> <nb_refills>\n");
    printf("Values must be > 0\n");
}

static bool parse_positive(const char *str, int *out)
{
    char *end = NULL;
    long value;

    errno = 0;
    value = strtol(str, &end, 10);
    if (errno != 0 || end == str || *end != '\0' || value <= 0
        || value > INT_MAX)
        return false;
    *out = (int)value;
    return true;
}

bool parse_arguments(int ac, char **av)
{
    const char *fight_ms = getenv("PANORAMIX_FIGHT_MS");

    if (ac != 5 || !parse_positive(av[1], &data.nb_villagers)
        || !parse_positive(av[2], &data.pot_size)
        || !parse_positive(av[3], &data.nb_fights)
        || !parse_positive(av[4], &data.nb_refills))
        return false;
    data.servings_left = data.pot_size;
    data.active_villagers = data.nb_villagers;
    data.waiting_villagers = 0;
    data.refill_requested = false;
    data.fight_ms = fight_ms ? (unsigned int)atoi(fight_ms) : 1000;
    return true;
}

static int join_all(pthread_t *villagers, int created, pthread_t *druid)
{
    for (int i = 0; i < created; i++)
        pthread_join(villagers[i], NULL);
    if (druid)
        pthread_join(*druid, NULL);
    return created == data.nb_villagers && druid ? 0 : EXIT_ERROR;
}

int run_simulation(void)
{
    pthread_t druid;
    pthread_t *villagers = malloc(sizeof(pthread_t) * data.nb_villagers);
    int created = 0;
    int status;

    if (!villagers)
        return EXIT_ERROR;
    pthread_mutex_init(&data.mutex, NULL);
    sem_init(&data.druid_sem, 0, 0);
    sem_init(&data.villagers_sem, 0, 0);
    if (pthread_create(&druid, NULL, druid_thread, NULL) != 0)
        return free(villagers), EXIT_ERROR;
    for (; created < data.nb_villagers; created++)
        if (pthread_create(&villagers[created], NULL, villager_thread,
            (void *)(intptr_t)created) != 0)
            break;
    status = join_all(villagers, created, &druid);
    pthread_mutex_destroy(&data.mutex);
    sem_destroy(&data.druid_sem);
    sem_destroy(&data.villagers_sem);
    free(villagers);
    return status;
}
