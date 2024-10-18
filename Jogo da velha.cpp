
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clrscr()
{
    system("@cls||clear");
}

char** resetGame(char game[3][3]){
	for(int i =0; i< 3; i ++){
		for( int k = 0; k < 3; k++){
			if(i == 2 ){
				game[i][k] = ' ';
			}else{
			game[i][k] = '_';
			}
		}
	}
}

void printGame(char game[3][3]){

		printf("--------- JOGO DA VELHA --------- \n");
	printf("               Coluna   1 2 3\n");
	printf("              Linha: 1  %c|%c|%c\n", game[0][0],game[0][1],game[0][2]);
	printf("              Linha: 2  %c|%c|%c\n", game[1][0],game[1][1],game[1][2]);
	printf("              Linha: 3  %c|%c|%c\n", game[2][0],game[2][1],game[2][2]);

}


void rules(){

	int start = 0;
	char buffer;

	printf("Bem vindo ao Jogo da velha para jogar você precisa seguir algumas regras básicas:\n");
	printf("1 Regra: O terminal ira indicar de qual e vez do jogador.\n");
	printf("2 Regra: O jogador devera entrar com 2 valores a linha e a coluna ex: 1 2 tanto linha quanto coluna devera estar no range de 1 e 3 caso contrario o programa emitira um erro\n");
	printf("3 Regra: o primeiro jogador que criar uma sequencia de 3 valores sem ser interrompido ganhara o jogo.");

	while (start != 1) {
        printf("Para começar o jogo digite 1: ");

        if (scanf("%d", &start) != 1) {
            printf("Entrada inválida. Por favor, digite o número 1.\n");
            while ((buffer = getchar()) != '\n' && buffer != EOF);
        } else if (start != 1) {
            printf("Entrada incorreta. Você precisa digitar 1 para começar o jogo.\n");
        }
    }


}

char** play(char player,int linha, int coluna,char game[3][3]){
	game[linha][coluna] = player;
}

void getLineAndRow(char player, int *varL, int *varC) {
    int validInput = 0;
    char buffer;
    int canPlay = 0;

    while (!validInput ) {
        printf("Jogador %c\nDigite a linha e a coluna (dois números): ", player);

        if (scanf("%d %d", varL, varC) == 2) {
            validInput = 1;
        } else {
            printf("Entrada inválida. Por favor, digite números inteiros.\n");
            while ((buffer = getchar()) != '\n' && buffer != EOF);
        }
    }
}

int checkWinner(int *winner,char game[3][3], char player){



    for(int i = 0; i < 3; i ++){
        if((game[i][0] != '_' && game[i][0] != ' ') || (game[0][i] != '_' && game[0][i] != ' ') ){
            if((game[i][1] != '_' && game[i][1] != ' ') || (game[1][i] != '_' && game[1][i] != ' ')){
                if((game[i][2] != '_'&& game[i][2] != ' ') || (game[2][i] != '_'&& game[2][i] != ' ')){
                    if((game[i][0] == game[i][1] && game[i][1] == game[i][2]) || (game[0][i] == game[1][i] && game[1][i] == game[2][i])){
                        *winner = 1;
                        printf("\n\n\nganhou: %c\n\n\n", player);
                        break;
                    }
                }
            }
        }




        if((game[0][0] != '_' && game[0][0] != ' ') || (game[2][0]!= '_' && game[2][0] != ' ')){
            if(game[1][1] != '_' && game[1][1] != ' '){
                if((game[2][2] != '_'&& game[2][2] != ' ') || (game[0][2] != '_' && game[0][2] != ' ')){
                    if((game[0][0] == game[1][1] && game[1][1] == game[2][2]) || (game[0][2] == game[1][1] && game[1][1] == game[2][0])){
                        printf("\n\n\nganhou: %c\n\n\n", player);
                        *winner = 1;
                        break;
                    }
                }
            }
        }


	}




}

int isValidPosition(char position, int isABot){

    if(position == '_' || position == ' '){
        return 1;
    }else{
        if(isABot == 1){
        printf("\njogada invalida campo já preenchido jogue novamente.\n");
        }
        return 0;
    }
}
//O
void botMove(char game[3][3], int *varL,int *varC){

srand(time(0));

    //check Corners
    int line;
    int column;
    while(true){
        line = rand() % (2 - 0 + 1) + 0;
        column= rand() % (2 - 0 + 1) + 0;
        if(isValidPosition(game[line][column], 0) == 1) break;
    }

    *varL = line;
    *varC = column;
}



int main() {
	char game[3][3];
	int playerXL, playerXC, playerOL, playerOC;
	int winner = 0;

	rules();
	resetGame(game);
	clrscr();

	while(winner == 0 ){
	printGame(game);


    // para desativar o bot basta comentar daqui até
    botMove(game, &playerOL, &playerOC);
    game[playerOL][playerOC] = 'O';
    printGame(game);
    checkWinner(&winner, game, 'O');
    // aqui


    while(true){
    getLineAndRow('X', &playerXL, &playerXC);
    if(isValidPosition(game[playerXL -1][playerXC-1], 1) == 1) break;
    }
	game[playerXL -1][playerXC -1]='X';
	printGame(game);
    checkWinner(&winner, game, 'X');

	if(winner == 1){
        break;
	}

    // para jogar com dois jogares descomente a baixo

    /*

    while(true){
        getLineAndRow('O', &playerOL, &playerOC);
        if(isValidPosition(game[playerOL-1][playerOC-1]) == 1) break;
    }


	game[playerOL -1][playerOC -1]='O';
	checkWinner(&winner, game, 'O');
	printGame(game);
    */
	}


	printGame(game);

	return 0;
}


