%%cuda

#include <stdio.h>
#define N 16 
#define M 5

__global__ void conv(const float* inp, const float* mask, float* oup){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i<N){
        float res = 0.0f;
        for(int j=0; j<M; j++){
            int idx = i - j;
            if(idx >= 0){
                res += inp[idx] * mask[j];
            }
        }
        oup[i] = res;
    }
}

int main() {
    float inp[16];
    float mask[5];
    for(int i=0; i<N; i++){
        inp[i] = i+1;
        if(i<M){
            mask[i] = 0.2;
        }
    }
    int is = N * sizeof(float);
    int ms = M * sizeof(float);
    float oup[16];
    float *d_i, *d_m, *d_o;
    cudaMalloc((void**)&d_i, is);
    cudaMalloc((void**)&d_m, ms);
    cudaMalloc((void**)&d_o, is);
    cudaMemcpy(d_i, inp, is, cudaMemcpyHostToDevice);
    cudaMemcpy(d_m, mask, ms, cudaMemcpyHostToDevice);
    conv<<<1, N>>>(d_i, d_m, d_o);
    cudaMemcpy(oup, d_o, is, cudaMemcpyDeviceToHost);
    for(int i=0; i<N; i++){
        printf("%f\t", oup[i]);
    }
    cudaFree(d_i);
    cudaFree(d_o);
    cudaFree(d_m);
}

