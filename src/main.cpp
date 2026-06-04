#include "args.hpp"
#include "codegen.hpp"
#include "error.hpp"
#include "lexer.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

int main(int argc, char* argv[]) {

        auto args = parse_args(argc, argv);

        if (!args) {
                return EXIT_FAILURE;
        }

        if (args->input_file.empty()) {
                std::cerr << "No input file specified\n";
                return EXIT_FAILURE;
        }

        std::ifstream file(args->input_file);

        if (!file) {
                std::cerr << "Failed to open file\n";
                return EXIT_FAILURE;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        auto lexer_result = generate_tokens(buffer.str());

        if (std::holds_alternative<Error>(lexer_result)) {
                std::cerr << error_to_string(std::get<Error>(lexer_result)) << '\n';

                return EXIT_FAILURE;
        }

        const auto& tokens = std::get<std::vector<Token>>(lexer_result);

        auto asm_result = generate_asm(tokens);

        if (std::holds_alternative<Error>(asm_result)) {
                std::cerr << error_to_string(std::get<Error>(asm_result)) << '\n';

                return EXIT_FAILURE;
        }

        const auto& generated_asm = std::get<std::vector<std::string>>(asm_result);

        std::ofstream asm_file(args->output_file + ".asm");

        if (!asm_file) {
                std::cerr << "Failed to open assembly file\n";
                return EXIT_FAILURE;
        }

        for (const auto& line : generated_asm) {
                asm_file << line << '\n';
        }

        asm_file.close();

        std::string asm_command = "nasm -f elf64 " + args->output_file + ".s -o " + args->output_file + ".o";

        if (std::system(asm_command.c_str()) != 0) {
                std::cerr << "Assembler failed\n";
                return EXIT_FAILURE;
        }

        std::string link_command = "g++ -fuse-ld=mold -nostdlib -o " + args->output_file + " " + args->output_file + ".o";

        if (std::system(link_command.c_str()) != 0) {
                std::cerr << "Linker failed\n";
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}