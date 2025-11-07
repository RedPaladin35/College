#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char* s1 = NULL;
    char* s2 = NULL;
    char* s = NULL;
    int m = 6;
    int n = 3;
    if(rank == 0){
        s1 = (char*)malloc((m+1)*sizeof(char));
        s2 = (char*)malloc((m+1)*sizeof(char));
        s = (char*)malloc((2*m+1)*sizeof(char));
        strcpy(s1, "string");
        strcpy(s2, "length");
    }
    char* ss1 = (char*)malloc((m/n+1)*sizeof(char));
    char* ss2 = (char*)malloc((m/n+1)*sizeof(char));
    MPI_Scatter(s1, m/n, MPI_CHAR, ss1, m/n, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(s2, m/n, MPI_CHAR, ss2, m/n, MPI_CHAR, 0, MPI_COMM_WORLD);
    char* ss = (char*)malloc((2*(m/n)+1)*sizeof(char));
    for(int i=0; i<m/n; i++){
        ss[2*i] = ss1[i];
        ss[2*i+1] = ss2[i];
    }
    MPI_Gather(ss, 2*(m/n), MPI_CHAR, s, 2*(m/n), MPI_CHAR, 0, MPI_COMM_WORLD);
    if(rank == 0){
        printf("%s\n", s);
        free(s1);
        free(s2);
        free(s);
    }
    free(ss1);
    free(ss2);
    free(ss);
    MPI_Finalize();
    
}
