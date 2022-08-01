#pragma once

#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>

using namespace std;

// creating shortcuts for pair<int, int> and tuple<double, int, int>
typedef pair<int, int> Node;
typedef tuple<double, int, int> Tuple;

struct Cell {
    // Row and Column index of its parent
    Node parent;

    // distance = cost + heuristic
    double distance, cost, heuristic;
    Cell() : parent(-1, -1), distance(-1), cost(-1), heuristic(-1) { }
};

class AStar {
public:
    // A Utility Function to check whether given Cell is valid or not.
    template <size_t ROW, size_t COL>
    bool IsValid(const array<array<int, COL>, ROW>& grid, const Node& point)
    { 
        // Returns true if row number and column number is in range
        if (ROW > 0 && COL > 0)
            return (point.first >= 0) 
                && (point.first < ROW)
                && (point.second >= 0)
                && (point.second < COL);

        return false;
    }

    // A Utility Function to check whether the given Cell is blocked
    template <size_t ROW, size_t COL>
    bool IsUnblocked(const array<array<int, COL>, ROW>& grid, const Node& point)
    {
        // Returns true if the Cell is not blocked else false
        return IsValid(grid, point) && grid[point.first][point.second] == 1;
    }

    // A Utility Function to check whether destination Cell has been reached 
    bool IsDestination(const Node& position, const Node& dest)
    {
        return position == dest;
    }

    // A Utility Function to calculate the 'heuristic' heuristics.
    double CalculateHValue(const Node& src, const Node& dest)
    {
        // heuristic is estimated with the two points distance formula
        return sqrt(pow((src.first - dest.first), 2.0) + pow((src.second - dest.second), 2.0));
    }

    // A Utility Function to trace the path from the source to destination
    template <size_t ROW, size_t COL>
    void TracePath(const array<array<Cell, COL>, ROW>& cellDetails, const Node& dest)
    {
        printf("\nThe Path is ");

        stack<Node> Path;

        int row = dest.first;
        int col = dest.second;
        Node next_node = cellDetails[row][col].parent;

        do 
        {
            Path.push(next_node);
            next_node = cellDetails[row][col].parent;
            row = next_node.first;
            col = next_node.second;
        } 
        while (cellDetails[row][col].parent != next_node);

        Path.emplace(row, col);
        while (!Path.empty()) 
        {
            Node p = Path.top();
            Path.pop();
            printf("-> (%d,%d) ", p.first, p.second);
        }
    }

