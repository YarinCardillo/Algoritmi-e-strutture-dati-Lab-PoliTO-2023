#include "stdio.h"
#include "string.h"
#include "ctype.h"
#define filein "corse.txt"
#define fileout "outputFile.txt"

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
void printFunction(corse array2[], int rows2);
void sortingData(corse *array2[], int rows2);
void sortingOra(corse *array2[], int k);
void sortingCodice(corse *array2[], int rows2);
void sortingPartenza(corse *array2[], int rows2);
void sortingArrivo(corse *array2[], int rows2);
void ricercaPartenza(corse *array2[], int rows2);
int stazcmp(const char *s1, const char *s2);
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

    selezionaDati(corseArray, numRow);
    return 0;
}


void selezionaDati(corse *array, int rows) {
    int keep;
    corse *corseRef[rows];

    for (int i = 0; i < rows; ++i) {
        corseRef[i] = &array[i];
    }

    do {
        comando cmd = leggiComando();
        fprintf(stdout, "\n");

        switch (cmd) {
            case 0:
                printFunction(array, rows);
                keep = 1;
                break;
            case 1:
                sortingData(corseRef, rows);
                keep = 1;
                break;
            case 2:
                sortingCodice(corseRef, rows);
                keep = 1;
                break;
            case 3:
                sortingPartenza(corseRef, rows);
                keep = 1;
                break;
            case 4:
                sortingArrivo(corseRef, rows);
                keep = 1;
                break;
            case 5:
                ricercaPartenza(corseRef, rows);
                keep = 1;
                break;
            case 6:
                keep = 0;
                break;
            default:
                fprintf(stdout, "Input errato, ripetere\n");
                keep = 1;
                break;
        }
    } while (keep);
}


comando leggiComando(){
    comando c;
    char matrix[r_fine+1][17]={"stampa", "sorting_data", "sorting_codice", "sorting_partenza", "sorting_arrivo", "ricerca_partenza", "fine"};
    char command[17];

    fprintf(stdout, "\nDigitare correttamente uno dei seguenti comandi:\n"
                    "stampa | sorting_data | sorting_codice | sorting_partenza | sorting_arrivo | ricerca_partenza | fine (per terminare)\n");
    fscanf(stdin, "%s", command);
    for (int i = 0; i < 12; ++i)
        command[i]=tolower(command[i]);

    c = stampa;
    while(c<r_fine+1 && strcmp(command, matrix[c])!=0){
        c++;
    }
    return c;
}


void printFunction(corse *array2, int rows2){
    unsigned short choice;
    fprintf(stdout, "Scegli se stampare a video (1) o su file (2):\n");
    fscanf(stdin, "%hd", &choice);
    if (choice != 1 && choice != 2) {
        fprintf(stdout, "Input errato\n");
    }
    if (choice == 1) {
        for (int i = 0; i < rows2; ++i) {
            fprintf(stdout, "%s %s %s %s %s %s %d\n", array2[i].codiceTratta, array2[i].partenza,
                    array2[i].destinazione, array2[i].data, array2[i].oraPartenza, array2[i].oraArrivo,
                    array2[i].ritardo);
        }
    } else if(choice==2){
        FILE *fp2;
        fp2 = fopen(fileout, "w");
        if (fp2 == NULL){fprintf(stdout, "Errore apertura file\n"); return;}
        for (int i = 0; i < rows2; ++i) {
            fprintf(fp2, "%s %s %s %s %s %s %d\n", array2[i].codiceTratta, array2[i].partenza,
                    array2[i].destinazione, array2[i].data, array2[i].oraPartenza, array2[i].oraArrivo,
                    array2[i].ritardo);
        }
        fprintf(stdout, "Log printed on 'outputFile.txt'\n");
        fclose(fp2);
    }
}


void sortingData(corse **array2, int rows2){
    corse *temp;
    for (int i = 0; i < rows2-1; i++) {
        for (int j = 0; j < rows2-1-i; j++) {
            if(strcmp(array2[j]->data, array2[j+1]->data)>0) {
                temp = array2[j];
                array2[j] = array2[j + 1];
                array2[j + 1] = temp;
            }
            else if(strcmp(array2[j]->data, array2[j+1]->data)==0){
                sortingOra(array2, j);
            }
        }
    }
    fprintf(stdout, "Log ordinato per data:\n");

    for (int i = 0; i < rows2; ++i) {
        fprintf(stdout, "%s %s %s %s %s %s %d\n", array2[i]->codiceTratta, array2[i]->partenza,
                array2[i]->destinazione, array2[i]->data, array2[i]->oraPartenza, array2[i]->oraArrivo,
                array2[i]->ritardo);
    }
}


