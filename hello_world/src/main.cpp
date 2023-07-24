#include "raylib.h"

const float SCREEN_WIDTH = 500;
const float SCREEN_HEIGHT = 500;
const char* SCREEN_TITLE = "Hello World";

int main() {
    // Initialize Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    // Render Loop
    while(!WindowShouldClose()) {
        // <--- Update System --->

        // <--- Render --->
        BeginDrawing();
            ClearBackground(BLACK);
            // Draw
            DrawCircle(250, 250, 100, ORANGE);

        EndDrawing();
    }

    // Close openGL state
    CloseWindow();


    return 0;
}
