#include "stdlib.h"
#include "stdio.h"

int main(){

float *v;
int N;

    fprintf(stdout, "N? ");
    fscanf(stdin, "%d", &N);
    v = (float *) malloc(N*sizeof(float));
    if(v==NULL) exit(1);

    fprintf(stdout, "%d", v);


    fprintf(stdout, "\n\nN? ");
    fscanf(stdin, "%d", &N);
    v = (float *) realloc(v, N*sizeof(float));
    if(v==NULL) exit(1);

    fprintf(stdout, "%d", v);

    free(v);


    return 0;
}