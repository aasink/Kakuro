#pragma once
#include <QWidget>

class QPushButton;

class StartPage : public QWidget {
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);

signals:
    void startGameClicked();        // signal for buttons
    void howToPlayClicked();
    void exitClicked();

private:
    QPushButton *startButton;
    QPushButton *helpButton;        // buttons
    QPushButton *exitButton;
};
