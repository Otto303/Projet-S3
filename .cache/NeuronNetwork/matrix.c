#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to multiply matrix A (m n) with vector x (n) and store the result in vector res (m)
void mat_vec_mul_optimized(double** A, double* x, double* res, int m, int n)
{
    // Matrix-vector multiplication with loop unrolling for performance
    for (size_t i = 0; i < m; i++)
    {
        double sum = 0.0;

        // Process 4 elements at a time if n is large
        size_t j = 0;
        for (; j <= n - 4; j += 4)
        {
            sum += A[i][j] * x[j] +
                   A[i][j + 1] * x[j + 1] +
                   A[i][j + 2] * x[j + 2] +
                   A[i][j + 3] * x[j + 3];
        }

        // Process the remaining elements
        for (; j < n; j++)
            sum += A[i][j] * x[j];

        res[i] = sum;
    }
}
/*
int main() {
    int m = 10000;  // Number of rows
    int n = 10000;  // Number of columns

    // Allocate memory for the matrix A
    double** A = (double**)malloc(m * sizeof(double*));
    for (int i = 0; i < m; i++) {
        A[i] = (double*)malloc(n * sizeof(double));
    }

    // Allocate memory for vectors x and y
    double* x = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(m * sizeof(double));

    // Initialize matrix A and vector x with random values
    srand(time(NULL));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (double)(rand() % 100) / 10.0;
        }
    }

    for (int i = 0; i < n; i++) {
        x[i] = (double)(rand() % 100) / 10.0;
    }

    // Measure the execution time
    clock_t start = clock();
    mat_vec_mul_optimized(A, x, y, m, n);
    clock_t end = clock();

    // Print execution time
    printf("Matrix-vector multiplication completed in %lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Free allocated memory
    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}
*/
