
#include<math.h>
#include "Board.hpp"
#include <iostream>

using namespace std;
using namespace WarGame;


Soldier *&Board::operator[](std::pair<int, int> location) {
    return board[location.first][location.second];
}

Soldier *Board::operator[](std::pair<int, int> location) const {
    return board[location.first][location.second];
}

bool Board::has_soldiers(int player_number) const {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr && board[i][j]->_playerNumber == player_number) {
                return true;
            }
        }
    }
    return false;
}

double dist(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void Board::moveStep(std::pair<int, int> &source, Board::MoveDIR direction) {
    switch (direction) {
        case Up :
            if (source.first + 1 < board.size() && board[source.first + 1][source.second] ==
                                                   nullptr) {   //not exit from board and no have there a soldier.
                board[source.first + 1][source.second] = board[source.first][source.second];
                board[source.first][source.second] = nullptr;
                source.first = source.first + 1;
            } else {
                __throw_invalid_argument("invalid step on the board");
            }
            break;
        case Down:
            if (source.first - 1 >= 0 && board[source.first - 1][source.second] ==
                                         nullptr) {   //not exit from board and no have there a soldier.
                board[source.first - 1][source.second] = board[source.first][source.second];
                board[source.first][source.second] = nullptr;
                source.first -= 1;
            } else {
                __throw_invalid_argument("invalid step on the board");
            }
            break;
        case Right:
            if (source.second - 1 >= 0 && board[source.first][source.second - 1] ==
                                          nullptr) {   //not exit from board and no have there a soldier.
                board[source.first][source.second - 1] = board[source.first][source.second];
                board[source.first][source.second] = nullptr;
                source.second -= 1;
            } else {
                __throw_invalid_argument("invalid step on the board");
            }
            break;
        case Left:
            if (source.second + 1 < board[source.first].size() && board[source.first][source.second + 1] ==
                                                                  nullptr) {   //not exit from board and no have there a soldier.
                board[source.first][source.second + 1] = board[source.first][source.second];
                board[source.first][source.second] = nullptr;
                source.second += 1;
            } else {
                __throw_invalid_argument("invalid step on the board");
            }
            break;
        default:
            __throw_invalid_argument("invalid step on the board can only move: Up, Down, Right, Left");
    }
}

void Board::minDistToAttack(std::pair<int, int> source, int player_number) {
    double minDist = 1000;
    int iMin, JMin;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr && board[i][j]->_playerNumber != player_number) {
                double candidateMin = dist(source.first, source.second, i, j);
                if (candidateMin < minDist) {
                    minDist = candidateMin;
                    iMin = i;
                    JMin = j;
                }
            }
        }
    }
    if (minDist != 1000) {
        // board[iMin][JMin]->_life -= board[source.first+1][source.second]->_power;
        board[source.first][source.second]->activate(*board[iMin][JMin]);
    }
}

void Board::move(int player_number, std::pair<int, int> source, Board::MoveDIR direction) {
//board[source.first][source.second]->activate(reinterpret_cast<Soldier &>(board[0][1]));
    moveStep(source, direction);
    minDistToAttack({source.first, source.second}, player_number);

    if (board[source.first][source.second]->_isCommander) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] != nullptr && board[i][j]->_playerNumber == player_number &&
                    !board[i][j]->_isCommander) {
                    if (FootCommander *n = dynamic_cast<FootCommander *>(board[i][j])) {
                        minDistToAttack({i, j}, player_number);
                    }
                }
            }
        }
    }


}



