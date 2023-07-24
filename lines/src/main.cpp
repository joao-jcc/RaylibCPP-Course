#include "raylib.h"
#include "raymath.h"
#include "CLI11.hpp"
#include "Colors.hpp"
#include "generators.hpp"

#include <iostream>
#include <cmath> 
#include <vector>
#include <string>
#include <fstream>


float SCREEN_WIDTH;
float SCREEN_HEIGHT;
const char* SCREEN_TITLE = "Lines";


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
    CLI::App app{"Draw lines"};

    // Add a subcommand for generating the square spiral
    CLI::App* square_spiral_cmd = app.add_subcommand("square_spiral", "Generate square spiral");
    int square_spiral_size = 6;
    int square_spiral_points = 60;
    std::string square_spiral_path="";
    square_spiral_cmd->add_option("--size", square_spiral_size, "Size of the square spiral");
    square_spiral_cmd->add_option("--points", square_spiral_points, "Number of points in the square spiral");
    square_spiral_cmd->add_option("--path", square_spiral_path, "Path to save square spiral");

    // Add a subcommand for generating the Koch curve
    CLI::App* koch_cmd = app.add_subcommand("koch", "Generate Koch curve");
    int koch_size = 999;
    int koch_angle = 0;
    int koch_epochs = 7;
    std::string koch_path;
    koch_cmd->add_option("--size", koch_size, "Size of the Koch curve");
    koch_cmd->add_option("--angle", koch_angle, "Angle of the Koch curve");
    koch_cmd->add_option("--epochs", koch_epochs, "Number of epochs for the Koch curve");
    koch_cmd->add_option("--path", koch_path, "Path to save Koch curve");

        // Add a subcommand for generating the Koch curve
    CLI::App* koch_t_cmd = app.add_subcommand("koch_t", "Generate Koch triangles curve");
    std::string koch_t_input, koch_t_output;
    koch_t_cmd->add_option("--input", koch_t_input, "Path for input Kock curve");
    koch_t_cmd->add_option("--output", koch_t_output, "Path for output Kock curve");

    // Add command-line options for origin, draw rate, and path command
    float draw_rate=10;
    std::string path_command="";
    std::string origin_str="";
    std::string screen_str="";
    auto* main_cmd = app.add_option_group("Main Command", "Main command options");
    main_cmd->add_option("--origin", origin_str, "Origin coordinates (X,Y)");
    main_cmd->add_option("--screen", screen_str, "Screen Dimensions (WIDTH HEIGHT)");
    main_cmd->add_option("--rate", draw_rate, "Draw rate");
    main_cmd->add_option("--path", path_command, "Path to commands file");

    // Parse the command-line arguments
    CLI11_PARSE(app, argc, argv);

    // Check if any subcommand is provided

    if (square_spiral_cmd->parsed()) {
        // Generate the square spiral
        if (square_spiral_cmd->count("--size") == 0 || square_spiral_cmd->count("--points") == 0 || square_spiral_cmd->count("--path") == 0) {
            std::cerr << "Error: Missing required option(s) for the square_spiral command: --size --points --path" << std::endl;
            return 1;
        }
        square_spiral(square_spiral_size, square_spiral_points, square_spiral_path);
        return 0;
    }

    if (koch_cmd->parsed()) {
        if (koch_cmd->count("--size") == 0 || koch_cmd->count("--angle") == 0 || koch_cmd->count("--epochs") == 0 || koch_cmd->count("--path") == 0) {
            std::cerr << "Error: Missing required option(s) for the square_spiral command: --size --angle --epochs --path" << std::endl;
            return 1;
        }
        // Generate the Koch curve
        koch(koch_size, koch_angle, koch_epochs, koch_path);
        return 0;
    }

    if (koch_t_cmd->parsed()) {
        if (koch_t_cmd->count("--input") == 0 || koch_t_cmd->count("--output") == 0) {
            std::cerr << "Error: Missing required option(s) for the square_spiral command: --input --output" << std::endl;
            return 1;
        }
        // Generate the Koch curve
        koch_triangle(koch_t_input, koch_t_output);
        return 0;
    }

    // If no subcommand is provided, proceed to draw lines
    // Check for the required options for the main command
    if (origin_str.empty() || screen_str.empty() || path_command.empty() || draw_rate == 0) {
        std::cerr << "Error: Missing required option(s) for the main command: --origin --rate --screen --path" << std::endl;
        return 1;
    }
    
    // Split the origin_str into individual X and Y coordinates
    size_t comma_pos = origin_str.find(",");
    float origin_x = std::stof(origin_str.substr(0, comma_pos));
    float origin_y = std::stof(origin_str.substr(comma_pos + 1));

    // Split the origin_str into individual X and Y coordinates
    comma_pos = screen_str.find(",");
    SCREEN_WIDTH = std::stof(screen_str.substr(0, comma_pos));
    SCREEN_HEIGHT = std::stof(screen_str.substr(comma_pos + 1));

    // Reading and storing the commands from the specified file
    std::vector<Command> commands;
    read_commands(path_command, commands);

    Vector2 origin{origin_x, origin_y};
    draw(origin, draw_rate, commands);

    return 0;
}
