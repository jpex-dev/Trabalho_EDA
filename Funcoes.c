/*****************************************************************//**
 * \file   Funcoes.c
 * \brief
 *
 * \author peixoto
 * \date   March 2024
 * 
 * Explicação de cada função resumida no header.h
 *********************************************************************/

 // Esta linha é usada para poder deixar executar mesmo tendo vulnerabilidades tais como scanf....
#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * 
 * 
 * @param valor
 * @return 
 */
ElementoMatriz* CriaElementoMatriz(int valor) {
    //aloca a memoria necessaria para esse elemento da matriz
    ElementoMatriz* novo = (ElementoMatriz*)malloc(sizeof(ElementoMatriz));
    if (novo == NULL) {
        // da print de um standard error se de erro ao alocar memeoria
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
    // atribui o valor novo (elemento que vem no dos parametros) á variavel da matriz
    if (matriz->elementos[linha][coluna] == NULL) {
        matriz->elementos[linha][coluna] = novo;
    }
    else {
        // se nao for nulo o elemento ele cria um, e da lhe o valor do proximo.
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
    // abre o ficheiro
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o ficheiro %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    // aloca a memoria necessaria para a matriz
    Matriz* matriz = (Matriz*)malloc(sizeof(Matriz));
    if (matriz == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a matriz.\n");
        exit(EXIT_FAILURE);
    }

    // Dá á matriz os valores da linha e coluna que vem de parametros calculados antes
    matriz->linhas = linhas;
    matriz->colunas = colunas;

    // aloca o espaço da matriz
    matriz->elementos = (ElementoMatriz***)malloc(sizeof(ElementoMatriz**) * linhas);
    if (matriz->elementos == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os elementos da matriz.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < linhas; i++) {
        // aloca memoria dos elementos
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
                fprintf(stderr, "Erro ao ler o ficheiro.\n");
                continue;
            }
            // 
            ElementoMatriz* novo = CriaElementoMatriz(temp);
            // insere na matriz com lkinha de i e coluna de j e o elemento novo
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
        fprintf(stderr, "Erro ao abrir o ficheiro %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    // calculo da linhas e colunas

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
        fprintf(stderr, "Erro: ficheiro vazio ou formato inválido.\n");
        exit(EXIT_FAILURE);
    }
    //cria a mtriz confrome o calculo da linhas e colunas
    Matriz* matriz = NovaMatriz(num_linhas, num_colunas, filename);

    //DA ERRO A PARTIR DAQUI!!
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
        fprintf(stderr, "Erro: Falha ao abrir o ficheiro %s para escrita.\n", filename);
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

    // Escreve a matriz no ficheiro
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
 * @return int 
 */
int CalculaSomaMaxima(Matriz* matriz) {
    int somaMaxima = 0;


    //Percorre todas a matriz 
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {

            //aloca a memoria para a matriz dos elementos escolhidos
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
                // Inicializa a matriz de elementos escolhidos com zeros
                for (int l = 0; l < matriz->colunas; l++) {
                    escolhidos[k][l] = 0;
                }
            }


            // Inicia a soma atual com o valor da célula atual
            int somaAtual = matriz->elementos[i][j]->valor;
            // Marca a célula atual como escolhida
            escolhidos[i][j] = 1;

            // Marca toda a linha e coluna da célula atual como escolhida
            for (int k = 0; k < matriz->linhas; k++) {
                escolhidos[k][j] = 1;
            }
            for (int l = 0; l < matriz->colunas; l++) {
                escolhidos[i][l] = 1;
            }

            // Loop principal para calcular a soma máxima

            while (1) {
                int max = 0;
                int max_i = -1;
                int max_j = -1;
                // Encontra o próximo elemento não escolhido com o maior valor

                for (int k = 0; k < matriz->linhas; k++) {
                    for (int l = 0; l < matriz->colunas; l++) {
                        if (!escolhidos[k][l] && matriz->elementos[k][l]->valor > max) {
                            max = matriz->elementos[k][l]->valor;
                            max_i = k;
                            max_j = l;
                        }
                    }
                }
                // Se não houver mais elementos disponíveis, sai do loop

                if (max_i == -1 || max_j == -1) {
                    break;
                }
                // Adiciona o valor máximo encontrado à soma atual e marca o elemento escolhido
                somaAtual += max;
                escolhidos[max_i][max_j] = 1;
                // Marca toda a linha e coluna do elemento escolhido como escolhida

                for (int k = 0; k < matriz->linhas; k++) {
                    escolhidos[k][max_j] = 1;
                }
                for (int l = 0; l < matriz->colunas; l++) {
                    escolhidos[max_i][l] = 1;
                }
            }
            // Atualiza a soma máxima se a soma atual for maior

            if (somaAtual > somaMaxima) {
                somaMaxima = somaAtual;
            }
            // Liberta a memória alocada para a matriz de elementos escolhidos

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
