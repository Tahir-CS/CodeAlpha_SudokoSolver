#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class SudokuSolver {
private:
    static const int SIZE = 9;
    static const int SUBGRID_SIZE = 3;
    vector<vector<int>> grid;

public:
    // Constructor
    SudokuSolver() {
        grid.resize(SIZE, vector<int>(SIZE, 0));
    }

    // Display the Sudoku grid
    void displayGrid() {
        cout << "\n+-------+-------+-------+\n";
        for (int row = 0; row < SIZE; row++) {
            cout << "| ";
            for (int col = 0; col < SIZE; col++) {
                if (grid[row][col] == 0) {
                    cout << ". ";
                } else {
                    cout << grid[row][col] << " ";
                }
                if ((col + 1) % SUBGRID_SIZE == 0) {
                    cout << "| ";
                }
            }
            cout << "\n";
            if ((row + 1) % SUBGRID_SIZE == 0) {
                cout << "+-------+-------+-------+\n";
            }
        }
    }

    // Check if placing num at position (row, col) is valid
    bool isValidPlacement(int row, int col, int num) {
        // Check row constraint
        for (int c = 0; c < SIZE; c++) {
            if (grid[row][c] == num) {
                return false;
            }
        }

        // Check column constraint
        for (int r = 0; r < SIZE; r++) {
            if (grid[r][col] == num) {
                return false;
            }
        }

        // Check 3x3 subgrid constraint
        int startRow = row - row % SUBGRID_SIZE;
        int startCol = col - col % SUBGRID_SIZE;
        
        for (int r = 0; r < SUBGRID_SIZE; r++) {
            for (int c = 0; c < SUBGRID_SIZE; c++) {
                if (grid[r + startRow][c + startCol] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    // Find the next empty cell (returns false if no empty cell found)
    bool findEmptyCell(int& row, int& col) {
        for (row = 0; row < SIZE; row++) {
            for (col = 0; col < SIZE; col++) {
                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    // Backtracking algorithm to solve Sudoku
    bool solveSudoku() {
        int row, col;

        // If no empty cell is found, puzzle is solved
        if (!findEmptyCell(row, col)) {
            return true;
        }

        // Try numbers 1 through 9
        for (int num = 1; num <= 9; num++) {
            if (isValidPlacement(row, col, num)) {
                // Place the number
                grid[row][col] = num;

                // Recursively try to solve the rest of the puzzle
                if (solveSudoku()) {
                    return true;
                }

                // If placing num doesn't lead to solution, backtrack
                grid[row][col] = 0;
            }
        }

        // No valid number found, need to backtrack
        return false;
    }

    // Input Sudoku puzzle from user
    void inputPuzzle() {
        cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";
        cout << "Enter row by row, with spaces between numbers:\n\n";
        
        for (int row = 0; row < SIZE; row++) {
            cout << "Row " << (row + 1) << ": ";
            for (int col = 0; col < SIZE; col++) {
                cin >> grid[row][col];
                
                // Validate input
                if (grid[row][col] < 0 || grid[row][col] > 9) {
                    cout << "Invalid input! Please enter numbers between 0-9.\n";
                    col--; // Retry current position
                }
            }
        }
    }

    // Load a sample puzzle for testing
    void loadSamplePuzzle() {
        vector<vector<int>> sample = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };
        grid = sample;
    }

    // Check if the current grid state is valid
    bool isValidGrid() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (grid[row][col] != 0) {
                    int temp = grid[row][col];
                    grid[row][col] = 0; // Temporarily remove the number
                    
                    if (!isValidPlacement(row, col, temp)) {
                        grid[row][col] = temp; // Restore the number
                        return false;
                    }
                    
                    grid[row][col] = temp; // Restore the number
                }
            }
        }
        return true;
    }
};

// Display menu options
void displayMenu() {
    cout << "\n========== SUDOKU SOLVER ==========\n";
    cout << "1. Enter your own puzzle\n";
    cout << "2. Solve sample puzzle\n";
    cout << "3. Exit\n";
    cout << "===================================\n";
    cout << "Choose an option: ";
}

int main() {
    SudokuSolver solver;
    int choice;

    cout << "Welcome to the Sudoku Solver!\n";
    cout << "This program uses backtracking algorithm to solve Sudoku puzzles.\n";

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                solver.inputPuzzle();
                
                cout << "\nOriginal Puzzle:\n";
                solver.displayGrid();

                if (!solver.isValidGrid()) {
                    cout << "\nError: The entered puzzle is invalid!\n";
                    cout << "Please check for duplicate numbers in rows, columns, or 3x3 subgrids.\n";
                    break;
                }

                cout << "\nSolving puzzle...\n";
                
                if (solver.solveSudoku()) {
                    cout << "\nPuzzle solved successfully!\n";
                    cout << "\nSolution:\n";
                    solver.displayGrid();
                } else {
                    cout << "\nNo solution exists for this puzzle!\n";
                }
                break;
            }

            case 2: {
                solver.loadSamplePuzzle();
                
                cout << "\nSample Puzzle:\n";
                solver.displayGrid();

                cout << "\nSolving puzzle...\n";
                
                if (solver.solveSudoku()) {
                    cout << "\nPuzzle solved successfully!\n";
                    cout << "\nSolution:\n";
                    solver.displayGrid();
                } else {
                    cout << "\nNo solution exists for this puzzle!\n";
                }
                break;
            }

            case 3: {
                cout << "\nThank you for using Sudoku Solver!\n";
                return 0;
            }

            default: {
                cout << "\nInvalid choice! Please try again.\n";
                break;
            }
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}