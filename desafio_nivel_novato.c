// Cadastrar e exibir territórios

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn()

// Definir a estrutura

struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Função principal ---
int main(){

    // totalTerritorios = 0;

    struct Territorio vetor_terr[5]; //Objeto armazenar 5 territórios

    //Input de dados de cada um dos territórios 
    printf("=================================== \n\n");
    printf("Vamos cadastrar os cinco territórios iniciais do nosso mundo\n\n");

    for (int i = 0; i < 5; i++) {
        // Nome
        printf("Cadastrando Território %d\n", i + 1); 
        printf("Digite o nome: \n");
        scanf(" %29s", &vetor_terr[i].nome);
        // Cor
        printf("Digite a cor: \n");
        scanf(" %9s", &vetor_terr[i].cor);
        // Cor
        printf("Digite número de tropas: \n");
        scanf("%d", &vetor_terr[i].tropas);
        // totalTerritorios++
    }

    printf("Exibindo os territórios cadastrados:\n");
    for(int i = 0; i < 5; i++) {
        // Nome
        printf("Território %d\n", i + 1); 
        printf("Nome:  %s\n", vetor_terr[i].nome);
        printf("Cor:  %s\n", vetor_terr[i].cor);
        printf("Número de tropas: %d\n", vetor_terr[i].tropas);
        printf("\n");
        
    }

    return 0;

}
