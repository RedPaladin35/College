#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int sequentialSearch(int arr[], int n, int key){
    int idx = -1;
    #pragma omp parallel for num_threads(5)
    for(int i=0; i<n; i++){
        if(arr[i] == key){
            #pragma omp critical 
            {
                if(idx == -1 || i < idx){
                    idx = i;
                }
            }
        }
    }
    return idx;
}

int main(int argc, char *argv[]) {
    int n, i, key;
    scanf("%d", &n);
    int *arr = malloc(n*sizeof(int));
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    scanf("%d", &key);

    int idx = sequentialSearch(arr, n, key);
    if(idx != -1){
        printf("Element %d found at index %d\n", key, idx);
    } else {
        printf("Element %d not found\n", key);
    }
    free(arr);
    return 0;
}