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
typedef enum Comando{stampa, sort_data, sort_codice, sort_partenza, sort_arrivo, ricerca_partenza, r_fine}comando;

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
    char c;
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
    corse *corseRef1[rows], *corseRef2[rows], *corseRef3[rows], *corseRef4[rows], *corseRef5[rows];

    for (int i = 0; i < rows; ++i) {
        corseRef1[i] = &array[i];
        corseRef2[i] = &array[i];
        corseRef3[i] = &array[i];
        corseRef4[i] = &array[i];
        corseRef5[i] = &array[i];
    }
    sortingData(corseRef1, rows);
    sortingCodice(corseRef2, rows);
    sortingPartenza(corseRef3, rows);
    sortingArrivo(corseRef4, rows);
    do {

        comando cmd = leggiComando();
        fprintf(stdout, "\n");

        switch (cmd) {
            case 0:
                printFunction(array, rows);
                keep = 1;
                break;
            case 1:
                fprintf(stdout, "Log ordinato per data:\n");
                for (int i = 0; i < rows; ++i) {
                    fprintf(stdout, "%s %s %s %s %s %s %d\n", corseRef1[i]->codiceTratta, corseRef1[i]->partenza,
                            corseRef1[i]->destinazione, corseRef1[i]->data, corseRef1[i]->oraPartenza, corseRef1[i]->oraArrivo,
                            corseRef1[i]->ritardo);
                }
                keep = 1;
                break;
            case 2:
                fprintf(stdout, "Log ordinato per codice tratta:\n");
                for (int i = 0; i < rows; ++i) {
                    fprintf(stdout, "%s %s %s %s %s %s %d\n", corseRef2[i]->codiceTratta, corseRef2[i]->partenza,
                            corseRef2[i]->destinazione, corseRef2[i]->data, corseRef2[i]->oraPartenza, corseRef2[i]->oraArrivo,
                            corseRef2[i]->ritardo);
                }
                keep = 1;
                break;
            case 3:
                fprintf(stdout, "Log ordinato per stazione di partenza:\n");
                for (int i = 0; i < rows; ++i) {
                    fprintf(stdout, "%s %s %s %s %s %s %d\n", corseRef3[i]->codiceTratta, corseRef3[i]->partenza,
                            corseRef3[i]->destinazione, corseRef3[i]->data, corseRef3[i]->oraPartenza, corseRef3[i]->oraArrivo,
                            corseRef3[i]->ritardo);
                }
                keep = 1;
                break;
            case 4:
                fprintf(stdout, "Log ordinato per stazione di arrivo:\n");
                for (int i = 0; i < rows; ++i) {
                    fprintf(stdout, "%s %s %s %s %s %s %d\n", corseRef4[i]->codiceTratta, corseRef4[i]->partenza,
                            corseRef4[i]->destinazione, corseRef4[i]->data, corseRef4[i]->oraPartenza, corseRef4[i]->oraArrivo,
                            corseRef4[i]->ritardo);
                }
                keep = 1;
                break;
            case 5:
                ricercaPartenza(corseRef5, rows);
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
    char matrix[r_fine+1][17]={"stampa", "sort_data", "sort_codice", "sort_partenza", "sort_arrivo", "ricerca_partenza", "fine"};
    char command[17];

    fprintf(stdout, "\nDigitare correttamente uno dei seguenti comandi:\n"
                    "-> stampa\n"
                    "-> sort_data\n"
                    "-> sort_codice\n"
                    "-> sort_arrivo\n"
                    "-> ricerca_partenza\n"
                    "-> fine (per terminare)\n");
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
}


void ricercaPartenza(corse **array2, int rows2){
    char inputStaz[30];
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
