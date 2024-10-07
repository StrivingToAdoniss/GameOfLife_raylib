// Cell.cpp
#include "Cell.hpp"

Cell::Cell(int cellSize) {
    this->isAlive = false;
    this->setSize(cellSize);
}


void Cell::activate(){
    if(!this->isAlive){
        this->isAlive = true;
    }
}

void Cell::deactivate(){
    if(this->isAlive){
        this->isAlive = false;
    }
}

void Cell::setSize(int size){
    this->size = size;
}

bool Cell::getIsAlive() const{
 return this->isAlive;
}

int Cell::getSize() const{
    return this->size;
}

void Cell::toggle(){
    this->isAlive = !this->isAlive;
}