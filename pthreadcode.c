#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define N 1000
#define THREADS 4

int A[N][N], B[N][N], C[N][N];

void *multiplier(void *arg)
{
    int thread_id = *(int *)arg;
    int s = thread_id * N / THREADS;
    int e = (thread_id + 1) * N / THREADS;

    for (int i = s; i < e; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main()
{

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    pthread_t threads[THREADS];
    int thread_ids[THREADS];

    // initialize matrices with random values
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = i * j;
            B[i][j] = i + j;
            //A[i][j] = rand() % 10;
           // B[i][j] = rand() % 10;
        }
    }

    // create threads and start multiplication
    for (int i = 0; i < THREADS; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiplier, (void *)&thread_ids[i]);
    }

    // wait for threads to finish
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);

    printf("Result matrix C:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    // calculate time difference
    double execution_time = (end_time.tv_sec - start_time.tv_sec) +
                            (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Execution time: %.6f seconds\n", execution_time);

    return 0;
}
