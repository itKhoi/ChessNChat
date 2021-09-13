/***********************************************************
*
*A simple GTK example
*simple.c: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/

#include <gtk/gtk.h>
#include "ChessGUI.h"

/*Global Variables */

GtkWidget *window ;  
GtkWidget *fixed ; 
GtkWidget *chess_icon ; 
GtkWidget *table ; 


enum GRID Board[8][8];

int CB[8][8];

void InitBoard()
{
	//Row 8
	Board[0][0] = WHITE;
	Board[0][1] = BLACK;
	Board[0][2] = WHITE;
	Board[0][3] = BLACK;
	Board[0][4] = WHITE;
	Board[0][5] = BLACK;
	Board[0][6] = WHITE;
	Board[0][7] = BLACK;
	
	//Row 7
	Board[1][0] = BLACK;
	Board[1][1] = WHITE;
	Board[1][2] = BLACK;
	Board[1][3] = WHITE;
	Board[1][4] = BLACK;
	Board[1][5] = WHITE;
	Board[1][6] = BLACK;
	Board[1][7] = WHITE;
	
	//Row 6
	Board[2][0] = WHITE;
	Board[2][1] = BLACK;
	Board[2][2] = WHITE;
	Board[2][3] = BLACK;
	Board[2][4] = WHITE;
	Board[2][5] = BLACK;
	Board[2][6] = WHITE;
	Board[2][7] = BLACK;
	
	//Row 5
	Board[3][0] = BLACK;
	Board[3][1] = WHITE;
	Board[3][2] = BLACK;
	Board[3][3] = WHITE;
	Board[3][4] = BLACK;
	Board[3][5] = WHITE;
	Board[3][6] = BLACK;
	Board[3][7] = WHITE;
	
	//Row 4
	Board[4][0] = WHITE;
	Board[4][1] = BLACK;
	Board[4][2] = WHITE;
	Board[4][3] = BLACK;
	Board[4][4] = WHITE;
	Board[4][5] = BLACK;
	Board[4][6] = WHITE;
	Board[4][7] = BLACK;
	
	//Row 3
	Board[5][0] = BLACK;
	Board[5][1] = WHITE;
	Board[5][2] = BLACK;
	Board[5][3] = WHITE;
	Board[5][4] = BLACK;
	Board[5][5] = WHITE;
	Board[5][6] = BLACK;
	Board[5][7] = WHITE;
	
	//Row 2
	Board[6][0] = WHITE;
	Board[6][1] = BLACK;
	Board[6][2] = WHITE;
	Board[6][3] = BLACK;
	Board[6][4] = WHITE;
	Board[6][5] = BLACK;
	Board[6][6] = WHITE;
	Board[6][7] = BLACK;
	
	//Row 1
	Board[7][0] = BLACK;
	Board[7][1] = WHITE;
	Board[7][2] = BLACK;
	Board[7][3] = WHITE;
	Board[7][4] = WKING;
	Board[7][5] = WHITE;
	Board[7][6] = BLACK;
	Board[7][7] = WHITE;
	

}

