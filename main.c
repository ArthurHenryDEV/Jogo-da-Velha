#include <stdio.h>
#include <stdlib.h> // rand e srand
#include <string.h> // strcpy
#include <unistd.h> // usleep
#include <time.h>   // time

// Variáveis globais e funções 
char jogo3x3 [3][3];
char jogo4x4 [4][4];
char jogador1[50], jogador2[50];

struct Jogador {
    char nome[50];
    int vitorias;
};

// Função para limpar o buffer de entrada
void LimparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para limpar o terminal (multiplataforma)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//Verifica se a jogada é valida
int Validacao_Ocupado(char letra){
	if(letra == 'X' || letra == 'O')
		return 1;
	else
		return 0;
}

//Verificar se ela é vazia, ou seja, se for diferente de x e 0, ela é vazia
int PosicaoVazia3X3 (int x, int y) {
	if(jogo3x3 [x][y] != 'X' && jogo3x3[x][y] != 'O')
		return 1;
			
	return 0;
}

	// atualizar o ranking
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

int PosicaoVazia4X4 (int x, int y) {
	if(jogo4x4 [x][y] != 'X' && jogo4x4[x][y] != 'O')
		return 1;
			
	return 0;
}

void IniciarMatriz3X3(){
	int i,j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			jogo3x3[i][j] = ' ';
		}
	}

}

void IniciarMatriz4X4(){
	int i,j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			jogo4x4[i][j] = ' ';
		}
	}

}

//Verifica o lugar jogado é valido, ou seja no espaço 3x3
int Validacao_Coordenada3X3(int x, int y){
	if(x >= 0 && x < 3){
		if(y >= 0 && y <3)
			return 1; //Verdadeiro, é valido
	}
	
	return 0; //Falso, não é valido
}

int Validacao_Coordenada4X4(int x, int y){
	if(x >= 0 && x < 4){
		if(y >= 0 && y <4)
			return 1; //Verdadeiro, é valido
	}
	
	return 0; //Falso, não é valido
}


// Verificar se alguém ganhou o jogo por linha
int GanhouLinha3X3() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 2; j++){ 
            if(Validacao_Ocupado(jogo3x3[i][j]) && jogo3x3[i][j] == jogo3x3[i][j+1]) // j precisa ser j > 2 porque j > 3 ocasionaria erro. 
                igual++;
        }
        if(igual == 3) 
            return 1;
        igual = 1; // inicializar 'igual' novamente para a próxima linha
    }
    return 0;
}

int GanhouLinha4X4() {
    int i, j, igual = 1;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 3; j++){ 
            if(Validacao_Ocupado(jogo4x4[i][j]) && jogo4x4[i][j] == jogo4x4[i][j+1]) // j precisa ser j > 2 porque j > 3 ocasionaria erro. 
                igual++;
        }
        if(igual == 4) 
            return 1;
        igual = 1; // inicializar 'igual' novamente para a próxima linha
    }
    return 0;
}

// Verificar se alguém ganhou o jogo por coluna
int GanhouColuna3X3() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(Validacao_Ocupado(jogo3x3[j][i]) && jogo3x3[j][i] == jogo3x3[j+1][i])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int GanhouColuna4X4() {
    int i, j, igual = 1;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 3; j++) {
            if(Validacao_Ocupado(jogo4x4[j][i]) && jogo4x4[j][i] == jogo4x4[j+1][i])
                igual++;
        }
        if(igual == 4)
            return 1;
        igual = 1;
    }
    return 0;
}

