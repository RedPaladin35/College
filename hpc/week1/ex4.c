#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char str[50];
    printf("Enter a word: ");
    scanf("%49s", str);

    int n = strlen(str);
    int n2 = (n * (n + 1)) / 2;

    char ans[n2+1];
    int si[n];

    si[0] = 0;
    for(int i=1; i<n; i++){
        si[i] = si[i-1] + i;
    }

    omp_set_num_threads(5);

    #pragma omp parallel for 
    for(int i=0; i<n; i++){
        for(int j=0; j<= i; j++){
            ans[si[i] + j] = str[i];
        }
    }

    ans[n2] = '\0';
    printf("%s\n", ans);
}