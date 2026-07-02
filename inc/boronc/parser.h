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

#include <stddef.h>

#include "boronc/lexer.h"

typedef enum {
        STATEMENT_EXIT
} StatementType;

typedef struct {
        StatementType type;
        int value;
} Statement;

typedef struct {
        Statement* statements;
        size_t size;
        size_t capacity;
} AbstractSyntaxTree;

AbstractSyntaxTree parse(TokenStream tokens, Error* error_ptr);