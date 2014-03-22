#ifndef HOMEWORK2_SRC_A_STAR_H_
#define HOMEWORK2_SRC_A_STAR_H_

#include <deque>
#include <vector>
#include "game_grid.h"

// Return certain number of solutions (at most), packed in a vector
// of int deques of solutions, empty vector if no solution.
// Represented by enum in GameGrid.
std::vector<std::deque<int>> FindSolution(const GameGrid &grid,
                                          int solution_number = 1);

#endif  // HOMEWORK2_SRC_A_STAR_H_
