// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <unistd.h>

// sem_t wrt;             // Semaphore for writer (exclusive access)
// pthread_mutex_t mutex; // Mutex for protecting read_count
// int read_count = 0;    // Number of active readers
// int data = 0;          // Shared data

// // Reader function
// void* reader(void* arg) {
//     int id = *((int*)arg);
//     while (1) {
//         pthread_mutex_lock(&mutex);
//         read_count++;
//         if (read_count == 1) {
//             sem_wait(&wrt); // First reader locks writers
//         }
//         pthread_mutex_unlock(&mutex);

//         // Reading section
//         printf("Reader %d: read data = %d\n", id, data);
//         sleep(1);

//         pthread_mutex_lock(&mutex);
//         read_count--;
//         if (read_count == 0) {
//             sem_post(&wrt); // Last reader unlocks writers
//         }
//         pthread_mutex_unlock(&mutex);

//         sleep(rand() % 3);
//     }
// }

// // Writer function
// void* writer(void* arg) {
//     int id = *((int*)arg);
//     while (1) {
//         sem_wait(&wrt); // Writer gets exclusive access

//         // Writing section
//         data++;
//         printf("Writer %d: wrote data = %d\n", id, data);
//         sleep(2);

//         sem_post(&wrt); // Release resource

//         sleep(rand() % 3);
//     }
// }

// int main() {
//     pthread_t rtid[5], wtid[2];
//     int r_id[5], w_id[2];

//     sem_init(&wrt, 0, 1);
//     pthread_mutex_init(&mutex, NULL);

//     // Create 5 readers
//     for (int i = 0; i < 5; i++) {
//         r_id[i] = i + 1;
//         pthread_create(&rtid[i], NULL, reader, &r_id[i]);
//     }

//     // Create 2 writers
//     for (int i = 0; i < 2; i++) {
//         w_id[i] = i + 1;
//         pthread_create(&wtid[i], NULL, writer, &w_id[i]);
//     }

//     // Join threads (infinite loop, so will run continuously)
//     for (int i = 0; i < 5; i++) {
//         pthread_join(rtid[i], NULL);
//     }
//     for (int i = 0; i < 2; i++) {
//         pthread_join(wtid[i], NULL);
//     }

//     sem_destroy(&wrt);
//     pthread_mutex_destroy(&mutex);

//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include<semaphore.h>
// #include <unistd.h>

// pthread_mutex_t wrt;     // Mutex for writer (exclusive access)
// pthread_mutex_t mutex;   // Mutex for protecting read_count
// int read_count = 0;      // Number of active readers
// int data = 0;            // Shared data

// // Reader function
// void* reader(void* arg) {
//     int id = *((int*)arg);
//     while (1) {
//         pthread_mutex_lock(&mutex);
//         read_count++;
//         if (read_count == 1) {
//             pthread_mutex_lock(&wrt); // First reader locks writers
//         }
//         pthread_mutex_unlock(&mutex);

//         // Reading section
//         printf("Reader %d: read data = %d\n", id, data);
//         sleep(1);

//         pthread_mutex_lock(&mutex);
//         read_count--;
//         if (read_count == 0) {
//             pthread_mutex_unlock(&wrt); // Last reader unlocks writers
//         }
//         pthread_mutex_unlock(&mutex);

//         sleep(rand() % 3);
//     }
// }

// // Writer function
// void* writer(void* arg) {
//     int id = *((int*)arg);
//     while (1) {
//         pthread_mutex_lock(&wrt); // Writer gets exclusive access

//         // Writing section
//         data++;
//         printf("Writer %d: wrote data = %d\n", id, data);
//         sleep(2);

//         pthread_mutex_unlock(&wrt); // Release resource

//         sleep(rand() % 3);
//     }
// }

// int main() {
//     pthread_t rtid[5], wtid[2];
//     int r_id[5], w_id[2];

//     // Initialize mutexes
//     pthread_mutex_init(&wrt, NULL);
//     pthread_mutex_init(&mutex, NULL);

//     // Create 5 readers
//     for (int i = 0; i < 5; i++) {
//         r_id[i] = i + 1;
//         pthread_create(&rtid[i], NULL, reader, &r_id[i]);
//     }

//     // Create 2 writers
//     for (int i = 0; i < 2; i++) {
//         w_id[i] = i + 1;
//         pthread_create(&wtid[i], NULL, writer, &w_id[i]);
//     }

//     // Join threads (infinite loop, so will run continuously)
//     for (int i = 0; i < 5; i++) {
//         pthread_join(rtid[i], NULL);
//     }
//     for (int i = 0; i < 2; i++) {
//         pthread_join(wtid[i], NULL);
//     }

//     // Destroy mutexes
//     pthread_mutex_destroy(&wrt);
//     pthread_mutex_destroy(&mutex);

//     return 0;
// }
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

int data=0;
int readCount=0;

pthread_mutex_t mutex;
pthread_mutex_t wrt;

void* readerFun(void* args){
    int id=*((int*)args);
    while(1){
        pthread_mutex_lock(&mutex);
        readCount++;
        if(readCount==1){
            pthread_mutex_lock(&wrt);
        }
        pthread_mutex_unlock(&mutex);

        printf("reader %d read %d \n",id,data);

        pthread_mutex_lock(&mutex);
        readCount--;
        if(readCount==0){
            pthread_mutex_unlock(&wrt);
        }
        pthread_mutex_unlock(&mutex);

        sleep(rand()%3);
    }
    pthread_exit(NULL);
}
void* writerFun(void* args){
    int id=*((int*)args);
    while(1){
        pthread_mutex_lock(&wrt);

        data++;
        printf("writer %d produced %d\n",id,data);

        pthread_mutex_unlock(&wrt);

        sleep(rand()%3);
    }
    pthread_exit(NULL);
}
int main(){
    pthread_mutex_init(&wrt,NULL);
    pthread_mutex_init(&mutex,NULL);

    pthread_t writer[2];
    pthread_t reader[3];
    int writerid[2];
    int readerid[3];

    for(int i=0;i<2;i++){
        writerid[i]=i;
        pthread_create(&writer[i],NULL,writerFun,&writerid[i]);
    }
    for(int i=0;i<3;i++){
        readerid[i]=i;
        pthread_create(&reader[i],NULL,readerFun,&readerid[i]);
    }

    for(int i=0;i<2;i++){
        pthread_join(writer[i],NULL);
    }
    for(int i=0;i<5;i++){
        pthread_join(reader[i],NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&wrt);
    return 0;
}



