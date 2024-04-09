/*****************************************************************//**
 * \file   Main.c
 * \brief  
 * 
 * \author peixo
 * \date   March 2024
 *********************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "header.h"

int main() {
    // Abre o ficheiro para leitura
    char* ficheiro = "dados.txt";
 
    //Lê o ficheiro dados.txt
    Matriz* matriz = lerFicheiro(ficheiro);
    if (matriz == NULL) {
        printf("Erro ao ler o ficheiro.\n");
        return 1;
    }

    // Imprime a matriz
    //Somente para debug
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            ElementoMatriz* atual = matriz->elementos[i][j];
            while (atual != NULL) {
                printf("%d ", atual->valor);
                atual = atual->proximo;
            }
        }
        printf("\n");
    }
    int maximo= CalculaSomaMaxima(matriz);

    //Somente para debug
    printf("\n\n%d", maximo);

    freeMatriz(matriz); // Liberta a memória alocada pela matriz

    return 0;
}
