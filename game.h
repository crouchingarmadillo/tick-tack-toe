#ifndef GAME_H
#define GAME_H
#define N 3

typedef enum {
  GAME_EMPTY,
  GAME_O,
  GAME_X,
} GameMark;

typedef struct {
  GameMark grid[N][N];
} GameBoard;

char game_mark_show(GameMark const mark);

GameBoard game_board_init();

GameBoard game_board_init_with(GameMark const grid[N][N]);

void game_board_print(GameBoard const grid);

bool game_won(GameBoard const board, GameMark const mark);

GameMark game_player_mark(char const player_name[]);

GameBoard game_turn(char const player_name[], GameMark const player_mark, GameBoard board);

#endif
