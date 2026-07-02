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
#include <string.h>

#include "boronc/lexer.h"
#include "boronc/parser.h" z

#include <stdio.h>
#include <stdlib.h>

#include "boronc/error.h"
#include "boronc/lexer.h"
#include "boronc/parser.h"

static void ast_init(AbstractSyntaxTree* ast) {
        ast->statements = NULL;
        ast->size = 0;
        ast->capacity = 0;
}

static int ast_push(AbstractSyntaxTree* ast, Statement statement) {
        if (ast->size >= ast->capacity) {
                size_t new_capacity;

                if (ast->capacity == 0) {
                        new_capacity = 8;
                } else {
                        new_capacity = ast->capacity * 2;
                }

                Statement* new_data = realloc(ast->statements, new_capacity * sizeof(Statement));

                if (new_data == NULL) {
                        return 0;
                }

                ast->statements = new_data;
                ast->capacity = new_capacity;
        }

        ast->statements[ast->size] = statement;
        ast->size = ast->size + 1;

        return 1;
}

AbstractSyntaxTree parse(TokenStream tokens, Error* error_ptr) {
        AbstractSyntaxTree ast;
        ast_init(&ast);

        size_t index = 0;

        while (index < tokens.size) {
                Token current = tokens.data[index];

                if (current.type == EXIT) {
                        if (index + 1 >= tokens.size) {
                                if (error_ptr != NULL) {
                                        *error_ptr = error_make(SYNTAX_ERROR, "missing expression after exit");
                                }

                                goto error;
                        }

                        Token next = tokens.data[index + 1];

                        if (next.type != INTEGER_LITERAL) {
                                if (error_ptr != NULL) {
                                        *error_ptr = error_make(SYNTAX_ERROR, "expected integer literal after exit");
                                }

                                goto error;
                        }

                        Statement statement;
                        statement.type = STATEMENT_EXIT;
                        statement.value = atoi(next.value);

                        if (!ast_push(&ast, statement)) {
                                if (error_ptr != NULL) {
                                        *error_ptr = error_make(SYNTAX_ERROR, "out of memory");
                                }

                                goto error;
                        }

                        index = index + 2;
                        continue;
                }

                index = index + 1;
        }

        return ast;

error:
        free(ast.statements);
        ast.statements = NULL;
        ast.size = 0;
        ast.capacity = 0;

        return ast;
}