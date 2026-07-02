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

#include "boronc/lexer.h"

typedef struct {
        char** data;
        size_t size;
        size_t capacity;
} StringArray;

void generate_asm(TokenStream tokens);
void generate_asm_free(StringArray* assembly);