
/*
Foco 1: Fazer a estrtura para jogo da velha jxj
LÓGICA: 
    ENTRADA: 
    PROCESSAMENTO: 
    SAÍDA:

Foco 2: Fazer a estrtura para jogo da velha jxm
LÓGICA: 
    ENTRADA:
    PROCESSAMENTO: 
    SAÍDA:

Foco 3: Ranking
LÓGICA: 
    ENTRADA:
    PROCESSAMENTO: 
    SAÍDA:

Foco 4: Menu/Saida/Creditos
LÓGICA: 
    ENTRADA:
    PROCESSAMENTO: 
    SAÍDA:

Foco 5: Doc, vídeos
LÓGICA: 
    ENTRADA:
    PROCESSAMENTO: 
    SAÍDA:

Ranking/Menu/Sair
JXJ
JXM
Créditos/Documentação/Video
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



struct Jogador {
    char nome[50];
    char simb;
    int vitorias;
};

struct Ranking {
    struct Jogador j[10];
    int qtd;
} rankList;

// Função para limpar o terminal (multiplataforma)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa a execução de forma multiplataforma (em milissegundos)
void pausarTela(int milissegundos) {
#ifdef _WIN32
    Sleep(milissegundos); // Windows usa milissegundos
#else
    usleep(milissegundos * 1000); // usleep usa micro, então multiplica por 1000
#endif
}

int main(){
    int opcao, opcaoTabuleiro;

    do{
        limparTela();

        printf("===== JOGO DA VELHA =====\n");
        printf("1 - JOG x JOG\n");
        printf("2 - JOG x COM\n");
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            limparTela();

            printf("===== JOGADOR1 vs JOGADOR2 =====\n");
            printf("1 - Tabuleiro 3x3\n");
            printf("2 - Tabuleiro 4x4\n");
            printf("0 - Voltar\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoTabuleiro);

            if (opcaoTabuleiro == 1){
                printf("Iniciando JOGO 3x3 (JOG 1 vs JOG 2)...\n");
            }else if (opcaoTabuleiro == 2){
                printf("Iniciando JOGO 4x4 (JOG 1 vs JOG 2)...\n");
            }else if (opcaoTabuleiro == 0){
                printf("Voltando ao menu principal...\n");
            }else{
                printf("Opcao invalida!\n");
            }

            usleep(500000);

        }else if (opcao == 2){
            limparTela();
            
            printf("===== JOGADOR vs COMPUTADOR =====\n");
            printf("1 - Tabuleiro 3x3\n");
            printf("2 - Tabuleiro 4x4\n");
            printf("0 - Voltar\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoTabuleiro);

            if (opcaoTabuleiro == 1){
                printf("Iniciando JOGO 3x3 (JOG vs COM)...\n");
            }else if (opcaoTabuleiro == 2){
                printf("Iniciando JOGO 4x4 (JOG vs COM)...\n");
            }else if (opcaoTabuleiro == 0){
                printf("Voltando ao menu principal...\n");
            }else{
                printf("Opcao invalida!\n");
            }

            usleep(500000);

        }else if (opcao == 0){
            printf("Saindo do jogo...\n");

        }else{
            printf("Opcao invalida! Tente novamente.\n");
            usleep(500000);
        }

    }while (opcao != 0);

    return 0;
    }

