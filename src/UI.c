/************************************************************************
* UI Module: 								*
*									*
* Update Log:								*
*    JS		01/21/28				  	        *
*    JS		01/22/18						*
*    JS		01/24/18   						*
*    JS		01/27/18						*	
*    JS		01/29/18	       					*
*    JS		01/30/18
*
* iNote to self:
*	tasks
* 	-save player type, color, moves that each player performs
*
* 	-come up with funtion that allows player to save their game
*	to load it up at a later time. 
*	
*	load a game
*
*	how should save each game as
*		ideas are saving it as a player profile
*		this entails that i promp the user to enter a player
*		profile in the beginning of the game to load up 
*		their game that they wish to play.
*		
*	i think we should just allow the player to save one game, 
*	that way we can associate that name to load up name or just ask
*	the player if he just wishes to start a new game
*	 
*
*	 if (start new game)
*	 	load up the players profile (GameLog)
*	 	-delete the old GamesLog of the player
*	 	-write to the Players Game log
*	 	...
*
*********************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "dataStruct.h"
#include "legalMoves.h"
#include "Graphics.h"
#include "evaluation.h"

const int strLength = 6;

/************************************************************************
 * printIntro Funtion: This function prints a welcome message on screen *
 *  with basic information to assist ther user on getting started with  *
 * chess game.                                                          *
 *   Inputs:   None                                                     *
 *   Outputs:  prints out getting started instructions on screen	*
************************************************************************/
void printIntro();

/************************************************************************
* chooseMode Funtion: chooseMode function asks the user to choose the 	*
*  mode that they want to play under, against another player or against	*
*  a computer.                                                         	*
*   Inputs:  None                                                     	*
*   Returns: integer value for mode					*
*************************************************************************/
int chooseMode();

/************************************************************************
* delay Funtion: This function waits for specified number of seconds  	*
*   Inputs:  integer for number of seconds                              *
*   Outputs: None                                                       *
*************************************************************************/
void delay(int numSeconds);

/************************************************************************
* toUpper Funtion: This Fucntion converts a string of character and  	*
*  converts it to upper case, it does not return anything, has   	*
*   Inputs:  char Array[]                                            	*
*   Returns: coverts string array to upper case			        *
*************************************************************************/
void toUpper(char str[]);

void updateKings(int *wx,int *wy, int *bx, int *by,move *m);
void updateKingsUndo(int *wx,int *wy, int *bx, int *by,move *m);
void krMoved(move *m);
void copyBoard(square x[9][9],square y[9][9]);

