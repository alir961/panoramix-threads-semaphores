# Panoramix — Thread Synchronisation in C

![CI](https://github.com/alir961/panoramix-threads-semaphores/actions/workflows/ci.yml/badge.svg)

A classic concurrency problem written in C with POSIX threads, a mutex and semaphores. Villagers (threads) drink a serving from a shared pot before each fight. When the pot is empty, one villager wakes the druid (another thread), who refills it a limited number of times. Everyone must finish without deadlocks, lost wake-ups or data races.

```bash
make
./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
./panoramix 3 2 2 1
```

```
Druid: I'm ready... but sleepy...
Villager 0: Going into battle!
Villager 0: I need a drink... I see 0 servings left.
Villager 0: Hey Pano wake up! We need more potion.
Druid: Ah! Yes, yes. I'm awake! Working on it! Beware I can only make 0 more refills after this one.
Druid: I'm out of viscum. I'm going back to... zZz
Villager 0: Take that roman scum! Only 1 left.
...
```

## Design

- One **mutex** protects all shared state: servings, refills left, active and waiting villagers.
- `druid_sem` wakes the druid, either for a refill request or when the last villager goes home.
- `villagers_sem` releases waiting villagers. After a refill the druid posts it **once per waiting villager**, so nobody is left behind.
- A villager **releases the mutex before waiting** for a refill, so the druid can take it.
- Only one refill request is raised at a time (`refill_requested`). Villagers stop once the pot is empty and no refills are left.

## Testing

`tests/stress.sh` runs 96 parameter combinations and checks the invariants of the simulation:

- every serving is drunk: total fights = min(villagers × fights, pot × (refills + 1))
- no villager fights more than allowed, and no more refills are made than allowed
- every thread terminates (a timeout catches deadlocks)
- invalid arguments exit with code 84

```bash
make tests_run   # builds with -fsanitize=thread and -fsanitize=address,undefined and runs the suite on both
```

`PANORAMIX_FIGHT_MS` sets the fight duration (default 1000 ms). The tests set it to 0 to run fast.

### Fixing the original version

My first version (Epitech, 2023) hung or crashed in **60 of the 96 cases**. ThreadSanitizer, AddressSanitizer and the invariant checks led to these fixes:

| Bug | Symptom |
|---|---|
| Thread arrays allocated before parsing the arguments (size 1) | Heap buffer overflow, crash with many villagers |
| A villager waited for the refill while still holding the mutex the druid needed | Deadlock |
| The mutex was unlocked twice after a refill | Undefined behaviour |
| A single semaphore post after a refill | Other waiting villagers never woke up |
| The druid read shared counters without the lock, and stopped based on one villager's state | Data races, the druid exiting too early or too late |
| Compiler flags set in `FLAGS`, which make ignores | Warnings never enforced |

The current version passes the whole suite under both sanitizers, repeatedly. CI runs it on every push.
