//
// Created by Eliyahu on 05/20/2020.
//
#pragma once

#include "FootCommander.hpp"

class FootSoldier : public FootCommander {
public:
    FootSoldier(int x) : FootCommander(x) {
        this->_power = 10;
        this->_life = 100;
        this->_isCommander = false;
    }

    ~FootSoldier() {
    }

    void activate(Soldier &other) const override {
        other._life -= this->_power;
    }
};



