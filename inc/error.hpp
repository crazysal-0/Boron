#pragma once

#include <string>

enum class ErrorType {
        IllegalCharacterError,
};

struct Error {
        ErrorType type;
        std::string description;
};

std::string error_to_string(const Error& error);