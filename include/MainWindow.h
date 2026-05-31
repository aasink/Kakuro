#pragma once
#include <QMainWindow>
#include <QStackedWidget>

class StartPage;
class GamePage;
class QWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;
    StartPage *startPage;
    GamePage *gamePage;

private slots:
    void showStartPage();
    void showGamePage();
    void showHowToPlay();
    void showAbout();
};
