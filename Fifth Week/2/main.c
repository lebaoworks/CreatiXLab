#include <stdio.h> //I/O
#include <pthread.h> //thread
#include <time.h> //execution time
#include <windows.h> //sleep
#include <semaphore.h>
#define N 120

sem_t semaphore;
int number = 0;

void *threadFunc()
{
    while (number<N)
    {
        sem_wait(&semaphore);
        printf("%d \n",number++);
        sem_post(&semaphore);
    }
}
int main()
{
    int i;
    double semaphore_time, one_thread_time;

    clock_t start = clock();
    sem_init(&semaphore,0,6);
    pthread_t threads[6];
    for (i=0; i<6; i++)
        pthread_create(&threads[i], NULL, threadFunc, NULL);
    for (i=0; i<6; i++)
        pthread_join(threads[i],NULL);
    clock_t end = clock();
    semaphore_time = (double)(end-start)/CLK_TCK;

    start = clock();
    for (number=0; number<N; number++)
        printf("%d \n",number);
    end = clock();

    printf("Time for semaphore: %f\n",semaphore_time);
    printf("Time for 1 thread: %0.5f\n",(double)(end-start)/CLK_TCK);
    return 0;
}
