game: main.c game.c game.h
	g++ -std=c++20 -Wall -Wextra -Werror -pedantic game.c main.c && rm a.out && clang-19 -std=c23 -Wall -Wextra -Werror -pedantic -o game game.c main.c

