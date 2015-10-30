# Operating Systems Project 1
# Names: Adam Beckett May, Robert Kocovski, Daniel Ola, Andrew Lau
# Student Numbers: 100487239, 100536625, 100523811, 100522457
#	Lab02 Tutorial Assisstant: Somayyeh Aghababaei
SOURCES = myshell.c utility.c
CC = clang
CFLAGS = -Wall -Wextra -std=c99
LFLAGS =
LIBS = -lm
SOURCES = myshell.c utility.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = myshell.exe
.PHONY: clean help

%.exe : %.o
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

help:
	@echo "Valid targets:"
	@echo "  clean:  removes .o and .exe files"
