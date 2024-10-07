// MainMenuState.cpp
#include "MainMenuState.hpp"
#include "Application.hpp"
#include "SimulationState.hpp"
#include "ControlsState.hpp"

MainMenuState::MainMenuState(Application& app)
    : startButton(app.getScreenWidth() / 2 - 100, app.getScreenHeight() / 2 - 50, 200, 50, "Start Simulation"),
      controlsButton(app.getScreenWidth() / 2 - 100, app.getScreenHeight() / 2 + 20, 200, 50, "Controls"), 
      exitButton(app.getScreenWidth() / 2 - 100, app.getScreenHeight() / 2 + 90, 200, 50, "Exit") // Initialize exit button
{}

void MainMenuState::update(Application& app) {
    // Handle button interactions
    startButton.hovered = startButton.isHovered();
    controlsButton.hovered = controlsButton.isHovered();
    exitButton.hovered = exitButton.isHovered();

    // Transition to the appropriate state based on user input
    if (startButton.isClicked()) {
        app.changeState(new SimulationState(app)); // Transition to simulation state
    } else if (controlsButton.isClicked()) {
        app.changeState(new ControlsState(app)); // Transition to controls state
    } else if (exitButton.isClicked()) {
        app.quit(); // Exit the application
    }
}

void MainMenuState::draw(Application& app) const {
    ClearBackground({55, 55, 55, 255}); // Main menu background color

    int titleX = (app.getScreenWidth() - MeasureText(title.c_str(), titleFontSize)) / 2;
    int titleY = 350; // Distance from the top of the screen

    // Draw the title
    DrawText(title.c_str(), titleX, titleY, titleFontSize, WHITE);

    startButton.draw();
    controlsButton.draw();
    exitButton.draw(); 
}
