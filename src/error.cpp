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

#include "error.hpp"

std::string error_to_string(const Error& error) {
        switch (error.type) {
                case ErrorType::IllegalCharacterError:
                        return "Illegal Character: " + error.description;
                default:
                        return "Unknown Error";
        }
}