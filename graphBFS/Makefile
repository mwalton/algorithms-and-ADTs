# Michael Walton : mwwalton@ucsc.edu
# Makefile

GCC = gcc -g -Wall -Wextra -pedantic -std=c99
SOURCE = listdr.c list.c util.c graph.c graphdr.c findPath.c
HEADERS = list.h util.h graph.h
OBJECTS = ${SOURCE:.c=.o}
EXECBIN = listdr graphdr findPath
MISC = Makefile README

all : listdr graphdr findPath

findPath : findPath.o graph.o list.o util.o
	${GCC} -o findPath findPath.o graph.o list.o util.o

graphdr : graphdr.o list.o graph.o util.o
	${GCC} -o graphdr graphdr.o graph.o list.o util.o

listdr : listdr.o list.o util.o
	${GCC} -o listdr listdr.o list.o util.o

%.o : %.c
	${GCC} -c $<

zip :
	zip WaltonMProg5.zip ${HEADERS} ${SOURCE} ${MISC}

clean :
	rm ${OBJECTS} ${EXECBIN}
