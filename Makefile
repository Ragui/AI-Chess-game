all:
	cd src; make

test: 
	cd src; make test

clean:
	cd src; make clean

tar:
	gtar cvzf Chess_V1.0_src.tar.gz README INSTALL COPYRIGHT Makefile src doc bin --exclude=src/CVS --exclude=doc/CVS --exclude=bin/CVS
