#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <cstdlib>


const float SCREEN_WIDTH = 500;
const float SCREEN_HEIGHT = 500;
const char* SCREEN_TITLE = "Pixels";

// return a random umber in {-1, 0, 1}
int random_number(std::vector<int> numbers) {
    return numbers.at(rand() % numbers.size());
}

// Screen edges
bool edges(Vector2 pixel) {
    bool horizontal = pixel.x >= 0 && pixel.x <= SCREEN_WIDTH;
    bool vertical = pixel.y >= 0 && pixel.y <= SCREEN_HEIGHT;

    return horizontal && vertical;
}

// decision function to move a agent through the screen like a chees tower
Vector2 random_walk() {
    std::vector<int> motion_full{-1, 0, 1}; std::vector<int> motion_partial{-1, 1};
    float dx = random_number(motion_full);
    float dy = dx == 0 ? random_number(motion_partial) : 0;

    return Vector2{dx, dy};
}

Vector2 update_pixel(Vector2 pixel) {
    Vector2 new_pixel = Vector2Add(pixel, random_walk());
    return edges(new_pixel) ? new_pixel : pixel;
}


int main(){
    // Initialize window.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    // Pixels start
    std::vector<Vector2> pixels;
    Vector2 pixel_b{SCREEN_WIDTH/3, SCREEN_HEIGHT/3};
    Vector2 pixel_r{(2.0f/3.0f)*SCREEN_WIDTH, (2.0f/3.0f)*SCREEN_HEIGHT};
    pixels.push_back(pixel_b); pixels.push_back(pixel_r);

    // Pixels speed
    unsigned speed = 100;
    
    // Render loop.
    while (!WindowShouldClose())
    {
        // <----- UPDATE ----->
        for (int i=0; i < speed; ++i) {
            pixel_b = update_pixel(pixel_b);
            pixel_r = update_pixel(pixel_r);
            pixels.push_back(pixel_b); pixels.push_back(pixel_r);
        }

        // <----- RENDER ----->
        BeginDrawing();
            // Clear Background
            ClearBackground(BLACK);
            // <--- DRAW --->
            for (int i=0; i < pixels.size(); ++i) {
                i%2 == 0 ?  DrawPixel(pixels.at(i).x, pixels.at(i).y, BLUE) : DrawPixel(pixels.at(i).x, pixels.at(i).y, RED);          
            }
            
        EndDrawing();
    }
    // De Initialize context of opengl.
    CloseWindow();
}