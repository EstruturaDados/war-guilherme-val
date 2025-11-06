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

// Protótipos
void inicializarMapa(Territorio *mapa, const int qtd);
void exibirMapa(const Territorio *mapa, const int qtd);
void batalhar(Territorio *atacante, Territorio *defensor);
void verificarMissao(const Territorio *mapa, const int qtd, const char *corMissao, int tipoMissao);
int contarTerritoriosPorCor(const Territorio *mapa, const int qtd, const char *cor);

// ----------------------------------------------------------
// Funções auxiliares
// ----------------------------------------------------------
void limpaNewline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

// Inicializa o mapa com territórios pré-definidos
void inicializarMapa(Territorio *mapa, const int qtd) {
    const char *nomes[] = {"Brasil", "Rússia", "China", "Canadá", "Egito"};
    const char *cores[] = {"Verde", "Vermelho", "Azul", "Amarelo", "Preto"};
    const int tropasIniciais[] = {5, 4, 3, 6, 4};

    for (int i = 0; i < qtd; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].corExercito, cores[i]);
        mapa[i].tropas = tropasIniciais[i];
    }
}

// Mostra o estado atual do mapa
void exibirMapa(const Territorio *mapa, const int qtd) {
    printf("\n====================================================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================================\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %-10s | Exército %-8s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }
    printf("====================================================\n\n");
}

// Conta quantos territórios uma cor domina
int contarTerritoriosPorCor(const Territorio *mapa, const int qtd, const char *cor) {
    int contador = 0;
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mapa[i].corExercito, cor) == 0)
            contador++;
    }
    return contador;
}

// Simula uma batalha entre dois territórios
void batalhar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("⚠️ %s não pode atacar com apenas 1 tropa.\n\n", atacante->nome);
        return;
    }
    if (strcmp(atacante->corExercito, defensor->corExercito) == 0) {
        printf("⚠️ Não é possível atacar um território do mesmo exército!\n\n");
        return;
    }

    printf("🔥 %s (%s) atacou %s (%s)!\n",
           atacante->nome, atacante->corExercito,
           defensor->nome, defensor->corExercito);

    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("🎲 %s tirou %d | %s tirou %d\n",
           atacante->nome, dadoAtq, defensor->nome, dadoDef);

    if (dadoAtq >= dadoDef) {
        defensor->tropas--;
        printf("💥 Vitória do atacante! %s perdeu 1 tropa.\n", defensor->nome);

        if (defensor->tropas <= 0) {
            printf("🏳️ %s foi conquistado pelo exército %s!\n",
                   defensor->nome, atacante->corExercito);
            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->tropas = 1;
            atacante->tropas--;
        }
    } else {
        atacante->tropas--;
        printf("🛡️ Defesa bem sucedida! %s perdeu 1 tropa.\n", atacante->nome);
    }

    printf("📊 Após a batalha: %s (%d tropas) | %s (%d tropas)\n\n",
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
}

// Verifica o progresso da missão
void verificarMissao(const Territorio *mapa, const int qtd, const char *corMissao, int tipoMissao) {
    printf("\n====================================================\n");
    printf("VERIFICAÇÃO DE MISSÃO\n");
    printf("====================================================\n");

    if (tipoMissao == 1) {
        int restantes = contarTerritoriosPorCor(mapa, qtd, corMissao);
        printf("Missão: Destruir o exército %s.\n", corMissao);
        printf("Status: Restam %d territórios dominados por %s.\n", restantes, corMissao);
        if (restantes == 0)
            printf("🏆 Missão concluída! Você destruiu o exército %s!\n", corMissao);
        else
            printf("⏳ Continue atacando para vencer.\n");
    } else if (tipoMissao == 2) {
        const char *corJogador = mapa[0].corExercito; // cor do jogador principal (exemplo)
        int conquistas = contarTerritoriosPorCor(mapa, qtd, corJogador);
        printf("Missão: Conquistar 3 territórios com o exército %s.\n", corJogador);
        printf("Status: Você domina %d territórios.\n", conquistas);
        if (conquistas >= 3)
            printf("🏆 Missão concluída! Você conquistou 3 territórios!\n");
        else
            printf("⏳ Continue lutando para conquistar mais territórios.\n");
    }

    printf("====================================================\n\n");
}

// ----------------------------------------------------------
// Função principal (menu e loop principal do jogo)
// ----------------------------------------------------------
int main() {
    srand((unsigned int)time(NULL));

    Territorio *mapa = (Territorio *)calloc(QTD_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        printf("Erro de memória!\n");
        return 1;
    }

    inicializarMapa(mapa, QTD_TERRITORIOS);
    exibirMapa(mapa, QTD_TERRITORIOS);

    // Definir missão aleatória
    int tipoMissao = (rand() % 2) + 1; // 1 ou 2
    const char *corMissao = "Verde";   // alvo fixo (poderia ser sorteado também)

    printf("🎯 Sua missão secreta: ");
    if (tipoMissao == 1)
        printf("Destruir o exército %s!\n\n", corMissao);
    else
        printf("Conquistar 3 territórios!\n\n");

    int opcao;
    do {
        printf("=============== MENU ===============\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1: {
            int atq, def;
            exibirMapa(mapa, QTD_TERRITORIOS);
            printf("Número do território atacante (1-%d): ", QTD_TERRITORIOS);
            scanf("%d", &atq);
            printf("Número do território defensor (1-%d): ", QTD_TERRITORIOS);
            scanf("%d", &def);
            getchar();

            if (atq < 1 || atq > QTD_TERRITORIOS || def < 1 || def > QTD_TERRITORIOS || atq == def) {
                printf("⚠️ Escolha inválida!\n\n");
                break;
            }
            batalhar(&mapa[atq - 1], &mapa[def - 1]);
            break;
        }
        case 2:
            verificarMissao(mapa, QTD_TERRITORIOS, corMissao, tipoMissao);
            break;
        case 0:
            printf("Saindo do jogo...\n");
            break;
        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    free(mapa);
    printf("Memória liberada. Fim do jogo!\n");
    return 0;
}