void sortingOra(corse **array2, int k){
    corse *temp;
    if(strcmp(array2[k]->oraPartenza, array2[k+1]->oraPartenza)>0) {
        temp = array2[k];
        array2[k] = array2[k+1];
        array2[k+1] = temp;
    }
}


void sortingCodice(corse **array2, int rows2){
    corse *temp;
    for (int i = 0; i < rows2-1; i++) {
        for (int j = 0; j < rows2-1-i; j++) {
            if(strcmp(array2[j]->codiceTratta, array2[j+1]->codiceTratta)>0) {
                temp = array2[j];
                array2[j] = array2[j + 1];
                array2[j + 1] = temp;
            }
        }
    }
    fprintf(stdout, "Log ordinato per stazione di partenza:\n");

    for (int i = 0; i < rows2; ++i) {
        fprintf(stdout, "%s %s %s %s %s %s %d\n", array2[i]->codiceTratta, array2[i]->partenza,
                array2[i]->destinazione, array2[i]->data, array2[i]->oraPartenza, array2[i]->oraArrivo,
                array2[i]->ritardo);
    }
}


void sortingPartenza(corse **array2, int rows2){
    corse *temp;
    for (int i = 0; i < rows2-1; i++) {
        for (int j = 0; j < rows2-1-i; j++) {
            if(strcmp(array2[j]->partenza, array2[j+1]->partenza)>0) {
                temp = array2[j];
                array2[j] = array2[j + 1];
                array2[j + 1] = temp;
            }
        }
    }
    fprintf(stdout, "Log ordinato per stazione di partenza:\n");

    for (int i = 0; i < rows2; ++i) {
        fprintf(stdout, "%s %s %s %s %s %s %d\n", array2[i]->codiceTratta, array2[i]->partenza,
                array2[i]->destinazione, array2[i]->data, array2[i]->oraPartenza, array2[i]->oraArrivo,
                array2[i]->ritardo);
    }
}


void sortingArrivo(corse **array2, int rows2){
    corse *temp;
    for (int i = 0; i < rows2-1; i++) {
        for (int j = 0; j < rows2-1-i; j++) {
            if(strcmp(array2[j]->destinazione, array2[j+1]->destinazione)>0) {
                temp = array2[j];
                array2[j] = array2[j + 1];
                array2[j + 1] = temp;
            }
        }
    }
    fprintf(stdout, "Log ordinato per stazione di partenza:\n");

    for (int i = 0; i < rows2; ++i) {
        fprintf(stdout, "%s %s %s %s %s %s %d\n", array2[i]->codiceTratta, array2[i]->partenza,
                array2[i]->destinazione, array2[i]->data, array2[i]->oraPartenza, array2[i]->oraArrivo,
                array2[i]->ritardo);
    }
}


void ricercaPartenza(corse **array2, int rows2){
    char inputStaz[30], staz[30];
    int count=0;
    fprintf(stdout, "Inserire stazione di partenza:\n");
    fscanf(stdin, "%s", inputStaz);
    for (int i = 0; i < rows2; ++i) {
        if(stazcmp(inputStaz, array2[i]->partenza)) {
            fprintf(stdout, "%s %s %s %s %s %s %d\n", array2[i]->codiceTratta, array2[i]->partenza,
                    array2[i]->destinazione, array2[i]->data, array2[i]->oraPartenza, array2[i]->oraArrivo,
                    array2[i]->ritardo);
            count++;
        }
    }
    if(count==0)
        fprintf(stdout, "Nessuna stazione corrispondente\n");
}


int stazcmp(const char *s1, const char *s2){
    int count=0;
    char string1[strlen(s1)];
    char string2[strlen(s2)];
    for (int i = 0; i < strlen(s1); ++i) {
        string1[i]=tolower(s1[i]);
        string1[i+1]='\000';
    }
    for (int i = 0; i < strlen(s2); ++i) {
        string2[i]=tolower(s2[i]);
        string2[i+1]='\000';
    }
    for (int i = 0; i < strlen(string1) && i < strlen(string2) && count<strlen(string1); ++i) {
        if(string1[i]==string2[i])
            count++;
        else
            return 0;
    }
    if(count == strlen(s1))
        return 1;
    else
        return 0;
}
