/*LLVM Passes for:
 * 1. Simple Constant Propagation: -constprop
 * 2. Interprocedural Constant Propagation: -ipconstprop
 * 3. Sparse Conditional Constant Propagation: -sccp*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int use_var(int a, int b){
    return a + b;
}

int main(){
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    long int n = 10000000000;
    int a = 10;
    int b = 10;
    for (long int i = 0; i < n; i++) {
        a = (5 + b) + 5 - (b - 10); // equiv of a = 0
        b = (5 + a) - 5 - (a - 10); // equiv of b = 0
    }
    use_var (a, b);

    gettimeofday(&end_time, NULL);
    time_t elasped_time_usec = (end_time.tv_sec*1e6 + end_time.tv_usec) - (start_time.tv_sec *1e6 + start_time.tv_usec);
    printf("Run time: %.4g seconds\n", elasped_time_usec*1e-6);
    return 0;
}
