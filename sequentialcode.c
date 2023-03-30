#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main() {
    int **A, **B, **C;

    // Allocate memory for matrices A, B, and C
    A = (int **) calloc(N, sizeof(int *));
    B = (int **) calloc(N, sizeof(int *));
    C = (int **) malloc(N * sizeof(int *));
    for(int i = 0; i < N; i++) {
        A[i] = (int *) calloc(N, sizeof(int));
        B[i] = (int *) calloc(N, sizeof(int));
        C[i] = (int *) malloc(N * sizeof(int));
    }

    // Initialize matrices A and B
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = i * j;
            B[i][j] = i + j;
        }
    }

    // Multiply matrices A and B
    clock_t start_time = clock();
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
            
        }
    }
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

    // Free the memory
    for(int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
