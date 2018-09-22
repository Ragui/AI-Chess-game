/************************************************************************
 * legalMoves.c:                                                         *
 *                                                                       *
 * Update Log:                                                           *
 *     Ragui Halim 		01/19/2018				 *
 *     Ragui Halim 		01/23/2018                               *
 *     Martino Caldarella 	01/24/2018                               *
 *     Jacobis. Sorano         	01/27/2018                               *
 * *********************************************************************** */


#include "legalMoves.h"
#include "dataStruct.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "evaluation.h"
/*
 * Ignore the first two functions for now
 *
 * You should all check for the possible legal move
 * possible moves include:
 * 1- moving to an empty square
 * 2- capture the opponent's piece
 *
 * Do not forget to check if:
 * 1- one of your pieces is blocking the move (which makes the move illegal)
 * 2- if the king is in check only the pieces that can "save" it can move. All the other can't
 */

// returns if a move is legal or not given a string of the move
//bool legalMoveForUser(move *m){
bool legalForUser(move *m){
	int n = 0;
	int a, b;
	switch(board[m->x1][m->y1].p.name){
		case empty:
			return false;
		case king:
			kingLegalMoves(kingMoves, &n, board[m->x1][m->y1]);
			for(int i = 0; i < n; i++){
				a = kingMoves[i].x;
				b = kingMoves[i].y;
				if(m->x2 == a && m->y2 == b){
					return true;
				}
			}
			n = 0;
			return false;
		case queen:
			queenLegalMoves(queenMoves, &n, board[m->x1][m->y1]);
                        for(int i = 0; i < n; i++){
                                a = queenMoves[i].x;
                                b = queenMoves[i].y;
                                if(m->x2 == a && m->y2 == b){
                                        return true;
                                }
                        }
			n = 0;
                        return false;
		case knight:
			knightLegalMoves(knightMoves, &n, board[m->x1][m->y1]);
                        for(int i = 0; i < n; i++){
                                a = knightMoves[i].x;
                                b = knightMoves[i].y;
                                if(m->x2 == a && m->y2 == b){
                                        return true;
                                }
                        }
                        n = 0;
                        return false;
		case bishop:
                        bishopLegalMoves(bishopMoves, &n, board[m->x1][m->y1]);
                        for(int i = 0; i < n; i++){
                                a = bishopMoves[i].x;
                                b = bishopMoves[i].y;
                                if(m->x2 == a && m->y2 == b){
                                        return true;
                                }
                        }
                        n = 0;
                        return false;
		case pawn:
                        pawnLegalMoves(pawnMoves, &n, board[m->x1][m->y1]);
			for(int i = 0; i < n; i++){
                                a = pawnMoves[i].x;
                                b = pawnMoves[i].y;
                                if(m->x2 == a && m->y2 == b){
                                        return true;
                                }
                        }
                        n = 0;
                        return false;

		case rook:
                        rookLegalMoves(rookMoves, &n, board[m->x1][m->y1]);
                        for(int i = 0; i < n; i++){
                                a = rookMoves[i].x;
                                b = rookMoves[i].y;
                                if(m->x2 == a && m->y2 == b){
                                        return true;
                                }
                        }
                        n = 0;
                        return false;
		default:
			return false;
	}
}

bool checkMove(move *m, square s,movesList *l){
	bool b = true;	
	updateBoard(m);
	AddMoveToMoveList(l, m);
	int x = s.x, y = s.y;
	if(board[x][y].p.name == empty){
		x = m->x2;
		y = m->y2;
	}
	if(kingInCheck(board[x][y])){
		b = false;	
	}
	undo(l);
	return b;	
}

//returns the best move for the computer
int generateMoves(color r, square ws, square bs,movesList *l,int depth){
	int n = 0;
	int sum = 0;
	move m;
	for(int i = 1; i < 9;i++){
		for(int j = 1; j < 9;j++){
			if(board[i][j].p.name != empty && board[i][j].p.r == r){
				n = 0;
				switch(board[i][j].p.name){
					case pawn:
						pawnLegalMoves(pawnMoves, &n, board[i][j]);
						break;
					case rook:
						rookLegalMoves(rookMoves, &n, board[i][j]);
						break;
					case bishop:
						bishopLegalMoves(bishopMoves, &n, board[i][j]);
						break;
					case queen:
						queenLegalMoves(queenMoves, &n, board[i][j]);
						break;
					case knight:
						knightLegalMoves(knightMoves, &n, board[i][j]);
						break;
					case king:
						kingLegalMoves(kingMoves, &n, board[i][j]);
						break;
					default:
						break;
				}
				m.x1 = i;
				m.y1 = j;
				for(int c = 0; c < n; c++){
					switch(board[i][j].p.name){
                              			case pawn:
                                 	                m.x2 = pawnMoves[c].x;
							m.y2 = pawnMoves[c].y;
							if(checkMove(&m, board[i][j].p.r == white ? ws : bs,l)){
								allMoves[depth][sum+c] = m;
								break;
							}
							sum--;
							break;
                               			case rook:
                                 	                m.x2 = rookMoves[c].x;
                                                        m.y2 = rookMoves[c].y;
                                                        if(checkMove(&m, board[i][j].p.r == white ? ws : bs,l)){
                                                                allMoves[depth][sum+c] = m;
								break;
                                                        }
							sum--;
							break;
                                 		case bishop:
                                	                m.x2 = bishopMoves[c].x;
                                                        m.y2 = bishopMoves[c].y;
                                                        if(checkMove(&m, board[i][j].p.r == white ? ws : bs,l)){
                                                                allMoves[depth][sum+c] = m;
								break;
                                                        }
							sum--;
							break;
                                
						case queen:
                                	                m.x2 = queenMoves[c].x;
                                                        m.y2 = queenMoves[c].y;
                                                        if(checkMove(&m, board[i][j].p.r == white ? ws : bs,l)){
                                                                allMoves[depth][sum+c] = m;
								break;
                                                        }
							sum--;
							break;
                               	         	case knight:
                                         	        m.x2 = knightMoves[c].x;
                                                        m.y2 = knightMoves[c].y;
                                                        if(checkMove(&m, board[i][j].p.r == white ? ws : bs,l)){
                                                                allMoves[depth][sum+c] = m;
								break;
                                                        }
							sum--;
							break;
                                        	case king:
                                                	m.x2 = kingMoves[c].x;
                                                        m.y2 = kingMoves[c].y;
                                                        if(checkMove(&m, board[i][j].p.r == white ? ws : bs,l)){
                                                                allMoves[depth][sum+c] = m;
								break;
                                                        }
							sum--;
							break;
                                        	default:
                                                	break;
                                	}
				}
				sum += n;
			}
		}
	}
	return sum;	
}
void cleanArray(int i){
	move x = {0,0,0,0};
	for(int j = 0; j < 140; j++){
		allMoves[i][j] = x;
	}
}

