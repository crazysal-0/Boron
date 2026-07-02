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

#include "boronc/parser.h"

void generate_asm(AbstractSyntaxTree ast) {
        printf("section .text\n");
        printf("        global _start\n\n");
        printf("_start:\n");

        size_t index = 0;

        while (index < ast.size) {
                Statement statement = ast.statements[index];

                if (statement.type == STATEMENT_EXIT) {
                        printf("        mov rax, 60\n");
                        printf("        mov rdi, %d\n", statement.value);
                        printf("        syscall\n");
                }

                index++;
        }
}