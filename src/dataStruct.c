/************************************************************************
 * dataStruct.c:                                                         *
 *                                                                       *
 * Update Log:                                                           *
 *     	Ragui Halim 	00/19/2018                                       *
 * 	Jacobis S. 	01/24/2018					 *
 * 	Jacobis S. 	01/27/2018    added PrintMovesList 
 *
 *	Jacobis S.	01/27/2018              *
 ************************************************************************ */


#include "dataStruct.h"
#include "legalMoves.h"
#include <stdio.h>
#include <math.h>


movesEntry *NewMoveEntry(move *aMove)
{
    assert(aMove);
    movesEntry *e;
    e = malloc(sizeof(movesEntry));
    if(!e)
    {
        perror("Out of memory! abortorting...!");
        exit(10);
    }

    e->List = NULL;
    e->Next = NULL;
    e->Prev = NULL;
    e->m = aMove;
    return e;
}


void DeleteMoveEntry(movesEntry *e)
{
    assert(e);
   // e->List = NULL;
   // e->Next = NULL;
   // e->Prev = NULL;
   // DeleteMove(e->m);
    free(e);
   // e = NULL;
}

movesList *CreateMovesList(void)
{
    movesList *list;
    list = malloc(sizeof(movesList));
    if(!list)
    {
        perror("Out of memory! Your computer mosdef will crash... just saying.!!!");
        exit(10);
    }

    list->Length = 0;
    list->First = NULL;
    list->Last = NULL;

    return list;
}

void DeleteMovesList(movesList *aList)
{
    while(aList->Length){
	RemoveLastMoveFromList(aList);
    }		
    free(aList);



}


void AddMoveToMoveList(movesList *list, move *aMove)
{
    movesEntry *e;
    assert(list);
    assert(aMove);
    e = NewMoveEntry(aMove);
    if(list->Length)
    {
        e->List = list;
        e->Next = NULL;
        e->Prev = list->Last;
        list->Last->Next = e;
        list->Last = e;
    }
    else
    {
        e->List = list;
        e->Next = NULL;
        e->Prev = NULL;
        list->First = e;
        list->Last  = e;
    }

    list->Length++;
}

void  RemoveLastMoveFromList(movesList *list)
{
    movesEntry *e;		
    assert(list);
   if(list->Length)
   {
	e = list->Last;
	list->Last = e->Prev;
	if(list->Last)
	{
	    list->Last->Next = NULL;
	}
	else
	{
	    assert(list->First == e);
	    list->First = NULL;
	}
	list->Length--;
	DeleteMoveEntry(e);
	e = NULL;
	if(e != NULL)
        {
	    
	    printf("Critical errror, could not delete move!");
	}
   }
   else
   {
	e = NULL;	
   }
}

void LoadGameFile(const char *lFile, movesList *gameList)
{
    FILE *tFile;
    tFile = fopen(lFile, "r");
    if(tFile == NULL)
    {
	printf("Could not open file, Aborting!!!");
	exit(1);
    }

    fclose(tFile);
}

void SaveMovesListToFile(const char *saveFileName, movesList *gameList)
{
    FILE *tFile;
    tFile = fopen(saveFileName, "w");
    movesEntry *e;

    if(tFile == NULL)
    {
	printf("Could not open file, Aborting!!!");
	exit(1);
    }
    assert(gameList);

    e = gameList->First;
    while(e)
    {
	fprintf(tFile,"%d %d %d %d \n", e->m->x1, e->m->y1, e->m->x2, e->m->y2);
	e = e->Next;
    }    

    fclose(tFile); 
}

void PrintMovesList(movesList *list)
{
    movesEntry *moves;
    assert(list);
    moves = list->First;
    while(moves)
    {
	PrintMove(moves->m);
	moves = moves->Next;
    }    
}

void PrintMove(move *m)
{
    assert(m);

    printf("Move:%c%d %c%d \n", m->y1+64, m->x1, m->y2+64, m->x2);

}

void DeleteMove(move *aMove)
{
    assert(aMove);
    free(aMove);

}

