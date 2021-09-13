#include "move.h"
#include "translate.h"
#include "board.h"


int testBoard[8][8] = {
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 }
};

int CBX[8][8] = {
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 }
};

int sameTeam(int a, int b){
	if((a>0)&&(b>0)){
		return 1;
	}else if((a<0)&&(b<0)){
		return 1;
	}else{
		return 0;
	}
}

int whiteMove(int CB[8][8],int x, int z, int a, int c){
	CEP(CB,1);

	int valid = 0;

	int bcheckmate;
	int CMflag = 0;
	
	
	//Check that space is not empty
	if(CB[x][z]==0){
		printf("Sorry ol buddy ol pal. You can't move an empty space\n");
	
	//Check that you aren't killing your own piece
	}else if (sameTeam(CB[x][z],CB[a][c]) == 1){
		printf("I mean, I guess you can take your own piece. But rules are rules so no\n"); 
	}else if(CB[x][z]<0){
		printf("Hey. You can't do that. Not your piece\n");
	
	}else{
		if(scanMove(CB,x,z,a,c)==1){
			//Function for scanMoveCheck, but it's being dumb so I just put it here instead
			copyBoard(CB,testBoard);
			//Move the pieces
			testBoard[a][c] = testBoard[x][z];
			testBoard[x][z] = 0;
			//End function scanMoveCheck
			if(scanCheck(testBoard,1) == 0){
				//Moving a piece
			
				
				CB[a][c] = CB[x][z];
				CB[x][z] = 0;
				
				//promotion
				promotion(CB,0);
				
				if(pull(CB[a][c],3)==0){//If piece hasn't moved, update flag
					CB[a][c] += 100;
				}
				if(scanCheck(CB,-1)==1){
					printf("Black king is in check\n");
				}
				valid = 8;
			}
		}else{
			printf("Invalid Move\n");
			return 0;
		}
	}
	
	
	copyBoard(CB,CBX);
	
	//Scan to see if black is in checkmate here
	//Only check for checkmate if the king is in check
	if(scanCheck(CBX,-1) == 1){
		CMflag = 1;
		//Look through the entire board for pieces that can move
		for(int i = 0; i <=7;i++){
			for(int j = 0;j<=7;j++){
				//If the piece found is black
				if(sameTeam(CBX[i][j],-1) == 1){
					//Check the valid moves of that piece
					for(int ii = 0; ii<=7; ii++){
						for(int jj = 0; jj<=7;jj++){
							//Check if that move is even valid
							if((scanMove(CBX,i,j,ii,jj)==1)){
								copyBoard(CBX,testBoard);
								//Move the piece
								testBoard[ii][jj] = testBoard[i][j];
								testBoard[i][j] = 0;
								//If a black piece can move that results in the king escaping check
								//Quit this 4 deep for loop
								if(scanCheck(testBoard,-1) == 0){
									//printf("Black team is not in checkmate\n");
									bcheckmate = 0;
									i += 8;
									j += 8;
									ii+= 8;
									jj+= 8;
									return 5;
								}
							}
						}
					}
				}
			}
		}
	}
	if(CMflag == 1){
		return 2;
	}

	return 1;
	
	
}//end of whiteMove