int main()
{
    // turn = 0 is white's turn 
    // turn = 1 is black's turn
    // after each move you should update the turn
    // you can also use the player1 and player2 to check the color of the player
    FILE *file;
    file = NULL;   

    movesList *newList;
    int mode;			// user's option to play vs. computer or vs. another human 
    //int result;			// stores result for some evalutation
    char input[10];		// stores input from user
    char str[strLength];	// stores input from user
    char input2[10];
    char player1Name[40]  = "Player 1";
    char player2Name[40]  = "Player 2";


    move *move;			// values for current 
   
    newList = NULL; 
    move = NULL;		// starting value for new move from either player 1
				// player 2.	
     
    Wki_Moved = malloc(sizeof(bool));
    *Wki_Moved = false;		//set kings and rooks as 'not moved' (castling requisite)
    Bki_Moved = malloc(sizeof(bool));
    Wro1_Moved = malloc(sizeof(bool));
    Wro2_Moved = malloc(sizeof(bool));
    Bro1_Moved = malloc(sizeof(bool));
    Bro2_Moved = malloc(sizeof(bool));
    *Bki_Moved = false;
    *Wro1_Moved = false;
    *Wro2_Moved = false;
    *Bro1_Moved = false;
    *Bro2_Moved = false;
    LastMove = malloc(sizeof(move));
    LastMove = NULL;
    AImove = malloc(sizeof(move));
    AImove = NULL;
    player1 = malloc(sizeof(player));
    player2 = malloc(sizeof(player));
    int validInput(char in[]);
	
    printIntro();		// prints to screen introduction to the game

    mode = chooseMode();	// user choosen mode of two choices 
  
    // setting player types and colors depening on mode & sets player turn
    if(mode == 1)
    {
	player1->t = human;
	player2->t = computer;

        printf("%s please enter your name: ", player1Name);
	scanf("%s", player1Name);
	while((getchar()) != '\n');
        printf("%s select a chess color piece\n(Type \"white\" or \"black\"): ", player1Name);
	while(true){
		scanf("%s", input);
		while((getchar()) != '\n');
		if(strcmp(input, "white") == 0)
		{
			player1->r = white;
			player2->r = black;
			break;
		}
		else if(strcmp(input, "black") == 0)
		{	
			player1->r = black;
			player2->r = white;
			break;
		}
		else{
			printf("Invalid input. Please enter \"black\" or \"white\"\n");
		}
    }   
	
	file = fopen(player1Name, "rb+");
	if(file == NULL)
        {
	    file = fopen(player1Name, "wb");
	}
 
	fprintf(file, "Player Name:%s %d %d\n", player1Name, player1->t, player1->r);
	fprintf(file, "Player Name:%s %d %d\n", player2Name, player2->t, player2->r);
	fclose(file);
    }
    else if(mode == 2)
    {	
	player1->t = human;
	player2->t = human;

        printf("%s please enter your name: ", player1Name);
	scanf("%s", player1Name);
	while((getchar()) != '\n');
        printf("%s please enter your name: ", player2Name);
	scanf("%s", player2Name);
	while((getchar()) != '\n');
        printf("%s select a chess color piece\n(Type \"white\" or \"black\"): ", player1Name);

	
	while(true){
		scanf("%s", input);
		while((getchar()) != '\n');
		if(strcmp(input, "white") == 0)
		{
			player1->r = white;
			player2->r = black;
			break;
		}
		else if(strcmp(input, "black") == 0)
		{	
			player1->r = black;
			player2->r = white;
			break;
		}
		else{
			printf("Invalid input. Please enter \"black\" or \"white\"\n");
		}
	}
	file = fopen(player1Name, "rb+");
	if(file == NULL)
        {
	    file = fopen(player1Name, "wb");
	}

	fprintf(file, "Player Name:%s %d %d\n", player1Name, player1->t, player1->r);
	fprintf(file, "Player Name:%s %d %d\n", player2Name, player2->t, player2->r);
	fclose(file);
    }
    else{
	player1->t = computer;
        player2->t = computer;

	player1->r = white;
	player2->r = black;

        file = fopen(player1Name, "rb+");
        if(file == NULL)
        {
            file = fopen(player1Name, "wb");
        }

        fprintf(file, "Player Name:%s %d %d\n", player1Name, player1->t, player1->r);
        fprintf(file, "Player Name:%s %d %d\n", player2Name, player2->t, player2->r);
        fclose(file);
     }  


    initializeBoard();
    printf(">>>>>>>>>>>>>>>>>> White piece always goes first! <<<<<<<<<<<<<<<<<<\n");
    printf("*                                                                  *\n");
    delay(500);
    printf("*          Move must be entered as one word, for example:          *\n");
    delay(500);
    printf("*          to move a pawn from c2 to c3, the user types in         *\n");
    delay(500);
    printf("*          \"c2 c3\"and hit ENTER key to execute move                *\n");
    delay(500);
    printf("*  	   To undo, type undo.                                     *\n");
    delay(500);
    printf("*          To quit, type quit.                                     *\n");
    delay(500);
    printf("*                                                                  *\n");
    delay(500);
    printf("*                                                                  *\n");
    delay(500);
    printf("*               !!!!!!!    IT'S CHESS TIME   !!!!!!!               *\n");
    printf("*                                                                  *\n");
    delay(500);
    printf(">>>>>>>>>>>>>>>>>> White piece always goes first! <<<<<<<<<<<<<<<<<<\n\n");

    delay(1000);
    printBoard(); 

    newList = CreateMovesList(); // starts a new moves list to and will start collecting mmoves
    
    square tempBoard[9][9]; 
    int wx = 1,wy = 5,bx = 8,by = 5;
    int capture = 0;
    // Game flow loop 
    bool endGame = true;
    turn = malloc(sizeof(bool));
    *turn = 0;	
    while (endGame && capture < 100){
        if(*turn == 0)
        {   
		while(true){
			if((player1->r == white && player1->t == computer)||(player2->r == white && player2->t == computer)){
				copyBoard(board,tempBoard);
				alphaBeta(white, -99999, 99999, 5, 0,newList, board[wx][wy],board[bx][by]);
				copyBoard(tempBoard,board);
				move = AImove;
				PrintMove(AImove);
		//		delay(3000);
			}	
			else if(player1->r == white){
				printf("%s, please enter move: ", player1Name);
			}else{
				printf("%s, please enter move: ", player2Name);
			   }
			while(!((player1->r == white && player1->t == computer)||(player2->r == white && player2->t == computer))){
				scanf("%[^\n]s",input2);
				getchar();
				if(strcmp(input2, "quit") == 0 || strcmp(input2, "QUIT") == 0 ){
				    //best way to end game?
					if(player1->r == white){
						printf("%s WINS!\n", player2Name);
					}else{
						printf("%s WINS!\n", player1Name);
				   	}
					SaveMovesListToFile("GamesLog.txt", newList);
					free(Wki_Moved);
				   	free(Bki_Moved);
   					free(Wro1_Moved);
					free(Wro2_Moved);
   					free(Bro1_Moved);
    					free(Bro2_Moved);
   					free(LastMove);
   					//free(AImove);
   					free(player1);
  					free(player2);
					DeleteMovesList(newList);
 
					return 0;
				}
				else if(strcmp(input2, "save") == 0 || strcmp(input2, "SAVE") == 0 ){
				    //saveGame()??
					printf("Game Saved\n\n");
					SaveMovesListToFile("GamesLog.txt", newList);
					free(Wki_Moved);
					free(Bki_Moved);
 					free(Wro1_Moved);
   					free(Wro2_Moved);
				   	free(Bro1_Moved);
  				 	free(Bro2_Moved);
   					free(LastMove);
   					//free(AImove);
    					free(player1);
   					free(player2);
					DeleteMovesList(newList);
						
					return 0;

				}
				else if(strcmp(input2, "undo") == 0 || strcmp(input2, "UNDO") == 0 ){
					if(newList->Length < 2){
                                                printf("There is no move to undo.\n");
					}
                                        else{
		
                                                move= undo(newList);
						if(move != NULL){
							updateKingsUndo(&wx,&wy,&bx,&by,move);
							free(move);
                                                }
						move = undo(newList);
						if(move != NULL){
							updateKingsUndo(&wx,&wy,&bx,&by,move);
							free(move);
						}
                                                printBoard();
                                        }
					if(player1->r == white){
                                                printf("%s, please enter move: ", player1Name);
                                        }else{
                                                printf("%s, please enter move: ", player2Name);
                                        }	
				}
				else if(validInput(input2) == 1){
					str[0] = input2[0];
					str[1] = input2[1];
					str[3] = input2[3];
					str[4] = input2[4];
					toUpper(str);
					move = stringToMove(str);
					break;
				}
				 else if(validInput(input2) == 2){
                                        str[0] = input2[0];
                                        str[1] = input2[1];
                                        str[3] = input2[2];
                                        str[4] = input2[3];
                                        toUpper(str);
                                        move = stringToMove(str);
                                        break;
				}
				else{
					printf("Invalid input! Please enter a valid move, 'save', 'quit', or 'undo'.\n");
					if(player1->r == white){
						printf("%s, please enter move: ", player1Name);
					}else{
						printf("%s, please enter move: ", player2Name);
					}
				}
			}

		   if(board[move->x1][move->y1].p.name == empty){
			printf("\x1b[36m You've selected an empty square.\n\n\x1b[0m");
			free(move);
		   }
		   else if(board[move->x1][move->y1].p.r != white){
			printf("\x1b[36m Please select white pieces only.\n\n\x1b[0m");
			free(move);
		   }
		   else if(!legalForUser(move)){
			printf("\x1b[36m Not a legal move.\n\n\x1b[0m");
			free(move);
		   }
		   else
		   {
			int WX = wx, WY = wy, BX = bx, BY = by; 
			updateKings(&wx,&wy,&bx,&by,move);
			piece temp = board[move->x2][move->y2].p;
			updateBoard(move);
			if(kingInCheck(board[wx][wy])) 
			{
				if(!((player1->r == white && player1->t == computer)||(player2->r == white && player2->t == computer))){
					printf("\x1b[36m King will be in check. Select a different move.\n\x1b[0m");
				}
				wx = WX; wy = WY; bx = BX; by = BY;
				int X1 = move->x1, Y1 = move->y1;
				move->x1 = move->x2;
				move->y1 = move->y2;
				move->x2 = X1;
				move->y2 = Y1;
				updateBoard(move);
				board[move->x1][move->y1].p = temp;
			}
			else{   
				LastMove = move;
				krMoved(move);
				printBoard();
				if(move->p.name != empty || board[move->x2][move->y2].p.name == pawn){
					capture = 0;
				}
				else{
					capture++;
				}
				AddMoveToMoveList(newList, move);
				if(kingInCheck(board[bx][by])) 
				{
					printf("\x1b[36m The black king is in check position.\n\n\x1b[0m");
					if(Checkmate(board[bx][by]))
					{	
						printf("\x1b[36m Checkmate. White won.\n\n\x1b[0m");
						endGame = false;
					}
				}   
				else if(draw(board[bx][by],newList)){
					printf("Game ended in a tie.\n\x1b[0m");
					endGame = false;
				}	
				*turn = 1;
				break;
			}
		}
	}
	}
	else{
		while(true){
			if((player1->r == black && player1->t == computer)||(player2->r == black && player2->t == computer)){
				copyBoard(board,tempBoard);;
				alphaBeta(black, -99999, 99999, 5, 0,newList, board[wx][wy],board[bx][by]);
                                copyBoard(tempBoard,board);
				move = AImove;
				PrintMove(AImove);
			//	delay(1000);
                        }
			else if(player1->r == black){
				printf("%s, please enter move: ", player1Name);
			}else{
				printf("%s, please enter move: ", player2Name);
			}
	
			 while(!((player1->r == black && player1->t == computer)||(player2->r == black && player2->t == computer))){
				scanf("%[^\n]s",input2);
				getchar();
				if(strcmp(input2, "quit") == 0 || strcmp(input2, "QUIT") == 0 ){
					//best way to end game?
					if(player1->r == white){
						printf("%s WINS!\n", player1Name);
					}else{
						printf("%s WINS!\n", player2Name);
					}
					SaveMovesListToFile("GamesLog.txt", newList);
					free(Wki_Moved);
					free(Bki_Moved);
					free(Wro1_Moved);
   					free(Wro2_Moved);
   					free(Bro1_Moved);
   					free(Bro2_Moved);
  					free(LastMove);
  					//free(AImove);
  					free(player1);
   					free(player2);
					DeleteMovesList(newList);

					return 0;
				}
				else if(strcmp(input2, "save") == 0 || strcmp(input2, "SAVE") == 0 ){
					//saveGame()??
					SaveMovesListToFile("GamesLog.txt", newList);
					printf("Game Saved");
					free(Wki_Moved);
					free(Bki_Moved);
					free(Wro1_Moved);
					free(Wro2_Moved);
   					free(Bro1_Moved);
  					free(Bro2_Moved);
   					free(LastMove);
  				 	//free(AImove);
    					free(player1);
				        free(player2);
					DeleteMovesList(newList);
					return 0;
				}
				else if(strcmp(input2, "undo") == 0 || strcmp(input2, "UNDO") == 0 ){
                                        if(newList->Length < 2){
						printf("There is no move to undo.\n");
					}else{
						move= undo(newList);
                                                if(move != NULL){
                                                        updateKingsUndo(&wx,&wy,&bx,&by,move);
							free(move);
                                                }
                                                move = undo(newList);
                                                if(move != NULL){
                                                        updateKingsUndo(&wx,&wy,&bx,&by,move);
							free(move);
                                                }
						printBoard();
					}
					if(player1->r == black){
                                                printf("%s, please enter move: ", player1Name);
                                        }else{
                                                printf("%s, please enter move: ", player2Name);
                                        }
	
                                }			
				else if(validInput(input2) == 1){
					str[0] = input2[0];
					str[1] = input2[1];
					str[3] = input2[3];
					str[4] = input2[4];
					toUpper(str);
					move = stringToMove(str);
					break;
                                    
				}	
				 else if(validInput(input2) == 2){
                                        str[0] = input2[0];
                                        str[1] = input2[1];
                                        str[3] = input2[2];
                                        str[4] = input2[3];
                                        toUpper(str);
                                        move = stringToMove(str);
                                        break;
				}
				else{
					printf("Invalid input! Please enter a valid move, 'save', 'quit', or 'undo'.\n");
					if(player1->r == black){
						printf("%s, please enter move: ", player1Name);
					}else{
						printf("%s, please enter move: ", player2Name);
					}
				}
			}		
			if(board[move->x1][move->y1].p.name == empty){
				printf("\x1b[36m This is an empty square.\n\n\x1b[0m");
				free(move);
			}
			else if(board[move->x1][move->y1].p.r != black){
				printf("\x1b[36m Please select black pieces only.\n\n\x1b[0m");
				free(move);
			}
			else if(!legalForUser(move)){
				printf("\x1b[36m Not a legal move.\n\n\x1b[0m");
				free(move);
			}
			else{
				int WX = wx, WY = wy, BX = bx, BY = by;
				updateKings(&wx,&wy,&bx,&by,move);
				piece temp = board[move->x2][move->y2].p;
				updateBoard(move);
				if(kingInCheck(board[bx][by])) {
					if(!((player1->r == black && player1->t == computer)||
						(player2->r == black && player2->t == computer))){
						printf("\x1b[36m King will be in check. Select a different move.\n\x1b[0m");
					}
					wx = WX; wy = WY; bx = BX; by = BY;
					int X1 = move->x1, Y1 = move->y1;
					move->x1 = move->x2;
					move->y1 = move->y2;
					move->x2 = X1;
					move->y2 = Y1;
					updateBoard(move);
					board[move->x1][move->y1].p = temp;
				}
				else{
					LastMove = move;
					krMoved(move);
					printBoard();
					if(move->p.name != empty || board[move->x2][move->y2].p.name == pawn){
                                        	capture = 0;
                                	}
                                	else{
                                	        capture++;
                                	}
					AddMoveToMoveList(newList, move);
					if(kingInCheck(board[wx][wy])) {
						printf("\x1b[36m The white king is in check position.\n\n\x1b[0m");
						if (Checkmate(board[wx][wy])){
							printf("\x1b[36m Checkmate. Black won.\n\n \x1b[0m");
							endGame = false;
						}
					}
					else if(draw(board[wx][wy], newList)){
						printf("Game ended in a tie.\n \x1b[0m");
						endGame = false;
					}
					*turn = 0;
					break;
				}
		        }
		   SaveMovesListToFile(player1Name, newList);
		}
	}
   
    }

    if(capture > 99){
		printf("50 moves without any capture or pawn moves. Game ended in a tie.\n");
    }
    free(Wki_Moved);
    free(Bki_Moved);
    free(Wro1_Moved);
    free(Wro2_Moved);
    free(Bro1_Moved);
    free(Bro2_Moved);
    free(LastMove);
   // free(AImove);
    free(player1);
    free(player2);

    SaveMovesListToFile(player1Name, newList);
    DeleteMovesList(newList);
    return 0;

}