// function to change from string to move
// I suppose that the string is 5 chars and is valid
move *stringToMove(char *s){
	move *m = malloc(sizeof(move));
	m->y1 = s[0] - 64; // 64 is the ascii code for the char before 'A'
	m->y2 = s[3] - 64; 
	m->x1 = s[1] - 48; // 48 is the ascii code for '0'
	m->x2 = s[4] - 48;
	return m;
}

// function to initialize the board before the game starts
void initializeBoard(){
	for(int i = 1; i <= 8; i++){
		for(int j = 1; j <= 8; j++){
			board[i][j].x = i;
			board[i][j].y = j;
		}
	}

	// color	
	Wki.r = Wqu.r = Wkn1.r = Wkn2.r = Wbi1.r = Wbi2.r =  Wro1.r =  Wro2.r =  Wpa1.r = Wpa2.r =  Wpa3.r =  Wpa4.r =  Wpa5.r =  Wpa6.r =  Wpa7.r = Wpa8.r = white;
	 Bki.r = Bqu.r = Bkn1.r = Bkn2.r = Bbi1.r = Bbi2.r =  Bro1.r =  Bro2.r =  Bpa1.r = Bpa2.r =  Bpa3.r =  Bpa4.r =  Bpa5.r =  Bpa6.r =  Bpa7.r = Bpa8.r = black;

	//name
	Wki.name = Bki.name = king;
	Wqu.name = Bqu.name = queen;
	Wbi1.name = Wbi2.name = Bbi1.name = Bbi2.name = bishop;
	Wro1.name = Wro2.name = Bro1.name = Bro2.name = rook;
	Wkn1.name = Wkn2.name = Bkn1.name = Bkn2.name = knight;
	Wpa1.name = Wpa2.name = Wpa3.name = Wpa4.name = Wpa5.name = Wpa6.name = Wpa7.name = Wpa8.name = pawn;
	Bpa1.name = Bpa2.name = Bpa3.name = Bpa4.name = Bpa5.name = Bpa6.name = Bpa7.name = Bpa8.name = pawn;

	//promoted?
	 Wki.pr = Wqu.pr = Wkn1.pr = Wkn2.pr = Wbi1.pr = Wbi2.pr =  Wro1.pr =  Wro2.pr =  Wpa1.pr = Wpa2.pr =  Wpa3.pr =  Wpa4.pr =  Wpa5.pr =  Wpa6.pr =  Wpa7.pr = Wpa8.pr = false;
         Bki.pr = Bqu.pr = Bkn1.pr = Bkn2.pr = Bbi1.pr = Bbi2.pr =  Bro1.pr =  Bro2.pr =  Bpa1.pr = Bpa2.pr =  Bpa3.pr =  Bpa4.pr =  Bpa5.pr =  Bpa6.pr =  Bpa7.pr = Bpa8.pr = false;

	
	board[1][1].p = Wro1;
	board[1][2].p = Wkn1;
	board[1][3].p = Wbi1;
	board[1][4].p = Wqu;
	board[1][5].p = Wki;
	board[1][6].p = Wbi2;
	board[1][7].p = Wkn2;
	board[1][8].p = Wro2;

	board[8][1].p = Bro1;
        board[8][2].p = Bkn1;
        board[8][3].p = Bbi1;
        board[8][4].p = Bqu;
        board[8][5].p = Bki;
        board[8][6].p = Bbi2;
        board[8][7].p = Bkn2;
        board[8][8].p = Bro2;

	board[2][1].p = Wpa1;
        board[2][2].p = Wpa2;
        board[2][3].p = Wpa3;
        board[2][4].p = Wpa4;
        board[2][5].p = Wpa5;
        board[2][6].p = Wpa6;
        board[2][7].p = Wpa7;
        board[2][8].p = Wpa8;

	board[7][1].p = Bpa1;
        board[7][2].p = Bpa2;
        board[7][3].p = Bpa3;
        board[7][4].p = Bpa4;
        board[7][5].p = Bpa5;
        board[7][6].p = Bpa6;
        board[7][7].p = Bpa7;
        board[7][8].p = Bpa8;

}

