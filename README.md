# tick-tack-toe

This is a very basic terminal tick-tack-toe game. It was written primarily as an exercise to the author in writing C, with the goal of learning best practices for C. 
The author still needs to learn cmake and unit testing, but considers the rest quite successful.

The author was careful, but due to the lack of unit tests, there may be lingering bugs. Only very basic functionality was tested explicitly. 

## Features
- ASCII board
- Board marks of 'O' xor 'X'
- 2 players
- Different board sizes (default is 3x3 but may be changed with N parameter in game.h)
- Indices marking the board positions

It would be reasonble to refactor to allow different board mark options.
Or to allow different board sizes dynamically (the easiest solution would be to just use VLAs, but the author wished to avoid VLAs).
The author avoided this in the interest of keeping the project and its implementation as simple as possible.

## Building
The project was written in a proper subset of C++ and ensured to compile under both C++20 and C23.
The project is simple enough that it may be compiled manually using a C++ compiler that supports C++20 or a C compiler that supports C23.

### Make
If one has g++ and clang-19 then it is easiest to compile using the make file. One only needs to run
```
make
```
and an executable named `game` will be created.

### C
To compile using a C compiler, be sure it supports C23 and compile with the options `-Wall, -Werror, -Wextra, -pedantic`.
Using clang-19 for instance.
```
clang-19 -Wall -Wextra -Werror -pedantic -std=c23 -o game game.c main.c
```
The options other than the standard are not strictly necessary. But they are recommended to ensure strict adherence to the standard, and avoidance of many common errors.

### C++
To compile using a C++ compiler, be sure it supports C++20 and compile with the same options as for C.
Using g++ for instance.
```
g++ -Wall -Wextra -Werror -pedantic -std=c++20 -o game game.c main.c
```
