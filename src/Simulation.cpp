//Simulation.cpp
#include "Simulation.hpp"


Simulation::Simulation(Grid& grid, int FPS) : grid(grid){
    this->FPS = FPS;
}
void Simulation::Draw(){
    this->grid.draw();
}

std::vector<std::pair<int, int>> Simulation::getAllNeighborsOfCell(int row, int column) {
    std::vector<std::pair<int, int>> neighbors;

    std::vector<std::pair<int, int>> neighborOffsets = {
        {-1, 0}, // Directly above
        {1, 0},  // Directly below
        {0, -1}, // To the left
        {0, 1},  // To the right
        {-1, -1},// Diagonally above and to the left
        {-1, 1}, // Diagonally above and to the right
        {1, -1}, // Diagonally below and to the left
        {1, 1}   // Diagonally below and to the right
    };

    for (const auto& offset : neighborOffsets) {
        int neighborRow = (row + offset.first + this->grid.getRows()) % this->grid.getRows();
        int neighborColumn = (column + offset.second + this->grid.getColumns()) % this->grid.getColumns();
        neighbors.emplace_back(neighborRow, neighborColumn);
    }

    return neighbors;
}


std::vector<std::pair<int, int>> Simulation::getActiveNeighborsOfCell(int row, int column) {
    std::vector<std::pair<int, int>> activeNeighbors;

    // Retrieve all neighbors of the given cell
    std::vector<std::pair<int, int>> allNeighbors = getAllNeighborsOfCell(row, column);

    // Filter active neighbors
    for (const auto& neighbor : allNeighbors) {
        if (grid.getCell(neighbor.first, neighbor.second).getIsAlive()) {
            activeNeighbors.emplace_back(neighbor);
        }
    }

    return activeNeighbors;
}

// In Simulation::update
void Simulation::update() {
    std::vector<std::pair<int, int>> cellsToProcess;

    // Collect all active cells and all their neighbors
    for (std::pair<int, int> cell : grid.getActiveCells()) {
        int row = cell.first;
        int column = cell.second;

        // Add the active cell itself
        cellsToProcess.emplace_back(row, column);

        // Add all neighbors (regardless of their state)
        std::vector<std::pair<int, int>> allNeighbors = this->getAllNeighborsOfCell(row, column);
        cellsToProcess.insert(cellsToProcess.end(), allNeighbors.begin(), allNeighbors.end());
    }

    // Remove duplicates by sorting and using unique
    std::sort(cellsToProcess.begin(), cellsToProcess.end(), 
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool {
            if (a.first != b.first)
                return a.first < b.first;
            return a.second < b.second;
        }
    );
    cellsToProcess.erase(
        std::unique(cellsToProcess.begin(), cellsToProcess.end()),
        cellsToProcess.end()
    );

    // Temporary storage for cells to be toggled
    std::vector<std::pair<int, int>> cellsToToggle;

    // Instantiate the rule classes
    std::unique_ptr<Rule> liveRule = std::make_unique<LiveCellRule>();
    std::unique_ptr<Rule> deadRule = std::make_unique<DeadCellRule>();

    // Apply Conway's rules
    for (const auto& cell : cellsToProcess) {
        int row = cell.first;
        int column = cell.second;

        int aliveNeighbors = this->getActiveNeighborsOfCell(row, column).size();

        bool currentState = grid.getCell(row, column).getIsAlive();
        bool nextState = false;

        // Determine next state using polymorphism
        if (currentState) {
            nextState = liveRule->applyRule(currentState, aliveNeighbors);
        } else {
            nextState = deadRule->applyRule(currentState, aliveNeighbors);
        }

        // If state changes, add to toggle list
        if (currentState != nextState) {
            cellsToToggle.emplace_back(row, column);
        }
    }

    // Toggle cells accordingly
    for (const auto& cell : cellsToToggle) {
        grid.toggleCell(cell.first, cell.second);
    }
}



void Simulation::reset(){
    this->grid.reset();
}

void Simulation::randomizeGrid(double toggleProbability){
    if(toggleProbability < 0.0 || toggleProbability > 1.0) {
        throw std::invalid_argument("toggleProbability must be between 0.0 and 1.0");
    }

    // Set up random number generation
    // Seed with a real random value, if available
    std::random_device rd;
    // Use Mersenne Twister engine
    std::mt19937 gen(rd());
    // Define a Bernoulli distribution with the given probability
    std::bernoulli_distribution d(toggleProbability);

    // Iterate through all cells in the grid
    for(int row = 0; row < grid.getRows(); ++row) {
        for(int column = 0; column < grid.getColumns(); ++column) {
            // Generate a random bool based on toggleProbability
            bool shouldToggle = d(gen);

            if(shouldToggle) {
                grid.toggleCell(row, column);
            }
        }
    }
}

void Simulation::increaseSpeed() {
    FPS = (FPS < 60) ? FPS + 2 : 60; // Cap FPS to max 60
}

void Simulation::decreaseSpeed() {
    FPS = (FPS > 2) ? FPS - 2 : 2; // Cap FPS to min 2
}

int Simulation::getFPS() const {
    return FPS;
}

void Simulation::setFPS(int fps){
    if(fps < 2 || fps > 60) {
        throw std::invalid_argument("FPS must be between 2 and 60");
    }
    else{
        FPS = fps;
    }
}

void Simulation::draw(){
    this->grid.draw();
}