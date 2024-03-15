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

    // Percorre todas as células da matriz
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            // Inicializa as células como não escolhidas
            int** escolhidos = (int**)malloc(matriz->linhas * sizeof(int*));
            for (int k = 0; k < matriz->linhas; k++) {
                escolhidos[k] = (int*)malloc(matriz->colunas * sizeof(int));
                for (int l = 0; l < matriz->colunas; l++) {
                    escolhidos[k][l] = 0;
                }
            }

            // Inicia a soma a partir da célula atual
            int somaAtual = matriz->elementos[i][j]->valor;
            escolhidos[i][j] = 1;

            // Percorre as linhas e colunas marcando as células como escolhidas
            for (int k = 0; k < matriz->linhas; k++) {
                escolhidos[k][j] = 1;
            }
            for (int l = 0; l < matriz->colunas; l++) {
                escolhidos[i][l] = 1;
            }

            // Calcula a soma máxima percorrendo a matriz e escolhendo a célula de maior valor não marcada
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
                    break; // Não há mais células disponíveis para escolher
                }
                somaAtual += max;
                escolhidos[max_i][max_j] = 1;
                // Marca as células na mesma linha e coluna como escolhidas
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

            // Libera a memória alocada para a matriz de escolhas
            for (int k = 0; k < matriz->linhas; k++) {
                free(escolhidos[k]);
            }
            free(escolhidos);
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
