# Project: ZDR
# ©2013 by Vicente 'Ami603' Gimeno
# ©2020 by OpenSource Team
# Makefile 

ifneq ($(shell uname), AmigaOS)
	CC 		= ppc-amigaos-gcc
	DELETE		= rm -f
	STRIP = ppc-amigaos-strip
else
	CC 		= gcc
	DELETE		= delete
	STRIP = strip
endif

OBJ  = gui.o main.o handlelibraries.o events.o appstuff.o
BIN  = ZDR

CFLAGS = -gstabs -std=gnu99  -Wextra -Wall -Wno-pointer-sign -Wstrict-prototypes -Wshadow -Werror-implicit-function-declaration -Wwrite-strings -pedantic
LDFLAGS = -Wall -Werror

.PHONY: all all-before all-after clean clean-custom

all: all-before ZDR all-after

clean: clean-custom
	$(DELETE) $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS) $(LDFLAGS)
	$(CC) $(OBJ) -o $(BIN).debug $(CFLAGS) $(LDFLAGS)
	$(STRIP) --strip-all -R .comment $(BIN)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
