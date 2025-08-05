#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int i, n=5;
    int s_critical=0;
    int s_atomic=0;
    int s_lock=0;
    int s_reduction=0;
    int s_master=0;
    int arr[n];
    printf("Enter 5 elements:");
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    omp_lock_t lock;
    omp_init_lock(&lock);

    // allows execution of code in critical section by only one thread at a time
    #pragma omp parallel for shared(s_critical)
    for(i=0; i<n; i++){
        #pragma omp critical 
        {
            s_critical += arr[i];
        }
    }

    // for efficient that critical, but only works for performing simple operations on the shared variable
    #pragma omp parallel for shared(s_atomic)
    for(i=0; i<n; i++){
        #pragma omp atomic 
        s_atomic += arr[i];   
    }
    
    // divides work among threads and at the end the results are combined
    #pragma omp parallel for reduction(+:s_reduction)
    for(i=0; i<n; i++){
        s_reduction += arr[i];
    }

    // only allows the master thread to execute this code block
    #pragma omp parallel shared(s_master)
    {
        #pragma omp master 
        {
            for(i=0; i<n; i++){
                s_master += arr[i];
            }
        }
    }

    // uses locking and unlocking mechanism to do mutual exclusion
    #pragma omp parallel for shared(s_lock, lock)
    for(i=0; i<n; i++){
        omp_set_lock(&lock);
        s_lock += arr[i];
        omp_unset_lock(&lock);
    }


    omp_destroy_lock(&lock);

    printf("Sum using critical section: %d\n", s_critical);
    printf("Sum using atomic: %d\n", s_atomic);
    printf("Sum using reduction: %d\n", s_reduction);
    printf("Sum using master: %d\n", s_master);
    printf("Sum using locks: %d\n", s_lock);


    return 0;
}