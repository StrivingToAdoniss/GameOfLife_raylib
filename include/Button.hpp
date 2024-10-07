//Button.hpp
#pragma once
#include <raylib.h>
#include <string>

class Button {
private:
    Rectangle bounds;
    std::string text;
    Color normalColor;
    Color hoverColor;

public:
    bool hovered;

    Button(float x, float y, float width, float height, const std::string& text);

    void draw() const;
    bool isHovered() const;
    bool isClicked() const;
};
