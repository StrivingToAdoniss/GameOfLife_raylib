// ControlsState.cpp
#include "ControlsState.hpp"
#include "Application.hpp"
#include "MainMenuState.hpp"

ControlsState::ControlsState(Application& app) {
    // Initialize any state-specific data here if needed
}

void ControlsState::update(Application& app) {
    // Return to the main menu if ESC is pressed
    if (IsKeyPressed(KEY_ESCAPE)) {
        // Pass the `Application&` directly to `MainMenuState`
        app.changeState(new MainMenuState(app));
    }
}

void ControlsState::draw(Application& app) const {
    ClearBackground({55, 55, 55, 255});
    
    int screenWidth = app.getScreenWidth();
    int screenHeight = app.getScreenHeight();
    
    // Font size and spacing for each line
    int fontSize = 18;
    int spacing = 10; // Space between lines

    // List of control texts
    std::vector<std::pair<std::string, int>> controlTexts = {
        {"Controls:", 20}, 
        {"UP arrow: Speed up", fontSize}, 
        {"DOWN arrow: Slow down", fontSize}, 
        {"R: Restart simulation", fontSize}, 
        {"ESC: Return to menu / Quit", fontSize},
        {"M: Mute music", fontSize}, 
        {"N: Next track", fontSize},
        {"B: Previous track", fontSize},
        {"Press ESC to go back", 20}
    };

    // Calculate total height of all text lines (sum of text heights + spacings)
    int totalHeight = 0;
    for (auto& [text, size] : controlTexts) {
        totalHeight += size + spacing;
    }
    totalHeight -= spacing; // Remove extra spacing after the last line

    // Starting y position for centering
    int startY = (screenHeight / 2) - (totalHeight / 2);

    // Draw each line of text centered horizontally and vertically
    int yOffset = startY;
    for (auto& [text, size] : controlTexts) {
        int textWidth = MeasureText(text.c_str(), size);
        int xPosition = screenWidth / 2 - textWidth / 2;
        DrawText(text.c_str(), xPosition, yOffset, size, WHITE);

        // Update yOffset for the next line
        yOffset += size + spacing;
    }
}

