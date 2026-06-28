#include "StartPage.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

StartPage::StartPage(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto *title = new QLabel("KAKURO", this);
    title->setObjectName("pageTitle");       
    title->setAlignment(Qt::AlignCenter);

    auto *subtitle = new QLabel("A number logic puzzle", this);  
    subtitle->setObjectName("bodyText");                       
    subtitle->setAlignment(Qt::AlignCenter); 

    // buttons
    startButton = new QPushButton("New Game", this);       
    helpButton  = new QPushButton("How to Play", this);
    exitButton  = new QPushButton("Exit", this);
    
    exitButton->setObjectName("secondaryButton");

    layout->addStretch(2);      
    layout->addWidget(title);
    layout->addSpacing(8);     
    layout->addWidget(subtitle);
    layout->addStretch(1);

    for (auto *btn : {startButton, helpButton, exitButton}) {
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->setMaximumWidth(300);
        btn->setMinimumWidth(160);
    }

    auto *btnLayout = new QVBoxLayout();
    btnLayout->setSpacing(0);
    btnLayout->setAlignment(Qt::AlignHCenter);
    btnLayout->addWidget(startButton, 0, Qt::AlignHCenter);
    btnLayout->addSpacing(12);
    btnLayout->addWidget(helpButton,  0, Qt::AlignHCenter);
    btnLayout->addSpacing(20);  
    btnLayout->addWidget(exitButton,  0, Qt::AlignHCenter);
    layout->setAlignment(Qt::AlignCenter);

    layout->addStretch(2);
    layout->addWidget(title);
    layout->addSpacing(8);
    layout->addWidget(subtitle);
    layout->addStretch(1);
    layout->addLayout(btnLayout);
    layout->addStretch(2);

    // connect buttons to signals
    connect(startButton, &QPushButton::clicked, this, &StartPage::startGameClicked);
    connect(helpButton,  &QPushButton::clicked, this, &StartPage::howToPlayClicked);
    connect(exitButton,  &QPushButton::clicked, this, &StartPage::exitClicked);
}
