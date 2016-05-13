/*LLVM Passes for:
 * 1. Simple Constant Propagation: -constprop
 * 2. Interprocedural Constant Propagation: -ipconstprop
 * 3. Sparse Conditional Constant Propagation: -sccp*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define ARRAY_SIZE 1000

struct foo {
    int m;
    int arr[ARRAY_SIZE];
};

void init_foo (struct foo* f){
    f->m = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        f->arr[i] = 1; 
    }
}

int use_var (int a, int b){
    return a+b;
}

/*To test if it can be optimized to the more efficient pass-by-pointer*/
int use_foo (const struct foo f){
    int sum;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += f.arr[i];
        sum %= 100;
    }
    return sum;
}


int reassociate (int num1, int num2, int dead_arg){
   return (100 + num1) -50 + (num2 - 50); // Equal to num1 + num2 
}

int main(){
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    long int n = 3000;
    int a = 1, b = 1, ret1, ret2;
    int dead_arr[100][100];

    for (long int i = 0; i < n; i++) { 
        struct foo f;
        for (int j = 0; j*j < 100*100; j++){//Loop Strength Reduction
            b = 131683%29*1613895%129*76; //Dead code
            for (int k = 0; k*k <100*100; k++){ //Loop Strength Reduction
                b = 10; //Constant propagation makes this dead code
                struct foo dead_f;
                init_foo(&dead_f);//dead_f should be eliminated by dce
                a = 131683%29*1613895%129*76; // a loop invariant and is dead here
                a = b + 10;
                init_foo(&f);
                f.m = reassociate(a, b, f.m); //Only the very last f in the loop is not dead
                a = j*4 + b;//Loop Strength Reduction
                b = k*8;//Loop Strength Reduction
                ret1 =use_var(a, b);
                dead_arr[j][k] = a + b; //dead code
            }
        }
        ret2 = use_foo(f); //Only the very last temp in the loop is not dead
    }

    gettimeofday(&end_time, NULL);
    time_t elasped_time_usec = (end_time.tv_sec*1e6 + end_time.tv_usec) - (start_time.tv_sec *1e6 + start_time.tv_usec);
    printf("Temp variables are: %d and %d\n",ret1, ret2);
    printf("Run time: %lu microseconds\n", elasped_time_usec);
    return 0;
}
