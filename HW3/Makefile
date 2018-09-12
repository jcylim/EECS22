#Makefile: PhotoLab

all: PhotoLab PhotoLabTest
	
clean:
	rm -f *.o
	rm -f PhotoLab
	rm -f PhotoLabTest

PhotoLab.o: PhotoLab.c FileIO.h Advanced.h DIPs.h Constants.h
	gcc -c -Wall -ansi -std=c99 PhotoLab.c -o PhotoLab.o 

PhotoLabTest.o: PhotoLab.c FileIO.h Advanced.h DIPs.h Constants.h
	gcc -c -Wall -ansi -std=c99 PhotoLab.c -o PhotoLabTest.o 

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -c -Wall -ansi -std=c99 FileIO.c -o FileIO.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -c -Wall -ansi -std=c99 Advanced.c -o Advanced.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -c -Wall -ansi -std=c99 DIPs.c -o DIPs.o

PhotoLab: PhotoLab.o FileIO.o libFilter.a
	gcc PhotoLab.o FileIO.o -L. -lFilter -o PhotoLab -lm

PhotoLabTest: FileIO.o PhotoLabTest.o libFilter.a
	gcc -g PhotoLabTest.o FileIO.o -L. -lFilter -o PhotoLabTest -lm -DDEBUG

libFilter.a: DIPs.o Advanced.o  
	ar rc libFilter.a DIPs.o Advanced.o
	ranlib libFilter.a

#EOF