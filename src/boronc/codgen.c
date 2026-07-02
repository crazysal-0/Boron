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

#include "boronc/codegen.h"
#include "boronc/lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boronc/codegen.h"
#include "boronc/lexer.h"

void generate_asm(TokenStream tokens) {
        size_t index = 0;

        printf("section .text\n");
        printf("        global _start\n");
        printf("\n");
        printf("_start:\n");

        while (index < tokens.size) {
                Token current = tokens.data[index];

                if (current.type == EXIT) {
                        printf("        mov rax, 60\n");

                        if (index + 1 < tokens.size) {
                                printf("        mov rdi, %s\n", tokens.data[index + 1].value);
                                index++;
                        }

                        printf("        syscall\n");
                }

                index++;
        }
}