void printIntro()
{
    delay(500);
    printf("\n\n\n");
    delay(200);
    printf("************************************************************\n");
    delay(200);
    printf("************************************************************\n");
    delay(200);
    printf("*******     Welcome to Kingdoms! The Chess Game!     *******\n");
    delay(200);
    delay(200);
    printf("************************************************************\n");

    printf("************************************************************\n\n\n");
    delay(500);
    printf("Kingdoms! is an exhilariting game of classic chess game \n");
    delay(200);
    printf("designed for chess novices and experts alike. There are \n");
    delay(200);
    printf("two modes that can be played: Player Vs. Player or Human Vs. \n");
    delay(200);
    printf("Computer!!!\n\n\n");
    delay(200);
}

int chooseMode()
{
   int mode;
   do
   {

        printf("************************************************************\n");
        printf("*             Please select from folliwng modes!           *\n");
        delay(200);
        printf("*             1 - human vs computer                        *\n");
        printf("*             2 - human vs human                           *\n");
        printf("*             3 - computer vs computer                     *\n");
        delay(200);
        printf("************************************************************\n");
        printf("Enter Selection: ");
        scanf("%d", &mode);
        printf("\n");
        while((getchar()) != '\n');

        if(mode != 1 && mode != 2 && mode != 3)
        {
            printf("              Incorrect input!! \n");
        }

    }while(mode != 1 && mode != 2 && mode != 3);

    return mode;
}


