
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
                                                   nullptr) {   //not exit from the board and no have there a soldier.
                board[source.first + 1][source.second] = board[source.first][source.second];
                board[source.first][source.second] = nullptr;
                source.first = source.first + 1;
            } else {
                __throw_invalid_argument("invalid step on the board");
            }
            break;
        case Down:
            if (source.first - 1 >= 0 && board[source.first - 1][source.second] ==
                                         nullptr) {   //not exit from the board and no have there a soldier.
                board[source.first - 1][source.second] = board[source.first][source.second];
                board[source.first][source.second] = nullptr;
                source.first -= 1;
            } else {
                __throw_invalid_argument("invalid step on the board");
            }
            break;
        case Left:
            if (source.second - 1 >= 0 && board[source.first][source.second - 1] ==
                                          nullptr) {   //not exit from the board and no have there a soldier.
                board[source.first][source.second - 1] = board[source.first][source.second];
                board[source.first][source.second] = nullptr;
                source.second -= 1;
            } else {
                __throw_invalid_argument("invalid step on the board");
            }
            break;
        case Right:
            if (source.second + 1 < board[source.first].size() && board[source.first][source.second + 1] ==
                                                                  nullptr) {   //not exit the from board and no have there a soldier.
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

void Board::minDistAttack(std::pair<int, int> source, int player_number) {
    double minDist = 1000;
    int iMin, JMin;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr && board[i][j]->_playerNumber != player_number) {
                double minCandidate = dist(source.first, source.second, i, j);
                if (minCandidate < minDist) {
                    minDist = minCandidate;
                    iMin = i;
                    JMin = j;
                }
            }
        }
    }
    if (minDist != 1000) {
        board[source.first][source.second]->activate(*board[iMin][JMin]);
        if(board[iMin][JMin]->_life<=0){
            delete(board[iMin][JMin]);
            board[iMin][JMin] = nullptr;
        }
    }
}

void Board::strongAttact(std::pair<int, int> source, int player_number) {
    double strongPlayer = 0;
    int iMax, JMax;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr && board[i][j]->_playerNumber != player_number) {
                double strongCandidate = board[i][j]->_life;
                if (strongCandidate > strongPlayer) {
                    strongPlayer = strongCandidate;
                    iMax = i;
                    JMax = j;
                }
            }
        }
    }
    if (strongPlayer != 0) {
        board[source.first][source.second]->activate(*board[iMax][JMax]);
        if(board[iMax][JMax]->_life<=0){
            delete(board[iMax][JMax]);
            board[iMax][JMax] = nullptr;
        }
    }
}

void Board::health(std::pair<int, int> source, int player_number) {
    int i = source.first;
    int j = source.second;
    if (i + 1 < board.size() && board[i + 1][j] != nullptr && board[i + 1][j]->_playerNumber == player_number) {
        board[source.first][source.second]->activate(*board[i + 1][j]);
    }
    if (i - 1 >= 0 && board[i - 1][j] != nullptr && board[i - 1][j]->_playerNumber == player_number) {
        board[source.first][source.second]->activate(*board[i - 1][j]);
    }
    if (j + 1 >= board[i].size() && board[i][j + 1] != nullptr && board[i][j + 1]->_playerNumber == player_number) {
        board[source.first][source.second]->activate(*board[i][j + 1]);
    }
    if (j - 1 >= 0 && board[i][j - 1] != nullptr && board[i][j - 1]->_playerNumber == player_number) {
        board[source.first][source.second]->activate(*board[i][j - 1]);
    }
    if (i - 1 >= 0 && j - 1 >= 0 && board[i-1][j - 1] != nullptr && board[i-1][j - 1]->_playerNumber == player_number) {
        board[source.first][source.second]->activate(*board[i-1][j - 1]);
    }
    if (i + 1 < board.size() && j + 1 < board[i].size()&& board[i+1][j + 1] != nullptr && board[i+1][j + 1]->_playerNumber == player_number) {
        board[source.first][source.second]->activate(*board[i+1][j + 1]);
    }
    if (i + 1 < board.size() &&  j - 1 >= 0 && board[i+1][j - 1] != nullptr && board[i+1][j - 1]->_playerNumber == player_number) {
        board[source.first][source.second]->activate(*board[i+1][j - 1]);
    }
    if (i - 1 >= 0 && j + 1 < board[i].size()&& board[i-1][j + 1] != nullptr && board[i-1][j + 1]->_playerNumber == player_number) {
        board[source.first][source.second]->activate(*board[i-1][j + 1]);
    }
}


void Board::move(int player_number, std::pair<int, int> source, Board::MoveDIR direction) {
    if (board[source.first][source.second] == nullptr ||
        board[source.first][source.second]->_playerNumber != player_number) {
        __throw_invalid_argument("There is no soldier in this location or it's not your soldier");
    }

    moveStep(source, direction);

    if (FootCommander *n = dynamic_cast<FootCommander *>(board[source.first][source.second])) {
        minDistAttack({source.first, source.second}, player_number);
    } else if (SniperCommander *n = dynamic_cast<SniperCommander *>(board[source.first][source.second])) {
        strongAttact({source.first, source.second}, player_number);
    } else if (ParamedicCommander *n = dynamic_cast<ParamedicCommander *>(board[source.first][source.second])) {
        health({source.first, source.second}, player_number);
    }

    if (board[source.first][source.second]->_isCommander) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] != nullptr && board[i][j]->_playerNumber == player_number &&
                    !board[i][j]->_isCommander) {
                    if (FootCommander *n = dynamic_cast<FootCommander *>(board[i][j])) {
                        if (FootCommander *n = dynamic_cast<FootCommander *>(board[source.first][source.second])) {
                            minDistAttack({i, j}, player_number);
                        }
                    } else if (SniperCommander *n = dynamic_cast<SniperCommander *>(board[i][j])) {
                        if (SniperCommander *n = dynamic_cast<SniperCommander *>(board[source.first][source.second])) {
                            strongAttact({i, j}, player_number);
                        }
                    } else if (ParamedicCommander *n = dynamic_cast<ParamedicCommander *>(board[i][j])) {
                        if (ParamedicCommander *n = dynamic_cast<ParamedicCommander *>(board[source.first][source.second])) {
                            health({source.first, source.second}, player_number);
                        }
                    }
                }
            }
        }
    }


}



