#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QAction>

class StartPage;
class GamePage;
class HelpPage;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stack;      // stack and pages
    StartPage *startPage;
    GamePage *gamePage;
    HelpPage *helpPage;

    QAction *gameMenu = nullptr;  // menus
    QAction *fileMenu = nullptr;

private slots:
    void showStartPage();
    void showGamePage();            // game controls
    void showHelpPage();
    void showHowToPlay();
    void showAbout();
};
