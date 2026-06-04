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

#include "codegen.hpp"
#include "error.hpp"
#include "lexer.hpp"

#include <string>
#include <vector>

CodegenResult generate_asm(const std::vector<Token>& tokens) {
        std::vector<std::string> generated_asm;

        generated_asm.push_back("section .text");
        generated_asm.push_back("        global _start");
        generated_asm.push_back("_start:");

        size_t index = 0;

        while (index < tokens.size()) {
                const auto& token = tokens[index];

                if (token.type == TokenType::_EXIT) {

                        if (index + 1 >= tokens.size()) {
                                return Error{ErrorType::SyntaxError, "expected INTEGER after _EXIT"};
                        }

                        if (tokens[index + 1].type != TokenType::INTEGER) {
                                return Error{ErrorType::SyntaxError, "expected INTEGER after _EXIT"};
                        }

                        generated_asm.push_back("        mov rax, 60");
                        generated_asm.push_back("        mov rdi, " + *tokens[index + 1].value);
                        generated_asm.push_back("        syscall");

                        index += 2;
                        continue;
                }

                if (token.type != TokenType::NEWLINE) {
                        return Error{ErrorType::SyntaxError, "expected _EXIT or NEWLINE, got " + token.to_string()};
                }

                index++;
        }

        return {generated_asm};
}