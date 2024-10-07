//main.cpp
#include "Application.hpp"

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int cellSize = 15;
    const int FPS = 6;

    // Create and run the application
    Application app(screenWidth, screenHeight, cellSize, FPS);
    app.run();

    return 0;
}
