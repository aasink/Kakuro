#include "GamePage.h"
#include "GridWidget.h"
#include "Game/Controller.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QFrame>
#include <QSizePolicy>

GamePage::GamePage(QWidget *parent) : QWidget(parent), elapsedSeconds(0), isPaused(false) {
 
    gameMenu = new QMenu("Game", this);                     // create game menu
    gameMenu->addAction("New Game", this, &GamePage::startNewGame);
    gameMenu->addAction("Reset", this, &GamePage::resetGame);
    gameMenu->addSeparator();
    gameMenu->addAction("Pause", this, &GamePage::pauseGame);
    gameMenu->addAction("Resume", this, &GamePage::resumeGame);
 
    fileMenu = new QMenu("File", this);                             // create file menu
    fileMenu->addAction("New Game", this, &GamePage::startNewGame);
    fileMenu->addAction("Reset", this, &GamePage::resetGame);
 
    gameTimer = new QTimer(this);           // setup game timer
    gameTimer->setInterval(1000);
    connect(gameTimer, &QTimer::timeout, this, &GamePage::onTimerTick);
 
    controller = new Controller();
    grid = new GridWidget(controller, this);
    grid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);   
    outerLayout->setSpacing(0);
 
    outerLayout->addWidget(buildInfoBar());
 
    auto *divider = new QFrame();
    divider->setFrameShape(QFrame::HLine);
    divider->setObjectName("divider");             
    outerLayout->addWidget(divider);
 
    auto *mainRow = new QHBoxLayout();
    mainRow->setSpacing(0);                        
    mainRow->addWidget(grid, 4);                    
    mainRow->addWidget(buildSidebar(), 1);          
 
    outerLayout->addLayout(mainRow, 1);
}

QWidget *GamePage::buildSidebar() {
    auto *sidebar = new QWidget(this);
    sidebar->setObjectName("sidebar");
    sidebar->setMinimumWidth(80);
    sidebar->setMaximumWidth(280);            
    sidebar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
 
    auto *layout = new QVBoxLayout(sidebar);
    layout->setContentsMargins(0, 0, 0, 0);       
    layout->setSpacing(0);
 
    layout->addStretch();
    layout->addWidget(buildToolRow());
    layout->addStretch();
    layout->addWidget(buildNumpad());
    layout->addStretch();
 
    return sidebar;
}

QWidget *GamePage::buildInfoBar() {
    auto *bar = new QWidget(this);
    bar->setObjectName("infoBar");                  
 
    auto *layout = new QHBoxLayout(bar);
    //layout->setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(16, 8, 16, 8);        
    layout->setSpacing(0);
 
    difficultyLabel = new QLabel("Difficulty: —", bar);
    difficultyLabel->setObjectName("bodyText");
 
    timerLabel = new QLabel("⏱  00:00", bar);
    timerLabel->setObjectName("timerLabel");
    timerLabel->setAlignment(Qt::AlignCenter);
 
    pauseButton = new QPushButton("⏸  Pause", bar);
    pauseButton->setObjectName("secondaryButton");
    connect(pauseButton, &QPushButton::clicked, this, [this]() {
        isPaused ? resumeGame() : pauseGame();
    });
 
    menuButton = new QPushButton("≡", bar);
    menuButton->setObjectName("menuButton");        
 
    auto *dropMenu = new QMenu(this);
    dropMenu->addAction("Start New Game", this, &GamePage::startNewGame);
    dropMenu->addAction("Reset Board", this, &GamePage::resetGame);
    dropMenu->addSeparator();
    dropMenu->addAction("Return to Start", this, [this]() {
        emit returnToStart();
    });
    menuButton->setMenu(dropMenu);
 
    layout->addWidget(difficultyLabel);
    layout->addStretch();
    layout->addWidget(timerLabel);
    layout->addStretch();
    layout->addWidget(pauseButton);
    layout->addWidget(menuButton);
 
    return bar;
}

QWidget *GamePage::buildToolRow() {
    auto *row = new QWidget(this);
    row->setObjectName("toolRow");
 
    auto *layout = new QGridLayout(row);
    layout->setSpacing(0);                         
    layout->setContentsMargins(0, 0, 0, 0);
 
    undoButton  = new QPushButton("↩ Undo",  row);
    eraseButton = new QPushButton("⌫ Erase", row);
    notesButton = new QPushButton("✏ Notes", row);
    hintButton  = new QPushButton("💡 Hint",  row);
 
    for (auto *btn : {undoButton, eraseButton, notesButton, hintButton}) {
        btn->setObjectName("secondaryButton");
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
 
    layout->addWidget(undoButton,  0, 0);
    layout->addWidget(eraseButton, 0, 1);
    layout->addWidget(notesButton, 1, 0);
    layout->addWidget(hintButton,  1, 1);
 
    connect(hintButton, &QPushButton::clicked, this, &GamePage::showHint);
    // TODO: connect undoButton, eraseButton, notesButton 
 
    return row;
}

QWidget *GamePage::buildNumpad() {
    auto *pad = new QWidget(this);
    pad->setObjectName("numpad");
 
    auto *layout = new QGridLayout(pad);
    layout->setSpacing(0);                      
    layout->setContentsMargins(0, 0, 0, 0);
 
    int digits[9] = {7, 8, 9, 4, 5, 6, 1, 2, 3};
    for (int i = 0; i < 9; ++i) {
        int digit = digits[i];
        numpadButtons[i] = new QPushButton(QString::number(digit), pad);
        numpadButtons[i]->setObjectName("numpadButton");
        numpadButtons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
 
        connect(numpadButtons[i], &QPushButton::clicked, this, [this, digit]() {
            grid->inputDigit(digit);  
        });
 
        layout->addWidget(numpadButtons[i], i / 3, i % 3);
    }
 
    return pad;
}

QMenu* GamePage::getGameMenu() const {          // get game & file menu
    return gameMenu;
}

QMenu* GamePage::getFileMenu() const {
    return fileMenu;
}

void GamePage::startNewGame() {             // game controls
    elapsedSeconds = 0;
    timerLabel->setText("⏱  00:00");
    isPaused = false;
    pauseButton->setText("⏸  Pause");
    grid->setVisible(true);       
    gameTimer->start();
    emit gameMessage("New game started", 3000);
    
    // TODO: generate new puzzle
}

void GamePage::resetGame() {
    elapsedSeconds = 0;
    timerLabel->setText("⏱  00:00");
    isPaused = false;
    pauseButton->setText("⏸  Pause");
    grid->setVisible(true);            
    gameTimer->stop();
    emit gameMessage("Game reset", 3000);

    // TODO: reset the board
}

void GamePage::pauseGame() {
    gameTimer->stop();
    isPaused = true;
    pauseButton->setText("▶  Resume");
    grid->setVisible(false); 
    emit gameMessage("Game paused — press Resume to continue", 0);
}

void GamePage::resumeGame() {
    gameTimer->start();
    isPaused = false;
    pauseButton->setText("⏸  Pause");
    grid->setVisible(true);             
    emit gameMessage("Game resumed", 3000);
}

void GamePage::showHint() {
    emit gameMessage("Hint: [Insert Hint]", 0);

    // TODO: display hint 
}

void GamePage::onTimerTick() {
    elapsedSeconds++;
    int mins = elapsedSeconds / 60;
    int secs = elapsedSeconds % 60;
    timerLabel->setText(QString("⏱  %1:%2").arg(mins, 2, 10, QChar('0')).arg(secs, 2, 10, QChar('0')));
}
