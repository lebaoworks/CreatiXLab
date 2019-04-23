#include <stdio.h> //I/O
#include <pthread.h> //thread
#include <time.h> //random seed
#include <windows.h> //sleep

void *thread1Func(void *threadId)
{
    srand(time(0)); //Seed for random integer
    int number;
    while (1)
    {
        FILE *pFile = fopen("number.txt","w");
        if (pFile != NULL)
        {
            number = rand()%31;
            fprintf(pFile, "%d", number);
            fclose(pFile);
        }
        Sleep(2000);
    }
}
void *thread2Func(void *threadId)
{
    int number;
    while (1)
    {
        FILE *pFile = fopen("number.txt", "r");
        if (pFile != NULL)
        {
            //read in file
            fscanf(pFile,"%d",&number);
            fclose(pFile);

            number*=number;
            printf("%d\n",number);

            pFile = fopen("output.txt", "w");
            if (pFile != NULL)
            {
                fprintf(pFile, "%d", number);
                fclose(pFile);
            }
        }
        Sleep(1000);
    }
}
int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread1, NULL, thread1Func, (void*) &thread1);
    pthread_create(&thread2, NULL, thread2Func, (void*) &thread1);
    pthread_exit(NULL);
    return 0;
}
