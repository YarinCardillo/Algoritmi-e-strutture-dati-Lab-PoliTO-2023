#include "stdlib.h"
#include "stdio.h"

typedef struct Corse{
    int a;
    int b;
    char c;
} corse;


int main(){

    int n = 3;
    corse array1[n];

    for (int i = 0; i < n; ++i) {
        array1[i].a = i;
        array1[i].b = i+1;
        array1[i].c = 'a'+i;
    }

    corse *elencoP[n];
    for (int i = 0; i < n; ++i) {
        elencoP[i] = &array1[i];
    }

    for (int i = 0; i < n; ++i) {
        fprintf(stdout, "%d %d %c\n", elencoP[i]->a, elencoP[i]->b, elencoP[i]->c);
    }




}