#ifndef LAB_2_MATRIX_H
#define LAB_2_MATRIX_H

#include <iostream>
#include <cmath>


class Board {
private:
    int* data;
    int size;
    int turn;
    int maxdepth;
public:

    Board() : data() {
        data = new int[1];
        size = 0;
        turn = 0;
        maxdepth = 10;
    }

    template<class X>
    Board(std::vector<X> items, int size) : size(size) {
        turn = 0;
        data = new int[size*size];
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                data[i * size + j] = items[i * size + j];
            }
        }
        maxdepth = 10;
    }

    Board(int size) : size(size){
        turn = 0;
        data = new int[size*size];
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                data[i * size + j] = 0;
            }
        }
        maxdepth = 10;
    }

    int GetSize() {
        return size;
    }

    int GetTurn() {
        return turn;
    }

    int &operator()(int row, int column) {
        assert(column >= 0 && column < size);
        assert(row >= 0 && row < size);
        return data[row * size + column];
    }

    ~Board() { delete[] data; }

    void MakeMove(int row, int column, int v) {
        data[row * size + column] = v;
        turn += 1;
    }

    void UndoMove(int row, int column) {
        data[row * size + column] = 0;
        turn -= 1;
    }

    bool inRow(int a,int b,int c) {
        return (a==b && b==c && a!=0);
    }

    bool isPossibleWin(int a,int b,int c) {
        return ((a==c && b==0 && a!=0) || (a==b && c==0 && a!=0) || (c==b && a==0 && b!=0));
    }

    int rollout() {
        int res = 0;
        for (int i=0; i<size; i++) {
            for (int j=0; j<size-2; j++) {
                if (isPossibleWin(data[i*size+j], data[i*size+j+1], data[i*size+j+2])) {
                    int move = (data[i*size+j] == 0) ? data[i*size+j+1] : data[i*size+j];
                    if(move == 1){
                        return -1;
                    } else {
                        res+=1;
                    }
                }
            }
        }
        for (int i=0; i<size; i++) {
            for (int j=0; j<size-2; j++) {
                if (isPossibleWin(data[j*size+i], data[(j+1)*size+i], data[(j+2)*size+i])) {
                    int move = (data[j*size+i] == 0) ? data[(j+1)*size+i] : data[j*size+i];
                    if(move == 1){
                        return -1;
                    } else {
                        res+=1;
                    }
                }
            }
        }

        for (int min_r = 0; min_r<size-2; min_r++) {
            for (int max_r = size-1; max_r>1; max_r--){
                if (isPossibleWin(data[(max_r-2)*size+min_r], data[(1 + max_r-2)*size+min_r+1],
                                  data[(2 + max_r-2)*size+min_r+2])) {
                    int move = (data[(max_r-2)*size+min_r] == 0) ? data[(1+max_r-2)*size+min_r+1]
                            : data[(max_r-2)*size+min_r];
                    if(move == 1){
                        return -1;
                    } else {
                        res+=1;
                    }
                }
                int m = max_r*size+min_r, n = (max_r-1)*size+min_r+1, l = (max_r-2)*size+min_r+2;
//                std::cout << max_r << ' ' << min_r << '\n';
//                std::cout << m << ' ' << n << ' ' << l << '\n';
                if (isPossibleWin(data[m], data[n], data[l])) {
                    int move = (data[max_r*size+min_r] == 0) ? data[(max_r-1)*size+min_r+1] : data[max_r*size+min_r];
                    if(move == 1){
                        return -1;
                    } else {
                        res+=1;
                    }
                }
            }
        }

        return res;
    }

    int isEnd(int r_move, int c_move) {
        int min_r = (r_move > 2) ? r_move-2 : 0;
        int max_r = (r_move < size-3) ? r_move+2 : size-1;
        int min_c = (c_move > 2) ? c_move-2 : 0;
        int max_c = (c_move < size-3) ? c_move+2 : size-1;

        for (int i=min_r; i<max_r+1; i++) {
            for (int j=min_c; j<max_c+1-2; j++) {
                std::cout << i << ' ' << j << '\n';
                if (inRow(data[i*size+j], data[i*size+j+1], data[i*size+j+2])) {
                    return -data[i*size+j];
                }
            }
        }
        for (int i=min_c; i<max_c+1; i++) {
            for (int j=min_r; j<max_r+1-2; j++) {
                std::cout << i << ' ' << j << '\n';
                if (inRow(data[j*size+i], data[(j+1)*size+i], data[(j+2)*size+i])) {
                    return -data[j*size+i];
                }
            }
        }

        for (int i = min_c; i<max_c-1; i++) {
            for (int j = max_r; j>min_r+1; j--){
//            std::cout << (j-2)*size+i << ' ' << (1+j-2)*size+i+1 << ' ' << (2+j-2)*size+i+2 << '\n';
            if (inRow(data[(j-2)*size+i], data[(1+j-2)*size+i+1], data[(2+j-2)*size+i+2])) {
                return -data[(j-2)*size+i];
            }
            std::cout << j*size+i << ' ' << (j-1)*size+i+1 << ' ' << (j-2)*size+i+2 << '\n';
            if (inRow(data[j*size+i], data[(j-1)*size+i+1], data[(j-2)*size+i+2])) {
                return -data[j*size+i];
            }
            }
        }

        if (turn == size*size) {
            return 0;
        }
        return 2;
    }


    int minimax(int depth, bool max, int a, int b, int r_move, int c_move) {
        int result = isEnd(r_move,c_move);
        if (result != 2) {
            return result * (maxdepth-depth);
        }
        int roll = 0;
        if (turn>3) {
            roll = rollout();
            if (depth == (maxdepth-1)) {
                return roll;
            }
        }

        if (max) {
            int bestscore = -1000;
            if (roll >= 1) {
                return 1 * ((maxdepth-1)-depth);
            }
            for (int i=0; i<size; i++) {
                for (int j=0; j<size; j++) {
                    if(data[i*size+j] == 0) {
                        MakeMove(i,j,-1);
                        int score = minimax(depth+1, false, a, b, i, j);
                        UndoMove(i,j);
                        if (score > bestscore) {
                            bestscore = score;
                        }
                        a = std::max(a,bestscore);
                        if (b<=a) {
                            break;
                        }
                    }
                }
            }
            return bestscore;
        } else {
            int bestscore = 1000;
            if (roll == -1) {
                return roll * ((maxdepth-1)-depth);
            }
            for (int i=0; i<size; i++) {
                for (int j=0; j<size; j++) {
                    if(data[i*size+j] == 0) {
                        MakeMove(i,j,1);
                        int score = minimax(depth+1, true, a, b, i, j);
                        UndoMove(i,j);
                        if (score < bestscore) {
                            bestscore = score;
                        }
                        b = std::min(b,bestscore);
                        if (b<=a) {
                            break;
                        }
                    }
                }
            }
            return bestscore;
        }
    }

    int CountNeighbours(int r, int c) {
        int res = 0;
        if (r>0) {
            res += data[(r-1)*size +c]*data[(r-1)*size+c];
            if (c>0) {
                res += data[(r-1) *size + c-1]*data[(r-1) *size + c-1];
            }
        }
        if (r<size-1) {
            res += data[(r+1) *size + c]*data[(r+1) *size +c];
            if (c<size-1) {
                res += data[(r+1) *size +c+1]*data[(r+1) *size +c+1];
            }
        }
        if (c>0) {
            res += data[r*size +c-1]*data[r*size +c-1];
            if (r<size-1) {
                res += data[(r+1) *size +c-1]*data[(r+1) *size +c-1];
            }
        }
        if (c<size-1) {
            res += data[r*size +c+1]*data[r*size +c+1];
            if (r>0) {
                res += data[(r-1) *size +c+1]*data[(r-1) *size +c+1];
            }
        }
        return res;
    }

    int Count2Neighbours(int r, int c) {
        int min_r = (r > 2) ? r-2 : 0;
        int max_r = (r < size-3) ? r+2 : size-1;
        int min_c = (c > 2) ? c-2 : 0;
        int max_c = (c < size-3) ? c+2 : size-1;

        int res = 0;
        for (int i = min_r; i<max_r+1; i++) {
            for (int j = min_c; j<max_c+1; j++) {
                res += data[i*size+j]*data[i*size+j];
            }
        }
        res -= 1;
        return res;
    }

    std::vector<int> bestChoice() {
        int bestscore = -1000;
        int score = -1000;
        int r_move, c_move;
        int moves = 1;
        int tmp = size*size - size;
        maxdepth=0;
        while(moves < 10000000) {
            if (tmp - maxdepth == 0)
                break;
            moves *= tmp - maxdepth;
            maxdepth++;
        }
        if (size>5 & size<16 & turn<8) {++maxdepth;}
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                if(data[i*size+j] == 0) {
                    MakeMove(i,j,-1);
                    if (Count2Neighbours(i,j)!=0) {
                        score = minimax(0, false, -1000, 1000, i,j) * 10;
                    }
                    UndoMove(i,j);
                    if (score > bestscore || (score == bestscore) & (CountNeighbours(i,j) > CountNeighbours(r_move,c_move))) {
                        bestscore = score;
                        r_move = i;
                        c_move = j;
                    }
                }
            }
        }
        std::vector<int> move = {r_move,c_move};
        return move;
    }

    void Clean() {
        turn = 0;
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                data[i * size + j] = 0;
            }
        }
    }

};

#endif //LAB_2_MATRIX_H