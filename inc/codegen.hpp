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
#include "lexer.hpp"

#include <string>
#include <vector>

#include <variant>

using CodegenResult = std::variant<std::vector<std::string>, Error>;
CodegenResult generate_asm(const std::vector<Token>& tokens);