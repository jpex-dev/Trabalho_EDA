#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Defini��o da estrutura de dados para um n� da lista ligada
typedef struct ElementoMatriz {
    int valor;
    struct ElementoMatriz* proximo;
} ElementoMatriz;

typedef struct Matriz {
    ElementoMatriz*** elementos;
    int linhas;
    int colunas;
} Matriz;

// Prot�tipos das fun��es
Matriz* NovaMatriz(const int linhas, const int colunas, char* filename);
Matriz* lerFicheiro(char* filename);
Matriz* InsereNaMatriz(Matriz* matriz, int linha, int coluna, ElementoMatriz* novo);
ElementoMatriz* CriaElementoMatriz(int valor);
int CalculaSomaMaxima(Matriz* matriz);
void freeMatriz(Matriz* matriz);

#endif
