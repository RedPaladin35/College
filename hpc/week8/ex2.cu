#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int start;
    int length;
} WordInfo;

__global__ void reverseWords(char* d_str, WordInfo* d_words, int N){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if(idx < N){
        int start = d_words[idx].start;
        int length = d_words[idx].length;

        for(int i=0; i<length/2; i++){
            char temp = d_str[start+i];
            d_str[start+i] = d_str[start+length-1-i];
            d_str[start+length-i-1] = temp;
        }
    }
}

int main(){
    char h_str[] = "I am a third year student";
    int l = strlen(h_str);
    printf("Original string:\n");
    printf("%s\n", h_str);
    
    int maxWords = 100;
    WordInfo* words = (WordInfo*)malloc(maxWords*sizeof(WordInfo));

    int wc=0;
    int i=0;

    while(i<l){
        while(i<l && h_str[i]==' ') i++;
        if(i>l) break;
        
        int start = i;
        while(i<l && h_str[i]!=' ') i++;
        int length = i-start;

        words[wc].start = start;
        words[wc].length = length;
        wc++;

        if(wc>maxWords) break;
    }

    char* d_str;
    WordInfo* d_words;
    cudaMalloc((void**)&d_str, l*sizeof(char));
    cudaMalloc((void**)&d_words, wc*sizeof(WordInfo));

    cudaMemcpy(d_str, h_str, l*sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_words, words, wc*sizeof(WordInfo), cudaMemcpyHostToDevice);

    reverseWords<<<1, 256>>>(d_str, d_words, wc);
    cudaMemcpy(h_str, d_str, l*sizeof(char), cudaMemcpyDeviceToHost);
    printf("After reversing:\n");
    printf("%s\n", h_str);

    cudaFree(d_str);
    cudaFree(d_words);
    free(words);
}