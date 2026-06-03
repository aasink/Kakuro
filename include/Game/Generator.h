 #pragma once
#include "Game/Board.h"

class Generator {
public:
    Generator() = default;

    // Generate a simple hardcoded puzzle
    Board generateSamplePuzzle();
};
