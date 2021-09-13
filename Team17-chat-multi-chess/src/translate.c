#include "translate.h"

/*How to translate ID*/
/*First is piece ID*/
/*1 = pawn 2 = rook 3 = knight 4 = bishop 5 = queen 6 = king*/
/*positive = white and negative = black*/
/*Second digit is the piece that tracks if the piece has moved yet 0 = false, 1 = true*/
/*Third digit is a flag for if the piece can move*/
/*Fourth digit is a flag for if the piece can kill*/

//White Pawn that has moved and can be EP
//1110

int pull(int x, int p){
    int t = x;
    for(int i = 1; i < p; i++){
        t=t/10;
    }
    return(t%10);
    
}

int abs(int x){
	if(x<0){
		return(x*-1);
	}else{
		return x;
	}
}

int clip(int l, int x, int r){
	if((l<=x)&&(x<=r)){
	    return 1;
	}else{
	    return 0;
	}
}