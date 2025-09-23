#include<stdio.h>

#define N 16
#define M 5

__global__ void conv(const float* input, const float* mask, float* output){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i<N){
        float res = 0.0f;
        for(int j=0; j<M; j++){
            int idx = i - j;
            if(idx >= 0){
                res += input[idx] * mask[j];
            }
        }
        output[i] = res;
    }
}

void printVector(float* c){
    for(int i=0; i<N; i++){
        printf("%f\t", c[i]);
    }
    printf("\n");
}

int main(){
    size_t is = N * sizeof(float);
    size_t ms = M * sizeof(float);

    float h_input[N], h_mask[M], h_output[N];
    for(int i=0; i<N; i++){
        h_input[i] = i + 1;
    }
    for(int i=0; i<M; i++){
        h_mask[i] = 0.2f;
    }

    float *d_input, *d_mask, *d_output;
    cudaMalloc((void**)&d_input, is);
    cudaMalloc((void**)&d_mask, ms);
    cudaMalloc((void**)&d_output, is);

    cudaMemcpy(d_input, h_input, is, cudaMemcpyHostToDevice);
    cudaMemcpy(d_mask, h_mask, ms, cudaMemcpyHostToDevice);

    int tpb = 256;
    int bpg = (N + tpb - 1) / tpb;
    conv<<<bpg, tpb>>>(d_input, d_mask, d_output);
    cudaMemcpy(h_output, d_output, is, cudaMemcpyDeviceToHost);

    printf("Input:\n");
    printVector(h_input);

    printf("Mask:\n");
    for(int i=0; i<5; i++){
        printf("%f\t", h_mask[i]);
    }
    printf("\n");

    printf("Output:\n");
    printVector(h_output);

    cudaFree(d_input);
    cudaFree(d_mask);
    cudaFree(d_output);
}