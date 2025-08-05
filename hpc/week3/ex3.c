#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void printVector(int *v, int n){
    for(int i=0; i<n; i++){
        printf("%d\t", v[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int n=5;
    int *a = malloc(n*sizeof(int));
    int *b = malloc(n*sizeof(int));
    int *add_res = malloc(n*sizeof(int));
    int *sub_res = malloc(n*sizeof(int));
    int *mul_res = malloc(n*sizeof(int));
    printf("Enter 5 elements for each vector:");
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
    }
    for(int i=0; i<n; i++){
        scanf("%d", &b[i]);
    }
    #pragma omp parallel num_threads(5)
    {
        #pragma omp single 
        {
            #pragma omp task
            {
                for(int i=0; i<n; i++){
                    add_res[i] = a[i] + b[i];
                }
                #pragma omp critical
                {
                    printf("Addition result:\n");
                    printVector(add_res, n);
                }
            }
            #pragma omp task 
            {
                for(int i=0; i<n; i++){
                    sub_res[i] = a[i] - b[i];
                }
                #pragma omp critical
                {
                    printf("Substraction result:\n");
                    printVector(sub_res, n);
                }
            }
            #pragma omp task 
            {
                for(int i=0; i<n; i++){
                    mul_res[i] = a[i] * b[i];
                }
                #pragma omp critical 
                {
                    printf("Multiplication result:\n");
                    printVector(mul_res, n);
                }
            }
            #pragma omp taskwait
        }
    }
    free(a);
    free(b);
    free(add_res);
    free(sub_res);
    free(mul_res);
    return 0;
}