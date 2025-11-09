#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// producer produces the item and put it in the buffer
// consumer take that item from the buffer and do it's process


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
/*
sem_wait(&empty); makes the producer wait if the buffer is full. 
It ensures that the producer only produces when there’s at least one empty slot available in the buffer.

        This is a counting semaphore operation.
        It decrements the value of the semaphore empty.
        If empty is greater than 0, it decrements and continues immediately.
        If empty is 0, it means the buffer is full →the producer thread is blocked (waits) until a consumer signals that a slot has become empty*/

        pthread_mutex_lock(&mutex);

        // Critical section
        buffer[in] = i;
        printf("Producer produced: %d\n", buffer[in]);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Signal full slot

        /*
        sem_post(&full); signals that the producer has produced an item and increased the count of full slots, allowing a consumer to proceed.
        This operation increments the semaphore full.
            It means the producer has added a new item → now one more slot is full.
            If any consumer thread was waiting on sem_wait(&full);, it gets unblocked (woken up) to consume an item.*/

        sleep(4); // Simulate time gap
    }
    pthread_exit(NULL);
}

// Consumer function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full); // Wait for available item
        /*
        sem_wait(&full) makes the consumer wait if the buffer is empty. It ensures the consumer only consumes when there is at least one filled slot.
        pthread_mutex_lock(&mutex);
        */

        // Critical section
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        /*Updates the out index using the circular buffer formula:
        (out + 1) % BUFFER_SIZE ensures that once the end of the buffer is reached, it wraps around to index 0.*/
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Signal empty slot
        /*Increments the empty semaphore count.
        Signals that there is now one more empty slot available in the buffer for the producer to use*/

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

