//
// Created by eliya on 05/25/2020.
//
#pragma once

#include "Soldier.hpp"

class ParamedicCommander : public Soldier {

public:
    ParamedicCommander(int x) : Soldier(x, 200, 0, true) {

    }

    virtual ~ParamedicCommander() {

    }

    void activate(Soldier &other) const override {
        other._life = other._initLife;
    }
};
