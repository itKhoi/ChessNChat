#include "board.h"
#include "translate.h"
#include "move.h"
#include <stdio.h>

int main(){
	
	printf("\n\n");

	int CB[8][8];
	CreateChessBoard(CB);
	int game = 0;
	
	printf("Welcome to Chess.\n");
	printf("\n\n");
	
	
	printBoard(CB);


	game = whiteMove(CB,6,3,3,3);
	printBoard(CB);
	
	game = blackMove(CB,1,4,3,4);
	printBoard(CB);
		



	if(game == 1){
		printf("White has won by checkmate\n Congratulations~\n");
		//fprintf(fp,"\nWhite has won by Checkmate\n");
	}
	if(game == -1){
		printf("Black has won by checkmate\n Congratulations~\n");
		//fprintf(fp,"\nBlack has won by Checkmate\n");
	}
}