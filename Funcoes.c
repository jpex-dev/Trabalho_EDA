#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <stdbool.h>

#define MAX_NUMBERS 1000

// Função para criar um novo nó na lista ligada
/**
 * .
 * 
 * \param linhas
 * \param colunas
 * \return 
 */
Matriz* CriaElementoMatriz(int v) {
    Matriz* aux = (Matriz*)malloc(sizeof(Matriz));
    if (aux == NULL) return NULL;
    aux->next = NULL;
    aux->valor = v;
    return aux;
}
Matriz* InsereNaMatriz(Matriz* ini, Matriz* novo) {
    if (ini == NULL) ini = novo;
    else
    {
        novo->next = ini;
        ini = novo;
    }
    return ini;
}

Matriz* NovaMatriz(int linhas, int colunas,char* filename) {
    int numeros[MAX_NUMBERS];
    int contador = 0;
    int temp;
    while (fread(&temp, sizeof(int), 1, filename) == 1 && contador < MAX_NUMBERS) {
        numeros[contador++] = temp;
        // Ignora o ';' após o número
        fseek(filename, 1, SEEK_CUR);
    }

}




// Função para carregar dados de um arquivo de texto para a matriz
Matriz* lerFicheiro(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }
    char line[1024];
    int num_linhas = 0; // Inicializa o número de linhas como 0
    int num_colunas = 0; // Inicializa o número de colunas como 0

    // Lê cada linha do arquivo
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

    Matriz* matriz = NovaMatriz(num_linhas, num_colunas,filename);

    printf("%d\n", num_linhas);
    printf("%d\n", num_colunas);

    return matriz;
}

//antes de ler variaveis fazer o malloc da mesma

//PEssoa* inicio = Null;
// inicio = Insere na lista (inicio,aux)
// usar cria pessoa ao ler o ficheiro, para cada char ser um espaço novo
// ter uma funçao de ler e outra de gravar, o de ler vai ter o inserir na matriz
// 
// Função para alterar um valor na matriz
void AdicionarValores(Matriz matrix) {
        
}
bool Grava(Matriz* i, char* f) {
    if ((i == NULL) || (strlen(f) == 0))return(false);
    !feof(f);

}

//// Função para liberar a memória alocada pela matriz
void freeMatriz(Matriz* matriz) {
    free(matriz);
}
