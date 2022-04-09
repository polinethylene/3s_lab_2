#ifndef INC_2S_LAB2_BOARDFOUR_H
#define INC_2S_LAB2_BOARDFOUR_H


#include <iostream>
#include <cmath>


class BoardFourInRow {
private:
    int* data;
    int size;
    int turn;
    int maxdepth;
public:

    BoardFourInRow() : data() {
        data = new int[1];
        size = 0;
        turn = 0;
        maxdepth = 10;
    }

    template<class X>
    BoardFourInRow(std::vector<X> items, int size) : size(size) {
        turn = 0;
        data = new int[size*size];
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                data[i * size + j] = items[i * size + j];
            }
        }
        maxdepth = 10;
    }

    BoardFourInRow(int size) : size(size){
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

    ~BoardFourInRow() { delete[] data; }

    void MakeMove(int row, int column, int v) {
        assert(column >= 0 && column < size);
        assert(row >= 0 && row < size);
        data[row * size + column] = v;
        turn += 1;
    }

    void UndoMove(int row, int column) {
        data[row * size + column] = 0;
        turn -= 1;
    }

    bool inRowThree(int a,int b,int c) {
        return (a==b && b==c && a!=0);
    }

    bool inRow(int a,int b,int c,int d) {
        return (a==b && b==c && d==c && a!=0);
    }

    bool isPossibleWin(int a,int b,int c, int d) {
        return ((inRowThree(a,b,c) && d==0) || (inRowThree(a,b,d) && c==0) || (inRowThree(a,d,c) && b==0) ||
                (inRowThree(b,d,c) && a==0));
    }

    int rollout() {      //change
        int res = 0;
        for (int i=0; i<size; i++) {
            for (int j=0; j<size-3; j++) {
                if (isPossibleWin(data[i*size+j], data[i*size+j+1], data[i*size+j+2], data[i*size+j+3])) {
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
            for (int j=0; j<size-3; j++) {
                if (isPossibleWin(data[j*size+i], data[(j+1)*size+i], data[(j+2)*size+i],data[(j+3)*size+i])) {
                    int move = (data[j*size+i] == 0) ? data[(j+1)*size+i] : data[j*size+i];
                    if(move == 1){
                        return -1;
                    } else {
                        res+=1;
                    }
                }
            }
        }

        for (int min_r = 0; min_r<size-3; min_r++) {
            for (int max_r = size-1; max_r>2; max_r--){
//                std::cout << (max_r-3)*size+min_r << ' ' << (1 + max_r-3)*size+min_r+1<< ' ' << (2 + max_r-3)*size+min_r+2
//                        << ' ' << (3 + max_r-3)*size+min_r+3 << '\n';
                if (isPossibleWin(data[(max_r-3)*size+min_r], data[(1 + max_r-3)*size+min_r+1],
                                  data[(2 + max_r-3)*size+min_r+2],data[(3 + max_r-3)*size+min_r+3])) {
                    int move = (data[(max_r-3)*size+min_r] == 0) ? data[(1+max_r-3)*size+min_r+1]
                                                                 : data[(max_r-3)*size+min_r];
                    if(move == 1){
                        return -1;
                    } else {
                        res+=1;
                    }
                }
                int m = max_r*size+min_r, n = (max_r-1)*size+min_r+1, l = (max_r-2)*size+min_r+2, p=(max_r-3)*size+min_r+3;
//                std::cout << max_r << ' ' << min_r << '\n';
//                std::cout << m << ' ' << n << ' ' << l << ' ' << p << '\n';
                if (isPossibleWin(data[m], data[n], data[l], data[p])) {
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

    int isEnd(int r_move, int c_move) {     //change
        int min_r = (r_move > 3) ? r_move-3 : 0;
        int max_r = (r_move < size-4) ? r_move+3 : size-1;
        int min_c = (c_move > 3) ? c_move-3 : 0;
        int max_c = (c_move < size-4) ? c_move+3 : size-1;


//        for (int i=min_r; i<max_r+1; i++) {
        int i=r_move;
        for (int j=min_c; j<max_c+1-3; j++) {
            if (inRow(data[i*size+j], data[i*size+j+1], data[i*size+j+2],data[i*size+j+3])) {
                return -data[i*size+j];
            }
        }
//        }
//        for (int i=min_c; i<max_c+1; i++) {
        i=c_move;
        for (int j=min_r; j<max_r+1-3; j++) {
//                std::cout << j*size+i << ' ' << (j+1)*size+i << ' ' << (j+2)*size+i<< ' ' << (j+3)*size+i << '\n';
            if (inRow(data[j*size+i], data[(j+1)*size+i], data[(j+2)*size+i], data[(j+3)*size+i])) {
                return -data[j*size+i];
            }
        }
//        }


        for (int i = min_c; i<max_c-2; i++) {
            for (int j = max_r; j>min_r+2; j--){
//                std::cout << (j-3)*size+i << ' ' << (1+j-3)*size+i+1 << ' ' << (2+j-3)*size+i+2 << ' '
//                        << (3+j-3)*size+i+3 << '\n';
                if (inRow(data[(j-3)*size+i], data[(1+j-3)*size+i+1], data[(2+j-3)*size+i+2],data[(3+j-3)*size+i+3])) {
                    return -data[(j-3)*size+i];
                }
//                std::cout << j*size+i << ' ' << (j-1)*size+i+1 << ' ' << (j-2)*size+i+2 << ' ' << (j-3)*size+i+3 << '\n';
                if (inRow(data[j*size+i], data[(j-1)*size+i+1], data[(j-2)*size+i+2], data[(j-3)*size+i+3])) {
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

//        std::cout << min_r << ' ' << max_r << ' ' << min_c << ' ' << max_c << '\n';

        int res = 0;
        for (int i = min_r; i<max_r+1; i++) {
            for (int j = min_c; j<max_c+1; j++) {
                res += data[i*size+j]*data[i*size+j];
            }
        }
        res -= 1;
        return res;
    }

    int GetMaxDepth(){
        return maxdepth;
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


#endif //INC_2S_LAB2_BOARDFOUR_H
