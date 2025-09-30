#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int start;
    int length;
} WordInfo;

__device__ bool compareWords(const char* sen, int start, int l, const char* target, int tl){
    if(l!=tl) return false;
    for(int i=0; i<l; i++){
        if(sen[start+i]!=target[i]) return false;
    }
    return true;
}

__global__ void countWords(const char* sen, int l, WordInfo* words, int wc, const char* target, int tl, int* d_count){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if(idx < wc){
        if(compareWords(sen, words[idx].start, words[idx].length, target, tl)){
            atomicAdd(d_count, 1);
        }
    }
}

int main(){
    char h_str[] = "what when what when what";
    char h_target[] = "what";

    int l = strlen(h_str);
    int tl = strlen(h_target);

    int i=0, wc=0;
    int maxWords = 100;

    WordInfo* h_words = (WordInfo*)malloc(maxWords * sizeof(WordInfo));

    while(i<l){
        while(i<l && h_str[i]==' ') i++;
        if(i>=l) break;

        int start = i;
        while(i<l && h_str[i]!=' ') i++;
        int length = i - start;

        h_words[wc].start = start;
        h_words[wc].length = length;
        wc++;

        if(wc > maxWords) break;
    }

    int h_count, zero=0;

    char *d_str, *d_target;
    WordInfo* d_words;
    int *d_count;

    cudaMalloc((void**)&d_str, l*sizeof(char));
    cudaMalloc((void**)&d_target, tl*sizeof(char));
    cudaMalloc((void**)&d_words, wc*sizeof(WordInfo));
    cudaMalloc((void**)&d_count, sizeof(int));

    cudaMemcpy(d_str, h_str, l*sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_target, h_target, tl*sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_words, h_words, wc*sizeof(WordInfo), cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &zero, sizeof(int), cudaMemcpyHostToDevice);

    countWords<<<1, 256>>>(d_str, l, d_words, wc, d_target, tl, d_count);
    cudaMemcpy(&h_count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("The word %s appears %d times.\n", h_target, h_count);

    cudaFree(d_str);
    cudaFree(d_target);
    cudaFree(d_words);
    cudaFree(d_count);
    free(h_words);
}