#include <stdio.h>
#include "string.h"


char *cercaRegexp(char *src, char *regexp);
int ifbrackets(const char *source, const char *reg, int *index, const int *jindex, int *leng);
int ifbracketsAlt(const char *source, const char *reg, int *index, const int *jindex, int *leng);
int ifperiod(char reg);


int main() {
    char stringaInput[100] = "UoAdatpMatoSotoCatoMoto";
    char stringaDaCercare[20] = "[NNCABBB].[pa]t[^op]";

    fprintf(stdout, "%s\n", cercaRegexp(stringaInput, stringaDaCercare));

    return 0;
}


char *cercaRegexp(char *src, char *regexp){

    char *p;
    int count=0;
    int i=0;


    int lenght = (int)strlen(regexp);
    for (int j = 0; j < strlen(src) && count < lenght; ++j) {


        if(src[j] == regexp[i] || ifperiod(regexp[i]) || ifbrackets(src, regexp, &i, &j, &lenght) || !ifbracketsAlt(src, regexp, &i, &j, &lenght)){
      //      if(regexp[i] == 't')
      //          fprintf(stdout, "ok\n");
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


int ifbrackets(const char *source, const char *reg, int *index, const int *jindex, int *leng){

    int trovato=0;
    int difference=0, differenceLen=0;
    if(reg[*index] == '[') {
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
    }
    if(trovato == 0) {
        *index = *index - difference;
        *leng += differenceLen;
    }

   return trovato;
}


int ifbracketsAlt(const char *source, const char *reg, int *index, const int *jindex, int *leng){

    int trovato=0;
    int difference=0, differenceLen=0;
    if(reg[*index] == '[' && reg[*index+1] == '^') {
        *index+=2;
        difference+=2;
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
    }
    int fakeindex = *index - difference;

    if(reg[fakeindex+1] != '^') {
        trovato = 2;
        *leng += differenceLen;
        *index -= difference;
    }
    *leng-=2;
    return trovato;

}


int ifperiod(char reg){
    if(reg == '.')
        return 1;
    else
        return 0;

}
