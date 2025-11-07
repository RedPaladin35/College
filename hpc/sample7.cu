%%cuda

#include <stdio.h>

__global__ void selsort(int *arr, int cols){
    int row = blockIdx.x;
    int rs = row * cols;
    
    if(threadIdx.x == 0){
        for(int i=0; i<cols-1; i++){
            int mi = i;
            for(int j=i+1; j<cols; j++){
                if(arr[rs+j] < arr[rs+mi]){
                    mi = j;
                }
            }
            if(mi != i){
                int t = arr[rs+i];
                arr[rs+i] = arr[rs+mi];
                arr[rs+mi] = t;
            }
        }
    }
}

int main(){
    int arr[12] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int s = 12 * sizeof(int);
    int rows = 3, cols=4;
    int *d_arr;
    cudaMalloc((void**)&d_arr, s);
    cudaMemcpy(d_arr, arr, s, cudaMemcpyHostToDevice);
    selsort<<<3, 1>>>(d_arr, cols);
    cudaMemcpy(arr, d_arr, s, cudaMemcpyDeviceToHost);
    for(int i=0; i<12; i++){
        printf("%d\t", arr[i]);
    }
    cudaFree(d_arr);
}
