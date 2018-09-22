/************************************************************************
 * legalMoves.h:                                                         *
 *                                                                       *
 * Update Log:                                                           *
 *     Ragui Halim 01/19/2018                                            *
 *     Jacobis S.  01/27/2018     LegalMoveForUser spelled correctly	 *
 *     Jacobis S. 01/28/2018						 *
 * ********************************************************************* */


#ifndef L_H
#define L_H

#include "dataStruct.h"
// legalMoves.h
// fucntion takes in a typedef move argument and returns a boolean of true
// if the move is legal or false if the move is not vaild 
//bool legalMoveForUser(move *m);

// returns if a move is legal or not given a move
bool legalForUser(move *m);

int generateMoves(color r, square ws, square bs,movesList *l,int depth);
int alphaBeta(color r, int alpha, int beta, int depth, int i,movesList *l, square ws, square bs);
/*return if the king or the rook have been moved atleast once (used for castling)*/
//void firstMoveMade(move *m){


// calculates the legal possible moves of the king and put them in the array "arr"
// n is the number of possible legal moves (equals Zero if there is no legal moves) 
// s is the position of the piece (using the piece field you can know the type and the color of the piece)
// the moves should include castling
void kingLegalMoves(des *arr, int *n, square s);

void queenLegalMoves(des *arr, int *n, square s);

void rookLegalMoves(des *arr, int *n, square s);

void knightLegalMoves(des *arr, int *n, square s);

void bishopLegalMoves(des *arr, int *n, square s);

// the moves should include "promotion" and "en passant"
void pawnLegalMoves(des *arr, int *n, square s);
 
bool EnPassant(piece p, piece p2);
/*
 * Given a square, we should calculate if black/white king is in check or not
 * we need to check if your move:
 * 1- will put the other team in check or 
 * 2- will put your team in check, which means it is illegal move
 * Also when your king is in check, your move should disable the check (not doing that is illegal) 
 * So we need to check if your king still in check position after the move
 *
 */
bool kingInCheck(square s);

bool Checkmate(square s);

bool draw(square s, movesList *list);

bool insuffmaterial();

bool threeRepetition(movesList *s);


bool stalemate(square s);

#endif
