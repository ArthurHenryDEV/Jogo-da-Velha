#include <stdio.h> 

// Variáveis globais
char jogo [3][3];
char jogador1[40], jogador2[40];

/*Iniciar a Matriz / Fica a nota, o caracter tem que ser diferente de X e O, 
pois vao ser usados pelos jogadores, indica espaços vazios*/
void IniciarMatriz(){

	int i,j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			jogo[i][j] = ' ';
		}
	}

}

//Verifica se a jogada é valida
int Validacao_Ocupado(char letra){
	if(letra == 'x' || letra == '0')
		return 1;
	else
		return 0;
}

//Verifica o lugar jogado é valido, ou seja no espaço 3x3
int Validacao_Coordenada(int x, int y){
	if(x >= 0 && x < 3){
		if(y >= 0 && y <3)
			return 1; //Verdadeiro, é valido
	}
	
	return 0; //Falso, não é valido
}

//Verificar se ela é vazia, ou seja, se for diferente de x e 0, ela é vazia
int PosicaoVazia (int x, int y) {
	if(jogo [x][y] != 'x' && jogo[x][y] != '0')
		return 1;
			
	return 0;
}

// Verificar se alguém ganhou o jogo por linha
int GanhouLinha() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 2; j++){ 
            if(Validacao_Ocupado(jogo[i][j]) && jogo[i][j] == jogo[i][j+1]) // j precisa ser j > 2 porque j > 3 ocasionaria erro. 
                igual++;
        }
        if(igual == 3) 
            return 1;
        igual = 1; // inicializar 'igual' novamente para a próxima linha
    }
    return 0;
}

// Verificar se alguém ganhou o jogo por coluna
int GanhouColuna() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(Validacao_Ocupado(jogo[j][i]) && jogo[j][i] == jogo[j+1][i])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

// Verificar vitória pela diagonal principal (esquerda para direita)
int GanhouDiagonalPrincipal() {
    int i, igual = 1;
    for(i = 0; i < 2; i++){
        if(Validacao_Ocupado(jogo[i][i]) && jogo[i][i] == jogo[i+1][i+1])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

// Verificar vitória pela diagonal secundaria (direita para esquerda)
int GanhouDiagonalSecundaria() {
    int i, igual = 1;
    for(i = 0; i < 2; i++){
        if(Validacao_Ocupado(jogo[i][3-i-1]) && jogo[i][3-i-1] == jogo[i+1][3-i-2])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

// Imprimir linha
void imprimir(){
    int l, c; // l = linha, c = coluna
    printf(" 0 1 2\n");
    for(l = 0; l < 3; l++) {
        printf("%d ", l);
        for(c = 0; c < 3; c++) {
            if(Validacao_Ocupado(jogo[l][c])){
                if(c < 2)
                    printf(" %c |", jogo[l][c]);
                else 
                    printf(" %c ", jogo[l][c]);
            }
            else{
                if(c < 2)
                    printf("   |");
                else
                    printf("   ");
            }
        }
        printf("\n\t--------\n");
    }
}

/*Void já que não precisa retornar nenhuma informação, 
motivo do Do while e não um If, e pra o usuario não abusar de usar
comandos invalidos, ele vai primeiro verificar se o lugar ta valido, e
depois ver se o lugar está vazio.
*/

void jogar(){
	int x, y, valida, jogadas = 0, ganhou = 0, ordem = 1;
	
	do {
		do {
		imprimir();
		printf("Digite a coordenada onde deseja jogar: ");
		scanf("%d%d", &x, &y);
		valida = Validacao_Coordenada(x, y);
		if(valida == 1)
			valida += PosicaoVazia(x, y);
	} while(valida != 2); //Quando valor for 2, é valido e o espaco ta vazio
	
	if(ordem == 1) //Qual jogador vai jogar, 1 pra jogador 1, e 2 para o jogador 2
		jogo[x][y] = 'x';
	else
		jogo[x][y] = '0';
		
	jogadas++; //Contar quantas jogadas foram feitas e para caso dê empate no jogo..

	
	ordem++;		
	if(ordem == 3)
		ordem = 1;
	ganhou +=  GanhouLinha();
	ganhou += GanhouColuna();
	ganhou += GanhouDiagonalPrincipal();
	ganhou += GanhouDiagonalSecundaria();
	
	} while(ganhou == 0 && jogadas < 9);
	
	if(ganhou != 0){
		if(ordem - 1 == 1)//Serve pra anular o incremento do ordem++ e apontar quem realmente venceu
			printf("\nParabens %s. Voce venceu!!!\n\n", jogador1);
		else
			printf("\nParabens %s. Voce venceu!!!\n\n", jogador2);
	}
	else
		printf("\nNinguem venceu. Empate!\n\n");
}




int main(){

printf("Hello World!\n");
	
}
