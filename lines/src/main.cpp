#include "raylib.h"
#include "raymath.h"
#include "Colors.hpp"
#include "generators.hpp"

#include <iostream>
#include <cmath> 
#include <vector>
#include <string>
#include <fstream>


const float SCREEN_WIDTH = 500;
const float SCREEN_HEIGHT = 500;
const char* SCREEN_TITLE = "Lines";


void read_commands(std::string file_path, std::vector<Command>& commands) {
    // Open the input file
    std::ifstream input_file(file_path);

    // Check if the file was opened successfully
    if (!input_file) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        exit(1);
    }

    // Read each Command from the file and store it in a vector
    Command command;
    while (input_file >> command.length >> command.angle) {
        // Add the read command struct to the vector
        commands.push_back(command);
    }

    // Close the input file
    input_file.close();
}

float radians(float degree) {
    return (M_PI/180) * degree;
}

Vector2 get_end_point(Vector2& start, float angle, float length) {
    float new_x = start.x + cos(-radians(angle)) * length;
    float new_y = start.y + sin(-radians(angle)) * length;

    return Vector2{new_x, new_y};
}

void draw_partial_line(Vector2& start, Vector2& end, float pixels_to_draw, float clock) {
    Vector2 direction = Vector2Normalize(Vector2Subtract(end, start));
    Vector2 step = Vector2Scale(direction, pixels_to_draw);
    Vector2 temp_end = Vector2Add(start, step);
    DrawLineEx(start, temp_end, 0.5, GOLD);
}

void draw(Vector2&origin, float draw_rate, std::vector<Command>& commands) {
    float clock = 0.0f;
 
    // Initialize Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    // Render Loop
    float pixels_to_draw = 0.0f; 
    float angle = 0.0f;
    Vector2 end; Vector2 start = origin;
    while(!WindowShouldClose()) {

        // <--- Update System --->
        clock += GetFrameTime();
        pixels_to_draw = clock * draw_rate;

        // <--- Render --->
        BeginDrawing();
            ClearBackground(BLACK);
            // Draw
            for (Command& command : commands) {
                pixels_to_draw -= command.length;
                angle = ((int)angle + (int)command.angle) % 360;
                end = get_end_point(start, angle, command.length);
                if (pixels_to_draw >= 0) {
                    DrawLineEx(start, end, 0.5, GOLD);
                } else {
                    draw_partial_line(start, end, pixels_to_draw + command.length, clock);
                    break;
                }
                start = end;
            }

            // Reset Draw to the next frame
            angle = 0.0f;
            start = origin;

        EndDrawing();
    }

    // Close openGL state
    CloseWindow();

}

int main(int argc, char* argv[]) {
    // Generates a square spiral with 60 points and line length of 6
    square_spiral(6, 60, "lines/src/square_spiral.txt");
    koch(100, 0, 1, "lines/src/koch.txt");
    if (argc != 5) {
        std::cout << "Uso: [executável] [origin_x origin_y] [draw_rate] [path_command]" << std::endl;
        return 1;
    }

    // Convert command-line arguments to the appropriate types
    float origin_x = std::stof(argv[1]);
    float origin_y = std::stof(argv[2]);
    float draw_rate = std::stof(argv[3]);
    std::string path_command = argv[4];

    // Reading and storing the commands from the specified file
    std::vector<Command> commands;
    read_commands(path_command, commands);

    Vector2 origin{origin_x, origin_y};
    draw(origin, draw_rate, commands);

    return 0;
}