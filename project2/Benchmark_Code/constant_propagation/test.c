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

#include<stdio.h>
int main(){
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    long int n = 10000000000;
    int a, b;
    for (long int i = 0; i < n; i++) {
        a = 10;
        b = 10;
        a = a + b; //should be propagated as a = 20
        b = b + 20; //should be propagated as b = 30
    }
    use_var(a, b);//should be propagated as use_var(20, 30)
    gettimeofday(&end_time, NULL);
    time_t elasped_time_usec = (end_time.tv_sec*1e6 + end_time.tv_usec) - (start_time.tv_sec *1e6 + start_time.tv_usec);
    printf("Run time: %.4g seconds\n", elasped_time_usec*1e-6);
    return 0;
}
