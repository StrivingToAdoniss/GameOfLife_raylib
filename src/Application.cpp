// Application.cpp
#include "Application.hpp"
#include "MainMenuState.hpp"

Application::Application(int width, int height, int cellSize, int FPS)
    : screenWidth(width), screenHeight(height), cellSize(cellSize), FPS(FPS),
      grid(height, width, cellSize), simulation(grid, FPS), currentState(nullptr), running(true),
      musicManager({"assets/music/Life in Motion.mp3"}, 0.5f) { 

    InitWindow(screenWidth, screenHeight, "Conway's Game of Life");

    SetExitKey(KEY_NULL);

    Image icon = LoadImage("assets/icon.ico");
    SetWindowIcon(icon);
    UnloadImage(icon);

    SetTargetFPS(60);

    WaitTime(1);

    // Start in the main menu (pass 'this' as reference)
    changeState(new MainMenuState(*this));
}

Application::~Application() {
    delete currentState; // Clean up state

    CloseWindow();
}

void Application::run() {
   // Create a map that associates keys with their actions
   std::map<int, std::function<void()>> keyActions = {
        {KEY_M, [this]() { musicManager.toggleMute(); }},
        {KEY_N, [this]() { musicManager.nextTrack(); }},
        {KEY_B, [this]() { musicManager.previousTrack(); }}
    };

    while (!WindowShouldClose() && running) {
        // Update music stream
        musicManager.update();

        // Iterate over the key-action map
        for (const auto& [key, action] : keyActions) {
            if (IsKeyPressed(key)) {
                action(); // Call the action associated with the key
            }
        }

        // Update and draw the current state
        currentState->update(*this);

        BeginDrawing();
        currentState->draw(*this);
        EndDrawing();
    }
}


void Application::changeState(State* newState) {
    if (currentState) delete currentState; // Clean up the old state
    currentState = newState;
}

void Application::quit() {
    running = false;
}
