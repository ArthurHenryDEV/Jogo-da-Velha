#include <stdio.h>


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


int main(){
	
	
printf("Hello World!\n");
	
}