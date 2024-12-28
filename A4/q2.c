#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int capacity, passengers;
sem_t car_sem, passenger_sem, ride_sem;

void *car(void *args)
{
    while (1)
    {
        printf("Car is ready to load passengers.\n");
        for (int i = 0; i < capacity; i++)
            sem_post(&passenger_sem);
        printf("Car is loaded with passengers.\n");
        printf("Car is running.\n");
        sleep(2);
        printf("Car has finished running.\n");
        for (int i = 0; i < capacity; i++)
            sem_post(&ride_sem);
        printf("Car is unloaded.\n");
    }
}

void *passenger(void *args)
{
    int id = *(int *)args;
    while (1)
    {
        sem_wait(&passenger_sem);
        printf("Passenger %d is boarding the car.\n", id);
        sem_wait(&ride_sem);
        printf("Passenger %d is getting off the car.\n", id);
    }
}

int main()
{
    printf("Enter the capacity of the car: ");
    scanf("%d", &capacity);
    printf("Enter the total number of passengers: ");
    scanf("%d", &passengers);

    if (capacity <= 0 || passengers <= 0)
    {
        printf("Error: The number of passengers and the capacity of the car must be greater than 0.\n");
        return 1;
    }

    pthread_t car_thread, passenger_threads[passengers];
    sem_init(&car_sem, 0, 0);
    sem_init(&passenger_sem, 0, 0);
    sem_init(&ride_sem, 0, 0);

    pthread_create(&car_thread, NULL, car, NULL);
    int ids[passengers];
    for (int i = 0; i < passengers; i++)
    {
        ids[i] = i + 1;
        pthread_create(&passenger_threads[i], NULL, passenger, &ids[i]);
    }

    pthread_join(car_thread, NULL);
    for (int i = 0; i < passengers; i++)
        pthread_join(passenger_threads[i], NULL);

    return 0;
}
