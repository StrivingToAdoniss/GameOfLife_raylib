// Rule.hpp
#pragma once

class Rule {
public:
    virtual bool applyRule(bool currentState, int aliveNeighbors) const = 0;
    virtual ~Rule() = default;
};

class LiveCellRule : public Rule {
public:
    bool applyRule(bool currentState, int aliveNeighbors) const override {
        // Any live cell with two or three live neighbors survives.
        return (aliveNeighbors == 2 || aliveNeighbors == 3);
    }
};

class DeadCellRule : public Rule {
public:
    bool applyRule(bool currentState, int aliveNeighbors) const override {
        // Any dead cell with exactly three live neighbors becomes a live cell.
        return (aliveNeighbors == 3);
    }
};
