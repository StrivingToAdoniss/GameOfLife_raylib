#pragma once
#include <raylib.h>
#include <map>
#include <functional>
#include "Grid.hpp"
#include "Simulation.hpp"
#include "State.hpp"
#include "MusicManager.hpp"

class Application {
private:
    int screenWidth;
    int screenHeight;
    int cellSize;
    int FPS;

    Grid grid;
    Simulation simulation;
    State* currentState;
    MusicManager musicManager;

    bool running;

public:
    Application(int width, int height, int cellSize, int FPS);
    ~Application();

    void run();
    void changeState(State* newState); // Change the current state
    void quit(); // Stop running the application

    // Accessors
    int getScreenWidth() const { return screenWidth; }
    int getScreenHeight() const { return screenHeight; }
    Grid& getGrid() { return grid; }
    Simulation& getSimulation() { return simulation; }
};
