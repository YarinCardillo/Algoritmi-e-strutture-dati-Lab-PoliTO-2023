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
typedef enum Comando{stampa, sorting_data, sorting_codice, sorting_partenza, sorting_arrivo, ricerca_partenza, r_fine}comando;

void selezionaDati(corse array[], int rows);
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
    selezionaDati(corseArray, numRow);

    return 0;
}

void selezionaDati(corse array[], int rows){
    int keep=0;
    FILE *fp;
    unsigned short choice;
    do {
        comando cmd = leggiComando();

        switch (cmd) {
            case 0:

                fprintf(stdout, "Scegli se stampare a video (1) o su file (2):\n");
                fscanf(stdin, "%hd", &choice);
                if(choice != 1 && choice != 2){
                    fprintf(stdout, "Input errato\n");
                    break;
                }
                if(choice==1){
                    for (int i = 0; i < rows; ++i) {
                        fprintf(stdout, "%s %s %s %s %s %s %d\n", array[i].codiceTratta, array[i].partenza, array[i].destinazione, array[i].data, array[i].oraPartenza, array[i].oraArrivo, array[i].ritardo);
                    }
                }
                else{
                    fp = fopen("outputFile.txt", "w");
                    if(fp==NULL) fprintf(stdout, "Errore apertura file\n");
                    for (int i = 0; i < rows; ++i) {
                        fprintf(fp, "%s %s %s %s %s %s %d\n", array[i].codiceTratta, array[i].partenza, array[i].destinazione, array[i].data, array[i].oraPartenza, array[i].oraArrivo, array[i].ritardo);
                    }
                    fprintf(stdout, "Log printed on 'outputFile.txt'\n");
                }

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
    char matrix[r_fine+1][17]={"stampa", "sorting_data", "sorting_codice", "sorting_partenza", "sorting_arrivo", "ricerca_partenza", "fine"};
    char command[14];

    fprintf(stdout, "Digitare correttamente uno dei seguenti comandi:\n"
                    "stampa | sorting_data | sorting_codice | sorting_partenza | sorting_arrivo | ricerca_partenza | fine (per terminare)\n");
    fscanf(stdin, "%s", command);
    for (int i = 0; i < 12; ++i) {
        command[i]=tolower(command[i]);
    }
    c = stampa;
    while(c<r_fine+1 && strcmp(command, matrix[c])!=0){
        c++;
    }
    return c;
}