#include "raylib.h"
#include <iostream>

const float SCREEN_WIDTH = 500;
const float SCREEN_HEIGHT = 500;
const char* SCREEN_TITLE = "Rectangle";

void update_direction(bool& up, bool& down, bool& right, bool& left, Rectangle& rec) {
    if (rec.y < 0) {
        up = false; down = true;
    } else if (rec.y > SCREEN_HEIGHT - rec.height) {
        up = true; down = false;
    }

    if (rec.x < 0) {
        left = false; right = true;
    } else if (rec.x > SCREEN_WIDTH - rec.width) {
        left = true; right = false;
    }
}


int main() {
    // Initialize Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    // Parâmetros do retângulo
    Rectangle rec = Rectangle{SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 100, 100};
    // flags de direção do retângulo
    bool up = false, down = true, right = true, left = false;

    // Render Loop
    while(!WindowShouldClose()) {
        // <--- Update System --->
        update_direction(up, down, right, left, rec);

        rec.x += left * -0.1 + right * 0.1;
        rec.y += up * -0.05 + down * 0.05;

        // <--- Render --->
        BeginDrawing();
            ClearBackground(BLACK);
            //DrawRectangle(rec.x, rec.y, rec.width, rec.height, SKYBLUE);
            // DrawRectangleV(rect_pos, rect_dim, LIME);
            // DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, GOLD);
            // DrawRectangleLinesEx(rec, 10, GRAY);
            // DrawRectanglePro(rec, Vector2{0, 0}, 0, PINK);
            DrawRectangleGradientH(rec.x, rec.y, rec.width, rec.height, SKYBLUE, PINK);

        EndDrawing();
    }

    // Close openGL state
    CloseWindow();


    return 0;
}
