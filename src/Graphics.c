/************************************************************************
 * Graphics.c:                                                           *
 *                                                                       *
 * Update Log:                                                           *
 *     Martino 		                                                         *
 *     Ragui Halim 01/20/2018                                            *
 *                                                                       *
 * *********************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graphics.h"


void printBoard(){

    printf("    ----------------------------------------------------------------------- \n");
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf(" 8 |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |\n",
           printPiece(board[8][1].p), printPiece(board[8][2].p), printPiece(board[8][3].p), printPiece(board[8][4].p),
           printPiece(board[8][5].p), printPiece(board[8][6].p), printPiece(board[8][7].p), printPiece(board[8][8].p));
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf("    -----------------------------------------------------------------------|\n");
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf(" 7 |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |\n",
           printPiece(board[7][1].p), printPiece(board[7][2].p), printPiece(board[7][3].p), printPiece(board[7][4].p),
           printPiece(board[7][5].p), printPiece(board[7][6].p), printPiece(board[7][7].p), printPiece(board[7][8].p));
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf("    -----------------------------------------------------------------------|\n");
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf(" 6 |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |\n",
           printPiece(board[6][1].p), printPiece(board[6][2].p), printPiece(board[6][3].p), printPiece(board[6][4].p),
           printPiece(board[6][5].p), printPiece(board[6][6].p), printPiece(board[6][7].p), printPiece(board[6][8].p));
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf("    -----------------------------------------------------------------------|\n");
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf(" 5 |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |\n",
           printPiece(board[5][1].p), printPiece(board[5][2].p), printPiece(board[5][3].p), printPiece(board[5][4].p),
           printPiece(board[5][5].p), printPiece(board[5][6].p), printPiece(board[5][7].p), printPiece(board[5][8].p));
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf("    -----------------------------------------------------------------------|\n");
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf(" 4 |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |\n", 
           printPiece(board[4][1].p), printPiece(board[4][2].p), printPiece(board[4][3].p), printPiece(board[4][4].p),
           printPiece(board[4][5].p), printPiece(board[4][6].p), printPiece(board[4][7].p), printPiece(board[4][8].p));
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf("    -----------------------------------------------------------------------|\n");
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf(" 3 |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |\n",
           printPiece(board[3][1].p), printPiece(board[3][2].p), printPiece(board[3][3].p), printPiece(board[3][4].p),
           printPiece(board[3][5].p), printPiece(board[3][6].p), printPiece(board[3][7].p), printPiece(board[3][8].p));
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf("    -----------------------------------------------------------------------|\n");
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf(" 2 |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |\n",
           printPiece(board[2][1].p), printPiece(board[2][2].p), printPiece(board[2][3].p), printPiece(board[2][4].p),
           printPiece(board[2][5].p), printPiece(board[2][6].p), printPiece(board[2][7].p), printPiece(board[2][8].p));
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf("    -----------------------------------------------------------------------|\n");
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf(" 1 |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |\n", 
           printPiece(board[1][1].p), printPiece(board[1][2].p), printPiece(board[1][3].p), printPiece(board[1][4].p),
           printPiece(board[1][5].p), printPiece(board[1][6].p), printPiece(board[1][7].p), printPiece(board[1][8].p));
    printf("   |        |        |        |        |        |        |        |        |\n");
    printf("    ----------------------------------------------------------------------- \n");
    printf("        A        B        C        D        E        F        G        H    \n\n");
}




char * printPiece(piece p){

        if(p.name == rook  && p.r == black){
            return "\x1b[31m""Ro""\x1b[0m";}
        else if(p.name  == knight && p.r == black){
            return "\x1b[31m""Kn""\x1b[0m";}
        else if(p.name == bishop && p.r == black){
            return "\x1b[31m""Bi""\x1b[0m";}
        else if(p.name == queen && p.r == black){
            return "\x1b[31m""Qu""\x1b[0m";}
        else if(p.name == king && p.r == black){
            return "\x1b[31m""Ki""\x1b[0m";}
        else if(p.name == pawn && p.r == black){
            return "\x1b[31m""Pa""\x1b[0m";}
        else if(p.name == rook && p.r == white){
            return "\x1b[33m""Ro""\x1b[0m";}
        else if(p.name == knight && p.r == white){
            return "\x1b[33m""Kn""\x1b[0m";}
        else if(p.name == bishop && p.r == white){
            return "\x1b[33m""Bi""\x1b[0m";}
        else if(p.name == queen && p.r == white){
            return "\x1b[33m""Qu""\x1b[0m";}
        else if(p.name == king && p.r == white){
            return "\x1b[33m""Ki""\x1b[0m";}
        else if(p.name == pawn && p.r == white){
            return "\x1b[33m""Pa""\x1b[0m";}
        else{  return "  ";}

}

