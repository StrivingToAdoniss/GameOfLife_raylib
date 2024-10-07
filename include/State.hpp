//State.hpp
#pragma once

class Application; // Forward declaration

class State {
public:
    virtual ~State() = default;

    virtual void update(Application& app) = 0;
    virtual void draw(Application& app) const = 0;
};

