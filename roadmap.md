# Boron Roadmap
This is the roadmap for Boron, it is subject to change, but this is the general plan for how I want to develop the language. I will be working on it in my free time, so it might take a bit to finish.

## Phase 1 - Core Execution ✓
- Exit codes
- Lexer
- Error handling

This phase just getting a compiler working, so I can add features later.

## Phase 2 - Parsing
- Parser
- A grammar rules file

In this phase I want to make a simple parser, because last time adding parsers with a ton of features was not a good idea so I am making a simple one so I can add on top of it.

## Phase 3 - Language Core
- Variables
- Math
- If statements
- While loops
- For loops

This phase will take a while, but once done I have everything I need to add on to it, except for functions, which will be in the next phase.

## Phase 5 - Language Model Decision
- Pick how my lannguage handles state and side effects

I will have to go back and edit stuff based on this, so I want to do it before I have to rewrite the compiler. The paradigm I want is to have it be imperative language with purity inference But I might change my mind. 

## Phase 4 - Functions
- Function definitions
- Function calls
- Return values

Now this is where the language feels complete, everything past here is just adding more features, the core syntax will be almost done.

## Phase 6 - Tooling + Safety
- Better error reporting
- VERY simple preprocessor (just with macros and includes, very very very simple)

Make the error messsages consistant, and add a preproccesor like in c so I can use macros and includes, so people wont have to just use one file or use cpp before compiling code.

## Phase 7 - Arrays and Hashmaps
- Arrays
- Hashmaps
- Foreach

Pretty self explanatory.

## Phase 7 - Standard Library
- Basic I/O
- Core utilities

This will take a bit... I will make a standard library with basic I/O, and string stuff. Maybe like a way to cast strings to numbers and stuff like that. Maybe even a math library with trig functions and stuff, but that is a maybe.

## Phase 8 - Final Touches
- VSCode extension
- Documentation
- Make errors even better

This is the final phase, after this phase I will release the language, and keep on polishing it. Some other stuff i might add after this is a package manager, or a raylib wrapper.