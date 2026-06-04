#include "error.hpp"

std::string error_to_string(const Error& error) {
        switch (error.type) {
                case ErrorType::IllegalCharacterError:
                        return "Illegal Character: " + error.description;
                default:
                        return "Unknown Error";
        }
}