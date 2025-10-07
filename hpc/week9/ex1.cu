#include <stdio.h>

__global__ void transformMatrix(float* arr, int m, int n){
    int r = blockIdx.y * blockDim.y + threadIdx.y;
    int c = blockIdx.x * blockDim.x + threadIdx.x;
    int id = r*n + c;
    if(r<m && c<n){
        int p = r+1;
        int val = arr[id];
        int res = 1.0f;
        for(int i=0; i<p; i++){
            res *= val;
        }
        arr[id] = res;
    }
}

int main(){
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    float h_matrix[m*n];
    for(int i=0; i<m*n; i++){
        scanf("%f", &h_matrix[i]);
    }
    int s = m*n*sizeof(float);
    float *d_matrix;
    cudaMalloc((void**)&d_matrix, s);
    cudaMemcpy(d_matrix, h_matrix, s, cudaMemcpyHostToDevice);
    dim3 blockDim(m, n, 1);
    transformMatrix<<<1, blockDim>>>(d_matrix, m, n);
    cudaMemcpy(h_matrix, d_matrix, s, cudaMemcpyDeviceToHost);
    for(int i=1; i<=m*n; i++){
        printf("%f\t", h_matrix[i-1]);
        if(i%3 == 0){
            printf("\n");
        }
    }
    cudaFree(d_matrix);
}