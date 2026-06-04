#include "codegen.hpp"
#include "error.hpp"
#include "lexer.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

int main(int argc, char* argv[]) {

        // open file

        if (argc < 2) {
                std::cerr << "Usage: " << argv[0] << " <source_file>\n";
                return EXIT_FAILURE;
        }

        std::ifstream file(argv[1]);

        if (!file) {
                std::cerr << "Failed to open file\n";
                return EXIT_FAILURE;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        // lexer

        auto result = generate_tokens(buffer.str());

        if (std::holds_alternative<Error>(result)) {
                std::cerr << error_to_string(std::get<Error>(result)) << '\n';
                return EXIT_FAILURE;
        }

        const auto& tokens = std::get<std::vector<Token>>(result);

        // codegen

        CodegenResult asm_result = generate_asm(tokens);

        if (std::holds_alternative<Error>(asm_result)) {
                std::cerr << error_to_string(std::get<Error>(asm_result)) << '\n';
                return EXIT_FAILURE;
        }

        const auto& generated_asm = std::get<std::vector<std::string>>(asm_result);

        for (const auto& line : generated_asm) {
                std::cout << line << '\n';
        }

        return EXIT_SUCCESS;
}