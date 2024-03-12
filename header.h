#ifndef HEADER_H
#define HEADER_H

// Definição da estrutura de dados para um nó da lista ligada
typedef struct Node {
    int** matriz;
    struct Node* next;
} Node;

// Definição da estrutura de dados para a matriz

// Protótipos das funções
Node* NovaMatriz( int linhas, int colunas);
Node* CriaMatriz();
//void setValue(Matrix* matrix, int row, int col, int value);
//void insertRow(Matrix* matrix, int row);
//void deleteRow(Matrix* matrix, int row);
//void printMatrix(Matrix* matrix);
void freeMatriz(Node* matriz);

#endif