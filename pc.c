#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5   // Size of the buffer

int buffer[BUFFER_SIZE];
int in = 0, out = 0;   // Indices for producer and consumer

// Semaphores
sem_t empty;   // Counts empty slots initially 5
sem_t full;    // Counts full slots 0
pthread_mutex_t mutex; // To protect buffer access

// Producer function
void* producer(void* arg) {
    int item;
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty); // Wait for empty slot
        pthread_mutex_lock(&mutex);

        // Critical section
        buffer[in] = i;
        printf("Producer produced: %d\n", buffer[in]);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Signal full slot

        sleep(4); // Simulate time gap
    }
    pthread_exit(NULL);
}

// Consumer function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full); // Wait for available item
        pthread_mutex_lock(&mutex);

        // Critical section
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Signal empty slot

        sleep(2); // Simulate time gap
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

