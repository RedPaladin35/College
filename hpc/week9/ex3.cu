#include <stdio.h>

__global__ void rowMul(float* d_a, float* d_b, float* d_res, int m, int n, int k){
    int r = blockIdx.x * blockDim.x + threadIdx.x;
    if(r<m){
        for(int c=0; c<n; c++){
            float sum = 0.0f;
            for(int x=0; x<k; x++){
                sum += d_a[r*k+x] * d_b[x*n+c]; 
            }
            d_res[r*n+c] = sum;
        }
    }
}

__global__ void colMul(float* d_a, float* d_b, float* d_res, int m, int n, int k){
    int c = blockIdx.x * blockDim.x + threadIdx.x;
    if(c<n){
        for(int r=0; r<m; r++){
            float sum = 0.0f;
            for(int x=0; x<k; x++){
                sum += d_a[r*k+x] * d_b[x*n+c];
            }
            d_res[r*n+c] = sum;
        }
    }
}

__global__ void elemMul(float* d_a, float* d_b, float* d_res, int m, int n, int k){
    int r = blockIdx.y * blockDim.y + threadIdx.y;
    int c = blockIdx.x * blockDim.x + threadIdx.x;
    if(r<m && c<n){
        float sum = 0.0f;
        for(int x=0; x<k; x++){
            sum += d_a[r*k+x] * d_b[x*n+c];
        }
        d_res[r*n+c] = sum;
    }
}

int main(){
    int m=3, n=3;
    float a[m][n] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    float b[m][n] = {{1, 2, 2}, {1, 2, 3}, {1, 2, 3}};
    float res[m][n];
    int s = m*n*sizeof(float);

    float *d_a, *d_b, *d_res;
    cudaMalloc((void**)&d_a, s);
    cudaMalloc((void**)&d_b, s);
    cudaMalloc((void**)&d_res, s);

    cudaMemcpy(d_a, a, s, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, s, cudaMemcpyHostToDevice);

    rowMul<<<1, 3>>>(d_a, d_b, d_res, m, n, 3);
    cudaMemcpy(res, d_res, s, cudaMemcpyDeviceToHost);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("%f\t", res[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    colMul<<<1, 3>>>(d_a, d_b, d_res, m, n, 3);
    cudaMemcpy(res, d_res, s, cudaMemcpyDeviceToHost);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("%f\t", res[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    dim3 blockDim(m, n, 1);
    elemMul<<<1, blockDim>>>(d_a, d_b, d_res, m, n, 3);
    cudaMemcpy(res, d_res, s, cudaMemcpyDeviceToHost);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("%f\t", res[i][j]);
        }
        printf("\n");
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_res);
}