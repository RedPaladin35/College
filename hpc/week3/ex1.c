#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void selectionSort(int arr[], int n){
    int i, j;
    for(i=0; i<n-1; i++){
        int min_idx = i;
        int min_val = arr[i];
        #pragma omp parallel for num_threads(5)
        for(j=i+1; j<n; j++){
            #pragma omp critical
            {
                if(arr[j]<min_val){
                    min_val = arr[j];
                    min_idx = j;
                }
            }
        }
        if(min_idx!=i){
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

int main(int argc, char *argv[]) {
    int n, i;
    scanf("%d", &n);
    int *arr = malloc(n*sizeof(int));
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Original array: \n");
    for(i=0; i<n; i++){
        printf("%d\t", arr[i]);
    }
    printf("\n");
    selectionSort(arr, n);
    printf("After sorting: \n");
    for(i=0; i<n; i++){
        printf("%d\t", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}