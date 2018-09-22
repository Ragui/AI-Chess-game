/************************************************************************
 * dataStruct.h:                                                         *
 *                                                                       *
 * Update Log:                                                           *
 *     Ragui Halim 01/19/2018                                            *
**	Jacobis Soriano 	01/29/18 

*                                                                       *
 * *********************************************************************** */


#ifndef DS_H
#define DS_H
#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>

typedef enum b{
	true = 1,
	false = 0
}bool;

typedef enum player_type{
	human = 0, computer = 1
}type;


typedef enum colors{
	black = 0, white = 1
}color;

typedef struct Player{
	type t;
	color r;		
}player;


typedef enum piece_name{
	king = 32767, queen = 975, bishop = 325, rook = 500, knight = 320, pawn = 100, empty = 0
}pieceName;


typedef struct Piece{
        color r;
        pieceName name;
	bool pr; //promoted?
//	bool alive;
//	int x;
//	int y;
}piece;

typedef struct Square{
	int x;
	int y; 
	piece p;
}square;

typedef struct Move{
	int x1, x2; 
	int y1, y2;
	piece p;
}move;

typedef struct destination{
	int x;
	int y;
}des;

typedef struct mEntry movesEntry;
typedef struct mList movesList;

struct mEntry
{
    movesList   *List;
    movesEntry  *Next;
    movesEntry  *Prev;
    move        *m;
};

struct mList
{
    int        Length;
    movesEntry *First;
    movesEntry *Last;
};

bool *Wki_Moved; 
bool *Bki_Moved;
bool *Wro1_Moved;
bool *Wro2_Moved;
bool *Bro1_Moved;
bool *Bro2_Moved;

movesEntry *NewMovesEntry(move *m);
void DeleteMoveEntry(movesEntry *e);
movesList *CreateMovesList(void);
void DeleteMovesList(movesList *aList);
void RemoveLastMoveFromList(movesList *list);
void AddMoveToMoveList(movesList *list, move *aMove);
void DeleteMove(move *aMove);
void LoadGameFile(const char *lFile, movesList *list);
void SaveMovesListToFile(const char *lFile, movesList *list);
void PrintMovesList(movesList *list);
void PrintMove(move *s); 
square board[9][9]; //to make it easy to count from 1-8
move *undo(movesList *list);

des kingMoves   [8]; //8 possible moves + 2 for castling
des knightMoves [8]; 
des rookMoves   [14];
des pawnMoves   [4]; // including en passant
des bishopMoves [13];
des queenMoves  [27];
bool *turn;

move allMoves[10][140];
// function to change from string to move
move *stringToMove(char *s);

// function to initialize the board before the game starts 
void initializeBoard();

// if the move is valid, we should update the board
// 1- The piece over the destination square will be updated 
// 2- The initial square will be updated to empty
void updateBoard(move *m);

pieceName Promotion();
piece Wki, Wqu, Wkn1, Wkn2, Wbi1, Wbi2, Wro1, Wro2, Wpa1, Wpa2, Wpa3, Wpa4, Wpa5, Wpa6, Wpa7, Wpa8;
piece Bki, Bqu, Bkn1, Bkn2, Bbi1, Bbi2, Bro1, Bro2, Bpa1, Bpa2, Bpa3, Bpa4, Bpa5, Bpa6, Bpa7, Bpa8;

move *LastMove;
move *AImove;

player *player1;

player *player2;
#endif
