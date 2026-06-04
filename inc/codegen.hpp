#pragma once

#include "error.hpp"
#include "lexer.hpp"

#include <string>
#include <vector>

#include <variant>

using CodegenResult = std::variant<std::vector<std::string>, Error>;
CodegenResult generate_asm(const std::vector<Token>& tokens);