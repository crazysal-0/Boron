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