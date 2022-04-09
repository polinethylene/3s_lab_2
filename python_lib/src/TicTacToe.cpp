#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <iostream>
#include "Board.h"
#include "BoardFour.h"

namespace py = pybind11;
using namespace std;

void declare_board(py::module &m) {
    using Class = Board;
    std::string pyclass_name = std::string("Board");
    py::class_<Class>(m, pyclass_name.c_str(), py::buffer_protocol(), py::dynamic_attr())
            .def(py::init<>())
            .def(py::init<int>())
            .def(py::init<vector<int>, int>())
            .def("GetSize",      &Class::GetSize)
            .def("GetTurn",     &Class::GetTurn)
            .def("MakeMove",    &Class::MakeMove)
            .def("UndoMove",      &Class::UndoMove)
            .def("inRow",     &Class::inRow)
            .def("isPossibleWin",    &Class::isPossibleWin)
            .def("rollout",      &Class::rollout)
            .def("isEnd",     &Class::isEnd)
            .def("minimax",    &Class::minimax)
            .def("bestChoice",      &Class::bestChoice)
            .def("Clean",      &Class::Clean);
}

void declare_board_4(py::module &m) {
    using Class = BoardFourInRow;
    std::string pyclass_name = std::string("BoardFourInRow");
    py::class_<Class>(m, pyclass_name.c_str(), py::buffer_protocol(), py::dynamic_attr())
            .def(py::init<>())
            .def(py::init<int>())
            .def(py::init<vector<int>, int>())
            .def("GetSize",      &Class::GetSize)
            .def("GetTurn",     &Class::GetTurn)
            .def("MakeMove",    &Class::MakeMove)
            .def("UndoMove",      &Class::UndoMove)
            .def("inRow",     &Class::inRow)
            .def("isPossibleWin",    &Class::isPossibleWin)
            .def("rollout",      &Class::rollout)
            .def("isEnd",     &Class::isEnd)
            .def("minimax",    &Class::minimax)
            .def("bestChoice",      &Class::bestChoice)
            .def("GetMaxDepth",      &Class::GetMaxDepth)
            .def("Clean",      &Class::Clean);
}

PYBIND11_MODULE(TicTacToe, m) {
    declare_board(m);
    declare_board_4(m);
}