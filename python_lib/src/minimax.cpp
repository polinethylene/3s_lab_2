#include "minimax.h"
#include <iostream>
#include "Board.h"

int ALPHA = -1000;
int BETA = 1000;

bool inRow(int a,int b,int c) {
    return (a==b && b==c && c==a && a!=0);
}

int isEnd(Board &board, int r_move, int c_move) {
    int size = board.GetSize();
    int min_r = (r_move > 2) ? r_move-2 : 0;
    int max_r = (r_move < size-3) ? r_move+2 : size-1;
    int min_c = (c_move > 2) ? c_move-2 : 0;
    int max_c = (c_move < size-3) ? c_move+2 : size-1;

    for (int i=min_r; i<max_r+1; i++) {
        for (int j=min_c; j<max_c+1-2; j++) {
            if (inRow(board(i,j), board(i,j+1), board(i,j+2))) {
                return -board(i,j);
            }
        }
    }
    for (int i=min_c; i<max_c+1; i++) {
        for (int j=min_r; j<max_r+1-2; j++) {
            if (inRow(board(j,i), board(j+1,i), board(j+2,i))) {
                return -board(j,i);
            }
        }
    }

    int l = 3;
    while(l--!=0 && min_r<size-2 && min_c<size-2 && max_r>1 && max_c>1) {
        if (inRow(board(min_r,min_c), board(min_r + 1,min_c+1), board(min_r + 2,min_c+2))) {
            return -board(min_r,min_c);
        }
        if (inRow(board(max_r,min_c), board(max_r-1,min_c+1), board(max_r-2,min_c+2))) {
            return -board(max_r,min_c);
        }
        min_r++;
        min_c++;
        max_r--;
        max_c--;
    }

    if (board.GetTurn() == size*size) {
        return 0;
    }
    return 2;
}

int minimax(Board board, int depth, bool max, int r_move, int c_move) {
    int result = board.isEnd(r_move,c_move);
//    int result = isEnd(board, r_move, c_move);
    if (result != 2) {
        return result;
    }
    int BOARDSIZE = board.GetSize();
    if (max) {
        int bestscore = -1000;
        for (int i=0; i<BOARDSIZE; i++) {
            for (int j=0; j<BOARDSIZE; j++) {
                if(board(i,j) == 0) {
                    board.MakeMove(i,j,-1);
                    int score = minimax(board, depth+1, false, i, j);
                    board.UndoMove(i,j);
                    if (score > bestscore) {
                        bestscore = score;
                    }
//                    a = std::max(a,score);
//                    if (b<=a) {
//                        break;
//                    }
                }
            }
        }
        return bestscore;
    } else {
        int bestscore = 1000;
        for (int i=0; i<BOARDSIZE; i++) {
            for (int j=0; j<BOARDSIZE; j++) {
                if(board(i,j) == 0) {
                    board.MakeMove(i,j,1);
                    int score = minimax(board, depth+1, true, i, j);
                    board.UndoMove(i,j);
                    if (score < bestscore) {
                        bestscore = score;
                    }
//                    b = std::min(b,score);
//                    if (b<=a) {
//                        break;
//                    }
                }
            }
        }
        return bestscore;
    }
}

int bestChoice(Board board) {
    int bestscore = -1000;
    int r_move, c_move;
    int BOARDSIZE = board.GetSize();
    for (int i=0; i<BOARDSIZE; i++) {
        for (int j=0; j<BOARDSIZE; j++) {
            if(board(i,j) == 0) {
                board.MakeMove(i,j,-1);
                int score = minimax(board, 0, false,i,j);
                board.UndoMove(i,j);
                if (score > bestscore) {
                    bestscore = score;
                    r_move = i;
                    c_move = j;
                }
            }
        }
    }
    board.MakeMove(r_move,c_move,-1);
    return 0;
}