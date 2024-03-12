#ifndef HEADER_H
#define HEADER_H

// Defini��o da estrutura de dados para um n� da lista ligada
typedef struct Node {
    int** matriz;
    struct Node* next;
} Node;

// Defini��o da estrutura de dados para a matriz

// Prot�tipos das fun��es
Node* NovaMatriz( int linhas, int colunas);
Node* CriaMatriz();
//void setValue(Matrix* matrix, int row, int col, int value);
//void insertRow(Matrix* matrix, int row);
//void deleteRow(Matrix* matrix, int row);
//void printMatrix(Matrix* matrix);
void freeMatriz(Node* matriz);

#endif