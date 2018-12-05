SRC = src/
BIN = bin/
BUILD = build/
MKDIR_P ?= mkdir -p

CC = gcc
FLAGS = -std=c99
SSL = -L/usr/local/lib -lssl -lcrypto

server = server.c

SOURCE = $(shell find . -name "*.c" -not -name "$(server)")
HEADERS = $(shell find . -name "*.h")

server: $(SOURCE) $(HEADERS)
	make checkdir
	$(CC) -o $(BIN)$@ $(SRC)$($@) $(SOURCE) $(FLAGS) $(SSL)
checkdir:
	$(MKDIR_P) $(dir $(BIN))
.PHONY: build
build:
	make -f build.mk EXEC=server
	make -f build.mk EXEC=client
clean:
	rm -rf $(BIN)*
	rm -rf $(BUILD)*
