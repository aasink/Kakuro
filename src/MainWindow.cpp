#include "MainWindow.h"
#include "StartPage.h"
#include "GamePage.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    resize(800, 800);          // initial size
    setMinimumSize(300, 300);  

    stack = new QStackedWidget(this);

    auto *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction("How to Play", this, SLOT(showHowToPlay()));
    helpMenu->addAction("About", this, SLOT(showAbout()));

    startPage = new StartPage(this);
    gamePage = new GamePage(this);

    statusBar()->showMessage("Welcome to Kakuro!", 3000);

    stack->addWidget(startPage); // index 0
    stack->addWidget(gamePage);  // index 1

    setCentralWidget(stack);
    resize(sizeHint());

    // Connect signals
    connect(startPage, &StartPage::startGameClicked, this, &MainWindow::showGamePage);
    connect(startPage, &StartPage::howToPlayClicked, this, &MainWindow::showHowToPlay);
    connect(startPage, &StartPage::exitClicked, this, &MainWindow::close);
    
    connect(gamePage, &GamePage::gameMessage, this, [this](const QString &msg, int timeoutMs) {
        statusBar()->showMessage(msg, timeoutMs);
    });

    showStartPage();  // Show start page initially
}

void MainWindow::showStartPage() {
    stack->setCurrentWidget(startPage);
}

void MainWindow::showGamePage() {
    stack->setCurrentWidget(gamePage);
    menuBar()->addMenu(gamePage->getGameMenu());
    menuBar()->addMenu(gamePage->getFileMenu());
}

void MainWindow::showHowToPlay() {
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

void MainWindow::showAbout() {
    QMessageBox::about(this,
        "About Kakuro",
        "Kakuro\n\nA puzzle game.\n\n");

        // TODO: add more about the game
}