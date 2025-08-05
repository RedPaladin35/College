#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int a, b;
    scanf("%d %d", &a, &b);
    #pragma omp parallel sections num_threads(4)
    {
        #pragma omp section
        {
            printf("%d + %d = %d\n", a, b, a+b);
        }
        #pragma omp section 
        {
            printf("%d - %d = %d\n", a, b, a-b);
        }
        #pragma omp section
        {
            printf("%d * %d = %d\n", a, b, a*b);
        }
        #pragma omp section 
        {
            if(b!=0){
                printf("%d / %d = %d\n", a, b, a/b);
            } else {
                printf("Division by zero not possible\n");
            }
        }
    }   
    return 0;
}