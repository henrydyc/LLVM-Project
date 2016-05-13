/*LLVM Passes for:
 * 1. Simple Constant Propagation: -constprop
 * 2. Interprocedural Constant Propagation: -ipconstprop
 * 3. Sparse Conditional Constant Propagation: -sccp*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int use_var (int a, int b){
    return a+b;
}

int main(){
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    long int n = 100000;
    int invariant, a, b;
    int arr[100][100];

    for (long int i = 0; i*i < n*n; i++) {//Loop Strength Reduction 
        for (int j = 0; j*j < 100*100; j++){//Loop Strength Reduction
            for (int k = 0; k*k <100*100; k++){ //Loop Strength Reduction
                invariant = n%17; //LICM
                a = j*4 + invariant;//Loop Strength Reduction
                b = k*8;//Loop Strength Reduction
                arr[j][k] =use_var(a, b);
            }
        }
    }

    gettimeofday(&end_time, NULL);
    time_t elasped_time_usec = (end_time.tv_sec*1e6 + end_time.tv_usec) - (start_time.tv_sec *1e6 + start_time.tv_usec);
    printf("Run time: %lu microseconds\n", elasped_time_usec);
    return 0;
}
