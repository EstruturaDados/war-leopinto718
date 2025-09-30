// Cadastrar, exibir territórios e simular ataques

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn()
#include <time.h>   // Para srand() e rand()

// Definir a estrutura
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Protótipos das funções ---
void cadastrarTerritorios(struct Territorio* mapa, int totalTerritorios);
void exibirTerritorios(struct Territorio* mapa, int totalTerritorios);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);
void limparBuffer();

// --- Função principal ---
int main() {
    int totalTerritorios;
    struct Territorio* mapa = NULL;
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    printf("=================================== \n\n");
    printf("SISTEMA DE GERENCIAMENTO DE TERRITÓRIOS\n\n");
    
    // Solicitar número total de territórios
    printf("Digite o número total de territórios a serem cadastrados: ");
    scanf("%d", &totalTerritorios);
    limparBuffer();
    
    // Validar entrada
    if (totalTerritorios <= 0) {
        printf("Número de territórios deve ser maior que zero!\n");
        return 1;
    }
    
    // Alocação dinâmica de memória para os territórios
    mapa = (struct Territorio*)calloc(totalTerritorios, sizeof(struct Territorio));
    
    // Verificar se a alocação foi bem-sucedida
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
    printf("\nMemória alocada para %d territórios.\n\n", totalTerritorios);
    
    // Cadastrar territórios
    cadastrarTerritorios(mapa, totalTerritorios);
    
    // Exibir territórios cadastrados
    printf("\n===================================\n");
    exibirTerritorios(mapa, totalTerritorios);
    
    // Sistema de ataques
    printf("\n===================================\n");
    printf("SISTEMA DE ATAQUES\n");
    
    int continuar = 1;
    while (continuar) {
        int indiceAtacante, indiceDefensor;
        
        // Exibir territórios disponíveis para ataque
        printf("\nTerritórios disponíveis:\n");
        for (int i = 0; i < totalTerritorios; i++) {
            printf("%d - %s (%s) - %d tropas\n", 
                   i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        
        // Selecionar território atacante
        printf("\nSelecione o território ATACANTE (1 a %d): ", totalTerritorios);
        scanf("%d", &indiceAtacante);
        limparBuffer();
        indiceAtacante--; // Ajustar para índice do array
        
        // Validar atacante
        if (indiceAtacante < 0 || indiceAtacante >= totalTerritorios) {
            printf("Território atacante inválido!\n");
            continue;
        }
        
        // Selecionar território defensor
        printf("Selecione o território DEFENSOR (1 a %d): ", totalTerritorios);
        scanf("%d", &indiceDefensor);
        limparBuffer();
        indiceDefensor--; // Ajustar para índice do array
        
        // Validar defensor
        if (indiceDefensor < 0 || indiceDefensor >= totalTerritorios) {
            printf("Território defensor inválido!\n");
            continue;
        }
        
        // Validar se não é o mesmo território
        if (indiceAtacante == indiceDefensor) {
            printf("Um território não pode atacar a si mesmo!\n");
            continue;
        }
        
        // Validar se as cores são diferentes
        if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
            printf("Não é possível atacar um território da mesma cor!\n");
            continue;
        }
        
        // Validar se o atacante tem tropas suficientes
        if (mapa[indiceAtacante].tropas <= 1) {
            printf("Território atacante não tem tropas suficientes para atacar!\n");
            continue;
        }
        
        // Realizar ataque
        printf("\n=== INICIANDO ATAQUE ===\n");
        printf("%s (%s) está atacando %s (%s)!\n", 
               mapa[indiceAtacante].nome, mapa[indiceAtacante].cor,
               mapa[indiceDefensor].nome, mapa[indiceDefensor].cor);
        
        atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
        
        // Exibir situação após o ataque
        printf("\n=== SITUAÇÃO APÓS O ATAQUE ===\n");
        exibirTerritorios(mapa, totalTerritorios);
        
        // Perguntar se deseja continuar
        printf("\nDeseja realizar outro ataque? (1 - Sim, 0 - Não): ");
        scanf("%d", &continuar);
        limparBuffer();
    }
    
    // Liberar memória alocada
    liberarMemoria(mapa);
    
    printf("\nPrograma finalizado. Memória liberada.\n");
    return 0;
}

// --- Função para cadastrar territórios ---
void cadastrarTerritorios(struct Territorio* mapa, int totalTerritorios) {
    printf("=================================== \n\n");
    printf("Vamos cadastrar os %d territórios do nosso mundo\n\n", totalTerritorios);

    for (int i = 0; i < totalTerritorios; i++) {
        printf("Cadastrando Território %d\n", i + 1); 
        
        // Nome
        printf("Digite o nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        limparBuffer();
        
        // Cor
        printf("Digite a cor: ");
        scanf(" %9[^\n]", mapa[i].cor);
        limparBuffer();
        
        // Tropas
        printf("Digite número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
        
        printf("\n");
    }
}

// --- Função para exibir territórios ---
void exibirTerritorios(struct Territorio* mapa, int totalTerritorios) {
    printf("EXIBINDO OS TERRITÓRIOS CADASTRADOS:\n\n");
    for(int i = 0; i < totalTerritorios; i++) {
        printf("Território %d\n", i + 1); 
        printf("  Nome:  %s\n", mapa[i].nome);
        printf("  Cor:   %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("\n");
    }
}

// --- Função para simular ataque entre territórios ---
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Simular dados de batalha (1-6 para cada lado)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);
    
    // Determinar vencedor
    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("\n>>> VITÓRIA DO ATACANTE! <<<\n");
        
        // Transferir cor (controle do território)
        printf("O território %s agora pertence aos %s!\n", defensor->nome, atacante->cor);
        strcpy(defensor->cor, atacante->cor);
        
        // Transferir metade das tropas do defensor para o atacante
        int tropasCapturadas = defensor->tropas / 2;
        if (tropasCapturadas == 0 && defensor->tropas > 0) {
            tropasCapturadas = 1; // Garantir pelo menos 1 tropa se havia alguma
        }
        
        atacante->tropas += tropasCapturadas;
        defensor->tropas -= tropasCapturadas;
        
        printf("%d tropas capturadas do território derrotado.\n", tropasCapturadas);
        
    } else if (dadoAtacante < dadoDefensor) {
        // Defensor vence
        printf("\n>>> VITÓRIA DO DEFENSOR! <<<\n");
        
        // Atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("O atacante perdeu 1 tropa no ataque frustrado.\n");
        } else {
            printf("O atacante não tem tropas para perder!\n");
        }
        
    } else {
        // Empate - ambos perdem uma tropa
        printf("\n>>> EMPATE! Ambos perdem tropas. <<<\n");
        
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("Atacante perdeu 1 tropa.\n");
        }
        
        if (defensor->tropas > 1) {
            defensor->tropas--;
            printf("Defensor perdeu 1 tropa.\n");
        }
    }
    
    printf("\nSituação atual:\n");
    printf("Atacante (%s): %d tropas\n", atacante->nome, atacante->tropas);
    printf("Defensor (%s): %d tropas\n", defensor->nome, defensor->tropas);
}

// --- Função para liberar memória alocada ---
void liberarMemoria(struct Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        mapa = NULL; // Boa prática: definir ponteiro como NULL após liberar
    }
}

// --- Função para limpar buffer de entrada ---
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}