# Boron Compiler \
Copyright (C) 2026 Samuel Little

# This program is free software: you can redistribute it and/or modify \
it under the terms of the GNU General Public License as published by \
the Free Software Foundation, either version 3 of the License, or \
(at your option) any later version.

# See <LICENSE> for details.

CC = gcc
CFLAGS = -Wall -Wextra -g -Iinc

NIM = nim
NIMFLAGS = c -d:release

BIN_DIR = bin
OBJ_DIR = obj

.PHONY: all dirs clean boronc boron boronpp

all: dirs boronc boron # boronpp

dirs:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

boronc: dirs
	$(CC) $(CFLAGS) src/boronc/*.c -o $(BIN_DIR)/boronc

boron: dirs
	$(NIM) $(NIMFLAGS) \
		-o:$(BIN_DIR)/boron \
		src/boron/main.nim

# boronpp: dirs \
	$(CC) $(CFLAGS) src/boronpp/*.c -o $(BIN_DIR)/boronpp

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)