int blackMove(int CB[8][8],int x, int z, int a, int c){
	CEP(CB,-1);

	int valid = 0;

	int wcheckmate;
	int CMflag = 0;			
	
	//Check that space is not empty
	if(CB[x][z]==0){
		printf("Sorry ol buddy ol pal. You can't move an empty space\n");
	
	//Check that you aren't killing your own piece
	}else if (sameTeam(CB[x][z],CB[a][c]) == 1){
		printf("I mean, I guess you can take your own piece. But rules are rules so no\n"); 
		
	}else if(CB[x][z]>0){
		printf("Hey. You can't do that. Not your piece\n");

	}
	else{
		if(scanMove(CB,x,z,a,c)==1){
			
			//Function for scanMoveCheck, but it's being dumb so I just put it here instead
				copyBoard(CB,testBoard);
				//Move the pieces
				testBoard[a][c] = testBoard[x][z];
				testBoard[x][z] = 0;
			//End function scanMoveCheck
			
			if(scanCheck(testBoard,-1) == 0){
				//Moving a piece
				
				CB[a][c] = CB[x][z];
				CB[x][z] = 0;
				
				//promotion
				promotion(CB,0);
				
				if(pull(CB[a][c],3)==0){//If piece hasn't moved, update flag
					CB[a][c] -= 100;
				}
				if(scanCheck(CB,1)==1){
					printf("White king is in check\n");
				}
				valid = 8;
			}
		}
		else{
			printf("Invalid Move\n");
			return 0;
		}
	}
	

	copyBoard(CB,CBX);
	
	//Scan to see if white is in checkmate here
	//Only check for checkmate if the king is in check
	if(scanCheck(CBX,1) == 1){
		CMflag = 1;
		//Look through the entire board for pieces that can move
		for(int i = 0; i <=7;i++){
			for(int j = 0;j<=7;j++){
				//If the piece found is white
				if(sameTeam(CBX[i][j],1) == 1){
					//Check the valid moves of that piece
					for(int ii = 0; ii<=7; ii++){
						for(int jj = 0; jj<=7;jj++){
							//Check if that move is even valid
							if(scanMove(CBX,i,j,ii,jj)==1){
								copyBoard(CB,CBX);
								copyBoard(CBX,testBoard);
								//Move the piece
								testBoard[ii][jj] = testBoard[i][j];
								testBoard[i][j] = 0;
								//If a white piece can move that results in the king escaping check
								//Quit this 4 deep for loop
								if(scanCheck(testBoard,1) == 0){
									//printf("White team is not in checkmate\n");
									wcheckmate = 0;
									i += 8;
									j += 8;
									ii+= 8;
									jj+= 8;
									return 5;
								}
							}
						}
					}
				}
			}
		}
	}
	
	if(CMflag == 1){
		return -2;
	}
	return 1;
	
}//end of blackMove

int scanMove(int CB[8][8], int x, int y, int a, int b){
	if(abs(pull(CB[x][y],4)) == 1){
		return(pawnMove(CB,x,y,a,b));
		
	}
	if(abs(pull(CB[x][y],4)) == 2){
		return(rookMove(CB,x,y,a,b));
	}
	if(abs(pull(CB[x][y],4)) == 3){
		return(knightMove(CB,x,y,a,b));
	}
	if(abs(pull(CB[x][y],4)) == 4){
		return(bishopMove(CB,x,y,a,b));
	}
	if(abs(pull(CB[x][y],4)) == 5){
		return(queenMove(CB,x,y,a,b));
	}
	if(abs(pull(CB[x][y],4)) == 6){
		return(kingMove(CB,x,y,a,b));
	}
	
	return 0;
	
}

int pawnMove(int CB[8][8], int x, int y, int a, int b){
	
	if(sameTeam(CB[x][y],CB[a][b]) == 1){
		return 0;
	}
	
	//White Pawn
	if(pull(CB[x][y],4) == 1){		
		//Case one space in front
		if((x-a == 1)&&(y == b)){
			//printf("One Space in front\n");	
			if(CB[a][b] == 0){
				return 1;
			}
		}
		//Case two spaces in front
		if((x-a == 2)&&(y==b)){
			//printf("Two Spaces in front\n");	
			if((CB[a][b] == 0)&&((pull(CB[x][y],3))==0)&&(CB[x-1][b]==0)){
				CB[x][y] += 10;
				return 1;
			}
		}
		//Case right diagonal capture
		if((x-a == 1) && (b-y == 1)){
			//printf("Right Diagonal capture\n");
			if(CB[a][b]<-1){
				return 1;
			}
			//Case En Passant
			if(abs(pull(CB[a+1][b],2)) == 1){
				//printf("En Passant success!\n");
				CB[a+1][b] = 0;
				return 1;
			}
		}
		
		//Case Left diagonal capture
		if((x-a == 1) && (y-b == 1)){
			//printf("Left Diagonal capture\n");
			if(CB[a][b]<-1){
				return 1;
			}
			//Case En Passant
			if(abs(pull(CB[a+1][b],2)) == 1){
				//printf("En Passant success!\n");
				CB[a+1][b] = 0;
				return 1;
			}
			
		}
		
		//printf("Illegal Pawn movement\n");
		return 0;

	}
	
	
	//Black Pawn
	if(pull(CB[x][y],4) == -1){
		//Case one space in front
		if((a-x == 1)&&(y == b)){
			//printf("One Space in front\n");	
			if(CB[a][b] == 0){
				return 1;
			}
		}
		//Case two spaces in front
		if((a-x == 2)&&(y==b)){
			//printf("Two Spaces in front\n");	
			if((CB[a][b] == 0)&&((pull(CB[x][y],3))==0)&&(CB[a-1][b])==0){
				CB[x][y] -= 10;
				return 1;
			}
		}
		//Case right diagonal capture
		if((a-x == 1) && (b-y == 1)){
			//printf("Right Diagonal capture\n");
			if(CB[a][b]>1){
				return 1;
			}
			//Case En Passant
			if(abs(pull(CB[a-1][b],2)) == 1){
				//printf("En Passant success!\n");
				CB[a-1][b] = 0;
				return 1;
			}
		}
		
		//Case Left diagonal capture
		if((a-x == 1) && (y-b == 1)){
			//printf("Left Diagonal capture\n");
			if(CB[a][b]>1){
				return 1;
			}
			//Case En Passant
			if(abs(pull(CB[a-1][b],2)) == 1){
				//printf("En Passant success!\n");
				CB[a-1][b] = 0;
				return 1;
			}
		}
		//printf("Illegal Pawn movement\n");
		return 0;
	}
	
	
	return 0;
	
}

