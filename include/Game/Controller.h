#pragma once
#include "Game/Board.h"
#include "Game/Generator.h"
#include "Game/Validator.h"
#include <vector>

class Controller {
public:
    Controller();

    const Board& getBoard() const;

    void setCellValue(int r, int c, int val);

    //bool isSolved() const;
    //std::vector<RunResult> validateBoard() const;

    void newGame();

private:
    Board board;
    Generator generator;
    //Validator validator;
};
