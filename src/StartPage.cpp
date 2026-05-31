#include "StartPage.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

StartPage::StartPage(QWidget *parent)
    : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);

    auto *title = new QLabel("Kakuro", this);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    // Buttons
    startButton = new QPushButton("Start Game", this);
    helpButton  = new QPushButton("How to Play", this);
    exitButton  = new QPushButton("Exit", this);

    layout->addWidget(startButton);
    layout->addWidget(helpButton);
    layout->addWidget(exitButton);

    layout->setAlignment(Qt::AlignCenter);

    // Connect buttons to signals
    connect(startButton, &QPushButton::clicked, this, &StartPage::startGameClicked);
    connect(helpButton,  &QPushButton::clicked, this, &StartPage::howToPlayClicked);
    connect(exitButton,  &QPushButton::clicked, this, &StartPage::exitClicked);
}
