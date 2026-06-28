#pragma once
#include <QWidget>
#include <QMenu>

class GridWidget;
class Controller;
class QTimer;
class QLabel;
class QPushButton;

class GamePage : public QWidget {
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    QMenu* getGameMenu() const;             // get game & file menus
    QMenu* getFileMenu() const;
    void startNewGame();

    QPushButton *menuButton;        // games hamburger menu

signals:
    void gameMessage(const QString &msg, const int timeout);
    void returnToStart();

private slots:        // game controls
    void resetGame();
    void pauseGame();
    void resumeGame();
    void showHint();
    void onTimerTick();

private:
    GridWidget *grid;      
    Controller *controller;

    QMenu *gameMenu;            // menus
    QMenu *fileMenu;

    QLabel *difficultyLabel;
    bool isPaused;

    QPushButton *pauseButton;   // buttons
    QPushButton *undoButton;
    QPushButton *eraseButton;
    QPushButton *notesButton;
    QPushButton *hintButton;

    QPushButton *numpadButtons[9];

    QTimer  *gameTimer;         // for timer
    QLabel *timerLabel;
    int elapsedSeconds;

    QWidget *buildInfoBar();    // helpers
    QWidget *buildSidebar();
    QWidget *buildToolRow();
    QWidget *buildNumpad();
};
