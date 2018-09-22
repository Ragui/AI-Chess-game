#include "dataStruct.h"
#include "evaluation.h"
#include <stdio.h>
#include "legalMoves.h"

int pawnValueBoard[8][8] = { 
			   {875,  875,  875,  875,  875,  875,  875,  875},
		       	   { 35, 50, 50, 50, 50, 50, 50, 35},
			    { 10, 10, 20, 30, 30, 20, 10, 10},
			    { 5,  5, 10, 27, 27, 10,  5,  5},
			    { 0,  0,  0, 25, 25,  0,  0,  0},
     			    { 5, -5,-10,  0,  0,-10, -5,  5},
			    { 5, 10, 10,-25,-25, 10, 10,  5},
			    { 0,  0,  0,  0,  0,  0,  0,  0}};

int knightValueBoard[8][8] = {
{-50,-40,-30,-30,-30,-30,-40,-50},
 {   -40,-20,  0,  0,  0,  0,-20,-40},
  {  -30,  0, 10, 15, 15, 10,  0,-30},
   { -30,  5, 15, 20, 20, 15,  5,-30},
   { -30,  0, 15, 20, 20, 15,  0,-30},
   { -30,  5, 10, 15, 15, 10,  5,-30},
   { -40,-20,  0,  5,  5,  0,-20,-40},
   { -50,-40,-20,-30,-30,-20,-40,-50}
};

int bishopValueBoard[8][8] = {
   { -20,-10,-10,-10,-10,-10,-10,-20},
   { -10,  0,  0,  0,  0,  0,  0,-10},
   { -10,  0,  5, 10, 10,  5,  0,-10},
   { -10,  5,  5, 10, 10,  5,  5,-10},
   { -10,  0, 10, 10, 10, 10,  0,-10},
   { -10, 10, 10, 10, 10, 10, 10,-10},
   { -10,  5,  0,  0,  0,  0,  5,-10},
   { -20,-10,-40,-10,-10,-40,-10,-20}
};

int kingValueBoard[8][8] = {
 { -30, -40, -40, -50, -50, -40, -40, -30},
 { -30, -40, -40, -50, -50, -40, -40, -30},
 { -30, -40, -40, -50, -50, -40, -40, -30},
 { -30, -40, -40, -50, -50, -40, -40, -30},
 { -20, -30, -30, -40, -40, -30, -30, -20},
 { -10, -20, -20, -20, -20, -20, -20, -10},
 {  20,  20,   0,   0,   0,   0,  20,  20},
  { 5,  30,  20,   0,   0,  10,  30,  5}
};

int evaluatePiece(square s){
	int score = 0;
	if(s.p.r == white){
		switch(s.p.name){
			case king:
				score += s.p.name + kingValueBoard[s.x-1][s.y-1]; 
				break;
			case pawn:
				score += s.p.name + pawnValueBoard[s.x-1][s.y-1];
				break;
			case bishop:
				score += s.p.name + bishopValueBoard[s.x-1][s.y-1];
                                break;
			case queen:
				score += s.p.name;
                                break;
			case knight:
				score += s.p.name + knightValueBoard[s.x-1][s.y-1];
                                break;
			case rook:
				score += s.p.name;
                                break;
			default:
				break;
		}
	}
	else{
		switch(s.p.name){
			case king:
                                score += s.p.name + kingValueBoard[9-s.x-1][9-s.y-1];
                                break;
                        case pawn:
                                score += s.p.name + pawnValueBoard[9-s.x-1][9-s.y-1];
                                break;
                        case bishop:
                                score += s.p.name + bishopValueBoard[9-s.x-1][9-s.y-1];
                                break;
                        case queen:
                                score += s.p.name;
                                break;
                        case knight:
                                score += s.p.name + knightValueBoard[9-s.x-1][9-s.y-1];
                                break;
                        case rook:
                                score += s.p.name;
                                break;
                        default:
                                break;
                }
	}
	return score;
}

int evaluateBoard(color r){
	int score = 0;
	int x;
	for( int i = 1; i< 9; i++){
                for(int j = 1; j < 9; j++){
			x = ((board[i][j].p.name == empty) ? 0 : evaluatePiece(board[i][j]));
			if(board[i][j].p.r == r){
				score += x;
			}
			else{
				score -= x;
			}
                }
        }
	return (r == white) ? score : -1*score;
}

