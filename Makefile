# General defines
CC = gcc
LEX = flex
YACC = bison
LIB = -lc  -lfl 
ELEX = lexic.l
EYACC = sintactic.y
OBJ = Compiladors2.o sintactic.tab.o lex.yy.o symtab.o
SRC = main.c symtab.c cua.c
SRCL = lex.yy.c
SRCY = sintactic.tab.c
BIN = Compiladors2
LFLAGS = -n -o $*.c 
YFLAGS = -d -v -o $*.c
OTHERS = sintactic.tab.h Compiladors2.output lexic.log

######################################################################

all : $(SRCL) $(SRCY)
	$(CC) -o $(BIN) $(SRCL) $(SRCY) $(SRC)  $(LIB)

$(SRCL) : $(ELEX)	
	$(LEX) $(LFLAGS) $<

$(SRCY) : $(EYACC)
	$(YACC) $(YFLAGS) $<

clean : 
	rm -f *~ $(BIN) $(OBJ) $(SRCL) $(SRCY) $(OTHERS)

