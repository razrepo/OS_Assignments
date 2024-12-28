#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Mutexes
pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t bowls[2];

void eating(int philosopher_id)
{
    printf("Philosopher %d is eating\n", philosopher_id);
    usleep(2000000); // Simulating eating time
}

void thinking(int philosopher_id)
{
    printf("Philosopher %d is thinking\n", philosopher_id);
    usleep(2000000); // Simulating thinking time
}

void *philosopher(void *args)
{
    int philosopher_id = *((int *)args);
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1)
    {
        thinking(philosopher_id);

        // Attempt to pick up forks
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);

        // Check if both bowls are available
        int bowl1 = 0;
        int bowl2 = 1;

        // Try to lock both bowls
        if (pthread_mutex_trylock(&bowls[bowl1]) == 0 && pthread_mutex_trylock(&bowls[bowl2]) == 0)
        {
            // Start eating
            eating(philosopher_id);

            // Put down forks and bowls
            pthread_mutex_unlock(&forks[left_fork]);
            pthread_mutex_unlock(&forks[right_fork]);
            pthread_mutex_unlock(&bowls[bowl1]);
            pthread_mutex_unlock(&bowls[bowl2]);
        }
        else
        {
            // Release forks if bowls are not available
            pthread_mutex_unlock(&forks[left_fork]);
            pthread_mutex_unlock(&forks[right_fork]);
        }
    }
}
// void *philosopher(void *args)
// {
//     int philosopher_id = *((int *)args);
//     int left_fork = philosopher_id;
//     int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

//     while (1)
//     {
//         thinking(philosopher_id);

//         // Attempt to pick up forks
//         pthread_mutex_lock(&forks[left_fork]);
//         pthread_mutex_lock(&forks[right_fork]);

//         // Check if both bowls are available
//         int bowl1 = 0;
//         int bowl2 = 1;

//         // Try to lock both bowls
//         if (pthread_mutex_trylock(&bowls[bowl1]) == 0 && pthread_mutex_trylock(&bowls[bowl2]) == 0)
//         {
//             // Start eating
//             eating(philosopher_id);

//             // Put down forks and bowls
//             pthread_mutex_unlock(&forks[left_fork]);
//             pthread_mutex_unlock(&forks[right_fork]);
//             pthread_mutex_unlock(&bowls[bowl1]);
//             pthread_mutex_unlock(&bowls[bowl2]);

//             // Introduce a delay before the next attempt
//             usleep(1000000); // Simulating a pause between actions
//         }
//         else
//         {
//             // Release forks if bowls are not available
//             pthread_mutex_unlock(&forks[left_fork]);
//             pthread_mutex_unlock(&forks[right_fork]);
//         }
//     }
// }

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutexes for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Initialize mutexes for bowls
    for (int i = 0; i < 2; ++i)
    {
        pthread_mutex_init(&bowls[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads (This will never happen in this example since philosophers run in an infinite loop)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        pthread_mutex_destroy(&forks[i]);
    }

    // Destroy mutexes for bowls
    for (int i = 0; i < 2; ++i)
    {
        pthread_mutex_destroy(&bowls[i]);
    }

    return 0;
}