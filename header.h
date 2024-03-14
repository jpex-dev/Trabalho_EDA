#ifndef HEADER_H
#define HEADER_H

// Definição da estrutura de dados para um nó da lista ligada
typedef struct Matriz {
    int* valor;
    struct Matriz* next;
} Matriz;


typedef struct MatrizFile {
    int valor;
};

// Definição da estrutura de dados para a matriz

// Protótipos das funções
Matriz* NovaMatriz( int linhas, int colunas,char* filename);
Matriz* lerFicheiro(char* filename);
Matriz* InsereNaMatriz(Matriz* ini, Matriz* novo);
Matriz* lerFicheiro(char* file);
Matriz* CriaElementoMatriz(int valor);

#endif