#include <gmp.h>
#include <time.h>
#include <stdio.h>

void multiply(mpz_t F[2][2], mpz_t M[2][2]);
void power(mpz_t F[2][2], int n);
void fibonacci(int n, mpz_t result);
void fibonacci_traditional_method(int n, mpz_t result);

int main() {
    int test_values[] = {50, 100, 1000, 10000, 100000, 1000000};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (int i = 0; i < num_tests; i++) {
        int n = test_values[i];
        mpz_t result_matrix, result_traditional;
        mpz_inits(result_matrix, result_traditional, NULL);

        clock_t start_time_matrix = clock();
        fibonacci(n, result_matrix);
        clock_t end_time_matrix = clock();

        double execution_time_matrix = ((double) (end_time_matrix - start_time_matrix)) / CLOCKS_PER_SEC;
        printf("Matrix method execution time for the %dth Fibonacci number: %f seconds\n", n, execution_time_matrix);

        clock_t start_time_traditional = clock();
        fibonacci_traditional_method(n, result_traditional);
        clock_t end_time_traditional = clock();

        double execution_time_traditional = ((double) (end_time_traditional - start_time_traditional)) / CLOCKS_PER_SEC;
        printf("Traditional method execution time for the %dth Fibonacci number: %f seconds\n", n, execution_time_traditional);

        mpz_clears(result_matrix, result_traditional, NULL);
    }

    return 0;
}

// Function to multiply two matrices F and M of size 2*2, and put the multiplication result back to F[][]
void multiply(mpz_t F[2][2], mpz_t M[2][2]) {
    mpz_t x, y, z, w;
    mpz_inits(x, y, z, w, NULL);

    // Computing values to store in matrix F
    mpz_mul(x, F[0][0], M[0][0]);
    mpz_addmul(x, F[0][1], M[1][0]);

    mpz_mul(y, F[0][0], M[0][1]);
    mpz_addmul(y, F[0][1], M[1][1]);

    mpz_mul(z, F[1][0], M[0][0]);
    mpz_addmul(z, F[1][1], M[1][0]);

    mpz_mul(w, F[1][0], M[0][1]);
    mpz_addmul(w, F[1][1], M[1][1]);

    // Storing the multiplication results back to matrix F
    mpz_set(F[0][0], x);
    mpz_set(F[0][1], y);
    mpz_set(F[1][0], z);
    mpz_set(F[1][1], w);

    mpz_clears(x, y, z, w, NULL);
}

// Function to calculate F[][] raise to the power n and put the result in F[][]
void power(mpz_t F[2][2], int n) {
    if (n == 0 || n == 1)
        return;
    mpz_t M[2][2];
    mpz_init_set_ui(M[0][0], 1);
    mpz_init_set_ui(M[0][1], 1);
    mpz_init_set_ui(M[1][0], 1);
    mpz_init_set_ui(M[1][1], 0);

    power(F, n / 2);
    multiply(F, F);

    if (n % 2 != 0)
        multiply(F, M);
}
// matrix multiplication method
void fibonacci(int n, mpz_t result) {
    mpz_t F[2][2];
    mpz_init_set_ui(F[0][0], 1);
    mpz_init_set_ui(F[0][1], 1);
    mpz_init_set_ui(F[1][0], 1);
    mpz_init_set_ui(F[1][1], 0);
    if (n == 0) {
        mpz_set_ui(result, 0);
        return;
    }

    power(F, n - 1);
    mpz_set(result, F[0][0]);
}

// Simple step by step addition method
void fibonacci_traditional_method(int n, mpz_t result) {
    if (n <= 1) {
        mpz_set_ui(result, n);
    } else {
        mpz_t n_minus_1, n_minus_2;
        mpz_init_set_ui(n_minus_1, 1);
        mpz_init_set_ui(n_minus_2, 0);

        for (int i = 2; i <= n; i++) {
            mpz_add(result, n_minus_1, n_minus_2);
            mpz_set(n_minus_2, n_minus_1);
            mpz_set(n_minus_1, result);
        }

        mpz_clears(n_minus_1, n_minus_2, NULL);
    }
}