// Verificar vitória pela diagonal principal (esquerda para direita)
int GanhouDiagonalPrincipal3X3() {
    int i, igual = 1;
    for(i = 0; i < 2; i++){
        if(Validacao_Ocupado(jogo3x3[i][i]) && jogo3x3[i][i] == jogo3x3[i+1][i+1])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

int GanhouDiagonalPrincipal4X4() {
    int i, igual = 1;
    for(i = 0; i < 3; i++){
        if(Validacao_Ocupado(jogo4x4[i][i]) && jogo4x4[i][i] == jogo4x4[i+1][i+1])
            igual++;
    }
    if(igual == 4)
        return 1;
    else
        return 0;
}

// Verificar vitória pela diagonal secundaria (direita para esquerda)
int GanhouDiagonalSecundaria3X3() {
    int i, igual = 1;
    for(i = 0; i < 2; i++){
        if(Validacao_Ocupado(jogo3x3[i][3-i-1]) && jogo3x3[i][3-i-1] == jogo3x3[i+1][3-i-2])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

int GanhouDiagonalSecundaria4X4() {
    int i, igual = 1;
    for(i = 0; i < 3; i++){
        if(Validacao_Ocupado(jogo4x4[i][3-i]) && jogo4x4[i][3-i] == jogo4x4[i+1][3-(i+1)])
            igual++;
    }
    if(igual == 4)
        return 1;
    else
        return 0;
}

// Imprimir linha
void Imprimir3X3(){
    limparTela();
    int l, c; // l = linha, c = coluna
    printf("\t   0   1   2\n\n");
    for(l = 0; l < 3; l++) {
        printf("\t%d ", l);
        for(c = 0; c < 3; c++) {
            if(c < 2)
                printf(" %c |", jogo3x3[l][c]);
            else 
                printf(" %c ", jogo3x3[l][c]);
        }
		if(l < 2){
        	printf("\n\t   ---------- \n");
		}
    }
}

void Imprimir4X4(){
    limparTela();
    int l, c; // l = linha, c = coluna
    printf("\t   0   1   2   3\n\n");
    for(l = 0; l < 4; l++) {
        printf("\t%d ", l);
        for(c = 0; c < 4; c++) {
            if(c < 3)
                printf(" %c |", jogo4x4[l][c]);
            else 
                printf(" %c ", jogo4x4[l][c]);
        }
		if(l < 3){
        	printf("\n\t   -------------- \n");
		}
    }
    printf("\n\n");
}

// Função da IA
void JogadaComputador3X3(int *x_ptr, int *y_ptr) {
    int x, y;
    do {
        x = rand() % 3;  // Sorteia coordenadas (0, 1 ou 2) até achar uma casa vazia
        y = rand() % 3;  // Mesma coisa pro y
    } while (PosicaoVazia3X3(x, y) == 0);
    // Devolve os valores armazenados em ponteiros para o jogo
    *x_ptr = x;
    *y_ptr = y;
}

void JogadaComputador4X4(int *x_ptr, int *y_ptr) {
    int x, y;
    do {
        x = rand() % 4;  // Sorteia coordenadas (0, 1, 2 ou 3) até achar uma casa vazia
        y = rand() % 4; 
    } while (PosicaoVazia4X4(x, y) == 0);
    *x_ptr = x;
    *y_ptr = y;
}

// Função de jogo
void Jogar3X3() {
	int x, y, valida, jogadas = 0, ordem = 1, ganhou = 0;
	do{
		do{
			Imprimir3X3();
			  printf("Digite a coordenada que deseja jogar: ");

    if (scanf("%d%d", &x, &y) != 2) {
        LimparBuffer();
        valida = 0;
    } else {
        valida = Validacao_Coordenada3X3(x, y);
        if(valida == 1)
            valida += PosicaoVazia3X3(x, y);
    }
			if(valida != 2){
				printf("\nCoordenada inválida ou já ocupada. Tente novamente.\n");
				usleep(1000000);
			}
		}while(valida != 2);
		if(ordem == 1)
			jogo3x3[x][y] = 'X';
		else 
			jogo3x3[x][y] = 'O';
		jogadas++;
		ordem++;
		if(ordem == 3)
			ordem = 1;
		ganhou = 0;
		ganhou += GanhouLinha3X3();
		ganhou += GanhouColuna3X3();
		ganhou += GanhouDiagonalPrincipal3X3();
		ganhou += GanhouDiagonalSecundaria3X3();
	}while(ganhou == 0 && jogadas < 9);
	if(ganhou != 0){
    	Imprimir3X3();
    	struct Jogador j;
    	if(ordem - 1 == 1){
        printf("\nParab�ns. Voc� venceu, %s!\n", jogador1);
        strcpy(j.nome, jogador1);
    } else {
        printf("\nParab�ns. Voc� venceu, %s!\n", jogador2);
        strcpy(j.nome, jogador2);
    }
    j.vitorias = 1;
    atualizarRanking(j);
	}
	else
    	printf("\nNingu�m venceu...");
	}
	
// Função de jogo para modo JOG X MAQ
void JogarComputador3X3() {
	int x, y, valida, jogadas = 0, ordem = 1, ganhou = 0;
	do{
		if(ordem == 1){
			do{
				Imprimir3X3();
	  printf("Digite a coordenada que deseja jogar: ");

    if (scanf("%d%d", &x, &y) != 2) {
        LimparBuffer();
        valida = 0;
    } else {
        valida = Validacao_Coordenada3X3(x, y);
        if(valida == 1)
            valida += PosicaoVazia3X3(x, y);
    }
				if (valida != 2){ // Mensagem de erro
					printf("\nCoordenada inválida ou já ocupada. Tente novamente.\n");
					usleep(1000000);
				}
			}while(valida != 2);
				jogo3x3[x][y] = 'X';
		}
		else{ 
			Imprimir3X3();
			printf("\nComputador está pensando...\n");
			usleep(1000000);
			JogadaComputador3X3(&x, &y);
			jogo3x3[x][y] = 'O';
		}
		jogadas++;
		ordem++;
		if(ordem == 3)
			ordem = 1;
		ganhou = 0;
		ganhou += GanhouLinha3X3();
		ganhou += GanhouColuna3X3();
		ganhou += GanhouDiagonalPrincipal3X3();
		ganhou += GanhouDiagonalSecundaria3X3();
	}while(ganhou == 0 && jogadas < 9);
	if(ganhou != 0){
    	Imprimir3X3();
    	struct Jogador j;
    	if(ordem - 1 == 1){
        printf("\n\nParab�ns. Voc� venceu, %s!\n", jogador1);
        strcpy(j.nome, jogador1);
    } else {
        printf("\n\nParab�ns. Voc� venceu, %s!\n\n", jogador2);
        strcpy(j.nome, jogador2);
    }
    j.vitorias = 1;
    atualizarRanking(j);
	}
	else
    	printf("\n\nNingu�m venceu...\n");
	}

void Jogar4X4() {
	int x, y, valida, jogadas = 0, ordem = 1, ganhou = 0;
	do{
		do{
			Imprimir4X4();
			  printf("Digite a coordenada que deseja jogar: ");

    if (scanf("%d%d", &x, &y) != 2) {
        LimparBuffer();
        valida = 0;
    } else {
        valida = Validacao_Coordenada4X4(x, y);
        if(valida == 1)
            valida += PosicaoVazia4X4(x, y);
    }
            if(valida != 2){
				printf("\nCoordenada inválida ou já ocupada. Tente novamente.\n");
				usleep(1000000);
			}
		}while(valida != 2);
		if(ordem == 1)
			jogo4x4[x][y] = 'X';
		else 
			jogo4x4[x][y] = 'O';
		jogadas++;
		ordem++;
		if(ordem == 3)
			ordem = 1;
        ganhou = 0;
		ganhou += GanhouLinha4X4();
		ganhou += GanhouColuna4X4();
		ganhou += GanhouDiagonalPrincipal4X4();
		ganhou += GanhouDiagonalSecundaria4X4();
	}while(ganhou == 0 && jogadas < 16);
	if(ganhou != 0){
    	Imprimir4X4();
    	struct Jogador j;
    	if(ordem - 1 == 1){
        printf("\nParab�ns. Voc� venceu, %s!\n", jogador1);
        strcpy(j.nome, jogador1);
    } else {
        printf("\nParab�ns. Voc� venceu, %s!\n", jogador2);
        strcpy(j.nome, jogador2);
    }
    j.vitorias = 1;
    atualizarRanking(j);
	}
	else
    	printf("\nNingu�m venceu...");
	}
void JogarComputador4X4() {
	int x, y, valida, jogadas = 0, ordem = 1, ganhou = 0;
	do{
		if(ordem == 1){
			do{
				Imprimir4X4();
				  printf("Digite a coordenada que deseja jogar: ");

    if (scanf("%d%d", &x, &y) != 2) {
        LimparBuffer();
        valida = 0;
    } else {
        valida = Validacao_Coordenada4X4(x, y);
        if(valida == 1)
            valida += PosicaoVazia4X4(x, y);
    }
				if (valida != 2){ // Mensagem de erro
					printf("\nCoordenada inválida ou já ocupada. Tente novamente.\n");
					usleep(1000000);
				}
			}while(valida != 2);
				jogo4x4[x][y] = 'X';
		}
		else{ 
			Imprimir4X4();
			printf("\nComputador está pensando...\n");
			usleep(1000000);
			JogadaComputador4X4(&x, &y);
			jogo4x4[x][y] = 'O';
		}
		jogadas++;
		ordem++;
		if(ordem == 3)
			ordem = 1;
		ganhou = 0;
		ganhou += GanhouLinha4X4();
		ganhou += GanhouColuna4X4();
		ganhou += GanhouDiagonalPrincipal4X4();
		ganhou += GanhouDiagonalSecundaria4X4();
	}while(ganhou == 0 && jogadas < 16);
	if(ganhou != 0){
    	Imprimir4X4();
    	struct Jogador j;
    	if(ordem - 1 == 1){
        printf("\n\nParab�ns. Voc� venceu %s!\n", jogador1);
        strcpy(j.nome, jogador1);
    } else {
        printf("\n\nParab�ns. Voc� venceu %s!\n\n", jogador2);
        strcpy(j.nome, jogador2);
    }
    j.vitorias = 1;
    atualizarRanking(j);
	}
	else
    	printf("\n\nNingu�m venceu...\n");
	}	

//mostrar o ranking quando solicitado
void mostrarRanking() {
    FILE *f = fopen("ranking.txt", "r");
    if (!f) {
        printf("\nNenhum ranking salvo ainda.\n");
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }
    printf("\n=== RANKING ===\n");
    char nome[50];
    int v;
    while (fscanf(f, "%49s %d", nome, &v) == 2)
        printf("%s - %d vitorias\n", nome, v);
    fclose(f);
    
    printf("\nPressione ENTER para voltar...");
    getchar();
    
}

int main(){
    int opcao, opcaoTabuleiro;
    srand(time(NULL)); // Semente para o gerador aleatório
    do{
        limparTela();

        printf("===== JOGO DA VELHA =====\n");
        printf("1 - JOG x JOG\n");
        printf("2 - JOG x COM\n");
        printf("3 - RANKING\n");
        printf("4 - CREDITOS\n");
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        LimparBuffer();

        // MENU JOG X JOG
        if (opcao == 1) {
            limparTela();
            printf("===== JOGADOR1 vs JOGADOR2 =====\n");
            printf("1 - Tabuleiro 3x3\n");
            printf("2 - Tabuleiro 4x4\n");
            printf("0 - Voltar\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoTabuleiro);
            LimparBuffer();

            // JOG X JOG 3X3
            if (opcaoTabuleiro == 1){

                printf("Iniciando JOGO 3x3 (JOG 1 vs JOG 2)...\n");
                usleep(100000);
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
                    IniciarMatriz3X3();
                    Jogar3X3();
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
                    printf("Voltando ao menu...\n");
                    usleep(1000000);
                }

            // JOG X JOG 4X4
            }else if (opcaoTabuleiro == 2){
                printf("Iniciando JOGO 4x4 (JOG 1 vs JOG 2)...\n");
                usleep(100000);
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
                    IniciarMatriz4X4();
                    Jogar4X4();
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
                    printf("Voltando ao menu...\n");
                    usleep(1000000);
                }
            }else if (opcaoTabuleiro == 0){
                printf("Voltando ao menu principal...\n");
            }else{
                printf("Opcao invalida!\n");
            }
            usleep(500000);

        // MENU JOG X MAQ
        }else if (opcao == 2){
            limparTela();
            printf("===== JOGADOR vs COMPUTADOR =====\n");
            printf("1 - Tabuleiro 3x3\n");
            printf("2 - Tabuleiro 4x4\n");
            printf("0 - Voltar\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoTabuleiro);
            LimparBuffer();

            // JOG X MAQ 3X3
            if (opcaoTabuleiro == 1){
                printf("Iniciando JOGO 3x3 (JOG vs COM)...\n");
                usleep(100000);
                int op;
                printf("\nJogador, digite seu nome: ");
                fgets(jogador1, 50, stdin);
                if (strchr(jogador1, '\n') == NULL) {
                    printf("Nome muito longo! Ele será cortado.\n");
                    usleep(1000000);
                    LimparBuffer();
                }
                else {
                    jogador1[strcspn(jogador1, "\n")] = 0;
                }
                strcpy(jogador2, "Computador");
                printf("\nVocê jogará contra o %s!\n\n", jogador2);
                usleep(1500000);
                do{
                    IniciarMatriz3X3();
                    JogarComputador3X3();
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
                    printf("Voltando ao menu...\n");
                    usleep(1000000);
                }

            // JOG X MAQ 4X4
            }else if (opcaoTabuleiro == 2){
                printf("Iniciando JOGO 4x4 (JOG vs COM)...\n");
                usleep(100000);
                int op;
                printf("\nJogador, digite seu nome: ");
                fgets(jogador1, 50, stdin);
                if (strchr(jogador1, '\n') == NULL) {
                    printf("Nome muito longo! Ele será cortado.\n");
                    usleep(1000000);
                    LimparBuffer();
                }
                else {
                    jogador1[strcspn(jogador1, "\n")] = 0;
                }
                strcpy(jogador2, "Computador");
                printf("\nVocê jogará contra o %s!\n\n", jogador2);
                usleep(1500000);
                do{
                    IniciarMatriz4X4();
                    JogarComputador4X4();
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
                    printf("Voltando ao menu...\n");
                    usleep(1000000);
                }
            }else if (opcaoTabuleiro == 0){
                printf("Voltando ao menu principal...\n");
            }else{
                printf("Opcao invalida!\n");
            }

            usleep(500000);

        }else if (opcao == 3){
            limparTela();    
            mostrarRanking();
        }else if (opcao == 4){   
            int op = 0;
            do{
            limparTela();
            printf("\n===== CREDITOS =====\n");
            printf("Arthur Henry Dias Paiva\n");
            usleep(1000000);
            printf("Abraão Henrique Franco de Araújo\n");
            usleep(1000000);
            printf("Guilherme Marques Andrade Mororó\n");
            usleep(1000000);
            printf("Enzo Morais Lucena\n");
            usleep(1000000);
            printf("Lucas Barbosa Holanda\n\n");
            printf("Tecle '1' para voltar ao menu: ");
            scanf("%d", &op);
            LimparBuffer();
            }while(op != 1);
        }else if (opcao == 0){
            printf("Saindo do jogo...\n");

        }else{
            printf("Opcao invalida! Tente novamente.\n");
            usleep(500000);
        }

    }while (opcao != 0);

    return 0;
    }
