#include "game_grid.h"

GameGrid::GameGrid(const int grid[][kSize])
        : zero_row_(-1),
          zero_col_(-1)
{
    for (int row = 0; row < kSize; row++)
        for (int col = 0; col < kSize; col++)
        {
            int entry = grid[row][col];
            entry_[row][col] = entry;
            if (entry == 0)
            {
                // assume there is exactly one zero in grid
                zero_row_ = row;
                zero_col_ = col;
            }
        }
}

// while moving, the inversed sum of the 'S' shape stay the same
bool GameGrid::HasSolution() const
{
    int inversed_sum = 0;
    for (int row = 0; row < kSize; row++)
        for (int col = 0; col < kSize; col++)
        {
            int number = entry_[row][col];
            if (number == 0)
                continue;
            // inversed on the same row
            if (row % 2 == 0)  // an even row
            {
                for (int j = col + 1; j < kSize; j++)
                {
                    // NOTICE: use > so 0 will never succeed
                    if (entry_[row][j] > number)
                        inversed_sum++;
                }
            }
            else  // an odd row
            {
                for (int j = col - 1; j >= 0; j--)
                {
                    if (entry_[row][j] > number)
                        inversed_sum++;
                }
            }
            // inversed on the rows below
            for (int i = row + 1; i < kSize; i++)
                for (int j = 0; j < kSize; j++)
                {
                    if (entry_[i][j] > number)
                        inversed_sum++;
                }
        }
    if (inversed_sum % 2 == 1)
        return false;
    return true;
}

bool GameGrid::CanMove(int direction) const
{
    switch (direction)
    {
        case Up:
        {
            if (zero_row_ == kSize - 1)
                return false;  // cannot move
            break;
        }
        case Down:
        {
            if (zero_row_ == 0)
                return false;  // cannot move
            break;
        }
        case Left:
        {
            if (zero_col_ == kSize - 1)
                return false;  // cannot move
            break;
        }
        case Right:
        {
            if (zero_col_ == 0)
                return false;  // cannot move
            break;
        }
        default:
        {
            return false;
        }
    }  // switch
    return true;
}

bool GameGrid::Move(int direction)
{
    switch (direction)
    {
        case Up:
        {
            if (zero_row_ == kSize - 1)
                return false;  // cannot move
            entry_[zero_row_][zero_col_] =
                    entry_[zero_row_ + 1][zero_col_];
            zero_row_++;
            break;
        }
        case Down:
        {
            if (zero_row_ == 0)
                return false;  // cannot move
            entry_[zero_row_][zero_col_] =
                    entry_[zero_row_ - 1][zero_col_];
            zero_row_--;
            break;
        }
        case Left:
        {
            if (zero_col_ == kSize - 1)
                return false;  // cannot move
            entry_[zero_row_][zero_col_] =
                    entry_[zero_row_][zero_col_ + 1];
            zero_col_++;
            break;
        }
        case Right:
        {
            if (zero_col_ == 0)
                return false;  // cannot move
            entry_[zero_row_][zero_col_] =
                    entry_[zero_row_][zero_col_ - 1];
            zero_col_--;
            break;
        }
    }  // switch
    // set the new zero
    entry_[zero_row_][zero_col_] = 0;
    return true;
}

bool operator==(const GameGrid &grid1, const GameGrid &grid2)
{
    for (int row = 0; row < GameGrid::kSize; row++)
        for (int col = 0; col < GameGrid::kSize; col++)
        {
            if (grid1[row][col] != grid2[row][col])
                return false;
        }
    return true;
}

std::ostream & operator<<(std::ostream &os, const GameGrid &grid)
{
    for (int row = 0; row < GameGrid::kSize; row++)
    {
        for (int col = 0; col < GameGrid::kSize; col++)
        {
            os << grid[row][col];
        }
        os << std::endl;
    }
    return os;
}
