#include <iostream>
#include "minimax.h"
#include "Board.h"

using namespace std;

char toString(int a) {
    if (a == 1) {
        return '#';
    } else if (a == -1) {
        return '0';
    } else {
        return '_';
    }
}

void print(Board& board) {
    int BOARDSIZE = board.GetSize();
    for (int i=0; i<BOARDSIZE; i++) {
        for (int j=0; j<BOARDSIZE; j++){
            cout << toString(board(i,j)) << " ";
        }
        cout << endl;
    }
}

int main() {
    int boardsize = 3;
    cout << "Enter n: ";
    cin >> boardsize;
    Board board = Board(boardsize);

    int r_move = 0, c_move = 0;
    while (true) {
        cin >> r_move;
        cin >> c_move;
        if (r_move < boardsize && c_move < boardsize) {
            board.MakeMove(r_move, c_move, 1);
            print(board);
            cout << "----------------------\n";
            if (isEnd(board,r_move,c_move)!=2) {
                if (isEnd(board,r_move,c_move)!=0){
                    cout << "# Wins\n";
                } else {
                    cout << "Draw\n";
                }
                break;
            }
        }
        vector<int> move = board.bestChoice<int>();

        print(board);
        if (board.isEnd(r_move,c_move)!=2) {
            if (board.isEnd(r_move,c_move)!=0){
                cout << "0 Wins\n";
            } else {
                cout << "Draw\n";
            }
            break;
        }
    }

    return 0;
}
