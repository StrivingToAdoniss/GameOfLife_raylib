//SimulationState.hpp
#pragma once
#include "State.hpp"
#include "Application.hpp"

class SimulationState : public State {
public:
    SimulationState(Application& app);

    void update(Application& app) override;
    void draw(Application& app) const override;

private:
    float accumulatedTime = 0.0f; // Accumulated time for simulation updates
};

