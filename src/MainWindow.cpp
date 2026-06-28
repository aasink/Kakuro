#include "MainWindow.h"
#include "StartPage.h"
#include "GamePage.h"
#include "HelpPage.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    resize(600, 600);          // initial size
    setMinimumSize(400, 400);  

    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    startPage = new StartPage(this);
    gamePage = new GamePage(this);
    helpPage = new HelpPage(this);

    stack->addWidget(startPage); // index 0
    stack->addWidget(gamePage);  // index 1
    stack->addWidget(helpPage); // index 2

    auto *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction("How to Play", this, SLOT(showHowToPlay()));
    helpMenu->addAction("About", this, SLOT(showAbout()));

    fileMenu = menuBar()->addMenu(gamePage->getFileMenu());
    fileMenu->setVisible(false);

    gameMenu = menuBar()->addMenu(gamePage->getGameMenu());
    gameMenu->setVisible(false);

    // Connect signals
    connect(startPage, &StartPage::startGameClicked, this, &MainWindow::showGamePage);
    connect(startPage, &StartPage::howToPlayClicked, this, &MainWindow::showHelpPage);
    connect(startPage, &StartPage::exitClicked, this, &MainWindow::close);
    
    connect(gamePage, &GamePage::gameMessage, this, [this](const QString &msg, int timeoutMs) {
        statusBar()->showMessage(msg, timeoutMs);
    });

    connect(helpPage, &HelpPage::backClicked, this, &MainWindow::showStartPage);
    connect(gamePage, &GamePage::returnToStart, this, &MainWindow::showStartPage);

    showStartPage();  // Show start page initially
}

void MainWindow::showStartPage() {                  // switch to start and game pages
    stack->setCurrentWidget(startPage);

    fileMenu->setVisible(false);
    gameMenu->setVisible(false);
    statusBar()->showMessage("Welcome to Kakuro!", 3000);

    QTimer::singleShot(1000, gamePage, &GamePage::startNewGame);
}

void MainWindow::showGamePage() {
    stack->setCurrentWidget(gamePage);

    fileMenu->setVisible(true);
    gameMenu->setVisible(true);
    statusBar()->showMessage("Good Luck!", 3000);
}

void MainWindow::showHelpPage() {
    stack->setCurrentWidget(helpPage);

    fileMenu->setVisible(false);
    gameMenu->setVisible(false);
}


// TODO: delete
void MainWindow::showHowToPlay() {                  // show instructions dialog
    QMessageBox::information(this,
        "How to Play Kakuro",
        "Kakuro is a logic puzzle similar to a crossword, but with numbers.\n\n"
        "- Each clue is a sum for a row or column.\n"
        "- Fill the empty cells with digits 1–9.\n"
        "- No digit repeats within a sum group.\n"
        "- The goal is to make all sums match the clues.\n\n"
        "Tip: Start with small sums and unique combinations!");

        // TODO: fix dialog box & add better instructions with examples
}

void MainWindow::showAbout() {          // show about dialog
    QMessageBox::about(this,
        "About Kakuro",
        "Kakuro\n\nA puzzle game.\n\n");

        // TODO: add more about the game
}