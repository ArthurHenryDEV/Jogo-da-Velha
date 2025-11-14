#include <stdio.h>
#include <string.h>

struct Jogador {
    char nome[50];
    int vitorias;
};

void atualizarRanking(struct Jogador j) {
    struct Jogador lista[100];
    int n = 0, achou = 0, i;
    FILE *f = fopen("ranking.txt", "r");

    if (f) {
        while (fscanf(f, "%49s %d", lista[n].nome, &lista[n].vitorias) == 2)
            n++;
        fclose(f);
    }

    for (i = 0; i < n; i++) {
        if (strcmp(lista[i].nome, j.nome) == 0) {
            lista[i].vitorias += j.vitorias;
            achou = 1;
            break;
        }
    }

    if (!achou)
        lista[n++] = j;

    f = fopen("ranking.txt", "w");
    for (i = 0; i < n; i++)
        fprintf(f, "%s %d\n", lista[i].nome, lista[i].vitorias);
    fclose(f);
}

void mostrarRanking() {
    FILE *f = fopen("ranking.txt", "r");
    if (!f) {
        printf("\nNenhum ranking salvo ainda.\n");
        return;
    }
    printf("\n=== RANKING ===\n");
    char nome[50];
    int v;
    while (fscanf(f, "%49s %d", nome, &v) == 2)
        printf("%s - %d vitorias\n", nome, v);
    fclose(f);
}

int main() {
    struct Jogador j;
    int op;

    printf("Digite seu nome: ");
    scanf("%49s", j.nome);
    j.vitorias = 0;

    do {
        printf("\n1 - Jogar\n2 - Ver ranking\n3 - Sair\nOpcao: ");
        scanf("%d", &op);

        if (op == 1) {
            printf("Simulando jogo...\n");
            printf("%s venceu!\n", j.nome);
            j.vitorias = 1;
            atualizarRanking(j);
        } else if (op == 2) {
            mostrarRanking();
        }
    } while (op != 3);

    return 0;
}

