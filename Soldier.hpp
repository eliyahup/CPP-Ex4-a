//
// Created by eliyahu on 05/20/2020.
//
#pragma once

#include "Board.hpp"


class Soldier {
public:

    int _playerNumber;
    int _life, _power, _initLife;
    bool _isCommander;

    Soldier(const int playerNumber, int life, int power, bool isCommander)
            : _playerNumber(playerNumber), _life(life), _initLife(life), _power(power), _isCommander(isCommander) {
    }

    virtual ~Soldier() {
    }

    virtual void activate(Soldier &other) const = 0;

};




