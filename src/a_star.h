#ifndef HOMEWORK2_SRC_A_STAR_H_
#define HOMEWORK2_SRC_A_STAR_H_

#include <deque>
#include "game_grid.h"

// Return int deque of solution, empty deque if no solution.
// Represented by enum in GameGrid.
std::deque<int> FindSolution(const GameGrid &grid);

#endif  // HOMEWORK2_SRC_A_STAR_H_
