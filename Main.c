#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "header.h"

#define MAX_NUMBERS 1000 // Define o tamanho máximo do array

int main() {
    FILE* arquivo;
    char nome_arquivo[100];
    int numeros[MAX_NUMBERS];
    int contador = 0;
    int num;

    // Solicita o nome do arquivo ao usuário


    // Abre o arquivo para leitura
    arquivo = fopen("dados.txt", "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê os dados do arquivo usando fread
  // Lê os números inteiros do arquivo separados por ';'
    while (fscanf(arquivo, "%d;", &num) != EOF) {
        numeros[contador++] = num;
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Exibe os números lidos
    printf("Números lidos do arquivo:\n");
    for (int i = 0; i < contador; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    return 0;
    return 0;
}