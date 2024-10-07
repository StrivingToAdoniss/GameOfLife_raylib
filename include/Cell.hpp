// Cell.hpp
#pragma once

class Cell {
    private:
        bool isAlive = false;
        int size;



    public:
        Cell(int cellSize);
        bool getIsAlive() const;

        int getSize() const;
        void setSize(int size);

        void activate();
        void deactivate();

        void toggle();

};