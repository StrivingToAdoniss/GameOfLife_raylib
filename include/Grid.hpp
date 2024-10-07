// Grid.hpp
#pragma once

#include "Cell.hpp"
#include <vector>
#include <raylib.h>
#include <stdexcept>
#include <algorithm>

class Grid
{
    private:
        int rows;
        int columns;
        std::vector<std::vector<Cell>> cells;
        std::vector<std::pair<int, int>> activeCells;
        bool isWithinGrid(int row, int column);

    public:
        Grid(int rows, int columns, int cellSize);
        Grid();

        int getRows() const;
        int getColumns() const;

        int getCellNumber() const;

        std::vector<std::vector<Cell>> getCells() const;
        const std::vector<std::pair<int, int>>& getActiveCells() const;

        Cell getCell(int row, int column);
        void setCell(int row, int column, Cell cell);

        void toggleCell(int row, int column);

        void fill(int cellSize);
        void draw() const;
        void update();
        void reset();
};