void ResetBoard()
{
	//Row 8
	Board[0][0] = BROOK;
	Board[1][0] = BKNIGHT;
	Board[2][0] = BBISHOP;
	Board[3][0] = BQUEEN;
	Board[4][0] = BKING;
	Board[5][0] = BBISHOP;
	Board[6][0] = BKNIGHT;
	Board[7][0] = BROOK;
	
	//Row 7
	Board[0][1] = BPAWN;
	Board[1][1] = BPAWN;
	Board[2][1] = BPAWN;
	Board[3][1] = BPAWN;
	Board[4][1] = BPAWN;
	Board[5][1] = BPAWN;
	Board[6][1] = BPAWN;
	Board[7][1] = BPAWN;
	
	//Row 6
	Board[0][2] = WHITE;
	Board[1][2] = BLACK;
	Board[2][2] = WHITE;
	Board[3][2] = BLACK;
	Board[4][2] = WHITE;
	Board[5][2] = BLACK;
	Board[6][2] = WHITE;
	Board[7][2] = BLACK;
	
	//Row 5
	Board[0][3] = BLACK;
	Board[1][3] = WHITE;
	Board[2][3] = BLACK;
	Board[3][3] = WHITE;
	Board[4][3] = BLACK;
	Board[5][3] = WHITE;
	Board[6][3] = BLACK;
	Board[7][3] = WHITE;
	
	//Row 4
	Board[0][4] = WHITE;
	Board[1][4] = BLACK;
	Board[2][4] = WHITE;
	Board[3][4] = BLACK;
	Board[4][4] = WHITE;
	Board[5][4] = BLACK;
	Board[6][4] = WHITE;
	Board[7][4] = BLACK;
	
	//Row 3
	Board[0][5] = BLACK;
	Board[1][5] = WHITE;
	Board[2][5] = BLACK;
	Board[3][5] = WHITE;
	Board[4][5] = BLACK;
	Board[5][5] = WHITE;
	Board[6][5] = BLACK;
	Board[7][5] = WHITE;
	
	//Row 2
	Board[0][6] = WPAWN;
	Board[1][6] = WPAWN;
	Board[2][6] = WPAWN;
	Board[3][6] = WPAWN;
	Board[4][6] = WPAWN;
	Board[5][6] = WPAWN;
	Board[6][6] = WPAWN;
	Board[7][6] = WPAWN;
	
	//Row 1
	Board[0][7] = WROOK;
	Board[1][7] = WKNIGHT;
	Board[2][7] = WBISHOP;
	Board[3][7] = WQUEEN;
	Board[4][7] = WKING;
	Board[5][7] = WBISHOP;
	Board[6][7] = WKNIGHT;
	Board[7][7] = WROOK;
    
}

void ReverseGridColor(int g_x, int g_y)
{
	if(Board[g_x][g_y] == BLACK)
	{
		Board[g_x][g_y] = WHITE;
	}
	else
	{
		Board[g_x][g_y] = BLACK;
	}
}


void SelectPiece(int g_x, int g_y){
	if(Board[g_x][g_y] == WKING){
		Board[g_x][g_y] = WKING_S;
		return;
	}
	if(Board[g_x][g_y] == WQUEEN){
		Board[g_x][g_y] = WQUEEN_S;
		return;
	}
	if(Board[g_x][g_y] == WKNIGHT){
		Board[g_x][g_y] = WKNIGHT_S;
		return;
	}
	if(Board[g_x][g_y] == WBISHOP){
		Board[g_x][g_y] = WBISHOP_S;
		return;
	}
	if(Board[g_x][g_y] == WROOK){
		Board[g_x][g_y] = WROOK_S;
		return;
	}
	if(Board[g_x][g_y] == WPAWN){
		Board[g_x][g_y] = WPAWN_S;
		return;
	}
	
	if(Board[g_x][g_y] == BKING){
		Board[g_x][g_y] = BKING_S;
		return;
	}
	if(Board[g_x][g_y] == BQUEEN){
		Board[g_x][g_y] = BQUEEN_S;
		return;
	}
	if(Board[g_x][g_y] == BKNIGHT){
		Board[g_x][g_y] = BKNIGHT_S;
		return;
	}
	if(Board[g_x][g_y] == BBISHOP){
		Board[g_x][g_y] = BBISHOP_S;
		return;
	}
	if(Board[g_x][g_y] == BROOK){
		Board[g_x][g_y] = BROOK_S;
		return;
	}
	if(Board[g_x][g_y] == BPAWN){
		Board[g_x][g_y] = BPAWN_S;
		return;
	}
}

void DeselectPiece(int g_x,int g_y){
	if(Board[g_x][g_y] == WKING_S){
		Board[g_x][g_y] = WKING;
		return;
	}
	if(Board[g_x][g_y] == WQUEEN_S){
		Board[g_x][g_y] = WQUEEN;
		return;
	}
	if(Board[g_x][g_y] == WKNIGHT_S){
		Board[g_x][g_y] = WKNIGHT;
		return;
	}
	if(Board[g_x][g_y] == WBISHOP_S){
		Board[g_x][g_y] = WBISHOP;
		return;
	}
	if(Board[g_x][g_y] == WROOK_S){
		Board[g_x][g_y] = WROOK;
		return;
	}
	if(Board[g_x][g_y] == WPAWN_S){
		Board[g_x][g_y] = WPAWN;
		return;
	}
	
	if(Board[g_x][g_y] == BKING_S){
		Board[g_x][g_y] = BKING;
		return;
	}
	if(Board[g_x][g_y] == BQUEEN_S){
		Board[g_x][g_y] = BQUEEN;
		return;
	}
	if(Board[g_x][g_y] == BKNIGHT_S){
		Board[g_x][g_y] = BKNIGHT;
		return;
	}
	if(Board[g_x][g_y] == BBISHOP_S){
		Board[g_x][g_y] = BBISHOP;
		return;
	}
	if(Board[g_x][g_y] == BROOK_S){
		Board[g_x][g_y] = BROOK;
		return;
	}
	if(Board[g_x][g_y] == BPAWN_S){
		Board[g_x][g_y] = BPAWN;
		return;
	}
}

