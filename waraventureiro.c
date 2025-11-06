#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 5

typedef struct {
    char nome[50];
    char corExercito[30];
    int tropas;
} Territorio;

// Remove '\n' do final da string
void limpaNewline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

// Cadastra os territórios dinamicamente
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    printf("====================================================\n");
    printf("CADASTRO DE TERRITÓRIOS\n\n");

    for (int i = 0; i < qtd; i++) {
        printf("--- Território %d ---\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        limpaNewline(mapa[i].nome);

        printf("Cor do Exército: ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        limpaNewline(mapa[i].corExercito);

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o \n deixado pelo scanf

        printf("\n");
    }
}

// Mostra o estado atual do mapa (uma linha por território)
void exibirMapa(Territorio *mapa, int qtd) {
    printf("====================================================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================================\n\n");

    for (int i = 0; i < qtd; i++) {
        printf("%d - %s | Exército %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }
    printf("\n");
}

// Simula um ataque entre dois territórios com saída detalhada
void batalhar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 0) {
        printf("⚠️ O atacante %s não tem tropas suficientes para atacar.\n", atacante->nome);
        return;
    }
    if (defensor->tropas <= 0) {
        printf("⚠️ O defensor %s já não tem tropas.\n", defensor->nome);
        return;
    }

    printf("%s (Atacante) atacou %s (Defensor)!\n", atacante->nome, defensor->nome);

    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf(" - Atacante %s tirou: %d no dado.\n", atacante->nome, dadoAtq);
    printf(" - Defensor %s rolou: %d no dado.\n", defensor->nome, dadoDef);

    if (dadoAtq >= dadoDef) {
        defensor->tropas--;
        printf("→ Vitória do atacante %s! O defensor %s perdeu 1 tropa.\n", atacante->nome, defensor->nome);

        if (defensor->tropas <= 0) {
            printf("💥 O território %s foi conquistado pelo exército %s!\n",
                   defensor->nome, atacante->corExercito);

            // transfere domínio: defensor passa a ter cor do atacante e recebe 1 tropa
            strcpy(defensor->corExercito, atacante->corExercito);

            // Se atacante tiver tropas suficientes, envia 1 tropa para o novo território
            if (atacante->tropas > 0) {
                defensor->tropas = 1;
                atacante->tropas--; // custo de envio
                printf("→ %s envia 1 tropa para o território conquistado (custo: -1 tropa).\n", atacante->nome);
            } else {
                // Caso atacante não tenha tropas para enviar (bizarro), deixa 0
                defensor->tropas = 0;
            }
        }
    } else {
        atacante->tropas--;
        printf("→ Defesa bem sucedida de %s! O atacante %s perdeu 1 tropa.\n", defensor->nome, atacante->nome);
    }

    // Mostrar tropas atuais depois do confronto
    printf("Estado pós-batalha: %s: %d tropa(s) | %s: %d tropa(s)\n",
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
}

// ----------------------------------------------------
// Função principal
// ----------------------------------------------------
int main() {
    srand((unsigned int)time(NULL));

    Territorio *mapa = (Territorio *)calloc(QTD_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, QTD_TERRITORIOS);

    // Exibir mapa após cadastro (cada território em sua própria linha)
    exibirMapa(mapa, QTD_TERRITORIOS);

    int opcao;
    do {
        printf("====================================================\n");
        printf("FASE DE ATAQUE - Escolha os territórios\n");
        printf("====================================================\n");

        int atq, def;
        printf("Número do território atacante (1-%d): ", QTD_TERRITORIOS);
        scanf("%d", &atq);
        printf("Número do território defensor (1-%d): ", QTD_TERRITORIOS);
        scanf("%d", &def);
        getchar();

        if (atq < 1 || atq > QTD_TERRITORIOS || def < 1 || def > QTD_TERRITORIOS || atq == def) {
            printf("⚠️ Escolha inválida! Tente novamente.\n\n");
            continue;
        }

        batalhar(&mapa[atq - 1], &mapa[def - 1]);
        printf("\n");
        exibirMapa(mapa, QTD_TERRITORIOS);

        printf("Deseja continuar atacando? (1 = sim / 0 = não): ");
        scanf("%d", &opcao);
        getchar();
        printf("\n");
    } while (opcao != 0);

    free(mapa);
    printf("Jogo finalizado. Memória liberada!\n");
    return 0;
}
