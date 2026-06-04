#include "Game/Board.h"
#include <stdexcept>
using namespace std;

Cell::Cell()                // default -> initialize blocked cell
    : type(CellType::Blocked), clueAcross(0), clueDown(0), value(0) {}

Board::Board() : m_rows(5), m_cols(5), grid(m_rows, std::vector<Cell>(m_cols)) {}

Board::Board(int rows, int cols)            //  initialize the grid with empty cells
    : m_rows(rows), m_cols(cols), grid(rows, std::vector<Cell>(cols)) {}


int Board::rows() const {         // get num of rows & cols
    return m_rows;
}

int Board::cols() const {
    return m_cols;
}


const Cell& Board::getCell(int r, int c) const {          // get cell value
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) throw out_of_range("Cell coordinates out of range");

    return grid[r][c];
}

void Board::setCellValue(int r, int c, int val) {         // set cell value
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) throw out_of_range("Cell coordinates out of range");
    
    Cell& cell = grid[r][c];
    if (cell.type != CellType::Empty) throw logic_error("Cannot set value in non-playable cell");

    cell.value = val;
}

void Board::setCellType(int r, int c, CellType type) {
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols)
        throw out_of_range("Cell coordinates out of range");

    grid[r][c].type = type;
}

void Board::setClueAcross(int r, int c, int sum) {
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols)
        throw out_of_range("Cell coordinates out of range");

    grid[r][c].clueAcross = sum;
}

void Board::setClueDown(int r, int c, int sum) {
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols)
        throw out_of_range("Cell coordinates out of range");

    grid[r][c].clueDown = sum;
}

