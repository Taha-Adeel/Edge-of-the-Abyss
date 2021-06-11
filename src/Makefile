#SFMLDIR=/usr/include/SFML
#INCLUDEDIR=$(SFMLDIR)
#LIBDIR=$(SFMLDIR)
CC=g++
CFLAGS=-c -g -Wall -Werror -pedantic -pedantic-errors #-I $(INCLUDEDIR)
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

SRCS=main.cpp game.cpp
OBJS=$(addsuffix .o,$(basename $(SRCS))) 
EXE=Edge_of_abyss
.PHONY	: clean all

all : $(EXE)

$(EXE)	: $(OBJS)
		$(CC) -o $@ $(OBJS) $(LIBFLAGS)


# $(OBJS)	:	%.o	: %.cpp
#  		$(CC) $(CFLAGS) $<

clean :
	rm $(OBJS) $(EXE)