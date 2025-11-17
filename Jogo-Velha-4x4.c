#include <stdio.h> 
#include <stdlib.h> // rand e srand
#include <time.h>   // time
#include <string.h> // strcpy
#include <unistd.h>

// Variáveis globais
char jogo [4][4];
char jogador1[50], jogador2[50];

// Função para limpar o buffer de entrada
void LimparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*Iniciar a Matriz / Fica a nota, o caracter tem que ser diferente de X e O, 
pois vao ser usados pelos jogadores, indica espaços vazios*/
void IniciarMatriz(){
	int i,j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			jogo[i][j] = ' ';
		}
	}

}

//Verifica se a jogada é valida
int Validacao_Ocupado(char letra){
	if(letra == 'X' || letra == 'O')
		return 1;
	else
		return 0;
}

//Verifica o lugar jogado é valido, ou seja no espaço 3x3
int Validacao_Coordenada(int x, int y){
	if(x >= 0 && x < 4){
		if(y >= 0 && y <4)
			return 1; //Verdadeiro, é valido
	}
	
	return 0; //Falso, não é valido
}

//Verificar se ela é vazia, ou seja, se for diferente de x e 0, ela é vazia
int PosicaoVazia (int x, int y) {
	if(jogo [x][y] != 'X' && jogo[x][y] != 'O')
		return 1;
			
	return 0;
}

// Verificar se alguém ganhou o jogo por linha
int GanhouLinha() {
    int i, j, igual = 1;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 3; j++){ 
            if(Validacao_Ocupado(jogo[i][j]) && jogo[i][j] == jogo[i][j+1]) // j precisa ser j > 2 porque j > 3 ocasionaria erro. 
                igual++;
        }
        if(igual == 4) 
            return 1;
        igual = 1; // inicializar 'igual' novamente para a próxima linha
    }
    return 0;
}

// Verificar se alguém ganhou o jogo por coluna
int GanhouColuna() {
    int i, j, igual = 1;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 3; j++) {
            if(Validacao_Ocupado(jogo[j][i]) && jogo[j][i] == jogo[j+1][i])
                igual++;
        }
        if(igual == 4)
            return 1;
        igual = 1;
    }
    return 0;
}

// Verificar vitória pela diagonal principal (esquerda para direita)
int GanhouDiagonalPrincipal() {
    int i, igual = 1;
    for(i = 0; i < 3; i++){
        if(Validacao_Ocupado(jogo[i][i]) && jogo[i][i] == jogo[i+1][i+1])
            igual++;
    }
    if(igual == 4)
        return 1;
    else
        return 0;
}

// Verificar vitória pela diagonal secundaria (direita para esquerda)
int GanhouDiagonalSecundaria() {
    int i, igual = 1;
    for(i = 0; i < 3; i++){
        if(Validacao_Ocupado(jogo[i][3-i]) && jogo[i][3-i] == jogo[i+1][3-(i+1)])
            igual++;
    }
    if(igual == 4)
        return 1;
    else
        return 0;
}

// Imprimir linha
void Imprimir(){
    int l, c; // l = linha, c = coluna
    printf("\t   0   1   2   3\n\n");
    for(l = 0; l < 4; l++) {
        printf("\t%d ", l);
        for(c = 0; c < 4; c++) {
            if(c < 3)
                printf(" %c |", jogo[l][c]);
            else 
                printf(" %c ", jogo[l][c]);
        }
		if(l < 3){
        	printf("\n\t   -------------- \n");
		}
    }
    printf("\n\n");
}

// Função de jogo
void Jogar() {
	int x, y, valida, jogadas = 0, ordem = 1, ganhou = 0;
	do{
		do{
			Imprimir();
			printf("Digite a coordenada que deseja jogar: ");
			scanf("%d%d", &x, &y);
			valida = Validacao_Coordenada(x, y);
			if(valida == 1)
				valida += PosicaoVazia(x, y);
            if(valida != 2){
				printf("\nCoordenada inválida ou já ocupada. Tente novamente.\n");
				usleep(1000000);
			}
		}while(valida != 2);
		if(ordem == 1)
			jogo[x][y] = 'X';
		else 
			jogo[x][y] = 'O';
		jogadas++;
		ordem++;
		if(ordem == 3)
			ordem = 1;
        ganhou = 0;
		ganhou += GanhouLinha();
		ganhou += GanhouColuna();
		ganhou += GanhouDiagonalPrincipal();
		ganhou += GanhouDiagonalSecundaria();
	}while(ganhou == 0 && jogadas < 16);
	if(ganhou != 0){
		Imprimir();
		if(ordem - 1 == 1)
			printf("\nParabéns. Você venceu, %s!\n", jogador1);
		else
			printf("\nParabéns. Você venceu, %s!\n", jogador2);
	}
	else
		printf("\nNinguém venceu...");
}



int main(){
	// menu
	int op;

	printf("Jogador 1, digite seu nome: ");
	fgets(jogador1, 50, stdin);
	if (strchr(jogador1, '\n') == NULL) {
        printf("Nome muito longo! Ele sera cortado.\n");
		usleep(1000000);
        LimparBuffer();
    }
	else {
        jogador1[strcspn(jogador1, "\n")] = 0;
    }
	printf("Jogador 2, digite seu nome: ");
	fgets(jogador2, 50, stdin);
	if (strchr(jogador2, '\n') == NULL) {
        printf("Nome muito longo! Ele será cortado.\n");
		usleep(1000000);
        LimparBuffer();
    }
	else {
        jogador2[strcspn(jogador2, "\n")] = 0;
    }
	do{
		IniciarMatriz();
		Jogar();
		printf("Deseja jogar novamente? \n1 - Sim\n2 - Não\n");
		if (scanf("%d", &op) != 1) {
            LimparBuffer();
            op = 0;
        }
		while(op != 1 && op != 2){
			printf("Caractere inválido. Tecle '1' para 'Sim' e '2' para 'Não'\n");
			if (scanf("%d", &op) != 1) {
                LimparBuffer();
                op = 0; 
            }
		}
	}while(op == 1);
	if(op == 2){
		printf("Voltando ao menu...");
		usleep(1000000);
	}
	return 0;
}
