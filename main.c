/*

Escrever um jogo da velha 3x3 em C utilizando todos os conceitos aprendidos até agora. 
O jogo deve permitir que dois jogadores joguem alternadamente ou que um jogador jogue contra uma máquina.
O jogo, também, deve contar com sistema de ranking, opção de sair da aplicação, créditos e menu para organização.                        

*/


#include <stdio.h>
#include <stdlib.h>

struct Jogador {
    char nome[50];
    char simb;
    int vitorias;
};

struct Ranking {
    struct Jogador j[10];
    int qtd;
} rankList;

int main() {
    return 0;
}

