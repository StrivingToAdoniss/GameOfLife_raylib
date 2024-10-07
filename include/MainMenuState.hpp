// MainMenuState.hpp
#pragma once
#include "State.hpp"
#include "Button.hpp"

class MainMenuState : public State {
private:
    Button startButton;
    Button controlsButton;
    Button exitButton;

    std::string title = "Conway's Game of Life";
    int titleFontSize = 50;

public:
    MainMenuState(Application& app); 

    void update(Application& app) override;
    void draw(Application& app) const override;
};

