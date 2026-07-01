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

void string_array_init(StringArray* array) {
        array->data = NULL;
        array->size = 0;
        array->capacity = 0;
}

int string_array_push(StringArray* array, const char* value) {
        if (array->size >= array->capacity) {
                size_t new_capacity = array->capacity == 0 ? 8 : array->capacity * 2;

                char** new_data = realloc(array->data, new_capacity * sizeof(char*));

                if (new_data == NULL) {
                        return 0;
                }

                array->data = new_data;
                array->capacity = new_capacity;
        }

        array->data[array->size] = strdup(value);

        if (array->data[array->size] == NULL) {
                return 0;
        }

        array->size++;
        return 1;
}

void string_array_free(StringArray* array) {
        if (array->data == NULL) {
                return;
        }

        for (size_t i = 0; i < array->size; i++) {
                free(array->data[i]);
        }

        free(array->data);

        array->data = NULL;
        array->size = 0;
        array->capacity = 0;
}

StringArray generate_asm(TokenStream tokens) {
        StringArray cg;
        size_t index = 0;

        string_array_init(&cg);

        string_array_push(&cg, "section .text");
        string_array_push(&cg, "        global _start");
        string_array_push(&cg, "");
        string_array_push(&cg, "_start:");

        while (index < tokens.size) {
                Token current = tokens.data[index];

                if (current.type == EXIT) {
                        char buffer[64];

                        string_array_push(&cg, "        mov rax, 60");

                        snprintf(buffer, sizeof(buffer), "        mov rdi, %s", tokens.data[index + 1].value);

                        string_array_push(&cg, buffer);
                        string_array_push(&cg, "        syscall");

                        index++;
                }

                index++;
        }

        return cg;
}

void generate_asm_free(StringArray* array) { string_array_free(array); }