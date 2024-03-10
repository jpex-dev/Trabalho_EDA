#include "header.h"
#include <stdio.h>

//ler ficheiro TXT

void lerFicheiro() {
    FILE* ficheiro = fopen("dados.txt", "r");
    if (ficheiro == NULL) {
        printf("Falha ao abrir o ficheiro");
        return;
    }

    int ch;
    while ((ch = fgetc(ficheiro)) != EOF) {
        printf("%c", ch); // Imprime o caractere
    }
    fclose(ficheiro);
}