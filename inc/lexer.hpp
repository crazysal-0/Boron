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

#pragma once

#include "error.hpp"

#include <optional>
#include <string>
#include <variant>
#include <vector>

enum class TokenType { _EXIT, INTEGER, NEWLINE };

static constexpr const char* token_type_to_string(TokenType type) {
        switch (type) {
                case TokenType::_EXIT:
                        return "EXIT";
                case TokenType::INTEGER:
                        return "INTEGER";
                case TokenType::NEWLINE:
                        return "NEWLINE";
        }
        return "UNKNOWN";
};

struct Token {
        TokenType type;
        std::optional<std::string> value;

        std::string to_string() const {
                if (!value) {
                        return token_type_to_string(type);
                }

                return std::string(token_type_to_string(type)) + ":" + *value;
        }
};

using LexerResult = std::variant<std::vector<Token>, Error>;

LexerResult generate_tokens(const std::string& source);