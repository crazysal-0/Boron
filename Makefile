# Boron Compiler \
Copyright (C) 2026 Samuel Little

# This program is free software: you can redistribute it and/or modify \
it under the terms of the GNU General Public License as published by \
the Free Software Foundation, either version 3 of the License, or \
(at your option) any later version.

# See <LICENSE> for details.

CC = gcc
CFLAGS = -Wall -Wextra -g -Iinc

BIN_DIR = bin
OBJ_DIR = obj

BORON_SRC = src/boron
BORONPP_SRC = src/boronpp
BORONC_SRC = src/boronc

BORON_OBJ = $(OBJ_DIR)/boron
BORONPP_OBJ = $(OBJ_DIR)/boronpp
BORONC_OBJ = $(OBJ_DIR)/boronc

# all: dirs boron boronpp boronc

dirs:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

# boron: \
 	$(CC) $(CFLAGS) $(BORON_SRC)/*.c -o $(BIN_DIR)/boron

# boronpp: \
	$(CC) $(CFLAGS) $(BORONPP_SRC)/*.c -o $(BIN_DIR)/boronpp

boronc:
	$(CC) $(CFLAGS) $(BORONC_SRC)/*.c -o $(BIN_DIR)/boronc

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)