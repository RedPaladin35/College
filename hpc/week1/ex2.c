#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    double a, b, sum, dif, prod, div=0;
    printf("Enter 2 nums: ");
    scanf("%lf %lf", &a, &b);

    #pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();
        if(tid == 0){
            sum = a+b;
        } else if(tid == 1){
            dif = a-b;
        } else if(tid == 2){
            prod = a*b;
        } else if(tid == 3){
            if(b!=0){
                div = a/b;
            }
        }
    }

    printf("%.2lf, %.2lf, %.2lf, %.2lf", sum, dif, prod, div);
    printf("\n");

    return 0;
}