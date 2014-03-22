#ifndef HOMEWORK2_SRC_GAME_GRID_H_
#define HOMEWORK2_SRC_GAME_GRID_H_

#include <iostream>

// There should be just one block of zero in the grid
class GameGrid
{
 public:
    enum { kSize = 3 };
    enum { Up, Left, Down, Right };

    explicit GameGrid(const int grid[][kSize]);
    bool HasSolution() const;
    bool CanMove(int direction) const;
    bool Move(int direction);
    const int * operator[](int index) const { return entry_[index]; }

 private:
    int entry_[kSize][kSize];
    int zero_row_;
    int zero_col_;
};

bool operator==(const GameGrid &grid1, const GameGrid &grid2);
std::ostream & operator<<(std::ostream &os, const GameGrid &grid);

#endif  // HOMEWORK2_SRC_GAME_GRID_H_
