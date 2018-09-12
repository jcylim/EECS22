######################################################################
# Makefile: Makefile for Assignment #3 EECS22 Fall 2017
#
# 11/08/17 Mina Moghadam : updated for EECS22 Assignment 3 Fall 2017
# 10/08/16 Tim Schmidt   : updated for EECS22 Assignment 3 Fall 2016
# 10/17/15 Tim Schmidt   : updated for EECS22 Assignment 3 Fall 2015
# 10/21/14 Nistha Tandiya: updated for EECS22 Assignment 3 Fall 2014
# 10/27/13 Yasaman Samei : updated for EECS22 Assignment 3 Fall 2013
# 10/16/11 Weiwei Chen   : updated for EECS22 Assignment 3 Fall 2012
# 10/10/11 Weiwei Chen   : initial solution version
#
######################################################################


# design names
DESIGN = PhotoLab PhotoLabTest

#libs
LIBS   = libFilter.a libFileIO.a

CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -ansi -Wall -c
LFLAGS = -ansi -Wall
AR     = ar rc
RANLIB = ranlib

IMAGES = bw.ppm \
         negative.ppm \
         colorfilter.ppm \
         edge.ppm \
         vflipflip.ppm \
         shuffle.ppm \
         vmirror.ppm \
         border.ppm \
         noise.ppm \
         sharpen.ppm \
         posterize.ppm \
         blur.ppm \ 
		 crop.ppm \
		 resize.ppm \
		 brightnessandcontrast.ppm \

all: PhotoLab PhotoLabTest


########### generate object files ###########

#target to generate FileIO.o
FileIO.o: FileIO.h FileIO.c Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

#target to generate DIPs.o
DIPs.o: Image.h DIPs.h DIPs.c Constants.h
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o

#target to generate Advanced.o
Advanced.o: Image.h Advanced.h Advanced.c Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

#target to generate Image.o
Image.o: Image.c Image.h Constants.h
	$(CC) $(CFLAGS) Image.c -o Image.o

#target to generate Test.o
Test.o: Image.h Test.h Test.c Constants.h 
	$(CC) $(CFLAGS) Test.c -o Test.o

#target to generate Test_DEBUG.o
Test_DEBUG.o: Image.h Test.h Test.c Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c Test_DEBUG.c -o Test_DEBUG.o

#target to generate PhotoLab.o
PhotoLab.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

#target to generate PhotoLab_DEBUG.o
PhotoLab_DEBUG.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab.c -o PhotoLab_DEBUG.o


########### generate library files ###########

#target to generate libFilter.a
libFilter.a: DIPs.o Advanced.o
	$(AR) libFilter.a Advanced.o DIPs.o
	$(RANLIB) libFilter.a


########### generate executables ###########

#target to generate PhotoLab
PhotoLab: PhotoLab.o FileIO.o libFilter.a
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o DIPs.o Advanced.o Image.o Test.o -L. -lFilter -o PhotoLab

#target to generate test
PhotoLabTest: PhotoLab_DEBUG.o FileIO.o libFilter.a
	$(CC) $(lflags) PhotoLab_DEBUG.o FileIO.o DIPs.o Advanced.o Image.o Test_DEBUG.o -L. -lFilter -o PhotoLabTest
	
#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)

