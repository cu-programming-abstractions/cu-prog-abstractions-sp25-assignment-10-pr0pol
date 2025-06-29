

/*
 * Main Program
 *
 * This program implements a knight moves solution using BFS (Breadth-First Search):
 *
 * 1. Test Cases:
 *    - Same position test (0 moves)
 *    - Adjacent knight moves
 *    - Standard chess problems
 *    - Negative coordinate handling
 *    - Large distance moves
 *
 * 2. Output Format:
 *    - Shows start and target positions
 *    - Displays minimum number of moves
 *    - Shows complete path of moves
 *    - Verifies path correctness
 *
 * 3. Test Verification:
 *    - Checks path validity (each move is a valid knight move)
 *    - Verifies path length matches minimum moves
 *    - Ensures start and end positions are correct
 *    - Validates edge cases
 */

#include "knight.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

using namespace std;

// Helper function to check if a move is a valid knight move
bool isValidKnightMove(const Pos& from, const Pos& to) {
    int rowDiff = abs(from.row - to.row);
    int colDiff = abs(from.col - to.col);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

// Helper function to print a position
void printPos(const Pos& pos) {
    cout << "(" << pos.row << ", " << pos.col << ")";
}

// Helper function to print and verify test results
bool printResults(const string& testName, const Pos& start, const Pos& target) {
    cout << "\n=== " << testName << " ===\n";
    cout << "Start: ";
    printPos(start);
    cout << " -> Target: ";
    printPos(target);
    cout << "\n";

    int minMoves = minKnightMoves(start, target);
    vector<Pos> path = getKnightPath(start, target);

    cout << "Minimum moves: " << minMoves << "\n";
    cout << "Path length: " << (path.size() - 1) << "\n";
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        printPos(path[i]);
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\n";

    bool testPassed = true;

    // Verify minimum moves matches path length
    if (minMoves != static_cast<int>(path.size()) - 1) {
        cout << "X Path length doesn't match minimum moves\n";
        testPassed = false;
    }

    // Verify start and end positions
    if (path.empty() || path[0] != start) {
        cout << "X Path doesn't start at correct position\n";
        testPassed = false;
    }
    if (path.empty() || path.back() != target) {
        cout << "X Path doesn't end at correct position\n";
        testPassed = false;
    }

    // Verify each move in path is a valid knight move
    for (size_t i = 1; i < path.size(); i++) {
        if (!isValidKnightMove(path[i-1], path[i])) {
            cout << "X Invalid knight move from ";
            printPos(path[i-1]);
            cout << " to ";
            printPos(path[i]);
            cout << "\n";
            testPassed = false;
        }
    }

    cout << string(50, '-') << "\n";

    if (testPassed) {
        cout << "V " << testName << " passed\n";
    }

    return testPassed;
}

int main() {
    cout << "Testing Knight Moves Algorithms\n";
    cout << string(50, '=') << "\n";

    int passedTests = 0;
    int totalTests = 0;

    // Test Case 1: Same position (should be 0 moves)
    {
        totalTests++;
        Pos start = {0, 0};
        Pos target = {0, 0};

        bool testPassed = printResults("Same Position Test", start, target);

        // Additional verification for same position
        int moves = minKnightMoves(start, target);
        if (moves != 0) {
            cout << "X Same position should require 0 moves, got " << moves << "\n";
            testPassed = false;
        }

        if (testPassed) passedTests++;
    }

    // Test Case 2: One knight move away
    {
        totalTests++;
        Pos start = {0, 0};
        Pos target = {2, 1};  // Classic knight move

        bool testPassed = printResults("Single Knight Move Test", start, target);

        // Should be exactly 1 move
        int moves = minKnightMoves(start, target);
        if (moves != 1) {
            cout << "X Single knight move should require 1 move, got " << moves << "\n";
            testPassed = false;
        }

        if (testPassed) passedTests++;
    }

    // Test Case 3: Two knight moves away
    {
        totalTests++;
        Pos start = {0, 0};
        Pos target = {0, 2};  // Requires 2 moves minimum

        bool testPassed = printResults("Two Knight Moves Test", start, target);

        if (testPassed) passedTests++;
    }

    // Test Case 4: Negative coordinates
    {
        totalTests++;
        Pos start = {0, 0};
        Pos target = {-2, -1};

        bool testPassed = printResults("Negative Coordinates Test", start, target);

        if (testPassed) passedTests++;
    }

    // Test Case 5: Large distance
    {
        totalTests++;
        Pos start = {0, 0};
        Pos target = {7, 7};  // Corner of standard chessboard

        bool testPassed = printResults("Large Distance Test", start, target);

        if (testPassed) passedTests++;
    }

    // Test Case 6: Asymmetric move
    {
        totalTests++;
        Pos start = {1, 1};
        Pos target = {4, 5};

        bool testPassed = printResults("Asymmetric Move Test", start, target);

        if (testPassed) passedTests++;
    }

    cout << "\nTest Summary: " << passedTests << "/" << totalTests << " tests passed\n";

    if (passedTests == totalTests) {
        cout << "All tests passed! Knight moves implementation is working correctly.\n";
    } else {
        cout << "Some tests failed. Check the implementation.\n";
    }

    return passedTests == totalTests ? 0 : 1;
}
