#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

struct car
{
    int id;
    int lrdirec;
};

int numCars = 0;
int leftV = 0;
int rightV = 0;
int tV = 2;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t left, right;

void *cross_bridge(void *ptr)
{
    struct car *car = (struct car *)ptr;

    sem_t *side = (car->lrdirec == 0) ? &left : &right;

    while (1)
    {
        pthread_mutex_lock(&mutex);

        while (numCars >= 5 || (car->lrdirec == 0 && rightV > 0) || (car->lrdirec == 1 && leftV > 0))
        {
            pthread_cond_wait(&cond, &mutex);
        }

        pthread_mutex_unlock(&mutex);

        sem_wait(side);

        // crossing the bridge

        pthread_mutex_lock(&mutex);

        numCars += 1;
        if (car->lrdirec == 0)
            leftV += 1;
        else
            rightV += 1;

        if (numCars < 5)
            pthread_cond_broadcast(&cond);

        pthread_mutex_unlock(&mutex);

        // printf("Car id %d is now crossing the bridge\n", car->id);
        sleep(tV);
        if (car->lrdirec == 0)
        {
            printf("Car number %d has crossed the bridge from left side\n", car->id);
        }
        else
        {
            printf("Car number %d has crossed the bridge from right side\n", car->id);
        }

        pthread_mutex_lock(&mutex);

        numCars -= 1;
        if (car->lrdirec == 0)
            leftV -= 1;
        else
            rightV -= 1;

        if (numCars < 5)
            pthread_cond_broadcast(&cond);

        pthread_mutex_unlock(&mutex);

        sem_post(side);
    }

    return NULL;
}

int main()
{
    int rCars;
    int lCars;

    printf("Enter number of cars crossing from the left side: ");
    scanf("%d", &lCars);
    printf("Enter number of cars crossing from the right side: ");
    scanf("%d", &rCars);

    sem_init(&left, 0, 5);
    sem_init(&right, 0, 5);

    pthread_t tid[lCars + rCars];
    struct car args[lCars + rCars];

    int j = 0;
    while (j < lCars)
    {
        args[j].id = j + 1;
        args[j].lrdirec = 0;
        pthread_create(&tid[j], NULL, cross_bridge, (void *)&args[j]);
        j++;
    }

    int i = lCars;
    while (i < rCars + lCars)
    {
        args[i].id = i + 1;
        args[i].lrdirec = 1;
        pthread_create(&tid[i], NULL, cross_bridge, (void *)&args[i]);
        i++;
    }

    int k = 0;
    while (k < lCars + rCars)
    {
        pthread_join(tid[k], NULL);
        k++;
    }

    sem_destroy(&left);
    sem_destroy(&right);

    return 0;
}
