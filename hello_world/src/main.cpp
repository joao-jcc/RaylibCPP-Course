#include "raylib.h"

const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 600;
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
            DrawCircle(100, 100, 100, ORANGE);

        EndDrawing();
    }

    // Close openGL state
    CloseWindow();


    return 0;
}
