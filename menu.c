#include <stdio.h>
#include <stdlib.h>

int main(){
    int opcao, opcaoTabuleiro;

do{
system("cls || clear");

printf("===== JOGO DA VELHA =====\n");
printf("1 - JOG x JOG\n");
printf("2 - JOG x COM\n");
printf("0 - Sair\n");
printf("==========================\n");
printf("Escolha uma opcao: ");
scanf("%d", &opcao);

if (opcao == 1) {
    system("cls || clear");

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

system("pause");

}else if (opcao == 2){
    system("cls || clear");

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

system("pause");

}else if (opcao == 0){
    printf("Saindo do jogo...\n");

}else{
    printf("Opcao invalida! Tente novamente.\n");
system("pause");
}

} while (opcao != 0);

return 0;
}
