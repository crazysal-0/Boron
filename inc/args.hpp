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

#include <optional>
#include <string>
#include <vector>

struct Args {
        std::string input_file;
        std::string output_file = "out";

        bool show_temp_files = false;
        bool help = false;
};

std::optional<Args> parse_args(int argc, char** argv);