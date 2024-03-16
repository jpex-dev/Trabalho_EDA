#pragma once
/*****************************************************************//**
 * \file   header.h
 * \brief  
 * 
 * \author peixoto
 * \date   March 2024
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da estrutura de dados para um nó da lista ligada

/**
 * Estrutura para Um elemento dentro da matriz
 */
typedef struct ElementoMatriz {
    int valor;
    struct ElementoMatriz* proximo;
} ElementoMatriz;

/**
 * Estrutura Matriz para conter os dados e assim tambem a coluna/linha onde se encontra o mesmo
 */

typedef struct Matriz {
    ElementoMatriz*** elementos;
    int linhas;
    int colunas;
} Matriz;

// Protótipos das funções
/**
 * Cria uma nova Matriz e o espaço do mesmo
 */
Matriz* NovaMatriz(const int linhas, const int colunas, char* filename);

/**
 *  Lê um ficheiro onde na qual a função de criar é nele contido
 *  Calcula tambem o tamanho da matriz dentro do ficheiro
 */
Matriz* lerFicheiro(char* filename);


/**
 * Insere os Ficheiro Lidos no ficheiro para a estrutura da matriz
 */
Matriz* InsereNaMatriz(Matriz* matriz, int linha, int coluna, ElementoMatriz* novo);


/**
 * Cria o elemeto da Matriz e o espaço do mesmo
 */
ElementoMatriz* CriaElementoMatriz(int valor);


/**
 * CAlcula a Soma maxima da mtriz nao podendo assim conter a mesma linhas / coluna
 */
int CalculaSomaMaxima(Matriz* matriz);


/**
 * Liberta o espaço alocado
 */
void freeMatriz(Matriz* matriz);

Matriz* escreveNaMatriz(Matriz* matriz, const char* filename, bool tipo_coluna_ou_linha, int array[]);

