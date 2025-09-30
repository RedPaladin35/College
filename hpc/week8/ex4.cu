#include <stdio.h>
#include <string.h>
#include <stdlib.h>

__global__ void reverseString(char* d_str, int l){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int half = l/2;

    if(idx < half){
        char temp = d_str[idx];
        d_str[idx] = d_str[l-idx-1];
        d_str[l-idx-1] = temp;
    }
}

int main(){
    char h_str[] = "I am a third year student";
    int l = strlen(h_str);

    char* d_str;
    cudaMalloc((void**)&d_str, l*sizeof(char));
    cudaMemcpy(d_str, h_str, l*sizeof(char), cudaMemcpyHostToDevice);

    reverseString<<<1, 256>>> (d_str, l);
    cudaMemcpy(h_str, d_str, l*sizeof(char), cudaMemcpyDeviceToHost);
    printf("%s\n", h_str);
    cudaFree(d_str);
}