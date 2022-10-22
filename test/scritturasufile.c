#include "stdio.h"
#include "stdlib.h"

int main(){


FILE *fp;
fp = fopen("outputfile.txt", "w");
if(fp==NULL){fprintf(stdout, "error opening file\n"); return -1;}

fprintf(fp, "Writing test\n");

fclose(fp);














return 0;
}
