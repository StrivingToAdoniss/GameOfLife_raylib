//Button.cpp
#include "Button.hpp"

Button::Button(float x, float y, float width, float height, const std::string& text)
    : bounds({x, y, width, height}), text(text),
      normalColor(GRAY), hoverColor(LIGHTGRAY), hovered(false) {}

void Button::draw() const {
    Color currentColor = hovered ? hoverColor : normalColor;

    DrawRectangleRec(bounds, currentColor);
    DrawRectangleLinesEx(bounds, 2, BLACK);
    DrawText(text.c_str(), bounds.x + (bounds.width - MeasureText(text.c_str(), 20)) / 2,
             bounds.y + (bounds.height - 20) / 2, 20, BLACK);
}

bool Button::isHovered() const {
    return CheckCollisionPointRec(GetMousePosition(), bounds);
}

bool Button::isClicked() const {
    return isHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
