#include "args.hpp"

#include <iostream>

std::optional<Args> parse_args(int argc, char** argv) {
        Args args;

        for (int i = 1; i < argc; ++i) {
                std::string arg = argv[i];

                if (arg == "-o") {

                        if (i + 1 >= argc) {
                                std::cerr << "error: missing output file after -o\n";
                                return std::nullopt;
                        }

                        args.output_file = argv[++i];
                }

                else if (arg == "--showtempfiles") {
                        args.show_temp_files = true;
                }

                else if (arg == "-h" || arg == "--help") {
                        args.help = true;
                }

                else if (!arg.empty() && arg[0] == '-') {
                        std::cerr << "error: unknown option '" << arg << "'\n";
                        return std::nullopt;
                }

                else {
                        if (!args.input_file.empty()) {
                                std::cerr << "error: multiple input files\n";
                                return std::nullopt;
                        }

                        args.input_file = arg;
                }
        }

        return args;
}