move *undo(movesList *list) {
	if(list->Last == NULL){
		printf("There is no moves to undo!\n");
		return NULL;
	}
	int x,y,i,j;
	move *m = malloc(sizeof(move));
	i = list->Last->m->x1;
	j = list->Last->m->y1;
	x = list->Last->m->x2;
	y = list->Last->m->y2;
	piece temp = list->Last->m->p;

	switch (board[x][y].p.name){
	   case pawn:
		if(board[x][y].p.pr == true){ //case for promotion
                        board[x][y].p.name = pawn;
                        board[x][y].p.pr = false;
                        m->x1 = x;
                        m->y1 = y;
                        m->x2 = i;
                        m->y2 = j;
                        updateBoard(m);
                        board[x][y].p = temp;
                        break;
                } 
		else if(temp.name != empty && abs(y-j)==1 ) {
			m->x1 = x;
			m->y1 = y;
			m->x2 = i;
			m->y2 = j;
			updateBoard(m);
			board[x][y].p = temp;
			break;
		}else if(temp.name == empty && abs(y-j)==1){
			m->x1 = x;
			m->y1 = y;
			m->x2 = i;
			m->y2 = j;
			temp.r = (board[x][y].p.r == white) ? black : white;
			updateBoard(m);
			temp.name = pawn;
			board[i][y].p = temp;
			break;
		}else if(temp.name == empty && abs(y-j)==0){
			m->x1 = x;
			m->y1 = y;
			m->x2 = i;
			m->y2 = j;
			updateBoard(m);
			break;
		}
		else{ 
			break;
		}

   	case king:
		if ((y-j)==2){
			m->x1 = x;
			m->y1 = y;
			m->x2 = i;
			m->y2 = j;
			updateBoard(m);
	
			m->x1 = x;
			m->y1 = y-1;
			m->x2 = i;
			m->y2 = 8;
			updateBoard(m);
			if(x == 1){
				*Wki_Moved = false;
				*Wro2_Moved = false;
			}
			else{
				*Bki_Moved = false;
				*Bro2_Moved = false;
			}
			break;
		}else if ((y-j)==-2)
			{m->x1 = x;
			m->y1 = y;
			m->x2 = i;
			m->y2 = j;
			updateBoard(m);

			m->x1 = x;
			m->y1 = y+1;
			m->x2 = i;
			m->y2 = 1;
			updateBoard(m);
			if(x == 1){
				*Wki_Moved = false;
				*Wro1_Moved = false;
			}
			else{
				*Bki_Moved = false;
				*Bro1_Moved = false;
			}
			break;
		}else{
			m->x1 = x;
			m->y1 = y;
			m->x2 = i;
			m->y2 = j;
			updateBoard(m);
			board[x][y].p = temp;
			break;
		}
		break;
	   default:
		if(board[x][y].p.pr == true){ //case for promotion
			board[x][y].p.name = pawn;
			board[x][y].p.pr = false; 
		}
		m->x1 = x;
		m->y1 = y;
		m->x2 = i;
		m->y2 = j;
		updateBoard(m);
		board[x][y].p = temp;
		break;
	}
	
	RemoveLastMoveFromList(list);
	if(list->Length != 0){
		LastMove = list->Last->m;
	}
	return m;
}


