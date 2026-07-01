#include <stdio.h>
#include <stdlib.h>

#include "boronc/codegen.h"
#include "boronc/error.h"
#include "boronc/lexer.h"

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

static void write_file(const char* path, StringArray* arr) {
        FILE* f = fopen(path, "w");
        if (!f)
                return;

        for (size_t i = 0; i < arr->size; i++) {
                fprintf(f, "%s\n", arr->data[i]);
        }

        fclose(f);
}

int main(int argc, char** argv) {
        if (argc < 2) {
                fprintf(stderr, "usage: boronc <file>\n");
                return 1;
        }

        char* source = read_file(argv[1]);
        if (!source) {
                fprintf(stderr, "read error\n");
                return 1;
        }

        Error err = {0};
        TokenStream tokens = tokenize(source, &err);

        if (err.type != 0) {
                fprintf(stderr, "%s\n", error_to_string(err));
                free(source);
                return 1;
        }

        StringArray asm_out = generate_asm(tokens);

        write_file("out.asm", &asm_out);

        tokenstream_free(&tokens);
        string_array_free(&asm_out);
        free(source);

        return 0;
}