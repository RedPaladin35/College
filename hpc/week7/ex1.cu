#include<stdio.h>
#define N 10

__global__ void add(int* a, int* b, int* c){
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if(id < N){
        c[id] = a[id] + b[id];
    }
}

void printVector(int* a){
    for(int i=0; i<N; i++){
        printf("%d\t", a[i]);
    }
    printf("\n");
}

int main(){
    size_t s = N * sizeof(int);

    int a[N], b[N], c[N];

    for(int i=0; i<N; i++){
        a[i] = i*2 + 3;
        b[i] = i*3 + 2;
    }

    printf("A values:\n");
    printVector(a);

    printf("B values:\n");
    printVector(b);

    int *d_a, *d_b, *d_c;
    cudaMalloc((void**)&d_a, s);
    cudaMalloc((void**)&d_b, s);
    cudaMalloc((void**)&d_c, s);

    cudaMemcpy(d_a, a, s, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, s, cudaMemcpyHostToDevice);

    printf("Value of N is %d\n", N);
    printf("Running with 1 block and N threads:\n");
    add<<<1, N>>>(d_a, d_b, d_c);
    cudaMemcpy(c, d_c, s, cudaMemcpyDeviceToHost);
    printVector(c);
    printf("--------\n");

    printf("Running with N blocks each having 1 thread:\n");
    add<<<N, 1>>>(d_a, d_b, d_c);
    cudaMemcpy(c, d_c, s, cudaMemcpyDeviceToHost);
    printVector(c);
    printf("--------\n");

    int tpb = 256;
    int bpg = (N + tpb - 1) / tpb;
    printf("Running with %d blocks and %d threads:\n", bpg, tpb);
    add<<<bpg, tpb>>>(d_a, d_b, d_c);
    cudaMemcpy(c, d_c, s, cudaMemcpyDeviceToHost);
    printVector(c);
    printf("--------\n");

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}