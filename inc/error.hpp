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

#include <string>

enum class ErrorType {
        IllegalCharacterError,
        SyntaxError,
};

struct Error {
        ErrorType type;
        std::string description;
};

std::string error_to_string(const Error& error);