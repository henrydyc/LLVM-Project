#include<stdio.h>

int add (int a, int b){
    return a+b;
}

void foo(int a, int b){
    int sum = add (a, b);
    printf("Sum = %d\n", a);
}

int main(){
    int a=0, b=1;
    foo(a, b);
    return 0;
}
