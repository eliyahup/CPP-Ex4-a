//
// Created by eliya on 05/25/2020.
//
#pragma once

#include "SniperCommander.hpp"

class Sniper  : public SniperCommander {
public:
    Sniper (int x) : SniperCommander(x) {
        this->_power = 50;
        this->_life = 100;
        this->_initLife = 100;
        this->_isCommander = false;
    }

    ~Sniper () {
    }

    void activate(Soldier &other) const override {
        other._life -= this->_power;
    }
};
