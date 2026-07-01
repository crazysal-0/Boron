/*
  Boron Compiler
  Copyright (C) 2026 Samuel Little

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  See <LICENSE> for details.
*/

#pragma once

#include "boronc/error.h"
#include <stddef.h>

typedef enum {
        EXIT,
        INTEGER_LITERAL,
        NEWLINE,
} TokenType;

typedef struct {
        TokenType type;
        char* value;
} Token;

typedef struct {
        Token* data;
        size_t size;
        size_t capacity;
} TokenStream;

Token token_make(TokenType type, const char* value);
void token_free(Token* token);

void tokenstream_init(TokenStream* ts);
int tokenstream_push(TokenStream* ts, Token token);
void tokenstream_free(TokenStream* ts);

TokenStream tokenize(const char* src, Error* error_ptr);