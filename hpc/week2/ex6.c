#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    char str[50];
    scanf("%49s", str);
    int n = strlen(str);
    #pragma omp parallel num_threads(n)
    {
        int tid = omp_get_thread_num();
        if(tid < n){
            char c = str[tid];
            if(isupper(c)){
                str[tid] = tolower(c);
            } else if(islower(c)){
                str[tid] = toupper(c);
            }
        }
        printf("Thread %d toggled character at index %d: %c\n", tid, tid, str[tid]);
    }
    printf("Final string: %s\n", str);
    return 0;
}