void delay(int numSeconds)
{
    int milliSeconds = 1000*numSeconds;
    clock_t startTime = clock();

    while(clock() < startTime + milliSeconds);
}

void toUpper(char str[])
{
	if(str[0] > 72){
		str[0] -= 97;
		str[0] += 65;
	}
	if(str[3] > 72){
		str[3] -=97;
		str[3] +=65;
	}
}

int validInput(char in[]){
	int i = 0;
	int j = 3;
	int m = 2;

	if(in[5] == '\0' && in[2] == ' '){
		if(((in[i] >= 65 && in[i] <= 72 && in[i+1] >= 48 && in[i+1] <= 56) ||
     		(in[i] >= 97 && in[i] <= 104 && in[i+1] >= 48 && in[i+1] <= 56))&&
		((in[j] >= 65 && in[j] <= 72 && in[j+1] >= 48 && in[j+1] <= 56) ||
		(in[j] >= 97 && in[j] <= 104 && in[j+1] >= 48 && in[j+1] <= 56))){
		return 1;
		}
		return 0;
	}
	else if(in[4] == '\0'){
		if(((in[i] >= 65 && in[i] <= 72 && in[i+1] >= 48 && in[i+1] <= 56) ||
                (in[i] >= 97 && in[i] <= 104 && in[i+1] >= 48 && in[i+1] <= 56))&&
                ((in[m] >= 65 && in[m] <= 72 && in[m+1] >= 48 && in[m+1] <= 56) ||
                (in[m] >= 97 && in[m] <= 104 && in[m+1] >= 48 && in[m+1] <= 56))){
                return 2;
		}	
		return 0;
	}	
	else{
		return 0;
	}
}

