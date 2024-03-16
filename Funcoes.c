/*****************************************************************//**
 * \file   Funcoes.c
 * \brief
 *
 * \author peixoto
 * \date   March 2024
 *********************************************************************/

 // Esta linha é usada para poder deixar executar mesmo tendo vulnerabilidades tais como scanf....
#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * .
 * 
 * @param valor
 * @return 
 */
ElementoMatriz* CriaElementoMatriz(int valor) {
    ElementoMatriz* novo = (ElementoMatriz*)malloc(sizeof(ElementoMatriz));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para um novo elemento da matriz.\n");
        exit(EXIT_FAILURE);
    }
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

/**
 * .
 * 
 * @param matriz
 * @param linha
 * @param coluna
 * @param novo
 * @return 
 */
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

/**
 * .
 * 
 * @param linhas
 * @param colunas
 * @param filename
 * @return 
 */
Matriz* NovaMatriz(const int linhas, const int colunas, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    Matriz* matriz = (Matriz*)malloc(sizeof(Matriz));
    if (matriz == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a matriz.\n");
        exit(EXIT_FAILURE);
    }
    matriz->linhas = linhas;
    matriz->colunas = colunas;
    matriz->elementos = (ElementoMatriz***)malloc(sizeof(ElementoMatriz**) * linhas);
    if (matriz->elementos == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os elementos da matriz.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < linhas; i++) {
        matriz->elementos[i] = (ElementoMatriz**)calloc(colunas, sizeof(ElementoMatriz*));
        if (matriz->elementos[i] == NULL) {
            fprintf(stderr, "Erro ao alocar memória para os elementos da matriz.\n");
            exit(EXIT_FAILURE);
        }
    }

    int temp;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (fscanf(file, "%d;", &temp) != 1) {
                fprintf(stderr, "Erro ao ler o arquivo.\n");
                continue;
            }
            ElementoMatriz* novo = CriaElementoMatriz(temp);
            matriz = InsereNaMatriz(matriz, i, j, novo);
        }
    }

    fclose(file);
    return matriz;
}

/**
 * .
 * 
 * @param filename
 * @return 
 */
Matriz* lerFicheiro(const char* filename) {
    int num_linhas = 1;
    int num_colunas = 1;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", filename);
        exit(EXIT_FAILURE);
    }

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

    if (num_linhas == 0 || num_colunas == 0) {
        fprintf(stderr, "Erro: arquivo vazio ou formato inválido.\n");
        exit(EXIT_FAILURE);
    }

    Matriz* matriz = NovaMatriz(num_linhas, num_colunas, filename);
    int numeros[] = { 1,2,3 };
    matriz = escreveNaMatriz(matriz, filename, true, numeros);
    return matriz;
}


/**
 * .
 * 
 * @param matriz
 * @param filename
 * @param tipo_coluna_ou_linha
 * @param array
 * @return 
 */
Matriz* escreveNaMatriz(Matriz* matriz, const char* filename, bool tipo_coluna_ou_linha, int array[]) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erro: Falha ao abrir o arquivo %s para escrita.\n", filename);
        exit(EXIT_FAILURE);
    }

    // Adiciona uma coluna extra ou uma linha extra à matriz
    if (tipo_coluna_ou_linha) {
        // Adiciona os valores por coluna
        for (int j = 0; j < matriz->colunas; j++) {
            for (int i = 0; i < matriz->linhas; i++) {
                ElementoMatriz* novo = CriaElementoMatriz(array[i]);
                matriz = InsereNaMatriz(matriz, i, j, novo);
            }
        }
        matriz->colunas++; // Incrementa o número de colunas na matriz
    }
    else {
        // Adiciona os valores por linha
        for (int i = 0; i < matriz->linhas; i++) {
            for (int j = 0; j < matriz->colunas; j++) {
                ElementoMatriz* novo = CriaElementoMatriz(array[j]);
                matriz = InsereNaMatriz(matriz, i, j, novo);
            }
        }
        matriz->linhas++; // Incrementa o número de linhas na matriz
    }

    // Escreve a matriz no arquivo
    for (int i = 0; i < matriz->linhas; i++) {
            ElementoMatriz* atual = (ElementoMatriz*)malloc(sizeof(ElementoMatriz));
            atual = matriz->elementos[i][matriz->colunas];
            
            while (atual != NULL) {
                fprintf(file, "%d;", atual->valor);
                atual = atual->proximo;
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return matriz;
}


/**
 * .
 * 
 * @param matriz
 * @return 
 */
int CalculaSomaMaxima(Matriz* matriz) {
    int somaMaxima = 0;

    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            int** escolhidos = (int**)malloc(matriz->linhas * sizeof(int*));
            if (escolhidos == NULL) {
                fprintf(stderr, "Erro ao alocar memória para os elementos escolhidos.\n");
                exit(EXIT_FAILURE);
            }
            for (int k = 0; k < matriz->linhas; k++) {
                escolhidos[k] = (int*)malloc(matriz->colunas * sizeof(int));
                if (escolhidos[k] == NULL) {
                    fprintf(stderr, "Erro ao alocar memória para os elementos escolhidos.\n");
                    exit(EXIT_FAILURE);
                }
                for (int l = 0; l < matriz->colunas; l++) {
                    escolhidos[k][l] = 0;
                }
            }

            int somaAtual = matriz->elementos[i][j]->valor;
            escolhidos[i][j] = 1;

            for (int k = 0; k < matriz->linhas; k++) {
                escolhidos[k][j] = 1;
            }
            for (int l = 0; l < matriz->colunas; l++) {
                escolhidos[i][l] = 1;
            }

            while (1) {
                int max = 0;
                int max_i = -1;
                int max_j = -1;
                for (int k = 0; k < matriz->linhas; k++) {
                    for (int l = 0; l < matriz->colunas; l++) {
                        if (!escolhidos[k][l] && matriz->elementos[k][l]->valor > max) {
                            max = matriz->elementos[k][l]->valor;
                            max_i = k;
                            max_j = l;
                        }
                    }
                }
                if (max_i == -1 || max_j == -1) {
                    break;
                }
                somaAtual += max;
                escolhidos[max_i][max_j] = 1;
                for (int k = 0; k < matriz->linhas; k++) {
                    escolhidos[k][max_j] = 1;
                }
                for (int l = 0; l < matriz->colunas; l++) {
                    escolhidos[max_i][l] = 1;
                }
            }

            if (somaAtual > somaMaxima) {
                somaMaxima = somaAtual;
            }

            for (int k = 0; k < matriz->linhas; k++) {
                free(escolhidos[k]);
            }
            free(escolhidos);
        }
    }

    return somaMaxima;
}
/**
 * .
 * 
 * @param matriz
 */
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
