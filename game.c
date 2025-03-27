#include <string.h>
#include <stdio.h>
#include "game.h"

#define IN_BOUNDS(i, j) ((i<N) && (j<N))

// Display a mark, returns 'E' if an incorrect mark is passed, as C enums are not typesafe
[[nodiscard]]
char game_mark_show(GameMark const mark) {
    switch (mark) {
    case GAME_EMPTY:
        return ' ';
    case GAME_O:
        return 'O';
    case GAME_X:
        return 'X';
    default:
        (void)fprintf(stderr, "game_mark_show error: invalid mark provided\n");
        return 'E';
    }
}

// Prints the game board to stdout
void game_board_print(GameBoard const board) {
    if (N <= 0) return;
    for (unsigned int i = 0; i < N; i++) printf(" %u  ", i);
    printf("\n");

    printf(" %c ", game_mark_show(board.grid[0][0]));
    for (unsigned int i = 1; i < N; i++) printf("| %c ", game_mark_show(board.grid[0][i]));
    printf(" 0\n");

    for (unsigned int i = 1; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) printf("----");
        printf("\n");
        printf(" %c ", game_mark_show(board.grid[i][0]));
        for (unsigned int j = 1; j < N; j++) {
            printf("| %c ", game_mark_show(board.grid[i][j]));
        }
        printf(" %u\n", i);
    }
}

// Creates a new (empty) board
[[nodiscard]]
GameBoard game_board_init() {
    GameBoard board;
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            board.grid[i][j] = GAME_EMPTY;
        }
    }

    return board;
}
// 
// Creates a new gameboard from an NxN array of marks
[[nodiscard]]
GameBoard game_board_init_with(GameMark const grid[N][N]) {
    GameBoard board;
    // N is assumed to be small enough to be stack allocated, so this copy should never fail
    (void)memcpy(board.grid, grid, N*N*sizeof(GameMark));

    return board;
}

// Returns true iff at least one column on the board has won for the mark
[[nodiscard]]
bool game_any_col(GameBoard const board, GameMark const mark) {
    for (unsigned int i = 0; i < N; i++) {
        bool col_found = true;
        for (unsigned int j = 0; j < N; j++) {
            if (board.grid[i][j] != mark) {
                col_found = false;
                break;
            }
        }
        if (col_found) return true;
    }
    return false;
}

// Returns true iff at least one row on the board has won for the mark
[[nodiscard]]
bool game_any_row(GameBoard const board, GameMark const mark) {
    for (unsigned int i = 0; i < N; i++) {
        bool row_found = true;
        for (unsigned int j = 0; j < N; j++) {
            if (board.grid[j][i] != mark) {
                row_found = false;
                break;
            }
        }
        if (row_found) return true;
    }
    return false;
}

// Returns true iff at least one diagonal on the board has won for the mark
[[nodiscard]]
bool game_any_diag(GameBoard const board, GameMark const mark) {
    bool topleft_to_bottomright_is_mark = true;
    for (unsigned int i = 0; i < N; i++) {
        if (board.grid[i][i] != mark) {
            topleft_to_bottomright_is_mark = false;
            break;
        }
    }
    if (topleft_to_bottomright_is_mark) return true;

    for (unsigned int i = 0; i < N; i++) {
        if (board.grid[i][N-i] != mark) return false;
    }
    return true;
}

// Returns true iff the mark has won on the provided board
[[nodiscard]]
bool game_won(GameBoard const board, GameMark const mark) {
    return game_any_col(board, mark) || game_any_row(board, mark) || game_any_diag(board, mark);
}

// Outputs the mark choice for player 'player_name'. If it's not O xor X outputs EMPTY mark.
[[nodiscard]]
GameMark game_player_mark(char const player_name[]) {
    char mark;
    printf("Player %s please input your preferred mark (O xor X):\n", player_name);
    scanf("%c", &mark);
    switch (mark) {
        case 'O':
            return GAME_O;
        case 'X':
            return GAME_X;
        default:
            return GAME_EMPTY;
    }
}

// Performs a turn for the specified player on the specified board and outputs the new board
[[nodiscard]]
GameBoard game_turn(char const player_name[], GameMark const player_mark, GameBoard board) {
    unsigned int i;
    unsigned int j;
    while (true) {
        printf("Player %s please input your mark location (0-%u,0-%u):\n", player_name, N-1, N-1);
        scanf("%u,%u", &i, &j);
        if (!IN_BOUNDS(i, j)) printf("Mark location out of bounds\n");
        else if (board.grid[j][i]) printf("Mark location already occupied\n");
        else {board.grid[j][i] = player_mark; return board;}
    }
}
