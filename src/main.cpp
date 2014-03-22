#include <cstdlib>
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
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

    std::vector<std::deque<int>> solutions = FindSolution(grid);

    if (solutions.empty())
    {
        std::cout << "no solution\n";
        fout << "no solution\n";
        return 0;
    }
    // else there is at least one solution
    // for every solution
    int solution_count = 1;
    for (auto solution : solutions)
    {
        // use a new grid to show
        GameGrid showing_grid(grid);
        int step_count = solution.size();

        std::cout << "Solution " << solution_count << ":\n"
                  << step_count << "\n\n";
        fout << "Solution " << solution_count << ":\n"
             << step_count << "\n\n";

        for (int direction : solution)
        {
            showing_grid.Move(direction);
            std::cout << grid << std::endl;
            fout << grid << std::endl;
        }

        std::cout << "\n\n";
        fout << "\n\n";
    }

    return 0;
}
