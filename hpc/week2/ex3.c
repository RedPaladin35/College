#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n, i;
    scanf("%d", &n);
    int *arr = malloc(n*sizeof(int));
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }    
    int sum_odd=0, sum_even=0;
    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section 
        {
            for(i=0; i<n; i++){
                if(arr[i]%2 == 0){
                    sum_even += arr[i];
                }
            }
        }
        #pragma omp section 
        {
            for(i=0; i<n; i++){
                if(arr[i]%2!=0){
                    sum_odd += arr[i];
                }
            }
        }
    }
    printf("%d %d\n", sum_even, sum_odd);
    free(arr);
    return 0;
}