#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "header.h"

int main() {
    // Abre o arquivo para leitura
    char* arquivo = "dados.txt";
    Matriz* matriz = lerFicheiro(arquivo);
    if (matriz == NULL) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    // Imprime a matriz
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

    freeMatriz(matriz); // Libera a memória alocada pela matriz

    return 0;
}