int alphaBeta(color r, int alpha, int beta, int depth, int i,movesList *l, square ws, square bs){

/*	srand(time(0));
	cleanArray(0);
	int sum = generateMoves(r,ws,bs,l,i);
	int x = rand()%sum;
	move *m = malloc(sizeof(move));
	m->x1 = allMoves[0][x].x1;
        m->y1 = allMoves[0][x].y1;
        m->x2 = allMoves[0][x].x2;
        m->y2 = allMoves[0][x].y2;
        AImove = m;		
	return 0;
*/	int bestValue = 0;
	int temp;
	
	if(depth == i){
		return evaluateBoard(r);
	}
	cleanArray(i);
	int sum = generateMoves(r,ws,bs,l,i);
	if(i == 0){
		move *m = malloc(sizeof(move));
		AImove = &allMoves[0][0];	
                m->x1 = AImove->x1;
                        m->y1 = AImove->y1;
                        m->x2 = AImove->x2;
                        m->y2 = AImove->y2;
                        AImove = m;
	}
	if(sum == 0 ){
		return evaluateBoard(r);
	}
			
	if(r == white){
		bestValue = -99999;
		for(int j = 0; j < sum; j++){
			if(allMoves[i][j].x1 > 0 && allMoves[i][j].y1 >  0 && allMoves[i][j].x2 > 0 && allMoves[i][j].y2 > 0 && 
				allMoves[i][j].x1 < 9 && allMoves[i][j].y1 < 9  && allMoves[i][j].x2 < 9 && allMoves[i][j].y2 < 9 
				&& legalForUser(&allMoves[i][j]) ){
			updateBoard(&allMoves[i][j]);
			LastMove = &allMoves[i][j];
			temp = alphaBeta(black, alpha, beta, depth, i+1,l,ws,bs);
			if(bestValue <  temp){
				bestValue = temp;
				if(i == 0){
					AImove = &allMoves[i][j];
				}
			}
			AddMoveToMoveList(l, &allMoves[i][j]);
			undo(l);
			if(l->Last != NULL){
				LastMove = l->Last->m;
			}
			alpha = (bestValue > alpha) ? bestValue : alpha;
			if(beta <= alpha){
				break;
			}
			}	
		}
		if(i == 0){
			move *m = malloc(sizeof(move));
			m->x1 = AImove->x1;
			m->y1 = AImove->y1;
			m->x2 = AImove->x2;
			m->y2 = AImove->y2;
			AImove = m;
		}

	}
	else{
		bestValue =  99999;
		for(int j = 0; j < sum; j++){
			if(allMoves[i][j].x1 > 0 && allMoves[i][j].y1 >  0 && allMoves[i][j].x2 > 0 && allMoves[i][j].y2 > 0 &&
                                allMoves[i][j].x1 < 9 && allMoves[i][j].y1 < 9  && allMoves[i][j].x2 < 9 && allMoves[i][j].y2 < 9
                                && legalForUser(&allMoves[i][j]) ){
			updateBoard(&allMoves[i][j]);
                        LastMove = &allMoves[i][j];
			temp = alphaBeta(white, alpha, beta, depth, i+1,l,ws,bs);
                        if(bestValue > temp){
				bestValue = temp;
				if(i == 0){
                                        AImove = &allMoves[i][j];
                                }
			}
			AddMoveToMoveList(l, &allMoves[i][j]);
			undo(l);
			if(l->Last != NULL){
                                LastMove = l->Last->m;
                        }
			beta = (bestValue < beta) ? bestValue : beta;
                        if(beta <= alpha){
                                break;
                        }
			}
		}
		if(i == 0){
                        move *m = malloc(sizeof(move));
                        m->x1 = AImove->x1;
                        m->y1 = AImove->y1;
                        m->x2 = AImove->x2;
                        m->y2 = AImove->y2;
                        AImove = m;
                }
	}
	return bestValue;
}


// calculates the legal possible moves of the king and put them in the array "arr"
//n is the number of possible legal moves (equals Zero if there is no legal moves)
// the moves should include castling


void queenLegalMoves(des *arr, int *n, square s){ 

    int m = 0;              /*legal moves counter*/

    int i = s.x + 1;        /*starting position: one square diagonal above/right*/
    int j = s.y + 1;

    if(i <= 8 && j <= 8 ){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){     /*also checks if position is empty*/
            while(board[i][j].p.name == empty){          /*moves diagonal forward/right if square is empty*/
                arr[m].x = i;
                arr[m].y = j;                         /*stores position as legal move in array*/
                m++;
                i+=1;
                j+=1;
                if((i > 8 || j > 8 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){    /*stops if reaches the edge or piece of the same color*/
                    break;
                }
                else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                    arr[m].x = i;
                    arr[m].y = j;
                    m++;
                    break;
                }/*fi*/
            }/*elihw*/
        }/*fi*/
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    i = s.x + 1;        /*starting position: one square diagonal above/left*/
    j = s.y - 1;

    if(i <= 8 && j >= 1 ){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){     /*also checks if position is empty*/

            while(board[i][j].p.name == empty){       /*move diagonal forward/left*/
                arr[m].x = i;
                arr[m].y = j;                         /*stores legal move in array*/
                m++;
                i+=1;
                j-=1;
                if((i > 8 || j < 1 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                    break;
                }
                else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                    arr[m].x = i;
                    arr[m].y = j;
                    m++;
                    break;
                }/*fi*/
            }/*elihw*/
        }/*fi*/
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }


    i = s.x - 1;            /*starting position: one square diagonal below/right*/
    j = s.y + 1;

    if(i >=1 && j <= 8 ){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){     /*also checks if position is empty*/

            while(board[i][j].p.name == empty){       /*move diagonal below/right*/
                arr[m].x = i;
                arr[m].y = j;                         /*stores legal move in array*/
                m++;
                i-=1;
                j+=1;
                if((i < 1 || j > 8 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                    break;
                }
                else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                    arr[m].x = i;
                    arr[m].y = j;
                    m++;
                    break;
                }/*fi*/
            }/*elihw*/
        }/*fi*/
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }
    i = s.x - 1;        /*starting position: one square diagonal below/left*/
    j = s.y - 1;

    if(i >= 1  && j >= 1 ){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){     /*also checks if position is empty*/
            while(board[i][j].p.name == empty){       /*move diagonal below/left*/
                arr[m].x = i;
                arr[m].y = j;                         /*stores legal move in array*/
                m++;
                i-=1;
                j-=1;
                if((i < 1 || j < 1 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                    break;
                }
                else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                    arr[m].x = i;
                    arr[m].y = j;
                    m++;
                    break;
                }/*fi*/
            }/*elihw*/
        }/*fi*/
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    i = s.x;
    j = s.y + 1;        /*starting position: one square right*/

    if((j <= 8 )){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){                                                    /*also checks if position is empty*/
        while(board[i][j].p.name == empty){       /*move straight right*/
            arr[m].x = i;
            arr[m].y = j;                         /*stores legal move in array*/
            m++;
            j+=1;
            if((j > 8 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                break;
            }
            else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                arr[m].x = i;
                arr[m].y = j;
                m++;
                break;
            }/*fi*/
        }/*elihw*/
	}
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/

    }
     

    i = s.x;
    j = s.y -  1;           /*starting position: one square left*/

    if((j >= 1 ) ){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){                                                    /*also checks if position is empty*/
        while(board[i][j].p.name == empty){       /*move straight left*/
            arr[m].x = i;
            arr[m].y = j;                         /*stores legal move in array*/
            m++;
            j-=1;
            if((j < 1 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                break;
            }
            else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                arr[m].x = i;
                arr[m].y = j;
                m++;
                break;
            }/*fi*/
        }/*elihw*/
	}
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    i = s.x + 1;            /*starting position: one square above*/
    j = s.y;

    if((i <= 8 )){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){                                                    /*also checks if position is empty*/
        while(board[i][j].p.name == empty){       /*move straight forward*/
            arr[m].x = i;
            arr[m].y = j;                         /*stores legal move in array*/
            m++;
            i+=1;
            if((i > 8 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                break;
            }
            else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                arr[m].x = i;
                arr[m].y = j;
                m++;
                break;
            }
        }/*elihw*/
	}
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){    /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
    }
    }


    i = s.x - 1;        /*starting position: one square below*/
    j = s.y;

    if((i >= 1 )){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){                                                    /*also checks if position is empty*/
        while(board[i][j].p.name == empty){       /*move straight backward*/
            arr[m].x = i;
            arr[m].y = j;                         /*stores legal move in array*/
            m++;
            i-=1;
            if((i < 1 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                break;
            }
            else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                arr[m].x = i;
                arr[m].y = j;
                m++;
                break;
            }/*fi*/
        }/*elihw*/
	}
	 else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    *n = m;   /*stores number of legal moves in '*n'*/

}


