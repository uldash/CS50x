#include <stdio.h>

// Prototype for meow function
void meow(int);

int main(void){
    meow(3);
}

// Function
void meow(int n){
    for(int i = 0; i < n; i++){
        printf("meow\n");
    }
    // error: use of undeclared identifier 'i'
    // printf(i);
}