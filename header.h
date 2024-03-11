#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100 // Defina o comprimento máximo da linha conforme necessário

typedef struct Ficheiro {
    int linhas;
    int colunas;
    int** matriz;
} Ficheiro;

typedef struct Node {
    int dados;
    struct Node* proximo;
} Node;

Ficheiro* CriaFicheiro();
void LimparEspacoFicheiro(Ficheiro* ficheiro);
void lerFicheiro(Ficheiro* ficheiro);
void escreverFicheiro(const Ficheiro* ficheiro);

#endif
