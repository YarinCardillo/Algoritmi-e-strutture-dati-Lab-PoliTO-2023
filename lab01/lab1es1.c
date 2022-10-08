#include <stdio.h>
#include "string.h"
#include "ctype.h"

char *cercaRegexp(char *src, char *regexp);
int isBrackets(const char *source, const char *reg, int *index, const int *jindex, int *leng);
int isCapOrLow(const char *source, const char *reg, int *index, const int *jindex, int *leng);
int isPeriod(char reg);


int main() {
    char stringaInput[100] = "aaSSwQtsMStoSotoCatoMoto";
    char stringaDaCercare[50] = "[^orq][ans].\\At\\aS[qop]";

    fprintf(stdout, "Your string: %s\n", stringaInput);
    fprintf(stdout, "\nYour substring: %s\n", stringaDaCercare);
    char *p = cercaRegexp(stringaInput, stringaDaCercare);
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

    for (int j = 0; j < strlen(src) && count < lenght; ++j) {

        if(src[j] == regexp[i]
        || isPeriod(regexp[i])
        || isBrackets(src, regexp, &i, &j, &lenght)
        || isCapOrLow(src, regexp, &i, &j, &lenght)){
            i++;
            count++;
            if(count == 1)
                p = &src[j];
        }
        else {
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
