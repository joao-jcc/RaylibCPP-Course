#include "raylib.h"
#include <iostream>

const float SCREEN_WIDTH = 500;
const float SCREEN_HEIGHT = 500;
const char* SCREEN_TITLE = "Triangles";


int main(){
    // Initialize window.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    // Triangle Vertex
    Vector2 p1 = Vector2{200, 200};
    Vector2 p2 = Vector2{400, 200};
    Vector2 p3 = Vector2{300, 400};

    // Render loop.
    while (!WindowShouldClose())
    {
        // <----- UPDATE ----->

        // <----- RENDER ----->
        BeginDrawing();
            // Clear Background
            ClearBackground(Color{13,17,23,255});
            // <--- DRAW --->
            DrawTriangle(p2, p1, p3, WHITE);
            DrawTriangleLines(p1, p2, p3, RED);
        EndDrawing();
    }
    // De Initialize context of opengl.
    CloseWindow();
}