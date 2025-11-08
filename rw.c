#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;             // Semaphore for writer (exclusive access)
pthread_mutex_t mutex; // Mutex for protecting read_count
int read_count = 0;    // Number of active readers
int data = 0;          // Shared data

// Reader function
void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&wrt); // First reader locks writers
        }
        pthread_mutex_unlock(&mutex);

        // Reading section
        printf("Reader %d: read data = %d\n", id, data);
        sleep(1);

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt); // Last reader unlocks writers
        }
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3);
    }
}

// Writer function
void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&wrt); // Writer gets exclusive access

        // Writing section
        data++;
        printf("Writer %d: wrote data = %d\n", id, data);
        sleep(2);

        sem_post(&wrt); // Release resource

        sleep(rand() % 3);
    }
}

int main() {
    pthread_t rtid[5], wtid[2];
    int r_id[5], w_id[2];

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create 5 readers
    for (int i = 0; i < 5; i++) {
        r_id[i] = i + 1;
        pthread_create(&rtid[i], NULL, reader, &r_id[i]);
    }

    // Create 2 writers
    for (int i = 0; i < 2; i++) {
        w_id[i] = i + 1;
        pthread_create(&wtid[i], NULL, writer, &w_id[i]);
    }

    // Join threads (infinite loop, so will run continuously)
    for (int i = 0; i < 5; i++) {
        pthread_join(rtid[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(wtid[i], NULL);
    }

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}

