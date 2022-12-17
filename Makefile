# AED 2018-2019, sem.2
# Makefile for LabAval Problem 2
# Last edit: abl 2019.03.19
#-----------------------------------------------------------------------
#   Compiler, Compiler Flags
CFLAGS = -Wall -std=c99 -O3

walker: walker.o 
	gcc $(CFLAGS) -o walker walker.o

walker.o: walker.c
	gcc $(CFLAGS) -c walker.c



FILES = $(shell ls *.puz)

t:
	for F in ${FILES}; do  ./walker $${F} ; done;

v:
	for F in ${FILES}; do  valgrind --leak-check=full ./walker $${F} ; done;


clean::
	rm -f *.o core walker *~
