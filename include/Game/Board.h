#pragma once
#include <vector>
using namespace std;

enum class CellType {       // Types of cells in the Kakuro grid
    Empty,
    Clue,
    Blocked
};

struct Cell {
    CellType type;
    int clueAcross;
    int clueDown;
    int value;          // 0 for empty, 1-9 for filled cells --> applys to clues too

    Cell();
};

class Board {
public:
    Board(int rows, int cols);

    int rows() const;       // Get number of rows & cols
    int cols() const;

    const Cell& getCell(int r, int c) const;            // get and set cell values
    void setCellValue(int r, int c, int val);

private:
    int m_rows;                     // Dimensions of the grid
    int m_cols;
    vector<vector<Cell>> grid;          // 2D grid of cells
};
