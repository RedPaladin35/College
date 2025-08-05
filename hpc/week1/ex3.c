#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <omp.h>
#include <string.h>

void toggleCase(char *str){
    int n = strlen(str);
    #pragma omp parallel for
    for(int i=0; i<n; i++){
        if(islower(str[i])){
            str[i] = toupper(str[i]);
        } else if(isupper(str[i])){
            str[i] = tolower(str[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    char str[50];
    scanf("%49s", str);
    omp_set_num_threads(5);
    toggleCase(str);
    printf("\n%s", str);
    printf("\n");
    return 0;
}