#include<stdio.h>
#include<omp.h>

void reverse_array(int *arr, int n){
    #pragma omp parallel for 
    for(int i=0; i<(n+1)/2; i++){
        int temp = arr[i];
        arr[i] = arr[n-1-i];
        arr[n-1-i] = temp;
    }
}

int main(){
    int arr[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int n = sizeof(arr) / sizeof(arr[0]);
    omp_set_num_threads((n+1)/2);
    reverse_array(arr, n);

    for(int i=0; i<n; i++){
        printf("%d\t", arr[i]);
    }
    printf("\n");
}