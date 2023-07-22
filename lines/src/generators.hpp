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


// Escreve as linhas que formam uma espiral quadrada em um arquivo .txt
int square_spiral(unsigned line_size, unsigned n_points, std::string path) {
     // Open a text file for writing
    std::ofstream output_file(path);

    if (!output_file) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
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
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }
    output_file << std::fixed << std::setprecision(6);

    std::vector<Command> commands;
    commands.push_back(Command{size, angle});
    // Recursive process to generate commands to draw the koch curve
    
    float length = commands.at(0).length;
    std::vector<Command> new_commands;
    for (Command command : commands) {
        new_commands.push_back(Command{length/3.0f, command.angle});
        new_commands.push_back(Command{length/3.0f, command.angle + 60});
        new_commands.push_back(Command{length/3.0f, command.angle - 120});
        new_commands.push_back(Command{length/3.0f, command.angle + 60});
    }

    for (Command command: new_commands) {
        output_file << command.length << " " << command.angle << std::endl;
    }
    // Close the file
    output_file.close();
    return 0;
}