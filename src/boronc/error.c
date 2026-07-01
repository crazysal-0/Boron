/*
  Boron Compiler
  Copyright (C) 2026 Samuel Little

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  See <LICENSE> for details.
*/

#include "boronc/error.h"

#include <stdio.h>

Error error_make(const ErrorType type, const char* restrict description) {
        return (Error){
            .type = type,
            .description = strdup(description),
        };
}

void error_free(Error* error) {
        free(error->description);
        error->description = NULL;
}

char* error_to_string(Error error) {
        static char buffer[128];

        switch (error.type) {
        case ILLEGAL_CHARACTER_ERROR:
                snprintf(buffer, sizeof(buffer), "IllegalCharacterError: %c", (char)error.description);
                break;

                return buffer;
        }
}