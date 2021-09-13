/*board.h will handle printing of the board only*/

#ifndef BOARD_H
#define BOARD_H

#define KYEL  "\x1B[33m"
#define KRED  "\x1B[31m"
#define RESET "\x1B[0m"

#include <stdio.h>
#include "translate.h"

void CreateChessBoard(int CB[8][8]);

void copyBoard(int CB[8][8], int Copy[8][8]);

void spaceDecode(int CB[8][8],int x,int y);

void printBoard(int CB[8][8]);

void printBoardN(int CB[8][8]);

void CEP(int CB[8][8],int color);

void promotion(int CB[8][8],int option);

#endif