#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000

int A[N][N], B[N][N], C[N][N];

void multiply() {
    #pragma omp parallel for
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            float cij = C[i][j];
            for(int k = 0; k < N; k++) {
                cij += A[i][k] * B[k][j];
            }
            C[i][j] = cij;
        }
    }
}

int main() {

    // Initialize matrices A and B
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Multiply matrices A and B using OpenMP
    clock_t start_time = clock();
    multiply();
    clock_t end_time = clock();

    // Print the result and execution time
    printf("Result matrix C:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    double duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Execution time: %lf seconds.\n", duration);


    return 0;
}
