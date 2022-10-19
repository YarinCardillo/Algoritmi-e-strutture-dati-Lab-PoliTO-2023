#include <stdio.h>
#include "stdlib.h"
#include "string.h"

int main() {
    typedef struct Studente{
        char nome[20];
        char cognome[20];
        int matricola;
    }studente;

    studente *jo=(studente *) malloc(sizeof(studente));

    strcpy(jo->nome, "Giovanni");
    strcpy(jo->cognome, "Crimaldi");
    jo->matricola = 123456;

    fprintf(stdout, "Nome: %s\n"
                    "Cognome: %s\n"
                    "Matricola: %d\n", jo->nome, jo->cognome, jo->matricola);

    return 0;
}
