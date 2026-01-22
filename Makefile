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
	 calclex.o \
	 parse.o \
	 utils.o

all: calc

clean:
	rm -f $(OBJS)
	rm -f *.o
	rm -f calclex.c
	rm -f calc
	rm -f out.xml
	rm -f out2.xml
	rm -f out

.c.o:
	g++ $(COPTS) $? -o $@

.cpp.o:
	g++ $(COPTS) $? -o $@

main.o: main.cpp calclex.c 
	g++ $(COPTS) main.cpp -o main.o

calclex.c: calc.l
	flex -o calclex.c calc.l

parse.o: parse.cpp
	g++ $(COPTS) parse.cpp -o parse.o

utils.o: utils.cpp
	g++ $(COPTS) utils.cpp -o utils.o

calclex.o: calclex.c
	g++ $(COPTS) -Wno-sign-compare $? -o $@

calc: $(OBJS)
	g++ $(OBJS) -o calc