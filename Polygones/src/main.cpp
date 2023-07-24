#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cmath>

const float SCREEN_WIDTH = 500;
const float SCREEN_HEIGHT = 500;
const char* SCREEN_TITLE = "Polygones";

float radians(float degree) {
    return (M_PI/180) * degree;
}


int main(int argc, char* argv[]){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    // Initialize window.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    // Triangle Vertex
    Vector2 center{SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
    // angle speed degrees/second
    float rotation_speed = 90;
    float translation_speed = 2;

    // angles trasnlations and rotation
    float angle_rot;
    float angle_trans;
    // Render loop.
    float time;
    while (!WindowShouldClose())
    {
        // <----- UPDATE ----->
        time = GetTime();
        angle_rot = rotation_speed * time;
        angle_trans = translation_speed * time;
        
        Color blue = BLUE;
        Color skyblue= SKYBLUE;
        float color_factor = std::sin(time)/2.0f + 0.5f;
        blue.g *= color_factor;
        blue.b *= color_factor;
        skyblue.g *= color_factor;
        skyblue.b *= color_factor;



        center.x = 250 + 50 * std::cos(angle_trans);
        center.y = 250 + 50 * std::sin(angle_trans);
        // <----- RENDER ----->
        BeginDrawing();
            // Clear Background
            ClearBackground(BLACK);
            // <--- DRAW --->
            DrawPoly(center, 8, 150, angle_rot, skyblue);
            for (int i=1; i < 20; ++i) {
                DrawPolyLinesEx(center, 8, 150 - i*10, angle_rot + i*10, 30, i%2 == 0 ? skyblue : blue);
            }

        EndDrawing();

    }
    // De Initialize context of opengl.
    CloseWindow();
}