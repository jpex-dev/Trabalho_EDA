#define _CRT_SECURE_NO_WARNINGS

#include "header.h"

ElementoMatriz* CriaElementoMatriz(int valor) {
    ElementoMatriz* novo = (ElementoMatriz*)malloc(sizeof(ElementoMatriz));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

Matriz* InsereNaMatriz(Matriz* matriz, int linha, int coluna, ElementoMatriz* novo) {
    if (matriz->elementos[linha][coluna] == NULL) {
        matriz->elementos[linha][coluna] = novo;
    }
    else {
        ElementoMatriz* atual = matriz->elementos[linha][coluna];
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
    return matriz;
}

Matriz* NovaMatriz(const int linhas, const int colunas, char* filename) {
    FILE* file = NULL;
    if (filename != NULL)
        file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    Matriz* matriz = (Matriz*)malloc(sizeof(Matriz));
    matriz->linhas = linhas;
    matriz->colunas = colunas;
    matriz->elementos = (ElementoMatriz***)malloc(sizeof(ElementoMatriz**) * linhas);
    for (int i = 0; i < linhas; i++) {
        matriz->elementos[i] = (ElementoMatriz**)calloc(colunas, sizeof(ElementoMatriz*));
    }

    int temp;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (filename != NULL && fscanf(file, "%d;", &temp) != 1) {
                printf("Erro ao ler o arquivo.\n");
                return NULL;
            }
            ElementoMatriz* novo = CriaElementoMatriz(temp);
            matriz = InsereNaMatriz(matriz, i, j, novo);
        }
    }

    if (file != NULL)
        fclose(file);
    return matriz;
}

Matriz* lerFicheiro(char* filename) {
    int num_linhas = 1;
    int num_colunas = 1;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Conta o número de linhas e colunas no arquivo
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            num_linhas++;
            num_colunas ++;
        }
        else if (ch == ';') {
            num_colunas++;
        }
    }
    num_colunas = num_colunas / num_linhas;
    fclose(file);

    // Cria a matriz com o tamanho contado
    Matriz* matriz = NovaMatriz(num_linhas, num_colunas, filename);
    return matriz;
}

void freeMatriz(Matriz* matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            ElementoMatriz* atual = matriz->elementos[i][j];
            while (atual != NULL) {
                ElementoMatriz* temp = atual;
                atual = atual->proximo;
                free(temp);
            }
        }
        free(matriz->elementos[i]);
    }
    free(matriz->elementos);
    free(matriz);
}
