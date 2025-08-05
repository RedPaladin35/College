#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char a[50], b[50];
    printf("Enter 2 words: ");
    scanf("%49s %49s", a, b);

    int l1 = strlen(a);
    int l2 = strlen(b);

    if(l1 != l2){
        fprintf(stderr, "Words must be of equal length.");
        return -1;
    }

    int l = l1 + l2;
    char *ans = malloc(l+1);

    omp_set_num_threads(5);

    #pragma omp parallel for 
    for(int i=0; i<l; i++){
        if(i % 2 == 0){
            ans[i] = a[i/2];
        } else {
            ans[i] = b[i/2];
        }
    }

    ans[l] = '\0';
    printf("%s\n", ans);
    free(ans);

    return 0;
}