void MovePiece(int g_x, int g_y)
{
	static int initialization = 0;
	
	if(initialization==0){
		CreateChessBoard(CB);
		initialization = 1;
	}
	

	static int square1 = 0;
	static int square2 = 0;
	static int move1x;
	static int move1y;
	static int move2x;
	static int move2y;
	static int turn = WHITE;
	
	int test;
	
	if(square1 == 0){
		//Check that an empty square isn't selected to move
		if((Board[g_x][g_y]==BLACK)||(Board[g_x][g_y]==WHITE)){
			printf("Invalid selection\n");
			return;
		}
		//Check that a player moves are alternating
		if(ChessTurn(g_x,g_y,turn)==0){
			return;
		}
	}
	
	//Store first click
	if (square1 == 0){
		//Check if the click is within bounds
		if(((g_x<=7)&&(g_x>=0))&&((g_y<=7)&&(g_y>=0))){
			move1x = g_x;
			move1y = g_y;
			square1 = 1;
			printf("First square selected at %d %d\n", g_x,g_y);
			SelectPiece(move1x,move1y);
			return;
		}
		
	} 
	
	//Check if they are the same square
	if((square2 == 0) && (square1 == 1)){
		if((move1x == g_x) && (move1y == g_y)){

			square1 = 0;
			square2 = 0;
			printf("First square deselected\n");
			DeselectPiece(move1x,move1y);
			return;
		}
		else{
			//Check if the click is within bounds
			if(((g_x<=7)&&(g_x>=0))&&((g_y<=7)&&(g_y>=0))){
				move2x = g_x;
				move2y = g_y;
				if(SameTeam(move1x,move1y,move2x,move2y)==1){
					//Check that own player's piece is not taken
					printf("Please don't take your own piece UwU\n");
					square1 = 0;
					DeselectPiece(move1x,move1y);
					return;
				}
				printf("Second square selected at %d %d\n", move2x,move2y);
				DeselectPiece(move1x,move1y);
				square2 = 1;
			}
		}
	} 

	if((square1 == 1) && (square2 == 1)){
		
		printBoard(CB);
		
		if(turn == WHITE){
			test = whiteMove(CB,move1y,move1x,move2y,move2x);
			if(test != 0){
				Board[move2x][move2y] = Board[move1x][move1y];
				if(((move1x+move1y)%2)==0){
					Board[move1x][move1y] = WHITE;
				}
				else{
					Board[move1x][move1y] = BLACK;
				}
				turn = BLACK;
				square1 = 0;
				square2 = 0;
				printBoard(CB);
				//Send move signals here*******************************
				printf("<CHESS>WHITE<x1>%d<y1>%d<x2>%d<y2>%d\n", move1x, move1y, move2x, move2y);
				printf("Black Player turn\n");
			}
		}
		else if(turn == BLACK){
			test = blackMove(CB,move1y,move1x,move2y,move2x);
			if(test != 0){
				Board[move2x][move2y] = Board[move1x][move1y];
				if(((move1x+move1y)%2)==0){
					Board[move1x][move1y] = WHITE;
				}
				else{
					Board[move1x][move1y] = BLACK;
				}
				turn = WHITE;
				square1 = 0;
				square2 = 0;
				printBoard(CB);
				//Send move signals here*******************************
				printf("<CHESS>BLACK<x1>%d<y1>%d<x2>%d<y2>%d\n", move1x, move1y, move2x, move2y);
				printf("White Player turn\n");
			}
		}
		square1 = 0;
		square2 = 0;
	}
	
}