int rookMove(int CB[8][8], int x, int y, int a, int b){
	
	if(sameTeam(CB[x][y],CB[a][b]) == 1){
		return 0;
	}
	
	//Valid flag is 0 for invalid and 1 for valid
	int valid;
	
	//Moving horizontally
	if(x == a){
		//Moving to the right
		if(b > y){
			//printf("Rook moving to the right\n");
			for(int i = y+1; i<=b;i++){
				if(i == b){
					//printf("Rook move valid\n");
					valid = 1;
				}
				//If there is a piece in the rooks path
				else if(CB[x][i] != 0){
					//printf("Rook move invalid\n");
					valid = 0;
					//Quit the for loop
					i+=8;
				}
			}
			return valid;
		}
		//Moving to the left
		if(y > b){
			//printf("Rook moving to the left\n");
			for(int i = y-1; i>=b;i--){
				if(i == b){
					//printf("Rook move valid\n");
					valid = 1;
				}
				//If there is a piece in the rooks path
				else if(CB[x][i] != 0){
					//printf("Rook move invalid\n");
					valid = 0;
					//Quit the for loop
					i-=8;
				}
			}
			return valid;
		}
	}
	
	//Moving vertically
	if(b == y){
		//Moving up
		if(a < x){
			//printf("Rook moving up\n");
			for(int i = x-1; i>=a;i--){
				if(i == a){
					//printf("Rook move valid\n");
					valid = 1;
				}
				//If there is a piece in the rooks path
				else if(CB[i][y] != 0){
					//printf("Rook move invalid\n");
					valid = 0;
					//Quit the for loop
					i-=8;
				}
			}
			return valid;
		}
		//Moving down
		if(a > x){
			//printf("Rook moving down\n");
			for(int i = x+1; i<=a;i++){
				if(i == a){
					//printf("Rook move valid\n");
					valid = 1;
				}
				//If there is a piece in the rooks path
				else if(CB[i][y] != 0){
					//printf("Rook move invalid\n");
					valid = 0;
					//Quit the for loop
					i+=8;
				}
			}
			return valid;
		}
	}
	
	//printf("Illegal Rook movement\n");
	return 0;
}

int bishopMove(int CB[8][8], int x, int y, int a, int b){
	
	if(sameTeam(CB[x][y],CB[a][b]) == 1){
		return 0;
	}
	
	//Valid flag is 0 for invalid and 1 for valid
	int valid = -1;
	
	//Temp variables
	int tx = x;
	int ty = y;
	
	//Moving to the right
	if(b>y){
		//Moving up
		if(x>a){
			//printf("Bishop forward right movement\n");
			while(valid == -1){
				ty++;
				tx--;
				if((clip(0,tx,7)==0) || (clip(0,ty,7)==0)){
					//printf("Rook move invalid\n");
					return 0;
				}
				if((tx == a)&&(ty == b)){
					return 1;
				}
				if(CB[tx][ty] != 0){
					//printf("Rook move invalid\n");
					return 0;
				}
			}
		}
		//Moving down
		if(x<a){
			//printf("Bishop backward right movement\n");
			while(valid == -1){
				ty++;
				tx++;
				if((clip(0,tx,7)==0) || (clip(0,ty,7)==0)){
					//printf("Rook move invalid\n");
					return 0;
				}
				if((tx == a)&&(ty == b)){
					return 1;
				}
				if(CB[tx][ty] != 0){
					//printf("Rook move invalid\n");
					return 0;
				}
			}
		}
	}
	//Moving to the left
	if(y>b){
		//Moving up
		if(x>a){
			//printf("Bishop forward left movement\n");
			while(valid == -1){
				ty--;
				tx--;
				if((clip(0,tx,7)==0) || (clip(0,ty,7)==0)){
					//printf("Rook move invalid\n");
					return 0;
				}
				if((tx == a)&&(ty == b)){
					return 1;
				}
				if(CB[tx][ty] != 0){
					//printf("Rook move invalid\n");
					return 0;
				}
			}
		}
		//Moving down
		if(x<a){
			//printf("Bishop backward right movement\n");
			while(valid == -1){
				ty--;
				tx++;
				if((clip(0,tx,7)==0) || (clip(0,ty,7)==0)){
					//printf("Rook move invalid\n");
					return 0;
				}
				if((tx == a)&&(ty == b)){
					return 1;
				}
				if(CB[tx][ty] != 0){
					//printf("Rook move invalid\n");
					return 0;
				}
			}
		}
	}
	
	//printf("Illegal Bishop movement\n");
	return 0;
}

