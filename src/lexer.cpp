/*
 * Boron Compiler
 * Copyright (C) 2026 Samuel Little
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * See <LICENSE> for details.
 */

#include "lexer.hpp"
#include "error.hpp"

#include <string>
#include <variant>
#include <vector>

LexerResult generate_tokens(const std::string& source) {
        std::vector<Token> tokens;
        size_t index = 0;

        while (index < source.length()) {
                char current_char = source[index];

                if (current_char == ' ' || current_char == '\t') {
                        index++;
                } else if (current_char == '\n') {
                        tokens.push_back({TokenType::NEWLINE});
                        index++;
                } else if (isalpha(current_char)) {
                        std::string word;

                        while (index < source.length() && isalpha(source[index])) {
                                word += source[index];
                                index++;
                        }

                        if (word == "exit") {
                                tokens.push_back({TokenType::_EXIT, word});
                        }

                } else if (isdigit(current_char)) {
                        std::string number;

                        while (index < source.length() && isdigit(source[index])) {
                                number += source[index];
                                index++;
                        }

                        tokens.push_back({TokenType::INTEGER, number});

                } else {
                        return Error{ErrorType::IllegalCharacterError, "Unexpected character: " + std::string(1, current_char)};
                }
        }

        return LexerResult(tokens);
}