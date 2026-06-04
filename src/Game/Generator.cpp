#include "Game/Generator.h"

Board Generator::generateSamplePuzzle() {
    Board board(5, 5);

    // Row 0
    board.setCellType(0,0, CellType::Blocked);
    board.setCellType(0,1, CellType::Blocked);
    board.setCellType(0,2, CellType::Clue);
    board.setClueDown(0,2, 20);
    board.setCellType(0,3, CellType::Clue);
    board.setClueDown(0,3, 29);
    board.setCellType(0,4, CellType::Blocked);

    // Row 1
    board.setCellType(1,0, CellType::Blocked);
    board.setCellType(1,1, CellType::Clue);
    board.setClueAcross(1,1, 17);
    board.setClueDown(1,1, 9);
    board.setCellType(1,2, CellType::Empty);
    board.setCellType(1,3, CellType::Empty);
    board.setCellType(1,4, CellType::Clue);
    board.setClueDown(1,4, 16);

    // Row 2
    board.setCellType(2,0, CellType::Clue);
    board.setClueAcross(2,0, 26);
    board.setCellType(2,1, CellType::Empty);
    board.setCellType(2,2, CellType::Empty);
    board.setCellType(2,3, CellType::Empty);
    board.setCellType(2,4, CellType::Empty);

    // Row 3
    board.setCellType(3,0, CellType::Clue);
    board.setClueAcross(3,0, 15);
    board.setCellType(3,1, CellType::Empty);
    board.setCellType(3,2, CellType::Empty);
    board.setCellType(3,3, CellType::Empty);
    board.setCellType(3,4, CellType::Empty);

    // Row 4
    board.setCellType(4,0, CellType::Blocked);
    board.setCellType(4,1, CellType::Clue);
    board.setClueAcross(4,1, 16);
    board.setCellType(4,2, CellType::Empty);
    board.setCellType(4,3, CellType::Empty);
    board.setCellType(4,4, CellType::Blocked);

    return board;
}
