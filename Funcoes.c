#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Fun��o para criar um novo n� na lista ligada
Node* NovaMatriz(int linhas, int colunas) {
    Node* matriz = (Node*)malloc(sizeof(Node));
    if (matriz == NULL) {
        fprintf(stderr, "Erro ao alocar mem�ria para a matriz.\n");
        exit(EXIT_FAILURE);
    }

    // Aloca mem�ria para as linhas da matriz
    matriz->matriz = (int**)malloc(linhas * sizeof(int*));
    if (matriz->matriz == NULL) {
        fprintf(stderr, "Erro ao alocar mem�ria para as linhas da matriz.\n");
        exit(EXIT_FAILURE);
    }

    // Aloca mem�ria para as colunas de cada linha da matriz e inicializa com zero
    for (int i = 0; i < linhas; i++) {
        matriz->matriz[i] = (int*)malloc(colunas * sizeof(int));
        if (matriz->matriz[i] == NULL) {
            fprintf(stderr, "Erro ao alocar mem�ria para as colunas da matriz.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < colunas; j++) {
            matriz->matriz[i][j] = 0;
        }
    }

    matriz->next = NULL;
    return matriz;
}
// Fun��o para carregar dados de um arquivo de texto para a matriz
Node* CriaMatriz() {
    FILE* file = fopen("dados.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }
    char line[1024];
    int num_linhas = 0; // Inicializa o n�mero de linhas como 0
    int num_colunas = 0; // Inicializa o n�mero de colunas como 0

    // L� cada linha do arquivo
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            num_linhas++;
            num_colunas++;

        }
        else if (ch == ';') {
            num_colunas++;
        }
    }
    num_colunas = num_colunas / num_linhas;

    fclose(file);

    Node* matriz = NovaMatriz(num_linhas, num_colunas);

    printf("%d\n", num_linhas);
    printf("%d\n", num_colunas);

    return matriz;
}

// Fun��o para alterar um valor na matriz
void AdicionarValores(Node* matrix) {
        
}

//// Fun��o para inserir uma nova linha na matriz
//void insertRow(Matrix* matrix, int row) {
//    if (row < 0 || row > matrix->num_rows) {
//        fprintf(stderr, "Posi��o inv�lida para inser��o.\n");
//        exit(EXIT_FAILURE);
//    }
//    Node** new_rows = (Node**)malloc((matrix->num_rows + 1) * sizeof(Node*));
//    if (new_rows == NULL) {
//        fprintf(stderr, "Erro ao alocar mem�ria.\n");
//        exit(EXIT_FAILURE);
//    }
//    for (int i = 0; i < row; i++) {
//        new_rows[i] = matrix->rows[i];
//    }
//    new_rows[row] = NULL;
//    for (int i = row; i < matrix->num_rows; i++) {
//        new_rows[i + 1] = matrix->rows[i];
//    }
//    free(matrix->rows);
//    matrix->rows = new_rows;
//    matrix->num_rows++;
//}
//
//// Fun��o para remover uma linha da matriz
//void deleteRow(Matrix* matrix, int row) {
//    if (row < 0 || row >= matrix->num_rows) {
//        fprintf(stderr, "Posi��o inv�lida para remo��o.\n");
//        exit(EXIT_FAILURE);
//    }
//    free(matrix->rows[row]);
//    for (int i = row; i < matrix->num_rows - 1; i++) {
//        matrix->rows[i] = matrix->rows[i + 1];
//    }
//    matrix->num_rows--;
//}
//
//// Fun��o para imprimir a matriz na consola
//void printMatrix(Matrix* matrix) {
//    for (int i = 0; i < matrix->num_rows; i++) {
//        Node* current = matrix->rows[i];
//        while (current != NULL) {
//            printf("%d\t", current->value);
//            current = current->next;
//        }
//        printf("\n");
//    }
//}
//
//// Fun��o para liberar a mem�ria alocada pela matriz
void freeMatriz(Node* matriz) {
    free(matriz);
}
