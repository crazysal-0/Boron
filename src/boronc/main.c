/*
  Boron Compiler
  Copyright (C) 2026 Samuel Little

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  See <LICENSE> for details.
*/

#include <stdio.h>
#include <stdlib.h>

#include "boronc/codegen.h"
#include "boronc/error.h"
#include "boronc/lexer.h"
#include "boronc/parser.h"

static char* read_file(const char* path) {
        FILE* f = fopen(path, "rb");
        if (!f)
                return NULL;

        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        rewind(f);

        char* buffer = malloc(size + 1);
        if (!buffer) {
                fclose(f);
                return NULL;
        }

        fread(buffer, 1, size, f);
        buffer[size] = '\0';

        fclose(f);
        return buffer;
}

int main(int argc, char** argv) {
        if (argc < 2) {
                fprintf(stderr, "usage: boronc <file>\n");
                return 1;
        }

        char* source = read_file(argv[1]);
        if (!source) {
                fprintf(stderr, "error: could not read file\n");
                return 1;
        }

        Error err = {
            .type = NO_ERROR,
            .description = NULL,
        };

        TokenStream tokens = tokenize(source, &err);

        if (err.type != NO_ERROR) {
                fprintf(stderr, "%s\n", error_to_string(err));

                error_free(&err);
                free(source);

                return 1;
        }

        AbstractSyntaxTree ast = parse(tokens, &err);

        generate_asm(ast);

        free(source);

        return 0;
}