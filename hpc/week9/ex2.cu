#include <stdio.h>

__global__ void addRows(float* a, float* b, float* res, int m, int n){
    int r = blockDim.x * blockIdx.x + threadIdx.x;
    if(r<m){
        for(int c=0; c<n; c++){
            res[r*n+c] = a[r*n+c] + b[r*n+c];
        }
    }
}

__global__ void addCols(float* a, float* b, float* res, int m, int n){
    int c = blockDim.x * blockIdx.x + threadIdx.x;
    if(c<n){
        for(int r=0; r<m; r++){
            res[r*n+c] = a[r*n+c] + b[r*n+c];
        }
    }
}

__global__ void addElems(float* a, float* b, float* res, int m, int n){
    int r = blockIdx.y * blockDim.y + threadIdx.y;
    int c = blockIdx.x * blockDim.x + threadIdx.x;
    if(r<m && c<n){
        res[r*n+c] = a[r*n+c] + b[r*n+c];
    }
}

int main(){
    int m = 3;
    int n = 3;
    float a[9] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    float b[9] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    float res[9];
    int s = m*n*sizeof(float);

    float *d_a, *d_b, *d_res;
    cudaMalloc((void**)&d_a, s);
    cudaMalloc((void**)&d_b, s);
    cudaMalloc((void**)&d_res, s);

    cudaMemcpy(d_a, a, s, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, s, cudaMemcpyHostToDevice);

    addRows<<<1, 3>>>(d_a, d_b, d_res, m, n);
    cudaMemcpy(res, d_res, s, cudaMemcpyDeviceToHost);
    for(int i=1; i<=m*n; i++){
        printf("%f\t", res[i-1]);
        if(i%3==0){
            printf("\n");
        }
    }
    printf("\n");

    addCols<<<1, 3>>>(d_a, d_b, d_res, m, n);
    cudaMemcpy(res, d_res, s, cudaMemcpyDeviceToHost);
    for(int i=1; i<=m*n; i++){
        printf("%f\t", res[i-1]);
        if(i%3==0){
            printf("\n");
        }
    }
    printf("\n");

    dim3 blockDim(m, n, 1);
    addElems<<<1, blockDim>>>(d_a, d_b, d_res, m, n);
    cudaMemcpy(res, d_res, s, cudaMemcpyDeviceToHost);
    for(int i=1; i<=m*n; i++){
        printf("%f\t", res[i-1]);
        if(i%3==0){
            printf("\n");
        }
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_res);
}