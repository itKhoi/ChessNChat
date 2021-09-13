#ifndef MOVE_H
#define MOVE_H

#include <stdio.h>

//Movement program flow

//Move selected->is space empty->call valid move which calls (piece)Move which also calls path blocked -> call inCheck with a dummy board -> move piece 

int whiteMove(int CB[8][8],int x, int z, int a, int c);

int blackMove(int CB[8][8],int x, int z, int a, int c);

int sameTeam(int a, int b);//Sees if piece ID are the same polarity

int findKing(int CB[8][8], int side);

int scanCheck(int CB[8][8], int side);

int scanCastleCheck(int CB[8][8],int x, int y, int side);

//Takes the board and location
//Then calls appropriate function for that piece
int scanMove(int CB[8][8], int x, int y, int a, int b);

int pawnMove(int CB[8][8], int x, int y, int a, int b); //Function checks that the pawn at that location can move to that square

int rookMove(int CB[8][8], int x, int y, int a, int b); //Function checks that the rook at that location can move to that square

int knightMove(int CB[8][8], int x, int y, int a, int b); //Function checks that the knight at that location can move to that square

int bishopMove(int CB[8][8], int x, int y, int a, int b); //Function checks that the bishop at that location can move to that square

int queenMove(int CB[8][8], int x, int y, int a, int b); //Function checks that the queen at that location can move to that square

int kingMove(int CB[8][8], int x, int y, int a, int b); //Function checks that the king at that location can move to that square


#endif