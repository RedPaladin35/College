#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count_words(const char* line){
    int count = 0;
    int in_word = 0;
    while(*line){
        if(isspace(*line)){
            in_word = 0;
        } else if(!in_word) {
            in_word = 1;
            count++;
        }
        line++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char line[300];
    int word_count = 0;

    if(rank == 0){
        FILE *fp  = fopen(argv[1], "r");
        if(!fp){
            printf("Error opening file.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        for(int i=1; i<size; i++){
            if(fgets(line, 300, fp) == NULL){
                line[0] = '\0';
            }
            MPI_Send(line, strlen(line)+1, MPI_CHAR, i, i, MPI_COMM_WORLD);
        }
        fclose(fp);

        int total_words = 0;

        for(int i=1; i<size; i++){
            int wc;
            MPI_Recv(&wc, 1, MPI_CHAR, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d counted %d words.\n", i, wc);
            total_words += wc;
        }

        printf("Total word count: %d\n", total_words);
    } else {
        MPI_Recv(line, 300, MPI_CHAR, 0, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        word_count = count_words(line);
        MPI_Send(&word_count, 1, MPI_CHAR, 0, rank, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}