#**************************************
# Makefile
#
# Makefile for compiler parser
#
# Author: Theodore Gwynn 
# based on code by Phil Howard 
# theo.gwynn@oit.edu
# phil.howard@oit.edu
#
# Date: Jan. 12, 2016
#

COPTS=-Wall -g -c -O0 -std=c++11 
OBJS=main.o \
	 langlex.o \
	 cSymbolTable.o

all: calc

clean:
	rm -f $(OBJS)
	rm -f *.o
	rm -f langlex.c
	rm -f calc
	rm -f out.xml
	rm -f out2.xml
	rm -f out

.c.o:
	g++ $(COPTS) $? -o $@

.cpp.o:
	g++ $(COPTS) $? -o $@

main.o: main.cpp langlex.c 
	g++ $(COPTS) main.cpp -o main.o

langlex.c: lang.l
	flex -o langlex.c lang.l

cSymbolTable.o: cSymbolTable.cpp
	g++ $(COPTS) cSymbolTable.cpp -o cSymbolTable.o

langlex.o: langlex.c
	g++ $(COPTS) -Wno-sign-compare $? -o $@

calc: $(OBJS)
	g++ $(OBJS) -o calc