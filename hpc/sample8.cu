%%cuda
#include <stdio.h>

__global__ void mul(int *d_val, int* d_col, int *d_row, int *x, int *y, int m){
    int row = blockDim.x * blockIdx.x + threadIdx.x;
    if(row < m){
        int rs = d_row[row];
        int re = d_row[row+1];
        int prod = 0;
        for(int i=rs; i<re; i++){
            int col_idx = d_col[i];
            prod += d_val[i] * x[col_idx];
        }
        y[row] = prod;
    }
}

int main(){
    int m = 5;
    int n = 5;
    int a[m][n] = {
        {1, 0, 2, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 5, 0, 6},
        {7, 0, 0, 8, 0},
        {0, 9, 0, 0, 10}
    };
    printf("Original array:\n");
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int nnz = 0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(a[i][j] != 0){
                nnz++;
            }
        }
    }
    int val[nnz], col[nnz], row[m+1];
    int val_idx = 0;
    row[0] = 0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(a[i][j]!=0){
                val[val_idx] = a[i][j];
                col[val_idx] = j;
                val_idx++;
            }
        }
        row[i+1] = val_idx;
    }
    printf("CSR format:\n");
    printf("Values:\n");
    for(int i=0; i<nnz; i++){
        printf("%d\t", val[i]);
    }
    printf("\nColumn values:\n");
    for(int i=0; i<nnz; i++){
        printf("%d\t", col[i]);
    }
    printf("\nRow pointer values:\n");
    for(int i=0; i<m+1; i++){
        printf("%d\t", row[i]);
    }
    printf("\n");
    int x[m] = {1, 1, 1, 1, 1};
    int y[n];
    printf("X matrix: {1, 1, 1, 1, 1}\n");
    int *d_val, *d_col, *d_row, *d_x, *d_y;
    cudaMalloc((void**)&d_val, 4*nnz);
    cudaMalloc((void**)&d_col, 4*nnz);
    cudaMalloc((void**)&d_row, 4*6);
    cudaMalloc((void**)&d_x, 4*5);
    cudaMalloc((void**)&d_y, 4*5);
    cudaMemcpy(d_val, val, 4*nnz, cudaMemcpyHostToDevice);
    cudaMemcpy(d_col, col, 4*nnz, cudaMemcpyHostToDevice);
    cudaMemcpy(d_row, row, 4*6, cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, 4*5, cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, 4*5, cudaMemcpyHostToDevice);
    mul<<<1, 256>>>(d_val, d_col, d_row, d_x, d_y, m);
    cudaMemcpy(y, d_y, 4*5, cudaMemcpyDeviceToHost);
    printf("Final result:\n");
    for(int i=0; i<5; i++){
        printf("%d\t", y[i]);
    }
}
