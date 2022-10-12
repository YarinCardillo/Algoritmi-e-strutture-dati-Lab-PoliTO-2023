#include <stdio.h>
#include "string.h"
#include "ctype.h"

// funzione generale richiesta dal laboratorio, prende in input dal main la stringa da analizzare e la sottostringa da cercare
char *cercaRegexp(char *src, char *regexp);

// funzione chiamata da cercaRegexp per verificare la presenza di parentesi quadre
int isBrackets(const char *source, const char *reg, int *index, const int *jindex, int *leng);

// funzione chiamata da cercaRegexp per verificare la presenza di \a o \A
int isCapOrLow(const char *source, const char *reg, int *index, const int *jindex, int *leng);

// funzione chiamata da cercaRegexp per verificare la presenza di punti fermi
int isPeriod(char reg);


int main() {
    char inputString[100] = "aaSSwQtsMStoSotoCatoMoto";
    char substring[50] = "[^orq][ans].\\At\\aS[qop]";

    fprintf(stdout, "Your string: %s\n", inputString);
    fprintf(stdout, "\nYour substring: %s\n", substring);
    char *p = cercaRegexp(inputString, substring);
    if(p == NULL)
        fprintf(stdout, "\nSubstring not found.\n");
    else
        fprintf(stdout, "\nSubstring found at: %s\n", p);

    return 0;
}


char *cercaRegexp(char *src, char *regexp){
    char *p;
    int count=0;
    int i=0;
    int lenght = (int)strlen(regexp);

    // questo ciclo itera sugli elementi della inputString e su ciascuno verra' effettuata l'analisi
    for (int j = 0; j < strlen(src) && count < lenght; ++j) {

        /*
         * In questa condizione if si verifica se:
         * - l'attuale lettera della inputString coincide con l'attuale lettera della substring cercata
         * OR
         * - l'attuale lettera della inputString e' un punto
         * OR
         * - l'attuale lettera della inputString e' una parentesi quadra
         * OR
         * - l'attuale lettera della inputString e' un backslash
         */
        if(src[j] == regexp[i]
        || isPeriod(regexp[i])
        || isBrackets(src, regexp, &i, &j, &lenght)
        || isCapOrLow(src, regexp, &i, &j, &lenght)){
            i++;
            // quando il counter raggiungera' la lenght della substring, avremo trovato la parola cercata
            count++;

            // solo se siamo al primo "hit", inizializziamo il pointer alla casella corrente della inputString
            if(count == 1)
                p = &src[j];
        }
        else {
           /*
            * Se non abbiamo un hit, a prescindere, ripartiamo da zero.
            * j -= count serve a riportarci indietro nella inputString, per evitare di saltare lettere
            * a causa dei precedenti hit andati a segno.
            */
            j-=count;
            count = 0;
            i=0;
            lenght = (int)strlen(regexp);
        }
    }
    if(count == lenght)
        return p;
    else
        return NULL;
}


int isBrackets(const char *source, const char *reg, int *index, const int *jindex, int *leng){

    if(reg[*index] == '[') {
        int trovato=0;
        /*
         * difference e differenceLen servono a ripristinare, nel caso di "miss", i valori di i e lenght che, passati "by reference"
         * vengono modificati rispettivamente per avanzare nella substring e per rimuovere dalla lunghezza dlla substring
         * il contributo delle parentesi quadre e dell'accento circonflesso.
         */
        int difference=0, differenceLen=0;

        switch (reg[*index+1]){
            case '^':
                *index+=2;
                *leng-=2;
                while(reg[*index] != ']'){
                    if(source[*jindex] != reg[*index]){
                        *index+=1;
                        *leng-=1;
                    }
                    else {
                        return 0;
                    }
                }
                return 1;

            default:

                *index+=1;
                difference++;
                while(reg[*index] != ']' && trovato == 0){
                    if(source[*jindex] == reg[*index]){
                        trovato = 1;
                        while(reg[*index] != ']') {
                            *index+=1;
                            *leng-=1;
                        }
                    }
                    else {
                        *index += 1;
                        difference++;
                    }
                    *leng-=1;
                    differenceLen++;
                }
                if(!trovato) {
                    *index = *index - difference;
                    *leng += differenceLen;
                }
                return trovato;
        }
    }
    else
        return 0;
}


int isCapOrLow(const char *source, const char *reg, int *index, const int *jindex, int *leng){
    if(reg[*index] == '\\'){
        *index+=1;
        switch(reg[*index]){
            case 'a':
                if(islower(source[*jindex])) {
                    *leng-=1;
                    return 1;
                }
                else
                    return 0;
            case 'A':
                if(isupper(source[*jindex])) {
                    *leng-=1;
                    return 1;
                }
                else
                    return 0;
        }
    }
    else
        return 0;
}


int isPeriod(char reg){
    if(reg == '.')
        return 1;
    else
        return 0;
}