int queenMove(int CB[8][8], int x, int y, int a, int b){
	return((rookMove(CB,x,y,a,b)) || (bishopMove(CB,x,y,a,b)));
}

int knightMove(int CB[8][8], int x, int y, int a, int b){
	
	if(sameTeam(CB[x][y],CB[a][b]) == 1){
		return 0;
	}
	
	//Check that path is 3 spaces only
	if(((abs(a-x)+abs(b-y)) == 3)&&((abs(a-x)>0)&&(abs(b-y)))){
		return 1;
	}
	else{
		//printf("Illegal Knight movement\n");
		return 0;
	}
		
}

int kingMove(int CB[8][8], int x, int y, int a, int b){
	
	if(sameTeam(CB[x][y],CB[a][b]) == 1){
		return 0;
	}
	
	int side;
	if(x == 7){
		side = 1;
	}
	if(x == 0){
		side = -1;
	}
	
	
	//Castling king side
	if((x == a) && (b-y==2)){
		//Empty spaces
		if((CB[x][y+1] == 0)&&(CB[x][y+2] == 0)){
			//king and rook haven't moved
			if((pull(CB[x][y],3) == 0) && (pull(CB[x][7],3) == 0)){
				if((scanCastleCheck(CB,x,y,side) == 0) && (scanCastleCheck(CB,x,y-1,side) == 0) && (scanCastleCheck(CB,x,y-2,side) == 0)){
					//delete the rook
					CB[x][7] = 0;
					if(x == 0){
						CB[x][5] = -2100;
					}	
					if(x == 7){
						CB[x][5] = 2100;
					}					
					return 1;
				}
			}
		}
	}
	
	//Castling queen side
	if((x == a) && (y-b==2)){
		//Empty spaces
		if((CB[x][y-1] == 0)&&(CB[x][y-2] == 0)){
			//king and rook haven't moved
			if((pull(CB[x][y],3) == 0) && (pull(CB[x][7],3) == 0)){
				if((scanCastleCheck(CB,x,y,side) == 0) && (scanCastleCheck(CB,x,y-1,side) == 0) && (scanCastleCheck(CB,x,y-2,side) == 0)){
					//delete the rook
					CB[x][0] = 0;
					if(x == 0){
						CB[x][3] = -2100;
					}	
					if(x == 7){
						CB[x][3] = 2100;
					}					
					return 1;
				}
			}
		}
	}
	
	//Regular movement
	if(((abs(x-a)+abs(y-b))<=2)&&((abs(x-a))!=2)&&((abs(y-b))!=2)){
		return 1;
	}

	return 0;
}

int findKing(int CB[8][8], int side){
	for(int i = 0;i<=7;i++){
		for(int j = 0;j<=7;j++){
			if((abs(pull(CB[i][j],4)) == 6)&&((sameTeam(CB[i][j],side)) == 1)){
				return(100+10*i+j);
			}
		}
	}
	return 0;
}

int scanCheck(int CB[8][8],int side){
	int FK = findKing(CB,side);
	int kx,ky;
	kx = pull(FK,2);
	ky = pull(FK,1);
	
	//Loop through the board
	for(int i = 0;i<=7;i++){
		for(int j = 0;j<=7;j++){
			//Find a piece that is on opposite team of the king
			if(sameTeam(CB[i][j],side) == 0){
				if(scanMove(CB,i,j,kx,ky) == 1){
					return 1;
				}
			}
		}
	}
	
	return 0;
}

int scanCastleCheck(int CB[8][8],int x, int y, int side){	
	//Loop through the board
	for(int i = 0;i<=7;i++){
		for(int j = 0;j<=7;j++){
			//Find a piece that is on opposite team of the king
			if(sameTeam(CB[i][j],side) == 0){
				if(scanMove(CB,i,j,x,y) == 1){
					return 1;
				}
			}
		}
	}
	
	return 0;
}
