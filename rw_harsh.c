/*
in this program there are two Critical section 
1. readCount: this Critical section used by the Readers 
To update the count safely (shared between readers)
- protected by the mutex
-no two readers increment/decrement it simultaneously

2. data : Writers and Readers, Writers and Readers
- protected by the wrt*/



#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

int data=0; // shared resource 
int readCount=0; // number of active readers

pthread_mutex_t mutex;  //mutex ensures that only 1 thread can access the Critical section
/*
| Function                            | Purpose                                                      |
| ----------------------------------- | ------------------------------------------------------------ |
| `pthread_mutex_lock(&mutex);`       | Locks the mutex — blocks if another thread already holds it. |
| `pthread_mutex_unlock(&mutex);`     | Unlocks the mutex — allows other threads to proceed.         |
| `pthread_mutex_init(&mutex, NULL);` | Initializes the mutex before using it.                       |
| `pthread_mutex_destroy(&mutex);`    | Frees resources when done.                                   |
*/

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



/*


#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>

int main(){

    pthread_mutex_init(&wrt,NULL);
    pthread_mutex_init(&mutex,NULL);


    p_thread_t writer[2];
    p_thread_t reader[3];

    int wid[2];
    int rid[3];

    for(int i=0;i<n;i++){

        wid[i]=i;
        pthread_create(&reader[i],NULL,readerFun,&wid[i]);
    }


    for(int i=0;i<3;i++){
        rid[i]=i;
        pthread_create(&writer[i],NULL,writerFun,&rid[i]);
    }


    for(int i)


}
*/