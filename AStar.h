#ifndef ASTAR_H
#define ASTAR_H
#include <bits/stdc++.h>

using namespace std;

#define ROW 21
#define COL 30

class AStar {

public:
    // Creating a shortcut for int, int pair type
    typedef pair<int, int> Pair;

    // Creating a shortcut for pair<int, pair<int, int>> type
    typedef pair<double, pair<int, int> > pPair;

    // A structure to hold the necessary parameters
    struct cell {
        // Row and Column index of its parent
        // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
        int parent_i, parent_j;
        // f = g + h
        double f, g, h;
    };
    pair<int,int> list[51];
    // A Utility Function to check whether given cell (row, col)
    // is a valid cell or not.
    bool isValid(int row, int col);
    bool isUnBlocked(char grid[][COL], int row, int col);
    bool isDestination(int row, int col, Pair dest);
    double calculateHValue(int row, int col, Pair dest);
    void tracePath(cell cellDetails[][COL], Pair dest);
    void aStarSearch(char grid[][COL], Pair src, Pair dest);
};

#endif // ASTAR_H
