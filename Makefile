# Project: ZDR
# ©2013 by Vicente 'Ami603' Gimeno
# Makefile 

CC   = ppc-amigaos-gcc
OBJ  = gui.o main.o handlelibraries.o events.o appstuff.o
BIN  = ZDR


CFLAGS = -ggdb -std=gnu99  -Wextra -Wall -Wno-pointer-sign -Wstrict-prototypes -Wshadow -Werror-implicit-function-declaration -Wwrite-strings -pedantic -mcrt=newlib
LDFLAGS = -Wall -Werror -mcrt=newlib

.PHONY: all all-before all-after clean clean-custom

all: all-before ZDR all-after


clean: clean-custom
	delete $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS) $(LDFLAGS)
	$(CC) $(OBJ) -o $(BIN).debug $(CFLAGS) $(LDFLAGS)
	strip --strip-all -R .comment $(BIN)


%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
