
DIR=$(shell pwd)
BIN_DIR=$(DIR)/bin
SRC_DIR=$(DIR)
PROGRAM=$(BIN_DIR)

$(shell [ -d "$(PROGRAM)" ] || mkdir -p $(PROGRAM))

CC=gcc
CFLAGS=-Wall -g 

.PHONY: all clean rebuild

all:$(OBJS) 
	$(CC) $(CFLAGS) main.c menu.c readfile.c lzw.c -lm -o $(PROGRAM)/xxx

rebuild: clean all

clean:
	rm -rf $(BIN_DIR)/* 

