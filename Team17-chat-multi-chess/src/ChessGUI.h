/***********************************************************
*
*A simple GTK example
*simple.h: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/

#ifndef CHESSGUI_H
#define CHESSGUI_H

#include "string.h"
#include "move.h"
#include "board.h"
#include "translate.h"

#define MAX_MSGLEN  100 
#define SQUARE_SIZE 50  
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  (8*SQUARE_SIZE)
#define BOARD_HEIGHT (8*SQUARE_SIZE)
#define WINDOW_WIDTH  (BOARD_WIDTH + 8*BOARD_BORDER)
#define WINDOW_HEIGHT (BOARD_HEIGHT + 8*BOARD_BORDER)

enum GRID
{
	BLACK = 0,
	WHITE = 1,
	WKING,   WKING_S,
	WQUEEN,  WQUEEN_S,
	WKNIGHT, WKNIGHT_S,
	WBISHOP, WBISHOP_S,
	WROOK,   WROOK_S,
	WPAWN,   WPAWN_S,
	BKING,   BKING_S,
	BQUEEN,  BQUEEN_S,
	BKNIGHT, BKNIGHT_S,
	BBISHOP, BBISHOP_S,
	BROOK,   BROOK_S,
	BPAWN,   BPAWN_S
};


#endif
