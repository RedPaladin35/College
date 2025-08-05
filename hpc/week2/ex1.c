#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void fork_join_single(){
    printf("Single parallel directive\n");
    # pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        printf("Thread %d\n", tid);
    }
    printf("Back to sequential.\n");
}

void fork_join_multiple(){
    printf("Multiple parallel directive\n");
    #pragma omp parallel num_threads(10)
    {
        int tid = omp_get_thread_num();
        printf("First parallel region: thread %d\n", tid);
    }
    omp_set_num_threads(4);
    #pragma omp parallel 
    {
        int tid = omp_get_thread_num();
        printf("Second parallel region: thread %d\n", tid);
    }
    printf("All regions completed.\n");
}

void spmd_pattern(){
    printf("SPMD pattern\n");
    int data[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nt = omp_get_num_threads();
        int chunk = 8 / nt;
        int st = tid * chunk;
        int end = (tid == nt-1) ? 8 : st + chunk;

        for(int i=st; i<end; i++){
            printf("Thread %d processes data[%d] = %d\n", tid, i, data[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    fork_join_single();
    fork_join_multiple();
    spmd_pattern();
    return 0;
}