// if the move is valid, we should update the board
// // 1- The piece over the destination square will be updated
// // 2- The initial square will be updated to empty
void updateBoard(move *m){

	if(board[m->x1][m->y1].p.name == king && board[m->x1][m->y1].p.r == black &&  //castling black king with rook H8
	   m->x1 == 8 && m->y1 == 5 && m->x2 == 8 && m->y2 == 7){
                   board[m->x2][m->y2].p = board[m->x1][m->y1].p;
                   board[m->x1][m->y1].p.name = empty;
                   board[m->x2][m->y2 - 1].p = board[m->x2][m->y2 + 1].p;
	           board[m->x2][m->y2 + 1].p.name = empty;
		   *Bki_Moved = true;
	           *Bro2_Moved = true;	
	}
	else if(board[m->x1][m->y1].p.name == king && board[m->x1][m->y1].p.r == black &&  //castling black king with rook H1
                m->x1 == 8 && m->y1 == 5 && m->x2 == 8 && m->y2 == 3){
                   board[m->x2][m->y2].p = board[m->x1][m->y1].p;
                   board[m->x1][m->y1].p.name = empty;
                   board[m->x2][m->y2 + 1].p = board[m->x2][m->y2 - 2].p;
                   board[m->x2][m->y2 - 2].p.name = empty;
	           *Bki_Moved = true;
                   *Bro1_Moved = true;

	 }
	 else if(board[m->x1][m->y1].p.name == king && board[m->x1][m->y1].p.r == white &&  //castling white king with rook A8
                m->x1 == 1 && m->y1 == 5 && m->x2 == 1 && m->y2 == 7){
                   board[m->x2][m->y2].p = board[m->x1][m->y1].p;
                   board[m->x1][m->y1].p.name = empty;
                   board[m->x2][m->y2 - 1].p = board[m->x2][m->y2 + 1].p;
                   board[m->x2][m->y2 + 1].p.name = empty;
		   *Wki_Moved = true;
                   *Wro2_Moved = true;

	 }
	 else if(board[m->x1][m->y1].p.name == king && board[m->x1][m->y1].p.r == white &&  //castling white king with rook A1
                 m->x1 == 1 && m->y1 == 5 && m->x2 == 1 && m->y2 == 3){
                    board[m->x2][m->y2].p = board[m->x1][m->y1].p;
                    board[m->x1][m->y1].p.name = empty;
                    board[m->x2][m->y2 + 1].p = board[m->x2][m->y2 - 2].p;
                    board[m->x2][m->y2 - 2].p.name = empty;
		    *Bki_Moved = true;
            	    *Wro1_Moved = true;

	}
	else if(board[m->x1][m->y1].p.name == pawn && m->x1 == 5 && m->x2 == 6 && (m->y2-m->y1 == 1 || m->y1-m->y2 == 1) //en passant for wPA
		&& board[m->x1][m->y2].p.name == pawn && board[m->x1][m->y1].p.r != board[m->x1][m->y2].p.r 
		&& board[m->x2][m->y2].p.name == empty){
		m->p = board[m->x2][m->y2].p;
		board[m->x2][m->y2].p = board[m->x1][m->y1].p;
		board[m->x1][m->y2].p.name = empty;
		board[m->x1][m->y1].p.name = empty;
	}
	else if(board[m->x1][m->y1].p.name == pawn && m->x1 == 4 && m->x2 == 3 && (m->y2-m->y1 == 1 || m->y1-m->y2 == 1) //en passant for bPA
                && board[m->x1][m->y2].p.name == pawn && board[m->x1][m->y1].p.r != board[m->x1][m->y2].p.r
                && board[m->x2][m->y2].p.name == empty){
		m->p = board[m->x2][m->y2].p;
                board[m->x2][m->y2].p = board[m->x1][m->y1].p;
                board[m->x1][m->y2].p.name = empty;
		board[m->x1][m->y1].p.name = empty;
 	}
	else if(board[m->x1][m->y1].p.name == pawn && (m->x2 == 8 || m->x2 == 1)){ //promotion for pawn
		m->p = board[m->x2][m->y2].p;
		if(board[m->x1][m->y1].p.r == player1->r){
			if(player1->t == computer || (player2->t == computer && *turn == 1)){
				 board[m->x1][m->y1].p.name = queen;
			}
			else{
				board[m->x1][m->y1].p.name =  Promotion();
			}
		}
		else{
			if(player2->t == computer || (player1->t == computer && *turn == 0)){
                                 board[m->x1][m->y1].p.name = queen;
                        }
                        else{
                                board[m->x1][m->y1].p.name =  Promotion();
                        }
		}
		board[m->x1][m->y1].p.pr = true;
		board[m->x2][m->y2].p = board[m->x1][m->y1].p;
		board[m->x1][m->y1].p.name = empty;
	}       	  
	else{
		m->p = board[m->x2][m->y2].p;
		board[m->x2][m->y2].p = board[m->x1][m->y1].p;		//any other move
		board[m->x1][m->y1].p.name = empty;
	}
}



pieceName Promotion(){	
	char c;
	int flag = 0;
	pieceName pname;
		do{	//loops until user inputs a valid piece name
			printf("Which piece would you like to be promoted to? Input Q for Queen, N for Knight, B for Bishop, or R for Rook: ");
			scanf("%c",&c);
	
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
	return (pname);
}
