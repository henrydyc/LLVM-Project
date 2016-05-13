#include<stdio.h>
#include <sys/time.h>

int g_a =10; //dead global

int use_var(int var, int dead_arg){
    dead_arg*= 13168%17; //dead code
    return var + 1;
}

int main(){
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    long int n = 10000000000;
    int a, b;
    for (long int i = 0; i < n; i++) {
        b = i*13168%17; //dead code
        b = 10;
        a = use_var(1, 0); //dead code
        a = 10;
    }
    use_var(a, b);//b is a dead arg
    gettimeofday(&end_time, NULL);
    time_t elasped_time_usec = (end_time.tv_sec*1e6 + end_time.tv_usec) - (start_time.tv_sec *1e6 + start_time.tv_usec);
    printf("Run time: %.4g seconds\n", elasped_time_usec*1e-6);
    return 0;
}