void DrawBoard()
{
	int i, j;

    for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			switch(Board[i][j])
			{
				case BLACK:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/Bsquare.png") ;
					break;
				case WHITE:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/Wsquare.png") ;
					break;
					
					
				case WKING_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/WKing_S.png") ;
					break;
				case WQUEEN_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/WQueen_S.png") ;
					break;
				case WBISHOP_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/WBishop_S.png") ;
					break;
				case WKNIGHT_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/WKnight_S.png") ;
					break;
				case WROOK_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/WRook_S.png") ;
					break;
				case WPAWN_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/WPawn_S.png") ;
					break;
				case BKING_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/BKing_S.png") ;
					break;
				case BQUEEN_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/BQueen_S.png") ;
					break;
				case BBISHOP_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/BBishop_S.png") ;
					break;
				case BKNIGHT_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/BKnight_S.png") ;
					break;
				case BROOK_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/BRook_S.png") ;
					break;
				case BPAWN_S:
					chess_icon = gtk_image_new_from_file("./src/chess_icon/BPawn_S.png") ;
					break;
					
					
				case WKING:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WKing_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WKing_B.png") ;
					}
					break;
				case WQUEEN:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WQueen_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WQueen_B.png") ;
					}
					break;
				case WBISHOP:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WBishop_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WBishop_B.png") ;
					}
					break;
				case WKNIGHT:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WKnight_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WKnight_B.png") ;
					}
					break;
				case WROOK:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WRook_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WRook_B.png") ;
					}
					break;
				case WPAWN:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WPawn_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/WPawn_B.png") ;
					}
					break;
					
					
				case BKING:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BKing_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BKing_B.png") ;
					}
					break;
				case BQUEEN:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BQueen_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BQueen_B.png") ;
					}
					break;
				case BBISHOP:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BBishop_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BBishop_B.png") ;
					}
					break;
				case BKNIGHT:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BKnight_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BKnight_B.png") ;
					}
					break;
				case BROOK:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BRook_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BRook_B.png") ;
					}
					break;
				case BPAWN:
					if((i+j)%2==0){
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BPawn_W.png") ;
					}
					else{
						chess_icon = gtk_image_new_from_file("./src/chess_icon/BPawn_B.png") ;
					}
					break;	
				
				default:
					break;
				
			}
			gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}
}

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
	*g_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	*g_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
}

int ChessTurn(int g_x, int g_y, int turn){
	int color;
	if((Board[g_x][g_y]==WKING)||(Board[g_x][g_y]==WQUEEN)||(Board[g_x][g_y]==WKNIGHT)||(Board[g_x][g_y]==WBISHOP)||(Board[g_x][g_y]==WROOK)||(Board[g_x][g_y]==WPAWN)){
		color = WHITE;
	}
	if((Board[g_x][g_y]==BKING)||(Board[g_x][g_y]==BQUEEN)||(Board[g_x][g_y]==BKNIGHT)||(Board[g_x][g_y]==BBISHOP)||(Board[g_x][g_y]==BROOK)||(Board[g_x][g_y]==BPAWN)){
		color = BLACK;
	}
	if(turn != color){
		if(turn == BLACK){
			printf("Please select a black piece to move\n");
		}
		if(turn == WHITE){
			printf("Please select a white piece to move\n");
		}
	}
	return(turn==color);
}

