#include "raylib.h"
#include <vector>
#include <cmath> 
#include <fstream>
#include <iostream>
#include <iomanip>

typedef struct Command {
    float length;
    float angle;
} Command;

void read_commands(std::string path, std::vector<Command>& commands) {
    // Open the input file
    std::ifstream input_file(path);

    // Check if the file was opened successfully
    if (!input_file) {
        std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
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



int square_spiral(unsigned line_size, unsigned n_points, std::string path) {
     // Open a text file for writing
    std::ofstream output_file(path);

    if (!output_file) {
        std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
        return 1;
    }

    float size = line_size;
    for (unsigned i=0; i<n_points; ++i) {
        output_file << size << " 90" << std::endl;
        if (i%2 == 0 || i == 0) {size += line_size;};
    }

    // Close the file
    output_file.close();
    return 0;
}


int koch(float size, float angle, unsigned epochs, std::string path) {
    // Open a text file for writing
    std::ofstream output_file(path);

    if (!output_file) {
        std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
        return 1;
    }

    std::vector<Command> commands;
    commands.push_back(Command{size, angle});
    // Recursive process to generate commands to draw the koch curve

    for (unsigned i = 0; i < epochs; ++i) {
        std::vector<Command> new_commands;
        for (const Command& command : commands) {
            float length = command.length / 3.0f;
            new_commands.push_back(Command{length, command.angle});
            new_commands.push_back(Command{length, 60});
            new_commands.push_back(Command{length, -120});
            new_commands.push_back(Command{length, 60});
        }
        commands = new_commands;
    }

    // Print commands to the file, separated by a space
    for (const Command& command : commands) {
        output_file << command.length << " " << command.angle << std::endl;
    }

    // Close the file
    output_file.close();
    return 0;
}

int koch_triangle(std::string input_path, std::string output_path) {
    // Open a text file for writing
    std::ofstream output_file(output_path);

    if (!output_file) {
        std::cerr << "Erro ao abrir o arquivo: " << output_path << std::endl;
        return 1;
    }

    std::vector<Command> commands;
    read_commands(input_path, commands);

    float length = commands.at(0).length;
    unsigned size = commands.size();

    std::vector<Command> commands_copy;
    for (int i=0; i < size; ++i) {
        commands_copy.push_back(commands.at(i));
    }

    commands.push_back(Command{length, -120});
    for (int i=1; i < size; ++i) {
        commands.push_back(commands_copy.at(i));
    }
    commands.push_back(Command{length, -120});
    for (int i=1; i < size; ++i) {
        commands.push_back(commands_copy.at(i));
    }

    for (const Command& command : commands) {
        output_file << command.length << " " << command.angle << std::endl;
    }

    // Close the file
    output_file.close();
    return 0;

}