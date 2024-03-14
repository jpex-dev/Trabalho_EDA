#ifndef HEADER_H
#define HEADER_H

// Defini��o da estrutura de dados para um n� da lista ligada
typedef struct Matriz {
    int* valor;
    struct Matriz* next;
} Matriz;


typedef struct MatrizFile {
    int valor;
};

// Defini��o da estrutura de dados para a matriz

// Prot�tipos das fun��es
Matriz* NovaMatriz( int linhas, int colunas,char* filename);
Matriz* lerFicheiro(char* filename);
Matriz* InsereNaMatriz(Matriz* ini, Matriz* novo);
Matriz* lerFicheiro(char* file);
Matriz* CriaElementoMatriz(int valor);

#endif