
#include "knight.h"
#include <algorithm>
#include <cmath>

using namespace std;

/* -------- minKnightMoves -------- */
int minKnightMoves(const Pos& start, const Pos& target) {
    // Handle edge case: if start == target, return 0
    if (start == target) return 0;

    // Initialize BFS queue with start position and distance 0
    queue<Pos> BFS;
    BFS.push(start);
    int distance = 1;
    unordered_set<Pos, PosHash> visited;
    unordered_set<Pos, PosHash> toBeVisited;

    // BFS
    while (!BFS.empty())
    {
        int s = BFS.size();

        for (int i = 0; i < s; i++)
        {
            toBeVisited.clear();

            // Add knight Moves (8 possibilities)
            toBeVisited.insert({BFS.front().row + 2, BFS.front().col + 1});
            toBeVisited.insert({BFS.front().row + 2, BFS.front().col - 1});
            toBeVisited.insert({BFS.front().row - 2, BFS.front().col + 1});
            toBeVisited.insert({BFS.front().row - 2, BFS.front().col - 1});
            toBeVisited.insert({BFS.front().row + 1, BFS.front().col + 2});
            toBeVisited.insert({BFS.front().row + 1, BFS.front().col - 2});
            toBeVisited.insert({BFS.front().row - 1, BFS.front().col + 2});
            toBeVisited.insert({BFS.front().row - 1, BFS.front().col - 2});

            BFS.pop();

            // Check for target & add unvisited
            for (const Pos& p : toBeVisited)
            {
                if (p == target)
                {
                    return distance;
                }

                if (visited.find(p) == visited.end())
                {
                    visited.insert(p);
                    BFS.push(p);
                }
            }
        }
        distance++;
    }

    return -1;
}

/* -------- getKnightPath -------- */
vector<Pos> getKnightPath(const Pos& start, const Pos& target) {
    // Handle edge case: if start == target, return {start}
    if (start == target) return {start};
    // Initialize BFS queue with start position
    queue<Pos> BFS;
    BFS.push(start);
    // Use unordered_map to track parent positions for path reconstruction
    unordered_map<Pos, Pos, PosHash> parent;
    // Use unordered_set to track visited positions
    unordered_set<Pos, PosHash> visited;
    unordered_set<Pos, PosHash> toBeVisited;

    // BFS
    while (!BFS.empty())
    {
        // Add knight Moves (8 possibilities)
        toBeVisited.insert({BFS.front().row + 2, BFS.front().col + 1});
        toBeVisited.insert({BFS.front().row + 2, BFS.front().col - 1});
        toBeVisited.insert({BFS.front().row - 2, BFS.front().col + 1});
        toBeVisited.insert({BFS.front().row - 2, BFS.front().col - 1});
        toBeVisited.insert({BFS.front().row + 1, BFS.front().col + 2});
        toBeVisited.insert({BFS.front().row + 1, BFS.front().col - 2});
        toBeVisited.insert({BFS.front().row - 1, BFS.front().col + 2});
        toBeVisited.insert({BFS.front().row - 1, BFS.front().col - 2});

        Pos CurrentPos = BFS.front();
        BFS.pop();

        // Add unvisited, update parent map & check for target
        for (const Pos& p : toBeVisited)
        {
            if (visited.find(p) == visited.end())
            {
                parent[p] = CurrentPos;
                visited.insert(p);
                BFS.push(p);
            }

            if (p == target)
            {
                // Reconstruct
                vector<Pos> path;
                path.push_back(target);
                while (path.back() != start)
                {
                    path.push_back(parent[path.back()]);
                }
                reverse(path.begin(), path.end());
                return path;
            }
        }
    }
    return {};
}

/* -------- isValidPosition -------- */
bool isValidPosition(const Pos& pos, int boardSize) {
    if (boardSize == -1) {
        return true; // Infinite board
    }
    return pos.row >= 0 && pos.row < boardSize &&
           pos.col >= 0 && pos.col < boardSize;
}
