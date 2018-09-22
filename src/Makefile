# Makefile 
# Activity log:
# 		Martino 
# 		Ragui Halim 01/19/2018
#

CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -std=c99 -c -g

EXES = chess
OBJS = *.o

all: chess

test: chess
	cd ../bin; ./chess
 
chess: UI.o dataStruct.o Graphics.o legalMoves.o evaluation.o
	$(CC) $(LFLAGS) UI.o dataStruct.o Graphics.o legalMoves.o evaluation.o -o ../bin/chess 

UI.o: UI.c dataStruct.h legalMoves.h Graphics.h
	$(CC) $(CFLAGS) UI.c -o UI.o 

dataStruct.o: dataStruct.c dataStruct.h
	$(CC) $(CFLAGS) dataStruct.c -o dataStruct.o 

legalMoves.o: legalMoves.c dataStruct.h legalMoves.h evaluation.h 
	$(CC) $(CFLAGS) legalMoves.c -o legalMoves.o 

Graphics.o: Graphics.c Graphics.h
	$(CC) $(CFLAGS) Graphics.c -o Graphics.o 

evaluation.o: evaluation.c evaluation.h
	 $(CC) $(CFLAGS) evaluation.c -o evaluation.o 

clean:
	rm -rf $(OBJS) ../bin/chess
