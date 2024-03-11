#include "header.h"

Ficheiro* CriaFicheiro() {
    Ficheiro* ficheiro = (Ficheiro*)malloc(sizeof(Ficheiro));
    if (ficheiro == NULL) {
        printf("Erro ao alocar memória para Ficheiro.\n");
        exit(EXIT_FAILURE);
    }
    ficheiro->linhas = 0;
    ficheiro->colunas = 0;
    ficheiro->matriz = NULL;
    return ficheiro;
}

void LimparEspacoFicheiro(Ficheiro* ficheiro) {
    if (ficheiro == NULL) {
        return;
    }
    for (int i = 0; i < ficheiro->linhas; i++) {
        free(ficheiro->matriz[i]);
    }
    free(ficheiro->matriz);
    free(ficheiro);
}

void lerFicheiro(Ficheiro* ficheiro) {

    const char* filename = "dados.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Falha ao abrir o ficheiro '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }
    int colunas = 0;
    int linhas = 0;
    ficheiro->matriz = (int**)malloc(linhas * sizeof(int*));

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            ficheiro->matriz[linhas][colunas] = ch;
            linhas++;
            colunas++;
            
        }
        else if (ch == ';') {
            ficheiro->matriz[linhas][colunas] = ch;
            colunas++;
        }
    }
    colunas = colunas / linhas;

    ficheiro->linhas = linhas;
    ficheiro->colunas = colunas;

    rewind(file);

    printf("%d linhas \n", ficheiro->linhas);
    printf("%d colunas \n", ficheiro->colunas);
    

    for (int i = 0; i < ficheiro->linhas; i++)
        for (int j = 0; j < ficheiro->colunas; j++)
        {
            printf("%d", ficheiro->matriz[i][j]);
        }

    fclose(file);
}

void escreverFicheiro(const Ficheiro* ficheiro) {
    const char* filename = "dados.txt";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Falha ao abrir o ficheiro '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ficheiro->linhas; i++) {
        for (int j = 0; j < ficheiro->colunas; j++) {
            fprintf(file, "%d ", ficheiro->matriz[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
