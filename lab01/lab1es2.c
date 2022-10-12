#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#define filein "corse.txt"

typedef struct Corse{
    char codiceTratta[30];
    char partenza[30];
    char destinazione[30];
    char data[11];
    char oraPartenza[9];
    char oraArrivo[9];
    int ritardo;
}corse;
typedef enum Comando{r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine}comando;

void selezionaDati(corse array);
comando leggiComando();

int main(){
    FILE *fp;
    int numRow;
    fp = fopen(filein, "r");
    if(fp == NULL)
        fprintf(stdout, "Error input file\n");

    fscanf(fp, "%d", &numRow);
    corse corseArray[numRow];

    for (int i = 0; i < numRow; ++i) {
        fscanf(fp, "%s %s %s %s %s %s %d", corseArray[i].codiceTratta, corseArray[i].partenza, corseArray[i].destinazione, corseArray[i].data, corseArray[i].oraPartenza, corseArray[i].oraArrivo, &corseArray[i].ritardo);
    }
    for (int i = 0; i < numRow; ++i) {
        fprintf(stdout, "%s %s %s %s %s %s %d\n", corseArray[i].codiceTratta, corseArray[i].partenza, corseArray[i].destinazione, corseArray[i].data, corseArray[i].oraPartenza, corseArray[i].oraArrivo, corseArray[i].ritardo);
    }
    selezionaDati(corseArray[numRow]);

    return 0;
}

void selezionaDati(corse array){
    int keep=0;
    do {
        comando cmd = leggiComando();

        switch (cmd) {
            case 0:
                fprintf(stdout, "Palle 0\n");
                keep=1;
                break;
            case 1:
                fprintf(stdout, "Palle 1\n");
                keep=1;
                break;
            case 2:
                fprintf(stdout, "Palle 2\n");
                keep=1;
                break;
            case 3:
                fprintf(stdout, "Palle 3\n");
                keep=1;
                break;
            case 4:
                fprintf(stdout, "Palle 4\n");
                keep=1;
                break;
            case 5:
                fprintf(stdout, "Palle 5\n");
                keep=0;
                break;
            default:
                fprintf(stdout, "Input errato, ripetere\n");
                keep=1;
                break;
        }


    }while(keep);
}

comando leggiComando(){
    comando c;
    char matrix[r_fine+1][12]={"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    char command[14];

    fprintf(stdout, "Digitare correttamente uno dei seguenti comandi: date | partenza | capolinea | ritardo | ritardo_tot | fine (per terminare)");
    fscanf(stdin, "%s", command);
    for (int i = 0; i < 12; ++i) {
        command[i]=tolower(command[i]);
    }
    c = r_date;
    while(c<r_fine+1 && strcmp(command, matrix[c])!=0){
        c++;
    }
    return c;
}
