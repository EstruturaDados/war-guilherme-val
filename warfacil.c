#include <stdio.h>
#include <string.h>

#define QTD_TERRITORIOS 5

typedef struct {
    char nome[50];
    char corExercito[30];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[QTD_TERRITORIOS];

    printf("====================================================\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n\n");

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("--- Cadastrando Território %d ---\n", i + 1);

        printf("Nome do Território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército (ex: Azul, Verde, Vermelho): ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o \n deixado pelo scanf

        printf("\n");
    }

    // Exibição final igual à do vídeo
    printf("====================================================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================================\n\n");

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("TERRITÓRIO %d:\n", i + 1);
        printf(" - Nome: %s\n", mapa[i].nome);
        printf(" - Dominado por: Exército %s\n", mapa[i].corExercito);
        printf(" - Tropas: %d\n\n", mapa[i].tropas);
    }

    printf("====================================================\n");
    printf("Fim do cadastro.\n");

    return 0;
}
