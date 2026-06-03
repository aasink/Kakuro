#pragma once
#include <QWidget>

class GridWidget;
class QTimer;
class QLabel;

class GamePage : public QWidget {
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    QMenu* getGameMenu() const;             // get game & file menus
    QMenu* getFileMenu() const;

signals:
    void gameMessage(const QString &msg, const int timeout);

private slots:
    void startNewGame();        // game controls
    void resetGame();
    void pauseGame();
    void resumeGame();
    void showHint();

private:
    GridWidget *grid;       // grid, timer, and menus
    QTimer *gameTimer;
    QLabel *timerLabel;
    int elapsedSeconds;
    QMenu *gameMenu;
    QMenu *fileMenu;
};
