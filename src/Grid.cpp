// Grid.cpp
#include "Grid.hpp"

Grid::Grid(){

}

Grid::Grid(int height, int width, int cellSize) {
    this->rows = height/cellSize;
    this->columns = width/cellSize;
    this->fill(cellSize);
}

int Grid::getRows() const {
    return this->rows;
}

int Grid::getColumns() const {
    return this->columns;
}

int Grid::getCellNumber() const {
    return this->rows * this->columns;
}

std::vector<std::vector<Cell>> Grid::getCells() const {
    return this->cells;
}

const std::vector<std::pair<int, int>>&  Grid::getActiveCells() const{
    return this->activeCells;
}

Cell Grid::getCell(int row, int column) {
    if (this->isWithinGrid(row, column)) {
        return this->cells[row][column];
    }
    else {
        throw std::invalid_argument("Cell is out of bounds");
    }
}

void Grid::setCell(int row, int column, Cell cell) {
    if (this->isWithinGrid(row, column)) {
        this->cells[row][column] = cell;
    }
    else {
        throw std::invalid_argument("Cell is out of bounds");
    }
}

void Grid::toggleCell(int row, int column) {
    if (this->isWithinGrid(row, column)) {
        this->cells[row][column].toggle();
        std::pair<int, int> coord = std::make_pair(row, column);
        if(this->cells[row][column].getIsAlive()) {
            // Add to activeCells
            if(std::find(activeCells.begin(), activeCells.end(), coord) == activeCells.end()) {
                activeCells.emplace_back(coord);
            }
        } else {
            // Remove from activeCells
            activeCells.erase(
                std::remove(activeCells.begin(), activeCells.end(), coord),
                activeCells.end()
            );
        }
    }
    else {
        throw std::invalid_argument("Cell is out of bounds");
    }
}

void Grid::fill(int cellSize) {
    // Resize cells vector based on rows and columns
    this->cells.resize(this->rows);

    for (std::vector<Cell> &row : this->cells) {
        row.resize(this->columns, Cell(cellSize));
    }

    // Optionally populate the cells explicitly
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->cells[i][j] = Cell(cellSize);
        }
    }
}

void Grid::draw() const {
    const int cellSize = this->cells[0][0].getSize();

    Color colorGRAY = Color{55, 55, 55, 255};
    Color colorGREEN = Color{0, 255, 0, 255};
    Color borderColor = Color{0, 0, 0, 255};

    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->columns; col++) {
            const bool isAlive = this->cells[row][col].getIsAlive();

            Color color = isAlive ? colorGREEN : colorGRAY;

            // Draw the filled cell
            DrawRectangle(col * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);

            // Draw the border around the cell
            DrawRectangleLines(col * cellSize, row * cellSize, cellSize, cellSize, borderColor);
        }
    }
}

void Grid::update() {
    // Implement any grid update logic here
}

void Grid::reset() {
    for (const auto& cell : this->activeCells) {
        this->cells[cell.first][cell.second].deactivate();
    }

    this->activeCells.clear();
}

bool Grid::isWithinGrid(int row, int column) {
    return row >= 0 && row < this->rows && column >= 0 && column < this->columns;
}
