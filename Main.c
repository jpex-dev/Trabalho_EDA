#include "header.h"

int main() {
    Ficheiro* ficheiro = CriaFicheiro();
    lerFicheiro(ficheiro);
    //escreverFicheiro(ficheiro);
    //LimparEspacoFicheiro(ficheiro);
    printf("Dados lidos e escritos com sucesso.\n");
    return 0;
}