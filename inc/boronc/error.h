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

typedef enum {
        NO_ERROR,
        ILLEGAL_CHARACTER_ERROR
} ErrorType;

typedef struct {
        ErrorType type;
        char* description;
} Error;

Error error_make(const ErrorType type, const char* restrict description);
void error_free(Error* error);
char* error_to_string(const Error error);