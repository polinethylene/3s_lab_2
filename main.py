# This Python file uses the following encoding: utf-8
import sys
import re
import numpy as np
from PySide6 import QtCore, QtGui
from PySide6.QtWidgets import *
import TicTacToe as ttt


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("TicTacToe")

        self.move_made = QTextEdit(self)
        self.size_line = QLineEdit(self)
        self._button = QPushButton(" ", self)
        self.o_button = QPushButton("O", self)
        self.x_button = QPushButton("X", self)
        self.predict_button = QPushButton("PREDICT", self)
        self.play_button = QPushButton("PLAY", self)
        self.bestChoice_button = QPushButton("Make Prediction", self)
        self.o_count = 0
        self.x_count = 0
        self.label = QLabel(self)

        self.UiComponents(4)

        # self.show()

    def UiComponents(self, boardsize):
        self.play_button.setObjectName('Util')
        self.play_button.setGeometry(280, 30, 200, 50)
        self.play_button.setCheckable(True)
        self.play_button.setChecked(True)
        self.play_button.setStyleSheet("background-color : #90c1bc")
        self.play_button.clicked.connect(self.change_action_play)
        self.predict_button.setObjectName('Util')
        self.predict_button.setGeometry(520, 30, 200, 50)
        self.predict_button.setCheckable(True)
        self.predict_button.clicked.connect(self.change_action_predict)

        self.x_button.setObjectName('Sym')
        self.x_button.setGeometry(830, 130, 50, 50)
        self.x_button.setCheckable(True)
        self.x_button.setChecked(True)
        self.x_button.setStyleSheet("background-color : #90c1bc")
        self.x_button.clicked.connect(self.change_action_x)
        self.o_button.setObjectName('Sym')
        self.o_button.setGeometry(830, 180, 50, 50)
        self.o_button.setCheckable(True)
        self.o_button.clicked.connect(self.change_action_o)
        self._button.setObjectName('Sym')
        self._button.setGeometry(830, 230, 50, 50)
        self._button.setCheckable(True)
        self._button.clicked.connect(self.change_action)

        self.size_line.setPlaceholderText("size")
        self.size_line.setGeometry(830, 300, 100, 30)
        enter_button = QPushButton(self)
        enter_button.setObjectName('Sym')
        enter_button.setGeometry(930, 300, 50, 30)
        enter_button.clicked.connect(self.change_size)
        self.label.setGeometry(830, 340, 150, 30)
        self.label.setAlignment(QtCore.Qt.AlignCenter)

        self.bestChoice_button.setObjectName('Reset')
        self.bestChoice_button.setGeometry(830, 380, 150, 30)
        self.bestChoice_button.clicked.connect(self.make_prediction_action)

        self.move_made.setReadOnly(True)
        self.move_made.setGeometry(200, 725, 300, 50)
        reset_game = QPushButton("Reset Game", self)
        reset_game.setObjectName('Reset')
        reset_game.setGeometry(600, 725, 200, 50)
        reset_game.clicked.connect(self.reset_game_action)

        # self.ListUI()
        self.BoardUI_4(boardsize)
        # self.layout.setGeometry(QtCore.QRect(200, 100, 600, 600))

    def BoardUI(self, boardsize):
        self.board = ttt.Board(boardsize)
        self.push_list = []

        for _ in range(boardsize):
            temp = []
            for _ in range(boardsize):
                temp.append((QPushButton(self)))
            self.push_list.append(temp)

        n = int(600 / boardsize)
        for i in range(boardsize):
            for j in range(boardsize):
                self.push_list[i][j].setObjectName('board {} {}'.format(i, j))
                # self.push_list[i][j].setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
                self.push_list[i][j].resize(n,n)
                self.push_list[i][j].move(200 + n * j, 100 + n * i)
                self.push_list[i][j].show()

        for i in range(boardsize):
            for j in range(boardsize):
                self.push_list[i][j].clicked.connect(self.action_called)

    def BoardUI_4(self, boardsize):
        self.board = ttt.BoardFourInRow(boardsize)
        self.push_list = []

        for _ in range(boardsize):
            temp = []
            for _ in range(boardsize):
                temp.append((QPushButton(self)))
            self.push_list.append(temp)

        n = int(600 / boardsize)
        for i in range(boardsize):
            for j in range(boardsize):
                self.push_list[i][j].setObjectName('board {} {}'.format(i, j))
                self.push_list[i][j].resize(n,n)
                self.push_list[i][j].move(200 + n * j, 100 + n * i)
                self.push_list[i][j].show()

        for i in range(boardsize):
            for j in range(boardsize):
                self.push_list[i][j].clicked.connect(self.action_called)

    def ListUI(self):
        self.inputTextEdit = QTextEdit(self)
        self.inputTextEdit.setPlaceholderText("Set coordinates format: [row, column, symbol; row, column, symbol..]")
        # self.inputTextEdit.resize(600, 600)
        self.inputTextEdit.setGeometry(200, 100, 600, 600)
        self.inputTextEdit.setObjectName('display')
        self.inputTextEdit.show()

        # self.board = ttt.BoardFourInRow(boardsize)

    def delete(self):
        self.label.setText("")
        self.move_made.setPlainText("")
        boardsize = self.board.GetSize()
        for i in range(boardsize):
            for j in range(boardsize):
                self.push_list[i][j].deleteLater()

    def change_size(self):
        old_boardsize = self.board.GetSize()
        boardsize = int(self.size_line.text())
        if old_boardsize<16:
            self.delete()
        else:
            self.label.setText("")
            self.move_made.setPlainText("")
            self.inputTextEdit.deleteLater()
        if boardsize > 15 and self.play_button.isChecked() or boardsize < 4:
            boardsize = 4
            self.BoardUI_4(boardsize)
        elif boardsize > 15 and self.predict_button.isChecked():
            self.ListUI()
            self.board = ttt.BoardFourInRow(boardsize)
        else:
            self.BoardUI_4(boardsize)

    def change_action_play(self):
        if self.play_button.isChecked():
            self.play_button.setStyleSheet("background-color : #90c1bc")
            self.predict_button.setChecked(False)
            self.predict_button.setStyleSheet("background-color : #a5ddd7")
            self.reset_game_action()
        else:
            self.play_button.setStyleSheet("background-color : #a5ddd7")
            self.predict_button.setChecked(True)
            self.predict_button.setStyleSheet("background-color : #90c1bc")
            self.reset_game_action()

    def change_action_predict(self):
        if self.predict_button.isChecked():
            self.predict_button.setStyleSheet("background-color : #90c1bc")
            self.play_button.setChecked(False)
            self.play_button.setStyleSheet("background-color : #a5ddd7")
            self.reset_game_action()
        else:
            self.predict_button.setStyleSheet("background-color : #a5ddd7")
            self.play_button.setChecked(True)
            self.play_button.setStyleSheet("background-color : #90c1bc")
            self.reset_game_action()

    def change_action_x(self):
        if self.x_button.isChecked():
            self.x_button.setStyleSheet("background-color : #90c1bc")
            self.o_button.setChecked(False)
            self.o_button.setStyleSheet("background-color : #a5ddd7")
            self._button.setChecked(False)
            self._button.setStyleSheet("background-color : #a5ddd7")
        else:
            self.x_button.setStyleSheet("background-color : #a5ddd7")
            self._button.setChecked(True)
            self._button.setStyleSheet("background-color : #90c1bc")

    def change_action_o(self):
        if self.o_button.isChecked():
            self.o_button.setStyleSheet("background-color : #90c1bc")
            self.x_button.setChecked(False)
            self.x_button.setStyleSheet("background-color : #a5ddd7")
            self._button.setChecked(False)
            self._button.setStyleSheet("background-color : #a5ddd7")
        else:
            self.o_button.setStyleSheet("background-color : #a5ddd7")
            self._button.setChecked(True)
            self._button.setStyleSheet("background-color : #90c1bc")

    def change_action(self):
        if self._button.isChecked():
            self._button.setStyleSheet("background-color : #90c1bc")
            self.x_button.setChecked(False)
            self.x_button.setStyleSheet("background-color : #a5ddd7")
            self.o_button.setChecked(False)
            self.o_button.setStyleSheet("background-color : #a5ddd7")
        else:
            self._button.setStyleSheet("background-color : #a5ddd7")
            self.x_button.setChecked(True)
            self.x_button.setStyleSheet("background-color : #90c1bc")

    def reset_game_action(self):
        self.label.setText("")
        self.move_made.setPlainText("")
        self.board.Clean()
        self.x_count = 0
        self.o_count = 0

        if self.board.GetSize()<16:
            for buttons in self.push_list:
                for button in buttons:
                    button.setEnabled(True)
                    button.setText("")

    def action_called(self):
        button = self.sender()
        if self.play_button.isChecked():
            i, j = [int(s) for s in button.objectName().split() if s.isdigit()]
            button.setEnabled(False)

            font = int(0.4*int(600/self.board.GetSize()))
            button.setStyleSheet("font: bold {}px;".format(font))
            button.setText("X")
            self.board.MakeMove(i, j, 1)

            self.move_made.setPlainText("last move made row: {}, column: {}".format(i+1, j+1))
            win = self.board.isEnd(i, j)

            text = ""
            if win == -1:
                text = "X Won"
            elif win == 0:
                text = "Match is Draw"
            elif win == 1:
                text = "O Won"

            for buttons in self.push_list:
                for push in buttons:
                    push.setEnabled(False)

            if win == 2:
                ai_move_r, ai_move_c = self.board.bestChoice()
                button = self.push_list[ai_move_r][ai_move_c]
                font = int(0.4 * int(600 / self.board.GetSize()))
                button.setStyleSheet("font: bold {}px;".format(font))
                button.setText("O")
                self.board.MakeMove(ai_move_r, ai_move_c, -1)

                self.move_made.setPlainText("last move made row: {}, column: {}".format(ai_move_r, ai_move_c))
                # print(self.board.rollout())
                win = self.board.isEnd(ai_move_r, ai_move_c)
                text = ""
                if win == -1:
                    text = "X Won"
                elif win == 0:
                    text = "Match is Draw"
                elif win == 1:
                    text = "O Won"

                if win == 2:
                    for buttons in self.push_list:
                        for push in buttons:
                            if push.text() == "":
                                push.setEnabled(True)

            self.label.setText(text)

        elif self.predict_button.isChecked():
            i, j = [int(s) for s in button.objectName().split() if s.isdigit()]
            # button.setEnabled(False)
            end = 3
            if self.x_button.isChecked() and button.text()!='X':
                font = int(0.4 * int(600 / self.board.GetSize()))
                button.setStyleSheet("font: bold {}px;".format(font))
                button.setText("X")
                self.board.MakeMove(i, j, 1)
                end = self.board.isEnd(i,j)
                self.x_count += 1
            elif self.o_button.isChecked() and button.text()!='O':
                font = int(0.4 * int(600 / self.board.GetSize()))
                button.setStyleSheet("font: bold {}px;".format(font))
                button.setText("O")
                self.board.MakeMove(i, j, -1)
                end = self.board.isEnd(i,j)
                self.o_count += 1

            if end!=2:
                if button.text()=='O':
                    self.o_count -= 1
                if button.text()=='X':
                    self.x_count -= 1
                font = int(0.4 * int(600 / self.board.GetSize()))
                button.setStyleSheet("font: bold {}px;".format(font))
                button.setText("")
                self.board.UndoMove(i, j)

    def make_prediction_action(self):
        if self.board.GetSize()>15:
            self.x_count = 0
            self.o_count = 0
            self.board.Clean()
            boardsize = self.board.GetSize()
            text = self.inputTextEdit.toPlainText()
            text_clear = re.sub("[^\w\.\s\-]", "", text)
            data = np.fromstring(text_clear, dtype=int, sep=' ')
            board_data = np.reshape(data, (-1,3))
            print(board_data)
            for item in board_data:
                # print(item[0],item[1],item[2])
                if item[0]<boardsize and item[1]<boardsize and (item[2]==1 or item[2]==-1):
                    self.board.MakeMove(item[0],item[1],item[2])
                    if (item[2]==1):
                        self.x_count+=1
                    else:
                        self.o_count+=1
        if self.x_count != (self.o_count+1):
            # print(self.x_count)
            # print(self.o_count)
            self.move_made.setPlainText("Impossible situation")
        else:
            text = ""
            if self.board.GetSize() < 16:
                for buttons in self.push_list:
                    for push in buttons:
                        push.setEnabled(False)

            ai_move_r, ai_move_c = self.board.bestChoice()

            if self.board.GetSize() < 16:
                button = self.push_list[ai_move_r][ai_move_c]
                font = int(0.4 * int(600 / self.board.GetSize()))
                button.setStyleSheet("font: bold {}px;".format(font))
                button.setText("O")
                self.board.MakeMove(ai_move_r, ai_move_c, -1)
                self.o_count+=1

            self.move_made.setPlainText("predicted move: {}, column: {}".format(ai_move_r, ai_move_c))
            win = self.board.isEnd(ai_move_r, ai_move_c)
            if win == -1:
                text = "X Won"
            elif win == 0:
                text = "Match is Draw"
            elif win == 1:
                text = "O Won"

            if self.board.GetSize() < 16:
                if win == 2:
                    for buttons in self.push_list:
                        for push in buttons:
                            push.setEnabled(True)

            self.label.setText(text)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    with open("style.qss", "r") as f:
            _style = f.read()
            app.setStyleSheet(_style)

    window = MainWindow()
    window.resize(1100, 800)
    window.show()

    sys.exit(app.exec())
