#include "Game/BoardGenerator.h"

Board BoardGenerator::generateSamplePuzzle() {
    Board board(5, 5);

    // Row 0
    board.getCell(0,0).type = CellType::Blocked;
    board.getCell(0,1).type = CellType::Blocked;
    board.getCell(0,2).type = CellType::Clue;
    board.getCell(0,2).clueDown = 20;
    board.getCell(0,3).type = CellType::Clue;
    board.getCell(0,3).clueDown = 29;
    board.getCell(0,4).type = CellType::Blocked;

    // Row 1
    board.getCell(1,0).type = CellType::Blocked;
    board.getCell(1,1).type = CellType::Clue;
    board.getCell(1,1).clueAcross = 17;
    board.getCell(1,1).clueDown = 9;
    board.getCell(1,2).type = CellType::Empty;
    board.getCell(1,3).type = CellType::Empty;
    board.getCell(1,4).type = CellType::Clue;
    board.getCell(1,4).clueDown = 16;

    // Row 2
    board.getCell(2,0).type = CellType::Clue;
    board.getCell(2,0).clueAcross = 26;
    board.getCell(2,1).type = CellType::Empty;
    board.getCell(2,2).type = CellType::Empty;
    board.getCell(2,3).type = CellType::Empty;
    board.getCell(2,4).type = CellType::Empty;

    // Row 3
    board.getCell(3,0).type = CellType::Clue;
    board.getCell(3,0).clueAcross = 15;
    board.getCell(3,1).type = CellType::Empty;
    board.getCell(3,2).type = CellType::Empty;
    board.getCell(3,3).type = CellType::Empty;
    board.getCell(3,4).type = CellType::Empty;

    // Row 4
    board.getCell(4,0).type = CellType::Blocked;
    board.getCell(4,1).type = CellType::Clue;
    board.getCell(4,1).clueAcross = 16;
    board.getCell(4,2).type = CellType::Empty;
    board.getCell(4,3).type = CellType::Empty;
    board.getCell(4,4).type = CellType::Blocked;

    return board;
}
