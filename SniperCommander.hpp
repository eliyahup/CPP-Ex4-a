//
// Created by eliya on 05/25/2020.
//
#pragma once

#include "Soldier.hpp"

class SniperCommander  : public Soldier {
public:

    SniperCommander (int x) : Soldier(x, 120, 100, true) {

    }

    virtual ~SniperCommander  () {

    }

    void activate(Soldier &other) const override {
        other._life -= this->_power;
    }
};