int SameTeam(int g_x, int g_y, int gg_x, int gg_y){
	int piece1 = -1;
	int piece2 = -1;
	
	if((Board[gg_x][gg_y]==WHITE)||(Board[gg_x][gg_y]==BLACK)){
		return 0;
	}
	
	if((Board[g_x][g_y]==WKING)||(Board[g_x][g_y]==WQUEEN)||(Board[g_x][g_y]==WKNIGHT)||(Board[g_x][g_y]==WBISHOP)||(Board[g_x][g_y]==WROOK)||(Board[g_x][g_y]==WPAWN)||(Board[g_x][g_y]==WKING_S)||(Board[g_x][g_y]==WQUEEN_S)||(Board[g_x][g_y]==WKNIGHT_S)||(Board[g_x][g_y]==WBISHOP_S)||(Board[g_x][g_y]==WROOK_S)||(Board[g_x][g_y]==WPAWN_S)){
		piece1 = WHITE;
		printf("piece 1 is white\n");
	}
	if((Board[g_x][g_y]==BKING)||(Board[g_x][g_y]==BQUEEN)||(Board[g_x][g_y]==BKNIGHT)||(Board[g_x][g_y]==BBISHOP)||(Board[g_x][g_y]==BROOK)||(Board[g_x][g_y]==BPAWN)||(Board[g_x][g_y]==BKING_S)||(Board[g_x][g_y]==BQUEEN_S)||(Board[g_x][g_y]==BKNIGHT_S)||(Board[g_x][g_y]==BBISHOP_S)||(Board[g_x][g_y]==BROOK_S)||(Board[g_x][g_y]==BPAWN_S)){
		piece1 = BLACK;
		printf("piece 1 is black\n");
	}
	if((Board[gg_x][gg_y]==WKING)||(Board[gg_x][gg_y]==WQUEEN)||(Board[gg_x][gg_y]==WKNIGHT)||(Board[gg_x][gg_y]==WBISHOP)||(Board[gg_x][gg_y]==WROOK)||(Board[gg_x][gg_y]==WPAWN)){
		piece2 = WHITE;
		printf("piece 2 is white\n");
	}
	if((Board[gg_x][gg_y]==BKING)||(Board[gg_x][gg_y]==BQUEEN)||(Board[gg_x][gg_y]==BKNIGHT)||(Board[gg_x][g_y]==BBISHOP)||(Board[gg_x][gg_y]==BROOK)||(Board[gg_x][gg_y]==BPAWN)){
		piece2 = BLACK;
		printf("piece 2 is black\n");
	}
	
	return(piece1==piece2);
}

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below.
 */
static void
print_hello (GtkWidget *widget,
     gpointer   data)
{
  g_print ("Hello World\n");
}

static gboolean
on_delete_event (GtkWidget *widget,
         GdkEvent  *event,
         gpointer   data)
{
  /* If you return FALSE in the "delete_event" signal handler,
   * GTK will emit the "destroy" signal. Returning TRUE means
   * you don't want the window to be destroyed.
   *
   * This is useful for popping up 'are you sure you want to quit?'
   * type dialogs.
   */

  g_print ("delete event occurred\n"); 
  gtk_main_quit();
  return TRUE;
}

gint area_click (GtkWidget *widget,
                 GdkEvent  *event, 
                 gpointer  data)
{
  int x1, y1 ; 
  char words[MAX_MSGLEN] ; 

  int coord_x,  coord_y,  grid_x,  grid_y;

  struct BOARD *chess_board ; 
  struct SQUARE *chess_piece ;
  struct SQUARE *piece_dest ;   

  GdkModifierType state ; 

  gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ; 
  
  CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);

  //printf("coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x, coord_y, grid_x, grid_y);

  if(((grid_x<=7)&&(grid_x>=0))&&((grid_y<=7)&&(grid_y>=0))){
	  MovePiece(grid_x, grid_y);
  }
  else{
	  printf("Error Out of bounds grid_x = %d, grid_y = %d \n", grid_x, grid_y);
  }

    gtk_container_remove(GTK_CONTAINER(window), fixed) ; 
    table = gtk_table_new (2, 2, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard(); 

    /*set fixed*/

    fixed = gtk_fixed_new() ;
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(window), fixed) ;
    gtk_widget_show_all(window) ; 

  return TRUE ; 
}



int
main (int   argc,
      char *argv[])
{
  char str[MAX_MSGLEN]; 
 
  gtk_init(&argc, &argv) ;
  ResetBoard();
 
  /*create a new window */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ; 
  gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ; 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ; 
  gtk_window_set_title(GTK_WINDOW(window), "Let's play Chess!") ; 
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ; 


  /*register event handlers*/
  g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ; 
  gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ; 
  g_signal_connect(window, "button_press_event", G_CALLBACK(area_click), NULL) ; 

  /*create a table and draw the board*/
  table = gtk_table_new (2, 2, TRUE) ; 
  gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ; 
  DrawBoard();

  fixed = gtk_fixed_new() ; 
  gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ; 
  gtk_container_add(GTK_CONTAINER(window), fixed) ; 


  /*show the window*/
  gtk_widget_show_all(window) ; 
  gtk_main() ; 

  return 0 ;
}
