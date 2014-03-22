#include <cstdlib>
#include <iostream>
#include <fstream>
#include <deque>
#include "game_grid.h"
#include "a_star.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        std::exit(EXIT_FAILURE);
    }

    std::ofstream fout(argv[2]);
    if (!fout.is_open())
    {
        std::cerr << "Cannot open output file: (" << argv[2] << ")\n";
        std::exit(EXIT_FAILURE);
    }

    std::ifstream fin(argv[1]);
    if (!fin.is_open())
    {
        std::cerr << "Cannot open input file: (" << argv[1] << ")\n";
        std::exit(EXIT_FAILURE);
    }

    // buffer the game grid temporarily
    int grid_buffer[GameGrid::kSize][GameGrid::kSize];
    for (int row = 0; row < GameGrid::kSize; row++)
        for (int col = 0; col < GameGrid::kSize; col++)
        {
            char number_char;
            if (!(fin >> number_char))
            {
                std::cerr << "Cannot read number on "
                        "(" << row << ", " << col << ")\n";
                std::exit(EXIT_FAILURE);
            }
            grid_buffer[row][col] = number_char - '0';
        }

    fin.close();
    GameGrid grid(grid_buffer);

    std::deque<int> solution = FindSolution(grid);

    if (solution.empty())
    {
        std::cout << "no solution\n";
        fout << "no solution\n";
        return 0;
    }
    // else there is a solution
    int step_count = solution.size();
    std::cout << step_count << "\n\n";
    fout << step_count << "\n\n";
    for (int step = 0; step < step_count; step++)
    {
        grid.Move(solution[step]);
        std::cout << grid << std::endl;
        fout << grid << std::endl;
    }

    return 0;
}
