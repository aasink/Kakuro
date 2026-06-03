#include "GamePage.h"
#include "GridWidget.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>

GamePage::GamePage(QWidget *parent)
    : QWidget(parent), elapsedSeconds(0) {

    auto *layout = new QVBoxLayout(this);
    
    //  grid
    grid = new GridWidget(this);
    layout->addWidget(grid, 1);

    // Menus
    gameMenu = new QMenu("Game", this);
    gameMenu->addAction("Pause", this, SLOT(pauseGame()));
    gameMenu->addAction("Resume", this, SLOT(resumeGame()));
    gameMenu->addAction("Hint", this, SLOT(showHint()));

    fileMenu = new QMenu("File", this);
    fileMenu->addAction("New Game", this, SLOT(startNewGame()));
    fileMenu->addAction("Reset", this, SLOT(resetGame())); 


    // Timer
    timerLabel = new QLabel("Time: 0s", this);
    layout->addWidget(timerLabel);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, [this]() {
        elapsedSeconds++;
        timerLabel->setText(QString("Time: %1s").arg(elapsedSeconds));
    });

    setLayout(layout);
}



QMenu* GamePage::getGameMenu() const {          // get game & file menu
    return gameMenu;
}

QMenu* GamePage::getFileMenu() const {
    return fileMenu;
}



void GamePage::startNewGame() {             // game controls
    elapsedSeconds = 0;
    timerLabel->setText("Time: 0s");
    gameTimer->start(1000);
    emit gameMessage("New game started", 3000);
}

void GamePage::resetGame() {
    elapsedSeconds = 0;
    timerLabel->setText("Time: 0s");
    gameTimer->stop();
    emit gameMessage("Game Reset", 3000);
}

void GamePage::pauseGame() {
    gameTimer->stop();
    emit gameMessage("Game Paused", 0);

    // TODO: disable grid input & stop timer
}

void GamePage::resumeGame() {
    gameTimer->start(1000);
    emit gameMessage("Game Resumed", 3000);

    // TODO: enable grid input & restart timer
}

void GamePage::showHint() {
    emit gameMessage("Hint: [Insert Hint]", 0);

    // TODO: display hint 
}