void updateKings(int *wx,int *wy, int *bx, int *by,move *m){
        if(board[m->x1][m->y1].p.name == king){
                if(board[m->x1][m->y1].p.r == white){
                        *wx = m->x2;
                        *wy = m->y2;
                }
                else{
                        *bx = m->x2;
                        *by = m->y2;
                }
        }
}

void updateKingsUndo(int *wx,int *wy, int *bx, int *by,move *m){
        if(board[m->x2][m->y2].p.name == king){
                if(board[m->x2][m->y2].p.r == white){
                        *wx = m->x2;
                        *wy = m->y2;
                }
                else{
                        *bx = m->x2;
                        *by = m->y2;
                }
        }
}

void krMoved(move *m){
	if(board[m->x2][m->y2].p.name == king){
		if(board[m->x2][m->y2].p.r == white && m->x1 == 1 && m->y1 == 5){
			*Wki_Moved = true;
		}
		else if(board[m->x2][m->y2].p.r == black && m->x1 == 8 && m->y1 == 5){
			*Bki_Moved = true;
		}
	}
	else if(board[m->x2][m->y2].p.name == rook){
		if(board[m->x2][m->y2].p.r == white){
			if(m->x1 == 1 && m->y1 == 1){
				*Wro1_Moved = true;
			}
			else if(m->x1 == 1 && m->y1 == 8){
				*Wro2_Moved = true;
			}
		}
		else if(board[m->x2][m->y2].p.r == black){
			if(m->x1 == 8 && m->y1 == 1){
                                *Bro1_Moved = true;
                        }
                        else if(m->x1 == 8 && m->y1 == 8){
                                *Bro2_Moved = true;
                        }
		}
	}
}

void copyBoard(square x[9][9],square y[9][9]){
	for(int i = 1; i < 9; i++){
		for(int j = 1; j < 9; j++){
			y[i][j] = x[i][j];
		}
	}
}
