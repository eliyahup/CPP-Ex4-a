//
// Created by eliya on 05/25/2020.
//
#pragma once

#include "ParamedicCommander.hpp"

class Paramedic : public ParamedicCommander {
public:
    Paramedic(int x) : ParamedicCommander(x) {
        this->_power = 0;
        this->_life = 100;
        this->_isCommander = false;
    }

    ~Paramedic() {
    }

    void activate(Soldier &other) const override {
        other._life = other._initLife;

    }
};
