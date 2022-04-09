#ifndef INC_2S_LAB2_MINIMAX_H
#define INC_2S_LAB2_MINIMAX_H

#include "Board.h"

bool inRow(int a,int b,int c);
int isEnd(Board &board, int r_move, int c_move);
int minimax(Board board, int depth, bool max, int r_move, int c_move);
int bestChoice(Board board);

#endif //INC_2S_LAB2_MINIMAX_H
