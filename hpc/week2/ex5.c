#include <stdio.h>
#include <math.h>
#include <omp.h>

int is_prime(int num){
    if(num < 2) return 0;
    int l = (int)sqrt(num);
    for(int i=2; i<l; i++){
        if(num%i==0){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int start, end;
    scanf("%d %d", &start, &end);

    #pragma omp parallel for schedule(dynamic)
    for(int i =start; i<=end; i++){
        if(is_prime(i)){
            #pragma omp critical
            printf("%d\t", i);
        }
    }

    printf("\n");
    return 0;
}