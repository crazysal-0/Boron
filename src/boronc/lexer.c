#include "boronc/lexer.h"
#include "boronc/error.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Token token_make(TokenType type, const char* value) {
        char* copy = NULL;

        if (value != NULL) {
                size_t len = strlen(value);

                copy = malloc(len + 1);
                if (copy != NULL) {
                        memcpy(copy, value, len);
                        copy[len] = '\0';
                }
        }

        Token token;
        token.type = type;
        token.value = copy;

        return token;
}

void token_free(Token* token) {
        if (!token) {
                return;
        }

        free(token->value);
        token->value = NULL;
}

void tokenstream_init(TokenStream* ts) {
        ts->data = NULL;
        ts->size = 0;
        ts->capacity = 0;
}

int tokenstream_push(TokenStream* ts, Token token) {
        if (ts->size >= ts->capacity) {
                size_t new_cap = ts->capacity == 0 ? 8 : ts->capacity * 2;

                Token* new_data = realloc(ts->data, new_cap * sizeof(Token));
                if (!new_data) {
                        return 0;
                }

                ts->data = new_data;
                ts->capacity = new_cap;
        }

        ts->data[ts->size] = token;
        ts->size = ts->size + 1;

        return 1;
}

void tokenstream_free(TokenStream* ts) {
        if (!ts || !ts->data) {
                return;
        }

        for (size_t i = 0; i < ts->size; i++) {
                token_free(&ts->data[i]);
        }

        free(ts->data);

        ts->data = NULL;
        ts->size = 0;
        ts->capacity = 0;
}

TokenStream tokenize(const char* src, Error* error_ptr) {
        TokenStream ts;
        tokenstream_init(&ts);

        size_t i = 0;

        while (src[i] != '\0') {
                char c = src[i];

                if (c == ' ' || c == '\t') {
                        i = i + 1;
                        continue;
                }

                if (c == '\n') {
                        if (!tokenstream_push(&ts, token_make(NEWLINE, NULL))) {
                                goto error;
                        }

                        i = i + 1;
                        continue;
                }

                /* INTEGER LITERAL (NOW STORED AS STRING) */
                if (isdigit((unsigned char)c)) {
                        size_t start = i;

                        while (isdigit((unsigned char)src[i])) {
                                i = i + 1;
                        }

                        size_t len = i - start;

                        char* buf = malloc(len + 1);
                        if (!buf) {
                                goto error;
                        }

                        memcpy(buf, src + start, len);
                        buf[len] = '\0';

                        int ok = tokenstream_push(&ts, token_make(INTEGER_LITERAL, buf));

                        free(buf);

                        if (!ok) {
                                goto error;
                        }

                        continue;
                }

                /* IDENTIFIERS / KEYWORDS */
                if (isalpha((unsigned char)c)) {
                        size_t start = i;

                        while (isalpha((unsigned char)src[i])) {
                                i = i + 1;
                        }

                        size_t len = i - start;

                        char* buf = malloc(len + 1);
                        if (!buf) {
                                goto error;
                        }

                        memcpy(buf, src + start, len);
                        buf[len] = '\0';

                        if (strcmp(buf, "exit") == 0) {
                                free(buf);

                                if (!tokenstream_push(&ts, token_make(EXIT, NULL))) {
                                        goto error;
                                }

                                continue;
                        }

                        free(buf);

                        if (error_ptr) {
                                char tmp[2] = {c, '\0'};
                                *error_ptr = error_make(ILLEGAL_CHARACTER_ERROR, tmp);
                        }

                        goto error;
                }

                /* UNKNOWN CHARACTER */
                if (error_ptr) {
                        char tmp[2] = {c, '\0'};
                        *error_ptr = error_make(ILLEGAL_CHARACTER_ERROR, tmp);
                }

                goto error;
        }

        return ts;

error:
        tokenstream_free(&ts);
        return (TokenStream){0};
}