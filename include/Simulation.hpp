// Simulation.hpp
#pragma once
#include <iostream>
#include <random>
#include <memory>
#include "Rule.hpp"
#include "Grid.hpp"

class Simulation{
    private:
    Grid& grid;
    int FPS;

    public:
    Simulation(Grid& grid, int FPS);
    void Draw();
    std::vector<std::pair<int, int>> getAllNeighborsOfCell(int row, int column);
    std::vector<std::pair<int, int>> getActiveNeighborsOfCell(int row, int column);

    void update();

    void reset();

    void randomizeGrid(double toggleProbability = 0.5);

    void draw();

    void increaseSpeed();
    void decreaseSpeed();
    int getFPS() const;
    void setFPS(int fps); 
};