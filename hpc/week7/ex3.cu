#include<stdio.h>

#define N 10 

__global__ void computeSine(const float* input, float* output){
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if(id < N){
        output[id] = sinf(input[id]);
    }
}

void printVector(float* a){
    for(int i=0; i<N; i++){
        printf("%f\t", a[i]);
    }
    printf("\n");
}

int main(){
    float h_input[N], h_output[N];
    size_t s = N * sizeof(float);

    for(int i=0; i<N; i++){
        h_input[i] = i * 0.1f;
    }

    float *d_input, *d_output;
    cudaMalloc((void**)&d_input, s);
    cudaMalloc((void**)&d_output, s);

    cudaMemcpy(d_input, h_input, s, cudaMemcpyHostToDevice);
    
    computeSine<<<1, N>>>(d_input, d_output);
    cudaMemcpy(h_output, d_output, s, cudaMemcpyDeviceToHost);

    printf("Input in radians:\n");
    printVector(h_input);

    printf("Output in sine:\n");
    printVector(h_output);

    cudaFree(d_input);
    cudaFree(d_output);
}