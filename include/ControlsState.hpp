#pragma once
#include "State.hpp"

class ControlsState : public State {
public:
    ControlsState(Application& app); // Constructor that accepts Application reference

    void update(Application& app) override;
    void draw(Application& app) const override;
};
