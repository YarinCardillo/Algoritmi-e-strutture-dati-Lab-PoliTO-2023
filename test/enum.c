#include "stdio.h"
#include "string.h"

int main(){

char mese[9] = "aprile";
// typedef enum Mese {gennaio, febbraio, marzo, aprile, maggio, giugno, luglio, agosto, settembre, ottobre, novembre, dicembre} mesi;

int i=0;
char matriceMesi[12][10+1]={"gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno", "luglio", "agosto", "settembre", "ottobre", "novembre", "dicembre"};
while(i<12 && strcmp(mese, matriceMesi[i])!=0){
    i++;
}

fprintf(stdout, "%d\n", i+1);
}
