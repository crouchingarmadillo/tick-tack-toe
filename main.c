#include <stdlib.h>
#include <stdio.h>
#include "game.h"


int main() {
  GameBoard board = game_board_init();
  while (true) {
    GameMark player0_mark;
    while (!(player0_mark = game_player_mark("0")));
    GameMark player1_mark = player0_mark==GAME_O ? GAME_X : GAME_O;
    constexpr bool PLAYER0 = false;
    constexpr bool PLAYER1 = true;
    bool turn = PLAYER0;

    while(!game_won(board, GAME_O) && !game_won(board, GAME_X)) {
      game_board_print(board);
      if (turn == PLAYER1) board = game_turn("1", player1_mark, board);
      else board = game_turn("0", player0_mark, board);
      turn = !turn;
    }

    game_board_print(board);
    GameMark winning_mark = game_won(board, GAME_O) ? GAME_O : GAME_X;
    if (player0_mark == winning_mark) return printf("Player 0 won!\n");
    else return printf("Player 1 won!\n");
  }
  return EXIT_SUCCESS;
}
