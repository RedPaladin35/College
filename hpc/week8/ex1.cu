#include<stdio.h>
#include<string.h>
#include<stdlib.h>

__global__ void repeatString(char* d_output, char* d_input, int l, int N){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if(idx<N){
        int sp = idx * l;
        for(int i=0; i<l; i++){
            d_output[sp+i] = d_input[i];
        }
    }
}

int main(){
    const char* s = "Hello";
    int N = 3;

    int l = strlen(s);
    int ol = l*N;

    char h_output[ol+1];
    h_output[ol] = '\0';

    char *d_input, *d_output;
    cudaMalloc((void**)&d_input, l*sizeof(char));
    cudaMalloc((void**)&d_output, ol*sizeof(char));

    cudaMemcpy(d_input, s, l*sizeof(char), cudaMemcpyHostToDevice);

    repeatString<<<1, 256>>>(d_output, d_input, l, N);
    cudaMemcpy(h_output, d_output, ol*sizeof(char), cudaMemcpyDeviceToHost);

    printf("%s\n", h_output);
    cudaFree(d_input);
    cudaFree(d_output);
}