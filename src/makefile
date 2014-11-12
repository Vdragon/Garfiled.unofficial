########################################################
##                                                    ##
## GARFILED v0.101 (Linux) Makefile                   ##
## -------------------------------------------------- ##
## Designed to compile under GCC.                     ##
##                                                    ##
########################################################
CC = gcc
CFLAGS = -O2
LFLAGS = -s
DEL = rm
OBJS = garfiled.o
EXE = garfiled

$(EXE):	$(OBJS)
	$(CC) $(CFLAGS) -Wl,$(LFLAGS) -o $(EXE) $(OBJS)

$(OBJS): garfiled.c
		$(CC) $(CFLAGS) -c garfiled.c

clean:
	$(DEL) *.o
	$(DEL) $(EXE)
