#include "HelpPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>

HelpPage::HelpPage(QWidget *parent) : QWidget(parent) {

    auto *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    auto *topBar = new QWidget(this);       // bar to hold back button
    topBar->setFixedHeight(48);
    auto *topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(24, 8, 24, 8);

    auto *backButton = new QPushButton("← Back", topBar);       // back button
    backButton->setObjectName("secondaryButton");
    backButton->setFixedWidth(100);
    connect(backButton, &QPushButton::clicked, this, &HelpPage::backClicked);

    topBarLayout->addWidget(backButton);
    topBarLayout->addStretch();

    auto *scrollArea = new QScrollArea(this);       // scroll area
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto *content = new QWidget();
    auto *layout = new QVBoxLayout(content);
    layout->setContentsMargins(48, 32, 48, 48);
    layout->setSpacing(8);

    auto *title = new QLabel("How to play Kakuro");
    title->setObjectName("pageTitle");

    auto *subtitle = new QLabel("Everything you need to know to get started.");
    subtitle->setObjectName("bodyText");

    layout->addWidget(title);
    layout->addSpacing(4);
    layout->addWidget(subtitle);
    layout->addSpacing(16);
    layout->addWidget(makeDivider());
    layout->addSpacing(16);


    layout->addWidget(makeSectionLabel("What is Kakuro?"));
    layout->addSpacing(8);
    layout->addWidget(makeCard(
        "A number logic puzzle",
        "Kakuro is like a crossword puzzle, but instead of letters you fill in digits. "
        "Each row and column of white cells must add up to the clue number shown in the "
        "black cell next to it. No guessing — every puzzle has exactly one solution "
        "that can be found through logic alone."
    ));
    layout->addSpacing(24);



    layout->addWidget(makeSectionLabel("The rules"));
    layout->addSpacing(8);
    layout->addWidget(makeRuleRow("1", "Fill every white cell with a digit from 1 to 9."));
    layout->addWidget(makeRuleRow("2", "Each run of white cells must add up exactly to its clue number."));
    layout->addWidget(makeRuleRow("3", "No digit can repeat within the same run — each number can appear at most once."));
    layout->addWidget(makeRuleRow("4", "Zero is never used."));
    layout->addSpacing(24);



    layout->addWidget(makeSectionLabel("Reading the grid"));
    layout->addSpacing(8);
    layout->addWidget(makeCard(
        "Clue cells",
        "Black cells contain two numbers separated by a diagonal line. "
        "The top-right number is the sum for the run going across (→). "
        "The bottom-left number is the sum for the run going down (↓). "
        "A dash means there is no run in that direction."
    ));
    layout->addSpacing(24);



    layout->addWidget(makeSectionLabel("Tips to get started"));
    layout->addSpacing(8);
    layout->addWidget(makeCard(
        "Start with the most constrained runs",
        "A 2-cell run summing to 3 can only be 1+2. "
        "A 2-cell run summing to 17 can only be 8+9. "
        "Find these locked combinations first and use them as anchor points."
    ));
    layout->addSpacing(8);
    layout->addWidget(makeCard(
        "Cross-reference rows and columns",
        "Every cell belongs to both a row run and a column run. "
        "Use both clues together to narrow down which digits are possible for each cell."
    ));
    layout->addSpacing(24);


    layout->addWidget(makeSectionLabel("Controls"));
    layout->addSpacing(8);
    layout->addWidget(makeCard("Select a cell",    "Click on any white cell, or use the arrow keys to navigate."));
    layout->addSpacing(4);
    layout->addWidget(makeCard("Enter a digit",    "Type 1–9 on your keyboard, or use the on-screen numpad."));
    layout->addSpacing(4);
    layout->addWidget(makeCard("Clear a cell",     "Press Backspace or Delete to erase the current cell."));
    layout->addSpacing(4);
    layout->addWidget(makeCard("Check your work",  "Click Validate to highlight any incorrect cells."));

    layout->addStretch();

    scrollArea->setWidget(content);

    outerLayout->addWidget(topBar);
    outerLayout->addWidget(scrollArea);
}


QWidget *HelpPage::makeCard(const QString &title, const QString &body) {
    auto *card = new QFrame();
    card->setFrameShape(QFrame::NoFrame);
    card->setStyleSheet(
        "QFrame {"
        "  background-color: #16213e;"
        "  border: 1px solid #2a2a4a;"
        "  border-radius: 10px;"
        "}"
    );

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(16, 14, 16, 14);
    layout->setSpacing(4);

    auto *titleLabel = new QLabel(title);
    titleLabel->setObjectName("sectionTitle");
    titleLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #eaeaea; background: transparent; border: none;");

    auto *bodyLabel = new QLabel(body);
    bodyLabel->setObjectName("bodyText");
    bodyLabel->setWordWrap(true);
    bodyLabel->setStyleSheet("font-size: 13px; color: #a0a0b0; background: transparent; border: none;");

    layout->addWidget(titleLabel);
    layout->addWidget(bodyLabel);

    return card;
}


QWidget *HelpPage::makeRuleRow(const QString &number, const QString &text) {
    auto *row = new QWidget();
    auto *layout = new QHBoxLayout(row);
    layout->setContentsMargins(0, 4, 0, 4);
    layout->setSpacing(14);

    auto *numLabel = new QLabel(number);
    numLabel->setFixedSize(28, 28);
    numLabel->setAlignment(Qt::AlignCenter);
    numLabel->setStyleSheet(
        "background-color: #e94560;"
        "color: #eaeaea;"
        "border-radius: 14px;"
        "font-size: 12px;"
        "font-weight: bold;"
    );

    auto *textLabel = new QLabel(text);
    textLabel->setWordWrap(true);
    textLabel->setStyleSheet("font-size: 14px; color: #a0a0b0;");

    layout->addWidget(numLabel, 0, Qt::AlignTop);
    layout->addWidget(textLabel, 1);

    return row;
}


QWidget *HelpPage::makeSectionLabel(const QString &text) {
    auto *label = new QLabel(text.toUpper());
    label->setStyleSheet(
        "font-size: 11px;"
        "font-weight: bold;"
        "color: #606070;"
        "letter-spacing: 1px;"
    );
    return label;
}


QWidget *HelpPage::makeDivider() {
    auto *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("color: #2a2a4a;");
    return line;
}