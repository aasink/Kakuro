#include "Game/Controller.h"

Controller::Controller() {
    board = generator.generateSamplePuzzle();
}

const Board& Controller::getBoard() const {
    return board;
}

void Controller::setCellValue(int r, int c, int val) {
    board.setCellValue(r, c, val);
}

void Controller::newGame() {
    board = generator.generateSamplePuzzle();
}
