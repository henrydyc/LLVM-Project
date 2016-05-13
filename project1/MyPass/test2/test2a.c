#include<stdio.h>
extern void foo(float a);

int main(){
    foo(1.2f);
    printf("Hello!\n");
}
