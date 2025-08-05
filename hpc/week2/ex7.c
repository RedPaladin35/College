#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fibo(int n){
    if(n<=1) return n;
    return fibo(n-1) + fibo(n-2); 
}

int main(int argc, char *argv[]) {
    int n, i;
    scanf("%d", &n);
    int *arr = malloc(n*sizeof(int));
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    #pragma omp parallel num_threads(n)
    {
        int tid = omp_get_thread_num();
        int res = fibo(arr[tid]);
        printf("Thread %d: Fibonacci number for %d = %d\n", tid, arr[tid], res);
    }
    free(arr);
    return 0;
}