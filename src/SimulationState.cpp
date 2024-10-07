// SimulationState.cpp
#include "SimulationState.hpp"
#include "Application.hpp"
#include "MainMenuState.hpp"

SimulationState::SimulationState(Application& app) {
    app.getSimulation().randomizeGrid();
}

void SimulationState::update(Application& app) {
    // Get delta time for this frame
    float deltaTime = GetFrameTime();

    // Mute/unmute music, reset simulation, and change speed as before
    if (IsKeyPressed(KEY_ESCAPE)) {
        app.changeState(new MainMenuState(app));
    }
    if (IsKeyPressed(KEY_R)) {
        app.getSimulation().reset();
        app.getSimulation().randomizeGrid();
    }
    if (IsKeyPressed(KEY_UP)) {
        app.getSimulation().increaseSpeed();
    }
    if (IsKeyPressed(KEY_DOWN)) {
        app.getSimulation().decreaseSpeed();
    }

    // Calculate target frame time based on simulation FPS
    const float targetFrameTime = 1.0f / app.getSimulation().getFPS();

    // Accumulate time
    accumulatedTime += deltaTime;

    // Update the simulation based on the accumulated time
    while (accumulatedTime >= targetFrameTime) {
        app.getSimulation().update(); // Call the simulation's update method
        accumulatedTime -= targetFrameTime;
    }
}

void SimulationState::draw(Application& app) const {
    ClearBackground({55, 55, 55, 255});
    app.getSimulation().draw();

    // Display current FPS (simulation speed)
    int fps = app.getSimulation().getFPS();
    DrawText(TextFormat("Speed: %d FPS", fps), 10, 10, 20, WHITE);
}
