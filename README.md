# Boron
This is a compiler for a language I'm making! It was originally made in C++ but I started to forget my own codebase so I switched to c were there are ways to do things. It is going to be inspired by Lua and is meant to be used for making CLIs.

## Style
Snake_case for functions and variables. \
PascalCase for enums, typdef macros, structs. \
SCREEN_CASE for constants, #define macros, and enum members.
for constructors do the struct name and add _free
for destructors add _free to the struct name
if a function has unfreed memory, make a function with the name + _free that frees it. I know you dont really need cause the os clears the memory after the program stops anyway, but I think I will anyway

## License
GPLv3 — see LICENSE