#include "board.h"
#include <stdlib.h>
#include <assert.h>

//Board that holds default board setup


int dBoard[8][8] = {
		{-2,-3,-4,-5,-6,-4,-3,-2},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },
		{2 ,3 ,4 ,5 ,6 ,4 ,3 ,2 }
};

/*
int dBoard[8][8] = {
		{-2,-3,-4,-5,-6,-4,-3,-2},
		{-1,-1,-1,-1,0 ,-1,-1,-1},
		{0 ,0 ,0 ,0 ,-1,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{1 ,1 ,1 ,1 ,1 ,0 ,0 ,1 },
		{2 ,3 ,4 ,5 ,6 ,4 ,3 ,2 }
};
*/
//Function that prints proper pieces by decoding the piece ID
void spaceDecode(int CB[8][8],int x,int y){
	if(CB[x][y] == 0){
		printf("    ");
	}
	
	else if(pull(CB[x][y],4) == 1){//White pawn
		printf(" "KYEL"wP"RESET" ");
	}

	else if(pull(CB[x][y],4) == 2){//White rook
		printf(" "KYEL"wR"RESET" ");
	}	
	
	else if(pull(CB[x][y],4) == 3){//White knight
		printf(" "KYEL"wN"RESET" ");
	}
	
	else if(pull(CB[x][y],4) == 4){//White bishop
		printf(" "KYEL"wB"RESET" ");
	}
	
	else if(pull(CB[x][y],4) == 5){//White queen
		printf(" "KYEL"wQ"RESET" ");
	}
	
	else if(pull(CB[x][y],4) == 6){//White king
		printf(" "KYEL"wK"RESET" ");
	}
	
	else if(pull(CB[x][y],4) == -1){//Black pawn
		printf(" "KRED"bP"RESET" ");
	}

	else if(pull(CB[x][y],4) == -2){//Black rook
		printf(" "KRED"bR"RESET" ");
	}	
	
	else if(pull(CB[x][y],4) == -3){//Black knight
		printf(" "KRED"bN"RESET" ");
	}
	
	else if(pull(CB[x][y],4) == -4){//Black bishop
		printf(" "KRED"bB"RESET" ");
	}
	
	else if(pull(CB[x][y],4) == -5){//Black queen
		printf(" "KRED"bQ"RESET" ");
	}
	
	else if(pull(CB[x][y],4) == -6){//Black king
		printf(" "KRED"bK"RESET" ");
	}
}//End spaceDecode


void CreateChessBoard(int CB[8][8]){
	for(int x = 0; x < 8 ; x++){
		for(int y = 0; y < 8 ; y++){
			CB[x][y] = dBoard[x][y] * 1000;
			
		}
	}
	
}//End CreateChessBoard

void copyBoard(int CB[8][8], int Copy[8][8]){
	for(int x = 0; x < 8 ; x++){
		for(int y = 0; y < 8 ; y++){
			Copy[x][y] = CB[x][y];	
		}
	}
}

void printBoard(int CB[8][8]){
	for(int x = 0; x < 8 ; x++){
		printf("+----+----+----+----+----+----+----+----+\n");
		for(int y = 0; y < 8 ; y++){
			printf("|");
			spaceDecode(CB,x,y);
		}
		printf("|  %d\n",8-x);
	}
	printf("+----+----+----+----+----+----+----+----+\n");
	printf("  A    B    C    D    E    F    G    H\n");
	
	
}

void printBoardN(int CB[8][8]){
	for(int x = 0; x < 8 ; x++){
		for(int y = 0; y < 8 ; y++){
			printf("%6d",CB[x][y]);
		}
	printf("\n");
	}
}

void CEP(int CB[8][8], int color){
	for(int x = 0; x < 8 ; x++){
		for(int y = 0; y < 8 ; y++){
			if((pull(CB[x][y],2))== color){
				CB[x][y] += color*(-10);
			}

		}
	}
	
}

void promotion(int CB[8][8],int option){
	int p = 0;
	if(option == 0){
		for(int i =0;i<=7;i++){
			if(pull(CB[0][i],4) == 1){
				printf("White pawn available for promotion\n");
				while((clip(2,p,6) == 0)){
					printf("Enter 2 for Rook, 3 for knight, 4 for bishop, or 5 for queen: ");
					scanf("%d",&p);
				}
				CB[0][i] = p*1000+100;
			}
			if(pull(CB[7][i],4) == -1){
				printf("Black pawn available for promotion\n");
				while((clip(2,p,6) == 0)){
					printf("Enter 2 for Rook, 3 for knight, 4 for bishop, or 5 for queen: ");
					scanf("%d",&p);
				}
				CB[7][i] = (p*1000+100)*-1;
			}
		}	
	}
	if(option == -5){
		for(int i = 0; i<=7;i++){
			if(pull(CB[7][i],4) == -1){
				CB[7][i] = -5100;
			}
		}
	}
	if(option == 5){
		for(int i = 0; i<=7;i++){
			if(pull(CB[0][i],4) == 1){
				CB[7][i] = 5100;
			}
		}
	}

}







