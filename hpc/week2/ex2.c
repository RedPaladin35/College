#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int i, threads;
    scanf("%d", &i);
    threads = 5;

    #pragma omp parallel num_threads(5)
    {
        int tid = omp_get_thread_num();
        double result = pow(i, tid);
        printf("Thread %d: pow(%d, %d) = %.2lf\n", tid, i, tid, result);
    }

    return 0;
}