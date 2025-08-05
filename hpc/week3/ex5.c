#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int st = 1, end = 10000;
    long long sum = 0;
    double start_time, end_time;
    int chunk_size = 10;

    long long serial_sum = 0;
    for(int i=st; i<end; i++){
        serial_sum += i;
    }
    printf("Serial sum: %lld\n", serial_sum);

    omp_sched_t schedules[] = {omp_sched_static, omp_sched_dynamic, omp_sched_guided};
    const char *schedule_names[] = {"static", "dynamic", "guided"};

    int num_sch = 3;

    for(int s=0; s<num_sch; s++){
        sum = 0;
        omp_set_schedule(schedules[s], chunk_size);

        start_time = omp_get_wtime();
        #pragma omp parallel for reduction(+:sum) schedule(runtime)
        for(int i=st; i<end; i++){
            sum += i;
        }
        end_time = omp_get_wtime();
        printf("Sum with %s scheduling (chunk size %d): %lld, Time taken: %f seconds\n", schedule_names[s], chunk_size, sum, end_time - start_time);
    }

    return 0;
}