void rookLegalMoves(des *arr, int *n, square s){

    int m = 0;      /*legal positions counter*/
    int i = s.x;
    int j = s.y + 1;        /*starting position: one square right*/

    if((j <= 8 )){         /*checks if position is within the board*/
	if(board[i][j].p.name == empty){                                                            /*also checks if position is empty*/
        while(board[i][j].p.name == empty){       /*move straight right*/
            arr[m].x = i;
            arr[m].y = j;                         /*stores legal move in array*/
            m++;
            j+=1;
            if((j > 8 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                break;
            }
            else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                arr[m].x = i;
                arr[m].y = j;
                m++;
                break;
            }/*fi*/
        }/*elihw*/
	}
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }


    i = s.x;
    j = s.y -  1;           /*starting position: one square left*/

    if((j >= 1 ) ){         /*checks if position is within the board*/
     	if(board[i][j].p.name == empty){                                                       /*also checks if position is empty*/
        while(board[i][j].p.name == empty){       /*move straight left*/
            arr[m].x = i;
            arr[m].y = j;                         /*stores legal move in array*/
            m++;
            j-=1;
            if((j < 1 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                break;
            }
            else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                arr[m].x = i;
                arr[m].y = j;
                m++;
                break;
            }/*fi*/
        }/*elihw*/
	}
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    i = s.x + 1;            /*starting position: one square above*/
    j = s.y;

    if((i <= 8 ) ){         /*checks if position is within the board*/
     	if(board[i][j].p.name == empty){                                                       /*also checks if position is empty*/
        while(board[i][j].p.name == empty){       /*move straight forward*/
            arr[m].x = i;
            arr[m].y = j;                         /*stores legal move in array*/
            m++;
            i+=1;
            if((i > 8 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                break;
            }
            else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                arr[m].x = i;
                arr[m].y = j;
                m++;
                break;
            }
        }/*elihw*/
	}
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    i = s.x - 1;        /*starting position: one square below*/
    j = s.y;

    if((i >= 1 ) ){         /*checks if position is within the board*/
     	if(board[i][j].p.name == empty){                                                       /*also checks if position is empty*/
        while(board[i][j].p.name == empty){       /*move straight backward*/
            arr[m].x = i;
            arr[m].y = j;                         /*stores legal move in array*/
            m++;
            i-=1;
            if((i < 1 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                break;
            }
            else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                arr[m].x = i;
                arr[m].y = j;
                m++;
                break;
            }/*fi*/
        }/*elihw*/
	}
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }
     *n = m;   /*stores number of legal moves in '*n'*/


}

void knightLegalMoves(des *arr, int *n, square s){
    int m = 0;

    int i = s.x + 2;        //starting position: 2 above/1 right
    int j = s.y + 1;

    if((i <= 8) && (j <= 8) && (board[i][j].p.name == empty || board[i][j].p.r != s.p.r)){         /*checks if position is within the board*/   
             arr[m].x = i;
             arr[m].y = j;                         /*stores position as legal move in array*/
             m++;

        }

    i = s.x + 1;            //starting position: 1 above/2 right
    j = s.y + 2;



  if((i <= 8) && (j <= 8) && (board[i][j].p.name == empty || board[i][j].p.r != s.p.r)){  /*checks if position is within the board*/
             arr[m].x = i;
             arr[m].y = j;                         /*stores position as legal move in array*/
             m++;

  }

    i = s.x + 2;            //starting position: 2 above/1 left
    j = s.y - 1;

 if((i <= 8) && (j > 0) && (board[i][j].p.name == empty || board[i][j].p.r != s.p.r)){  /*checks if position is within the board*/
             arr[m].x = i;
             arr[m].y = j;                         /*stores position as legal move in array*/
             m++;

  }

    i = s.x + 1;        //starting position: 1 above/2 left
    j = s.y - 2;

 if((i <= 8) && (j > 0) && (board[i][j].p.name == empty || board[i][j].p.r != s.p.r)){  /*checks if position is within the board*/
             arr[m].x = i;
             arr[m].y = j;                         /*stores position as legal move in array*/
             m++;

  }
    
    i = s.x - 2;        //starting position: 2 below/1 left
    j = s.y - 1;

 if((i > 0) && (j > 0) && (board[i][j].p.name == empty || board[i][j].p.r != s.p.r)){  /*checks if position is within the board*/
             arr[m].x = i;
             arr[m].y = j;                         /*stores position as legal move in array*/
             m++;

  }

    i = s.x - 1;    //starting position: 1 below/2 left
    j = s.y - 2;

 if((i > 0) && (j > 0) && (board[i][j].p.name == empty || board[i][j].p.r != s.p.r)){  /*checks if position is within the board*/
             arr[m].x = i;
             arr[m].y = j;                         /*stores position as legal move in array*/
             m++;

  }

    i = s.x - 2;         //starting position: 2 below/1 right
    j = s.y + 1;

 if((i > 0) && (j <= 8) && (board[i][j].p.name == empty || board[i][j].p.r != s.p.r)){  /*checks if position is within the board*/
             arr[m].x = i;
             arr[m].y = j;                         /*stores position as legal move in array*/
             m++;

  }

    i = s.x - 1;            //starting position: 1 below/2 right
    j = s.y + 2;

 if((i > 0) && (j <= 8) && (board[i][j].p.name == empty || board[i][j].p.r != s.p.r)){  /*checks if position is within the board*/
             arr[m].x = i;
             arr[m].y = j;                         /*stores position as legal move in array*/
             m++;

  }

    *n = m;

}


void bishopLegalMoves(des *arr, int *n, square s){

    int m = 0;              /*legal moves counter*/

    int i = s.x + 1;        /*starting position: one square diagonal above/right*/
    int j = s.y + 1;

    if(i <= 8 && j <= 8 ){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){     /*also checks if position is empty*/
            while(board[i][j].p.name == empty){          /*moves diagonal forward/right if square is empty*/
                arr[m].x = i;
                arr[m].y = j;                         /*stores position as legal move in array*/
                m++;
                i+=1;
                j+=1;
                if((i > 8 || j > 8 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){    /*stops if reaches the edge or piece of the same color*/
                    break;
                }
                else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                    arr[m].x = i;
                    arr[m].y = j;
                    m++;
                    break;
                }/*fi*/
            }/*elihw*/
        }/*fi*/
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    i = s.x + 1;        /*starting position: one square diagonal above/left*/
    j = s.y - 1;

    if(i <= 8 && j >= 1 ){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){     /*also checks if position is empty*/

            while(board[i][j].p.name == empty){       /*move diagonal forward/left*/
                arr[m].x = i;
                arr[m].y = j;                         /*stores legal move in array*/
                m++;
                i+=1;
                j-=1;
                if((i > 8 || j < 1 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                    break;
                }
                else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                    arr[m].x = i;
                    arr[m].y = j;
                    m++;
                    break;
                }/*fi*/
            }/*elihw*/
        }/*fi*/
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    i = s.x - 1;            /*starting position: one square diagonal below/right*/
    j = s.y + 1;

    if(i >= 1 && j <= 8 ){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){     /*also checks if position is empty*/
            while(board[i][j].p.name == empty){       /*move diagonal below/right*/
                arr[m].x = i;
                arr[m].y = j;                         /*stores legal move in array*/
                m++;
                i-=1;
                j+=1;
                if((i < 1 || j > 8 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                    break;
                }
                else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                    arr[m].x = i;
                    arr[m].y = j;
                    m++;
                    break;
                }/*fi*/
            }/*elihw*/
        }/*fi*/
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    i = s.x - 1;        /*starting position: one square diagonal below/left*/
    j = s.y - 1;

    if(i >= 1 && j >= 1 ){         /*checks if position is within the board*/
        if(board[i][j].p.name == empty){     /*also checks if position is empty*/
            while(board[i][j].p.name == empty){       /*move diagonal below/left*/
                arr[m].x = i;
                arr[m].y = j;                         /*stores legal move in array*/
                m++;
                i-=1;
                j-=1;
                if((i < 1 || j < 1 ) || (board[i][j].p.name != empty && board[i][j].p.r == s.p.r)){         /*stops if reaches the edge or piece of the same color*/
                    break;
                }
                else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if reaches a piece of different color stores its position as legal move*/
                    arr[m].x = i;
                    arr[m].y = j;
                    m++;
                    break;
                }/*fi*/
            }/*elihw*/
        }/*fi*/
	else if (board[i][j].p.name != empty && board[i][j].p.r != s.p.r){     /*if starting position is occupied by a piece of a different color*/
            arr[m].x = i;                                                   /*stores position as legal move in array*/
            arr[m].y = j;
            m++;
     }/*fi*/
    }

    *n = m;   /*stores number of legal moves in '*n'*/

   
}
 


/* calculates the legal possible moves of the king and put them in the array "arr"
n is the number of possible legal moves (equals Zero if there is no legal moves)
 the moves should include castling*/
void kingLegalMoves(des *arr, int *n, square s){

    int m = 0;

        if((s.x <= 8 && s.y <= 8) && (s.x>0 && s.y>0)){ //need to also check if king moves into check for each move
                if(s.y-1>0){
                        if(s.p.r != board[s.x][s.y-1].p.r  || (board[s.x][s.y-1].p.name == empty)){ //left
                                arr[m].x = s.x;
                                arr[m].y = s.y-1;
                                m+=1;
                        }
                }
                if(s.x+1<=8 && s.y-1>0){
                        if(s.p.r != board[s.x+1][s.y-1].p.r  || (board[s.x+1][s.y-1].p.name == empty)){ //top left
                                arr[m].x = s.x+1;
                                arr[m].y = s.y-1;
                                m+=1;
                        }
                }
                if(s.x+1<=8){
                        if(s.p.r != board[s.x+1][s.y].p.r  || (board[s.x+1][s.y].p.name == empty)){ //top mid
                                arr[m].x = s.x+1;
                                arr[m].y = s.y;
                                m+=1;
                        }
                }
                if(s.x+1<=8 && s.y+1<=8){
                        if(s.p.r != board[s.x+1][s.y+1].p.r  || (board[s.x+1][s.y+1].p.name == empty)){ //top right
                                arr[m].x = s.x+1;
                                arr[m].y = s.y+1;
                                m+=1;
                        }
                }
                if(s.y+1<=8){
                        if(s.p.r != board[s.x][s.y+1].p.r  || (board[s.x][s.y+1].p.name == empty)){ //right
                                arr[m].x = s.x;
                                arr[m].y = s.y+1;
                                m+=1;
                        }
                }
                if(s.x-1>0 && s.y+1<=8){
                        if(s.p.r != board[s.x-1][s.y+1].p.r  || (board[s.x-1][s.y+1].p.name == empty)){ //bottom right
                                arr[m].x = s.x-1;
                                arr[m].y = s.y+1;
                                m+=1;
                        }
                }
                if(s.x-1>0){
                        if(s.p.r != board[s.x-1][s.y].p.r  || (board[s.x-1][s.y].p.name == empty)){ //bottom mid
                                arr[m].x = s.x-1;
                                arr[m].y = s.y;
                                m+=1;
                        }
                }
                if(s.x-1>0 && s.y-1>0){
                        if(s.p.r != board[s.x-1][s.y-1].p.r  || (board[s.x-1][s.y-1].p.name == empty)){ //bottom left
                                arr[m].x = s.x-1;
                                arr[m].y = s.y-1;
                                m+=1;
                        }
                }

        }
		
	
	if(*Wki_Moved == false && *Wro2_Moved == false){
       	    	 if(s.x == 1 && s.y == 5 && board[1][6].p.name == empty && board[1][7].p.name == empty &&
                    board[1][8].p.name == rook && board[1][8].p.r == s.p.r && !kingInCheck(board[1][6]) 
			&& !kingInCheck(board[1][7]) && !kingInCheck(board[1][5])){
               		 arr[m].x = 1;
               		 arr[m].y = 7;
               		 m++;
       		 	 }	
	}
	if(*Wki_Moved == false && *Wro1_Moved == false){
    	     if(s.x == 1 && s.y == 5 && board[1][4].p.name == empty && board[1][3].p.name == empty &&
     	        board[1][2].p.name == empty && board[1][1].p.name == rook && board[1][1].p.r == s.p.r
			&& !kingInCheck(board[1][4]) && !kingInCheck(board[1][3]) && !kingInCheck(board[1][5])){
        	       arr[m].x = 1;
       		       arr[m].y = 3;
        	       m++;
	         }
	}
	if(*Bki_Moved == false && *Bro2_Moved == false){
      		   if(s.x == 8 && s.y == 5 && board[8][6].p.name == empty && board[8][7].p.name == empty &&
       		      board[8][8].p.name == rook && board[8][8].p.r == s.p.r && !kingInCheck(board[8][6])
                        && !kingInCheck(board[8][7]) && !kingInCheck(board[8][5])){
              		 arr[m].x = 8;
              		 arr[m].y = 7;
               		 m++;
       		 }
	}
	if(*Bki_Moved == false && *Bro1_Moved == false){
        	 if(s.x == 8 && s.y == 5 && board[8][4].p.name == empty && board[8][3].p.name == empty &&
                    board[8][2].p.name == empty && board[8][1].p.name == rook && board[8][1].p.r == s.p.r &&
			!kingInCheck(board[8][4]) && !kingInCheck(board[8][3]) && !kingInCheck(board[8][5])){
               		 arr[m].x = 8;
               		 arr[m].y = 3;
               		 m++;
         	}
        }

        *n = m;

}
// the moves should include "promotion" and "en passant"
void pawnLegalMoves(des *arr, int *n, square s){
	int m = 0; //counts number of moves possible
	bool en_passant = false; //checks to see if en_passant if possible 
	if((s.x<=8 && s.y <=8) && (s.x>0 && s.y>0)){ 
		if(s.p.r == white){	//for wPA, case for initial move
			if(s.x == 2){  
				if(board[s.x+2][s.y].p.name == empty && board[s.x+1][s.y].p.name == empty){ //move forward 2
					arr[m].x = s.x+2;
					arr[m].y = s.y;
					m+=1;
				}	
			}
			//case after initial move for wPA
				if(s.x+1<=8 && board[s.x+1][s.y].p.name == empty){	//move forward 1
					arr[m].x = s.x+1;
					arr[m].y = s.y;
                       			m+=1;

				}
				if((s.x+1<=8 && s.y-1>0)&& (board[s.x+1][s.y-1].p.name != empty) && (s.p.r != board[s.x+1][s.y-1].p.r) ){	//attack left for wPA
					arr[m].x = s.x+1;
					arr[m].y = s.y-1;		
					m+=1;
				}
				if((s.x+1<=8 && s.y+1<=8) && (board[s.x+1][s.y+1].p.name != empty) && (s.p.r != board[s.x+1][s.y+1].p.r) ){ //attack right
					arr[m].x = s.x+1;
					arr[m].y = s.y+1;
					m+=1;
				}
				if(s.x == 5){	//case for en passant, need some way to associate captured piece with destination because the destination does not contain piece
					if(s.y-1>0 && board[s.x][s.y-1].p.name == pawn){
						en_passant = EnPassant(s.p, board[s.x][s.y-1].p);
						if(en_passant == true){
							arr[m].x = s.x+1;
							arr[m].y = s.y-1;
							m+=1;
						}
					}
					if(s.y+1 <= 8 && board[s.x][s.y+1].p.name == pawn){
						en_passant = EnPassant(s.p, board[s.x][s.y+1].p);
						if(en_passant == true){
							arr[m].x = s.x+1;
							arr[m].y = s.y+1;
							m+=1;
						}
					}
				}
			
		}
		else if(s.p.r == black){	//for bPA
			if(s.x == 7){ //black pawn start
				if(board[s.x-2][s.y].p.name == empty && board[s.x-1][s.y].p.name == empty){ //move forward 2
					arr[m].x = s.x-2;
					arr[m].y = s.y;
					m+=1;
				}
			}
				if((s.x-1>0) && (board[s.x-1][s.y].p.name == empty) ){ //move forward one
					arr[m].x = s.x-1;
					arr[m].y = s.y;
					m+=1;
				}
				if((s.x-1>0 && s.y-1>0)&& (board[s.x-1][s.y-1].p.name != empty) && (s.p.r != board[s.x-1][s.y-1].p.r) ){	//attack  left for bPA
					arr[m].x = s.x-1;
					arr[m].y = s.y-1;
					m+=1;

				}
				if((s.x-1>0 && s.y+1<=8)&& (board[s.x-1][s.y+1].p.name != empty) && (s.p.r !=board[s.x-1][s.y+1].p.r) ){	//attack  right
					arr[m].x = s.x-1;
					arr[m].y = s.y+1;
					m+=1;
				}
				if(s.x == 4){
					if(s.y-1>0 && board[s.x][s.y-1].p.name == pawn ){
						en_passant = EnPassant(s.p,board[s.x][s.y-1].p);
						if(en_passant == true){
							arr[m].x = s.x-1;
							arr[m].y = s.y-1;
							m+=1;
						}
					}
					if((s.y+1<=8) && board[s.x][s.y+1].p.name == pawn){
						en_passant = EnPassant(s.p,board[s.x][s.y+1].p);
						if(en_passant == true){
							arr[m].x = s.x-1;
							arr[m].y = s.y+1;
							m+=1;
						}
					}
				}
		}
	}
	*n = m;	
}

bool EnPassant(piece p, piece p2){ //p2 contains target pawn
	if(p.r == p2.r){ //if target is same color, en passant fails
		return false;
	}
	if(p.r == white && LastMove->x1 == 7 && LastMove->x2 == 5){	//need to also check if target pawn moved forward 2 on the previous move
		return true;
	}
	if(p.r == black && LastMove->x1 == 2 && LastMove->x2 ==4){
		return true;
	}

	return false;
}

/*
 *
 * given a square, we should calculate if black/white king is in check or not
 * we need to check if your move:
 * 1- will put the other team in check or
 * 2- will put your team in check, which means it is illegal move
 * Also when your king is in check, your move should disable the check (not doing that is illegal)
 * So we need to check if your king still in check position after the move
 *
 */
bool kingInCheck(square s){
	
	int a = s.x, b = s.y;
	// diagonal 1-a
	while(true){
		a += 1;
		b += 1;
		if(a > 8 || b > 8){
			break;
		}
		else if(board[a][b].p.name != empty){
			if(board[a][b].p.r != s.p.r){
				if(board[a][b].p.name == bishop || board[a][b].p.name == queen){
					return true;
				}
				else if(s.p.r == white && a-s.x == 1 && board[a][b].p.name == pawn){
					return true;
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}
	}
	
	a = s.x, b = s.y;
	//diagonal 2 - a
	while(true){
		a += 1;
		b -= 1;
		if(a > 8 || b  < 1){
                        break;
                }
                else if(board[a][b].p.name != empty){
                        if(board[a][b].p.r != s.p.r){
                                if(board[a][b].p.name == bishop || board[a][b].p.name == queen){
					return true;
                                }
                                else if(s.p.r == white && a-s.x == 1 && board[a][b].p.name == pawn){
					return true;
                                }
                                else{
                                        break;
                                }
                        }
                        else{
                                break;
                        }
                }

	}
	a = s.x, b = s.y;
	//diagonal 1 - b
	while(true){
                a -= 1;
                b -= 1;
                if(a < 1 || b  < 1){
                        break;
                }
                else if(board[a][b].p.name != empty){
                        if(board[a][b].p.r != s.p.r){
                                if(board[a][b].p.name == bishop || board[a][b].p.name == queen){
					return true;
                                }
                                else if(s.p.r == black && s.x - a == 1 && board[a][b].p.name == pawn){
					return true;
                                }
                                else{
                                        break;
                                }
                        }
                        else{
                                break;
                        }
                }

        }
	a = s.x, b = s.y;
	//diagonal 2 - b
	while(true){
                a -= 1;
                b += 1;
                if(a < 1 || b  > 8){
                        break;
                }
                else if(board[a][b].p.name != empty){
                        if(board[a][b].p.r != s.p.r){
                                if(board[a][b].p.name == bishop || board[a][b].p.name == queen){
                                        return true;
                                }
                                else if(s.p.r == black && s.x - a == 1 && board[a][b].p.name == pawn){
                                        return true;
                                }
                                else{
                                        break;
                                }
                        }
                        else{
                                break;
                        }
                }

        }

	a = s.x, b = s.y;
	// row
	while(true){
                b += 1;
                if(b  > 8){
                        break;
                }
                else if(board[a][b].p.name != empty){
                        if(board[a][b].p.r != s.p.r){
                                if(board[a][b].p.name == rook || board[a][b].p.name == queen){
                                        return true;
                                }
                                else{
                                        break;
                                }
                        }
                        else{
                                break;
                        }
                }

        }


	a = s.x, b = s.y;
	// row 3 - b
	while(true){
                b -= 1;
                if(b < 1){
                        break;
                }
                else if(board[a][b].p.name != empty){
                        if(board[a][b].p.r != s.p.r){
                                if(board[a][b].p.name == rook || board[a][b].p.name == queen){
                                        return true;
                                }
                                else{
                                        break;
                                }
                        }
                        else{
                                break;
                        }
                }

        }

	a = s.x, b = s.y;
	// col 4 - a
	while(true){
                a += 1;
                if(a > 8){
                        break;
                }
                else if(board[a][b].p.name != empty){
                        if(board[a][b].p.r != s.p.r){
                                if(board[a][b].p.name == rook || board[a][b].p.name == queen){
                                        return true;
                                }
                                else{
                                        break;
                                }
                        }
                        else{
                                break;
                        }
                }

        }	

	a = s.x, b = s.y;
	//col 4 - b
	while(true){
                a -= 1;
                if(a < 1){
                        break;
                }
                else if(board[a][b].p.name != empty){
                        if(board[a][b].p.r != s.p.r){
                                if(board[a][b].p.name == rook || board[a][b].p.name == queen){
                                        return true;
                                }
                                else{
                                        break;
                                }
                        }
                        else{
                                break;
                        }
                }

        }
	
	a = s.x, b = s.y;
	// knigh
	if(a+2 <= 8 && b+1 <= 8 && board[a+2][b+1].p.name == knight && board[a+2][b+1].p.r != s.p.r){
			return true;
	}
	else if(a+2 <= 8 && b-1 > 0 && board[a+2][b-1].p.name == knight && board[a+2][b-1].p.r != s.p.r){
                        return true;
        }
	else if(a+1 <= 8 && b-2 > 0 && board[a+1][b-2].p.name == knight && board[a+1][b-2].p.r != s.p.r){
                        return true;
        }
	else if(a+1 <= 8 && b + 2 <= 8 && board[a+1][b+2].p.name == knight && board[a+1][b+2].p.r != s.p.r){
                        return true;
        }	 	
	else if(a-2 > 0 && b-1 > 0 && board[a-2][b-1].p.name == knight && board[a-2][b-1].p.r != s.p.r){
                        return true;
        }
	else if(a-2 > 0 && b+1 <= 8 && board[a-2][b+1].p.name == knight && board[a-2][b+1].p.r != s.p.r){
                        return true;
        }
	else if(a-1 > 0 && b-2 > 0 && board[a-1][b-2].p.name == knight && board[a-1][b-2].p.r != s.p.r){
                        return true;
        }
	else if(a-1 > 0 && b+2 <= 8 && board[a-1][b+2].p.name == knight && board[a-1][b+2].p.r != s.p.r){
                        return true;
        }

	//king
	a = s.x, b = s.y;
	if(a+1 <= 8 && b+1 <= 8 && board[a+1][b+1].p.name == king && board[a+1][b+1].p.r != s.p.r){
		return true;
	}
	else if(a+1 <= 8 && board[a+1][b].p.name == king && board[a+1][b].p.r != s.p.r){
                        return true;
        }
        else if(a+1 <= 8 && b-1 > 0 && board[a+1][b-1].p.name == king && board[a+1][b-1].p.r != s.p.r){
                        return true;
        }
        else if(b + 1 <= 8 && board[a][b+1].p.name == king && board[a][b+1].p.r != s.p.r){
                        return true;
        }
        else if(b-1 > 0 && board[a][b-1].p.name == king && board[a][b-1].p.r != s.p.r){
                        return true;
        }
        else if(a-1 > 0 && b+1 <= 8 && board[a-1][b+1].p.name == king && board[a-1][b+1].p.r != s.p.r){
                        return true;
        }
        else if(a-1 > 0 && b-1 > 0 && board[a-1][b-1].p.name == king && board[a-1][b-1].p.r != s.p.r){
                        return true;
        }
        else if(a-1 > 0 && board[a-1][b].p.name == king && board[a-1][b].p.r != s.p.r){
                        return true;
        }
	
	return false;
}

// you can suppose that the king is in check. That function will not be called unless the king is in check.
bool Checkmate(square s){
/*
 * 
 * My idea is to get all the possible positions for all pieces and apply them.
 * for example: if one possible pos to the king is A1 A2 
 * 		what we will do is to play this move, and check if the king is still in check
 * 		If yes, we will try the other possible moves till we find a position where the king is not in check.
 * 		If we found that position, we simply return false.
 * 		If we did not, we return false.
 * We should not forget to return the board to its initial position after each trial.
 *
 */ 	

	int n = 0;
	int x,y;
	move *m = malloc(sizeof(move));
	//king
	kingLegalMoves(kingMoves, &n, s);
	for(int i = 0; i < n; i++){
		x = kingMoves[i].x;
		y = kingMoves[i].y;
		piece temp = board[x][y].p;
		m->x1 = s.x;
		m->y1 = s.y;
		m->x2 = x;
		m->y2 = y;
		updateBoard(m);
		if(!kingInCheck(board[x][y])){
			//undo the move
			m->x1 = x;
                	m->y1 = y;
                	m->x2 = s.x;
                	m->y2 = s.y;
                	updateBoard(m);
                	board[x][y].p = temp;
			free(m);
			return false;
		}
		// undo the move
		m->x1 = x;
		m->y1 = y;
		m->x2 = s.x;
		m->y2 = s.y;
		updateBoard(m);
		board[x][y].p = temp;
	}
	// other pieces 
	for(int i = 1; i <= 8; i++){
		for(int j = 1; j <= 8; j++){
			if(board[i][j].p.name != empty && board[i][j].p.r == s.p.r){
				// make a switch or if / else if to check what the piece is and call the corresponding function
				switch(board[i][j].p.name){
					case rook:
						rookLegalMoves(rookMoves, &n,board[i][j]);
						for(int c = 0; c < n; c++){
							x = rookMoves[c].x;
							y = rookMoves[c].y;
							piece temp = board[x][y].p;
							m->x1 = i;
							m->y1 = j;
                        	                        m->x2 = x;
                        	                        m->y2 = y;
							updateBoard(m);
                                	        	if(!kingInCheck(s)){
                                	        		m->x1 = x;
                                	        		m->y1 = y;
                                	        		m->x2 = i;
                                	        		m->y2 = j;
                                	        		updateBoard(m);
                                	        		board[x][y].p = temp;
								free(m);
                                	        	        return false;
                                                	}
                        	        	        m->x1 = x;
                                		        m->y1 = y;
                                        		m->x2 = i;
                             	        		m->y2 = j;
                                        		updateBoard(m);
                                        		board[x][y].p = temp;
						}
						break;

                                        case queen:
						queenLegalMoves(queenMoves, &n,board[i][j]);
                                                for(int c = 0; c < n; c++){
                                                        x = queenMoves[c].x;
                                                        y = queenMoves[c].y;
                                                        piece temp = board[x][y].p;
                                                        m->x1 = i;
                                                        m->y1 = j;
                                                        m->x2 = x;
                                                        m->y2 = y;
                                                        updateBoard(m);
                                                        if(!kingInCheck(s)){
                                                                m->x1 = x;
                                                                m->y1 = y;
                                                                m->x2 = i;
                                                                m->y2 = j;
                                                                updateBoard(m);
                                                                board[x][y].p = temp;
								free(m);
                                                                return false;
                                                        }
                                                        m->x1 = x;
                                                        m->y1 = y;
                                                        m->x2 = i;
                                                        m->y2 = j;
                                                        updateBoard(m);
                                                        board[x][y].p = temp;
                                                }
                                                break;

                                        case knight:
						knightLegalMoves(knightMoves, &n,board[i][j]);
                                                for(int c = 0; c < n; c++){
                                                        x = knightMoves[c].x;
                                                        y = knightMoves[c].y;
                                                        piece temp = board[x][y].p;
                                                        m->x1 = i;
                                                        m->y1 = j;
                                                        m->x2 = x;
                                                        m->y2 = y;
                                                        updateBoard(m);
                                                        if(!kingInCheck(s)){
                                                                m->x1 = x;
                                                                m->y1 = y;
                                                                m->x2 = i;
                                                                m->y2 = j;
                                                                updateBoard(m);
                                                                board[x][y].p = temp;
								free(m);
                                                                return false;
                                                        }
                                                        m->x1 = x;
                                                        m->y1 = y;
                                                        m->x2 = i;
                                                        m->y2 = j;
                                                        updateBoard(m);
                                                        board[x][y].p = temp;
                                                }
                                                break;

                                        case pawn:
						pawnLegalMoves(pawnMoves, &n,board[i][j]);
                                                for(int c = 0; c < n; c++){
                                                        x = pawnMoves[c].x;
                                                        y = pawnMoves[c].y;
                                                        piece temp = board[x][y].p;
                                                        m->x1 = i;
                                                        m->y1 = j;
                                                        m->x2 = x;
                                                        m->y2 = y;
                                                        updateBoard(m);
                                                        if(!kingInCheck(s)){
                                                                m->x1 = x;
                                                                m->y1 = y;
                                                                m->x2 = i;
                                                                m->y2 = j;
                                                                updateBoard(m);
                                                                board[x][y].p = temp;
								free(m);
                                                                return false;
                                                        }
                                                        m->x1 = x;
                                                        m->y1 = y;
                                                        m->x2 = i;
                                                        m->y2 = j;
                                                        updateBoard(m);
                                                        board[x][y].p = temp;
                                                }
                                                break;

                                        case bishop:
						bishopLegalMoves(bishopMoves, &n,board[i][j]);
                                                for(int c = 0; c < n; c++){
                                                        x = bishopMoves[c].x;
                                                        y = bishopMoves[c].y;
                                                        piece temp = board[x][y].p;
                                                        m->x1 = i;
                                                        m->y1 = j;
                                                        m->x2 = x;
                                                        m->y2 = y;
                                                        updateBoard(m);
                                                        if(!kingInCheck(s)){
                                                                m->x1 = x;
                                                                m->y1 = y;
                                                                m->x2 = i;
                                                                m->y2 = j;
                                                                updateBoard(m);
                                                                board[x][y].p = temp;
								free(m);
                                                                return false;
                                                        }
                                                        m->x1 = x;
                                                        m->y1 = y;
                                                        m->x2 = i;
                                                        m->y2 = j;
                                                        updateBoard(m);
                                                        board[x][y].p = temp;
                                                }
                                                break;	
							
					default:
						break;
				}
			}
		}
	}
	free(m);	
	return true;
}

bool draw(square s,movesList *list){
	if(stalemate(s)){
		printf("\x1b[36m Stalemate! ");
		return true;
	}
	else if(insuffmaterial()){
		printf("\x1b[36m Insufficient material to end the game. ");
		return true;
	}
	else if(threeRepetition(list)){
		printf("\x1b[36m Move repeated 3 times in a row.\n");
		printf("If you want to draw, type 'yes' else type 'no'. Any other word will be considered as no.\n");
		char x[3];
		scanf("%3s",x);
		if(strcmp(x,"yes")  == 0){
			return true;
		}
	}
	return false;
}

/*pieceName Promotion(type t){	
	char c;
	int flag = 0;
	pieceName pname;
	if(t == human){
		do{	//loops until user inputs a valid piece name
			printf("Which piece would you like to be promoted to? Input Q for Queen, N for Knight, B for Bishop, or R for Rook: ");
			c = getchar();
	
		 	switch(c){
				case 'Q':{
					pname = queen;
					flag = 1;
					break;
				}
				case 'N':{
					pname = knight;
					flag = 1;
					break;
				}
				case 'B':{
					pname = bishop;
					flag = 1;
					break;
				}
				case 'R':{
					pname = rook;
					flag = 1;
					break;
				}
				default:{
					printf("Invalid input. Inputted %c but expected an input of Q, N, B, or R. Please try again.\n", c);
					break;  
				}

			}
		} while(!flag);
	}
	else{
		pname = queen;
	}
	return (pname);
}*/


bool stalemate(square s){
	int n =0;
	int x,y;
	move *m = malloc(sizeof(move));	
	for(int i = 1; i <= 8; i++){
		for(int j = 1; j <= 8; j++){

			if(board[i][j].p.name != empty && board[i][j].p.r == s.p.r){
								
				// make a switch or if / else if to check what the piece is and call the corresponding function
				switch(board[i][j].p.name){			
					case rook:
						n = 0;
						rookLegalMoves(rookMoves, &n, board[i][j]);
						if(n > 0){
							free(m);
							return false;
						}
						break;

					case bishop:
						n = 0;
						bishopLegalMoves(rookMoves, &n, board[i][j]);
                                                if(n > 0){
							free(m);
                                                        return false;
                                                }
                                                break;
					case knight:
                                                n = 0;
                                                knightLegalMoves(rookMoves, &n, board[i][j]);
                                                if(n > 0){
							free(m);
                                                        return false;
                                                }
                                                break;
					case queen:
                                                n = 0;
                                                queenLegalMoves(rookMoves, &n, board[i][j]);
                                                if(n > 0){
							free(m);
                                                        return false;
                                                }
                                                break;
					case pawn:
                                                n = 0;
                                                pawnLegalMoves(rookMoves, &n, board[i][j]);
                                                if(n > 0){
							free(m);
                                                        return false;
                                                }
                                                break;
					default:
						break;		
				}	
			}
		}
	}
	kingLegalMoves(kingMoves, &n, s);
        for(int i = 0; i < n; i++){
                x = kingMoves[i].x;
                y = kingMoves[i].y;
                piece temp = board[x][y].p;
                m->x1 = s.x;
                m->y1 = s.y;
                m->x2 = x;
                m->y2 = y;
                updateBoard(m);
                if(!kingInCheck(board[x][y])){
                        m->x1 = x;
	                m->y1 = y;
        	        m->x2 = s.x;
               		m->y2 = s.y;
           		updateBoard(m);
          		board[x][y].p = temp;
			free(m);
			return false;
                }		
		m->x1 = x;
                m->y1 = y;
                m->x2 = s.x;
                m->y2 = s.y;
                updateBoard(m);
                board[x][y].p = temp;
        }
	free(m);				
	return true;											
}

bool threeRepetition(movesList *s){
	if (s->Length < 7){
		return false;	
	}

	int x,y,i,j;
	x = s->Last->m->x1;
	y = s->Last->m->y1;
	i = s->Last->m->x2;
	j = s->Last->m->y2;
	if(s->Last->Prev->Prev->m->x1 == i && s->Last->Prev->Prev->m->x2 == x && s->Last->Prev->Prev->m->y1 == j 
		&& s->Last->Prev->Prev->m->y2 == y
		&& s->Last->Prev->Prev->Prev->Prev->m->x1 ==  x && s->Last->Prev->Prev->Prev->Prev->m->x2 == i 
		&& s->Last->Prev->Prev->Prev->Prev->m->y1 == y && s->Last->Prev->Prev->Prev->Prev->m->y2 == j 
		&& s->Last->Prev->Prev->Prev->Prev->Prev->Prev->m->x1 ==  i && s->Last->Prev->Prev->Prev->Prev->Prev->Prev->m->x2 == x
                && s->Last->Prev->Prev->Prev->Prev->Prev->Prev->m->y1 == j && s->Last->Prev->Prev->Prev->Prev->Prev->Prev->m->y2 == y){
			return true;
	}
	return false;
}

bool insuffmaterial(){
       	int wbi = 0,bbi = 0,wkn = 0,bkn = 0;
	for(int i = 1; i <= 8; i++){
                for(int j = 1; j <= 8; j++){
                        if( board[i][j].p.name == queen || board[i][j].p.name == rook  || board[i][j].p.name == pawn){
					return false; 	
			}
			else if( board[i][j].p.name == bishop ){
					switch(board[i][j].p.r){
						case white:
							wbi++;
							break;
						case black: 
							bbi++;
							break;
                                        }
                        }
                        else if( board[i][j].p.name == knight){
                                        switch(board[i][j].p.r){
                                                case white:
                                                        wkn++;
                                                        break;
                                                case black:
                                                        bkn++;
                                                        break;
                                                }
                        }

		}
	}
	
	if(wbi > 1 || wkn > 1 || bbi > 1 || bkn > 1){
		return false;
	}
	else if( (wbi+wkn) == 2 || (bbi+bkn) == 2){
		return false;
	}
	else{
		return true;
	}			
			
}

