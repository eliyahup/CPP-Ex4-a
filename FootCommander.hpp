//
// Created by eliya on 05/20/2020.
//
#pragma once

#include "Board.hpp"
#include "Soldier.hpp"


class FootCommander : public Soldier {
public:

    FootCommander(int x) : Soldier(x, 150, 20, true) {

    }

    virtual ~FootCommander() {

    }

    void activate(Soldier &other) const override {
        other._life -= this->_power;
    }
};



