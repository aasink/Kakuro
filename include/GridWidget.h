#pragma once
#include <QWidget>
#include "Game/Controller.h"

class GridWidget : public QWidget {
    Q_OBJECT

public:
    explicit GridWidget(Controller* controller, QWidget *parent = nullptr);
    void inputDigit(int digit);         // called by numpad buttons

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    QSize sizeHint() const override;
    
private:
    Controller* controller;

    int cellSize  = 0;
    int offsetX   = 0;
    int offsetY   = 0;

    int selectedRow = -1;
    int selectedCol = -1;

    void recalculateLayout();   // ensure board is sized correclty
    bool isInRun(int r, int c) const;   // if cell is in across or fdown runs of selected cell
    void drawBlockedCell (QPainter &p, const QRect &rect) const;
    void drawClueCell    (QPainter &p, const QRect &rect, int across, int down) const;
    void drawEmptyCell   (QPainter &p, const QRect &rect, int value, bool selected, bool inRun)                                const;
 
    // colors for the board
    static constexpr auto COLOR_BLOCKED = "#000000";
    static constexpr auto COLOR_CLUE_BG = "#BDA4A9";
    static constexpr auto COLOR_CLUE_TEXT = "#eaeaea";
    static constexpr auto COLOR_CELL_BG = "#1e1e3a";
    static constexpr auto COLOR_CELL_BORDER = "#000000";
    static constexpr auto COLOR_CELL_TEXT = "#eaeaea";
    static constexpr auto COLOR_SELECTED = "#e94560";
    static constexpr auto COLOR_SELECTED_TEXT = "#ffffff";
    static constexpr auto COLOR_RUN_HIGHLIGHT = "#2a2a5a";
    static constexpr auto COLOR_DIAGONAL = "#2a2a4a";
};