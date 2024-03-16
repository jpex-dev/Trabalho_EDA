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

// Defini��o da estrutura de dados para um n� da lista ligada

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

// Prot�tipos das fun��es
/**
 * Cria uma nova Matriz e o espa�o do mesmo
 */
Matriz* NovaMatriz(const int linhas, const int colunas, char* filename);

/**
 *  L� um ficheiro onde na qual a fun��o de criar � nele contido
 *  Calcula tambem o tamanho da matriz dentro do ficheiro
 */
Matriz* lerFicheiro(char* filename);


/**
 * Insere os Ficheiro Lidos no ficheiro para a estrutura da matriz
 */
Matriz* InsereNaMatriz(Matriz* matriz, int linha, int coluna, ElementoMatriz* novo);


/**
 * Cria o elemeto da Matriz e o espa�o do mesmo
 */
ElementoMatriz* CriaElementoMatriz(int valor);


/**
 * CAlcula a Soma maxima da mtriz nao podendo assim conter a mesma linhas / coluna
 */
int CalculaSomaMaxima(Matriz* matriz);


/**
 * Liberta o espa�o alocado
 */
void freeMatriz(Matriz* matriz);

Matriz* escreveNaMatriz(Matriz* matriz, const char* filename, bool tipo_coluna_ou_linha, int array[]);

