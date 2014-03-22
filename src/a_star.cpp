#include "a_star.h"  // which include game_grid.h
#include <cmath>
#include <list>
#include <deque>
#include <vector>

namespace
{
// helper class
// FindSolution will find and save the solution to a deque
// (empty if no solutions).
// solution() will return the solution.
class AStar
{
 public:
    explicit AStar(const GameGrid &grid);
    ~AStar();
    bool FindSolution();

    std::deque<int> solution() const { return solution_; }

 private:
    struct Node
    {
     public:
        explicit Node(const GameGrid &grid);
        Node(const Node *p_old_node, int direction);
        GameGrid grid;
        int g;
        int h;
        int f;
        int moved_direction;
        const Node *parent;
    };

    static int h(const GameGrid &grid);
    static bool IsGoal(const Node *node);

    bool HandleIfInOpen(Node *p_new_node);
    bool HandleIfInClosed(Node *p_new_node);
    void InsertToOpoen(Node *p_new_node);
    void GenerateSolution(const Node *p_goal_node);

    std::list<Node *> open_;
    std::list<Node *> closed_;
    std::deque<int> solution_;
};  // class AStar

// functions for AStar
AStar::AStar(const GameGrid &grid)
        : open_(),
          closed_(),
          solution_()
{
    Node *p_first_node = new Node(grid);
    // push the first node into the open
    open_.push_front(p_first_node);
}

AStar::~AStar()
{
    for (Node *p_node: open_)
        delete p_node;  // delete nodes in open
    for (Node *p_node: closed_)
        delete p_node;  // delete nodes in closed
}

bool AStar::FindSolution()
{
    // keep popping the best node in open
    while (!open_.empty())
    {
        Node *best_node = open_.front();
        open_.pop_front();
        if (IsGoal(best_node))  // found the best solution
        {
            GenerateSolution(best_node);  // save the solution to deque
            return true;
        }
        closed_.push_front(best_node);  // add the node to closed
        for (int direction = 0; direction < 4; direction++)
        {
            if (!best_node->grid.CanMove(direction))
                continue;  // cannot move to this direction

            Node *p_new_node = new Node(best_node, direction);

            if (HandleIfInOpen(p_new_node))
                continue;  // already in open, handled
            if (HandleIfInClosed(p_new_node))
                continue;  // already in closed, handled
            // else it is a purely new node, add it to open
            InsertToOpoen(p_new_node);
        }
    }
    // no solutions, solution_ will stay empty
    return false;
}

// distant_sum
int AStar::h(const GameGrid &grid)
{
    // the start position of the entries
    static const int kStartPositionRow[GameGrid::kSize * GameGrid::kSize] =
            {-1, 0, 0, 0, 1, 2, 2, 2, 1};
    static const int kStartPositionCol[GameGrid::kSize * GameGrid::kSize] =
            {-1, 0, 1, 2, 2, 2, 1, 0, 0};
    int distant_sum = 0;
    for (int row = 0; row < GameGrid::kSize; row++)
        for (int col = 0; col < GameGrid::kSize; col++)
        {
            int entry = grid[row][col];
            if (entry > 0)
                distant_sum += std::abs(row - kStartPositionRow[entry])
                             + std::abs(col - kStartPositionCol[entry]);
        }
    return distant_sum;
}

inline bool AStar::IsGoal(const Node *node)
{
    return (node->h == 0);  // based on the way h() works
}

bool AStar::HandleIfInOpen(Node *p_new_node)
{
    for (auto iterator = open_.begin(); iterator != open_.end(); ++iterator)
    {
        Node *p_current_node = *iterator;
        if (p_current_node->grid == p_new_node->grid)  // same node found
        {
            if (p_current_node->g > p_new_node->g)  // new one is better
            {
                // delete the old node, remove it from open
                // and add the new node to open
                delete p_current_node;
                open_.erase(iterator);
                InsertToOpoen(p_new_node);
            }
            else  // nothing need to be done, just delete the new node
            {
                delete p_new_node;
            }
            return true;  // in open, and handled
        }
    }
    // not in open
    return false;
}


bool AStar::HandleIfInClosed(Node *p_new_node)
{
    for (auto iterator = closed_.begin(); iterator != closed_.end(); ++iterator)
    {
        Node *p_current_node = *iterator;
        if (p_current_node->grid == p_new_node->grid)  // same node found
        {
            if (p_current_node->g > p_new_node->g)  // new one is better.
            {
                // delete the old node, remove it from closed
                // and add the new node to open
                delete p_current_node;
                closed_.erase(iterator);
                InsertToOpoen(p_new_node);
            }
            else  // nothing need to be done, just delete the new node
            {
                delete p_new_node;
            }
            return true;  // in closed, and handled
        }
    }
    // not in closed.
    return false;
}

void AStar::InsertToOpoen(Node *p_new_node)
{
    int new_f = p_new_node->f;
    for (auto iterator = open_.begin(); iterator != open_.end(); ++iterator)
    {
        if ((*iterator)->f >= new_f)  // first worse node
        {
            // insert the new node before it
            open_.insert(iterator, p_new_node);
            return;
        }
    }
    // else the new node is the worst
    open_.push_back(p_new_node);
}

void AStar::GenerateSolution(const Node *p_goal_node)
{
    solution_.clear();  // make sure the deque is empty
    const Node *p_node = p_goal_node;
    while (p_node->parent)  // while the node still has a parent (not the root)
    {
        solution_.push_front(p_node->moved_direction);
        p_node = p_node->parent;
    }
}

AStar::Node::Node(const GameGrid &grid)
        : grid(grid),
          g(0),
          h(AStar::h(grid)),
          f(g + h),
          moved_direction(-1),
          parent(nullptr) {}

AStar::Node::Node(const Node *p_old_node, int direction)
        : grid(p_old_node->grid),
          g(p_old_node->g + 1),
          moved_direction(direction),
          parent(p_old_node)
{
    grid.Move(direction);
    h = AStar::h(grid);
    f = g + h;
}  // class Astar

}  // unnamed namespace

std::deque<int> FindSolution(const GameGrid &grid)
{
    if (!grid.HasSolution())  // no chance to find a solution
        return std::deque<int>();  // return an empty deque
    AStar solver(grid);
    solver.FindSolution();
    return solver.solution();
}
