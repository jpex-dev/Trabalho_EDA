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

    Matriz* matriz = NovaMatriz(num_linhas, num_colunas, filename);
    return matriz;
}



int CalculaSomaMaxima(Matriz* matriz) {
    int somaMaxima = 0;

    int** escolhidos = (int**)malloc(matriz->linhas * sizeof(int*));
    for (int i = 0; i < matriz->linhas; i++) {
        escolhidos[i] = (int*)malloc(matriz->colunas * sizeof(int));
        for (int j = 0; j < matriz->colunas; j++) {
            escolhidos[i][j] = 0;
        }
    }


    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            if (!escolhidos[i][j]) {
                int somaAtual = matriz->elementos[i][j]->valor;
                escolhidos[i][j] = 1;
                // Marca os elementos da linha e coluna como escolhidos
                for (int k = 0; k < matriz->colunas; k++) {
                    escolhidos[i][k] = 1;
                }
                for (int k = 0; k < matriz->linhas; k++) {
                    escolhidos[k][j] = 1;
                }

                // Procura o próximo maior elemento disponível
                int max = 0;
                int max_i = -1;
                int max_j = -1;
                for (int l = 0; l < matriz->linhas; l++) {
                    for (int m = 0; m < matriz->colunas; m++) {
                        if (!escolhidos[l][m] && matriz->elementos[l][m]->valor > max) {
                            max = matriz->elementos[l][m]->valor;
                            max_i = l;
                            max_j = m;
                        }
                    }
                }
                while (max_i != -1 && max_j != -1) {
                    somaAtual += max;
                    escolhidos[max_i][max_j] = 1;
                    for (int k = 0; k < matriz->colunas; k++) {
                        escolhidos[max_i][k] = 1;
                    }
                    for (int k = 0; k < matriz->linhas; k++) {
                        escolhidos[k][max_j] = 1;
                    }
                    max = 0;
                    max_i = -1;
                    max_j = -1;
                    for (int l = 0; l < matriz->linhas; l++) {
                        for (int m = 0; m < matriz->colunas; m++) {
                            if (!escolhidos[l][m] && matriz->elementos[l][m]->valor > max) {
                                max = matriz->elementos[l][m]->valor;
                                max_i = l;
                                max_j = m;
                            }
                        }
                    }
                }
                if (somaAtual > somaMaxima) {
                    somaMaxima = somaAtual;
                }
            }
        }
    }
    return somaMaxima;
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
