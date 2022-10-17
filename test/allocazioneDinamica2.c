#include "stdio.h"
#include "stdlib.h"


int main(){

    int *v;
    int count=1, i=0;

    v = (int *) malloc(count*sizeof(int));
    fprintf(stdout, "Insert values (0 to end):\n");
    while (fscanf(stdin, "%d", &v[i]) && v[i] != 0){
        i++;
        if(i==count) {
            count=count*2;
            v = (int *) realloc(v, count * sizeof(v));
        }
    }

    count=0;
    while (v[count]!=0){
        count++;
    }
    v = (int *) realloc(v, count * sizeof(v));


    for (i = 0; i < count; ++i) {
        fprintf(stdout, "v[%d] = %d\n", i, v[i]);
    }


    free(v);



    return 0;
}