    // A Function to find the shortest path between a given source Cell to a 
    // destination Cell according to A* Search Algorithm
    template <size_t ROW, size_t COL>
    void Search(const array<array<int, COL>, ROW>& grid, const Node& src, const Node& dest)
    {
        // If the source is out of range
        if (!IsValid(grid, src)) 
        {
            printf("Source is invalid\n");
            return;
        }

        // If the destination is out of range
        if (!IsValid(grid, dest)) 
        {
            printf("Destination is invalid\n");
            return;
        }

        // Either the source or the destination is blocked
        if (!IsUnblocked(grid, src) || !IsUnblocked(grid, dest)) 
        {
            printf("Source or the destination is blocked\n");
            return;
        }

        // If the destination Cell is the same as source Cell
        if (IsDestination(src, dest)) 
        {
            printf("We are already at the destination\n");
            return;
        }

        // Create a closed list and initialise it to false which means that no Cell has 
        // been included yet. This closed list is implemented as a boolean 2D array
        bool closedList[ROW][COL];
        memset(closedList, false, sizeof(closedList));

        // Declare a 2D array of structure to hold the details of that Cell
        array<array<Cell, COL>, ROW> cellDetails;

        int i, j;
        // Initialising the parameters of the starting node
        i = src.first, j = src.second;
        cellDetails[i][j].distance = 0.0;
        cellDetails[i][j].cost = 0.0;
        cellDetails[i][j].heuristic = 0.0;
        cellDetails[i][j].parent = { i, j };

        /*
        Create an open list having information as-
        <distance, <i, j>>
        where distance = cost + heuristic,
        and i, j are the row and column index of that Cell
        Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
        This open list is implemented as a set of tuple.*/
        std::priority_queue<Tuple, std::vector<Tuple>, std::greater<Tuple>> openList;

        // Put the starting Cell on the open list and set its
        // 'distance' as 0
        openList.emplace(0.0, i, j);

        // We set this boolean value as false as initially the destination is not reached.
        while (!openList.empty()) 
        {
            const Tuple& p = openList.top();
            // Add this vertex to the closed list
            i = get<1>(p); // second element of tuple
            j = get<2>(p); // third element of tuple

            // Remove this vertex from the open list
            openList.pop();
            closedList[i][j] = true;

            /*
                    Generating all the 8 successor of this Cell
                            N.W N N.E
                            \ | /
                            \ | /
                            W----Cell----E
                                    / | \
                            / | \
                            S.W S S.E

                    Cell-->Popped Cell (i, j)
                    N --> North     (i-1, j)
                    S --> South     (i+1, j)
                    E --> East     (i, j+1)
                    W --> West         (i, j-1)
                    N.E--> North-East (i-1, j+1)
                    N.W--> North-West (i-1, j-1)
                    S.E--> South-East (i+1, j+1)
                    S.W--> South-West (i+1, j-1)
            */
            for (int add_x = -1; add_x <= 1; add_x++) 
            {
                for (int add_y = -1; add_y <= 1; add_y++) 
                {
                    Node neighbour(i + add_x, j + add_y);
                    // Only process this Cell if this is a valid one
                    if (IsValid(grid, neighbour)) 
                    {
                        // If the destination Cell is the same as the current successor
                        if (IsDestination(neighbour, dest)) 
                        { 
                            // Set the Parent of the destination Cell
                            cellDetails[neighbour.first][neighbour.second].parent = { i, j };
                            printf("The destination Cell is found\n");
                            TracePath(cellDetails, dest);
                            return;
                        }
                        // If the successor is already on the closed list or if it is blocked, then
                        // ignore it. Else do the following
                        else if (!closedList[neighbour.first][neighbour.second] && IsUnblocked(grid, neighbour)) 
                        {
                            double gNew, hNew, fNew;
                            gNew = cellDetails[i][j].cost + 1.0;
                            hNew = CalculateHValue(neighbour, dest);
                            fNew = gNew + hNew;

                            // If it isn’t on the open list, add
                            // it to the open list. Make the
                            // current square the parent of this
                            // square. Record the distance, cost, and heuristic
                            // costs of the square Cell
                            //             OR
                            // If it is on the open list
                            // already, check to see if this
                            // path to that square is better,
                            // using 'distance' cost as the measure.
                            if (cellDetails[neighbour.first][neighbour.second].distance == -1
                                || cellDetails[neighbour.first][neighbour.second].distance > fNew) 
                            {
                                openList.emplace(fNew, neighbour.first, neighbour.second);

                                // Update the details of this Cell
                                cellDetails[neighbour.first][neighbour.second].cost = gNew;
                                cellDetails[neighbour.first][neighbour.second].heuristic = hNew;
                                cellDetails[neighbour.first][neighbour.second].distance = fNew;
                                cellDetails[neighbour.first][neighbour.second].parent = { i, j };
                            }
                        }
                    }
                }
            }
        }

        // When the destination Cell is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destination Cell. This may happen when the
        // there is no way to destination Cell (due to
        // blockages)
        printf("Failed to find the Destination Cell\n");
    }

    template <size_t ROW, size_t COL>
    void DisplayMap(const array<array<int, COL>, ROW>& grid, const Node& start, const Node& end)
    {
        constexpr char WALL = (char)219;

        for (int i = 0; i < ROW + 2; i++) cout << WALL;
        cout << endl;

        for (int x = 0; x < ROW; x++)
        {
            cout << WALL;

            for (int y = 0; y < COL; y++)
            {

                char output = grid[x][y] == 1 ? ' ' : (char)219;
                if (start.first == x && start.second == y) output = '@';
                else if (end.first == x && end.second == y) output = 'X';

                cout << output;
            }
            cout << WALL << endl;
        }
        for (int i = 0; i < ROW + 2; i++) cout << WALL;
        cout << endl;
    }
};