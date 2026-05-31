#pragma once
#include <QWidget>

class GridWidget;
class QTimer;
class QLabel;

class GamePage : public QWidget {
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    QMenu* getGameMenu() const;
    QMenu* getFileMenu() const;

signals:
    void gameMessage(const QString &msg, const int timeout);

private slots:
    void startNewGame();
    void resetGame();
    void pauseGame();
    void resumeGame();
    void showHint();

private:
    GridWidget *grid;
    QTimer *gameTimer;
    QLabel *timerLabel;
    int elapsedSeconds;
    QMenu *gameMenu;
    QMenu *fileMenu;
};
