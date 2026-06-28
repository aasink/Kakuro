#include "GridWidget.h"
#include "Game/Board.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QResizeEvent>


GridWidget::GridWidget(Controller* controller, QWidget *parent)
    : QWidget(parent), controller(controller) {
        setFocusPolicy(Qt::StrongFocus);
}


void GridWidget::recalculateLayout() {  // make sure the board stays square
    const Board &board = controller->getBoard();
    int rows = board.rows();
    int cols = board.cols();
 
    int size = std::min(width(), height());    // constrain to smallest dimension
    cellSize = size / std::max(rows, cols);            // square cells
    offsetX = (width() - cols * cellSize) / 2;   // center horizontally
    offsetY = (height() - rows * cellSize) / 2;   // center vertically
}
 
void GridWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    recalculateLayout();
}


bool GridWidget::isInRun(int r, int c) const {
    if (selectedRow < 0 || selectedCol < 0) return false;
 
    const Board &board = controller->getBoard();
 
    if (r == selectedRow) {             // check same row run
        int left = selectedCol;
        int right = selectedCol;
        while (left > 0 && board.getCell(r, left - 1).type == CellType::Empty) --left;
        while (right < board.cols() - 1 && board.getCell(r, right + 1).type == CellType::Empty) ++right;
        if (c >= left && c <= right) return true;
    }
 
    if (c == selectedCol) {         // check same col run
        int top = selectedRow;
        int bottom = selectedRow;
        while (top > 0 && board.getCell(top - 1, c).type == CellType::Empty) --top;
        while (bottom < board.rows() - 1 && board.getCell(bottom + 1, c).type == CellType::Empty) ++bottom;
        if (r >= top && r <= bottom) return true;
    }
 
    return false;
}


void GridWidget::paintEvent(QPaintEvent *) {
    if (cellSize == 0) recalculateLayout();
 
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
 
    const Board &board = controller->getBoard();
    int rows = board.rows();
    int cols = board.cols();
 
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            QRect rect(offsetX + c * cellSize, offsetY + r * cellSize, cellSize, cellSize);
            const Cell &cell = board.getCell(r, c);
 
            bool selected = (r == selectedRow && c == selectedCol);
            bool inRun = !selected && isInRun(r, c);
 
            switch (cell.type) {
                case CellType::Blocked:
                    drawBlockedCell(painter, rect);
                    break;
                case CellType::Clue:
                    drawClueCell(painter, rect, cell.clueAcross, cell.clueDown);
                    break;
                case CellType::Empty:
                    drawEmptyCell(painter, rect, cell.value, selected, inRun);
                    break;
            }
        }
    }
}
 
void GridWidget::drawBlockedCell(QPainter &p, const QRect &rect) const {
    p.fillRect(rect, QColor(COLOR_BLOCKED));
}
 
void GridWidget::drawClueCell(QPainter &p, const QRect &rect, int across, int down) const {
    p.fillRect(rect, QColor(COLOR_CLUE_BG));

    p.setPen(QPen(QColor(COLOR_CELL_BORDER), 1));
    p.drawRect(rect);

    QPolygon topRightTriangle;                              // right triangle 
    topRightTriangle << rect.topLeft() + QPoint(-1, -1)
                    << rect.topRight() + QPoint(1, -1)
                    << rect.bottomRight() + QPoint(1, 1);

    QPolygon bottomLeftTriangle;                                // left triangle
    bottomLeftTriangle << rect.topLeft() + QPoint(-1, -1)
                    << rect.bottomLeft() + QPoint(-1, 1)
                    << rect.bottomRight() + QPoint(1, 1);

    p.setPen(QPen(QColor(COLOR_DIAGONAL), 1));              // draw diagonal
    p.drawLine(rect.topLeft(), rect.bottomRight());

    int fontSize = std::max(8, cellSize / 4);
    QFont font = p.font();
    font.setPointSize(fontSize);
    font.setBold(false);
    p.setFont(font);
    p.setPen(QColor(COLOR_CLUE_TEXT));
 
    if (across > 0) {                           // add across clue
        p.setPen(QColor(COLOR_CLUE_TEXT));
        QRect topRight(rect.center().x(), rect.top(), rect.width() / 2, rect.height() / 2);
        p.drawText(topRight, Qt::AlignCenter, QString::number(across));
    }
    else {                                      // otherwise block
        p.setBrush(QColor(COLOR_BLOCKED));
        p.setPen(Qt::NoPen);
        p.drawPolygon(topRightTriangle);
        p.setBrush(Qt::NoBrush);
    }
 
    if (down > 0) {                             // add down cluse
        p.setPen(QColor(COLOR_CLUE_TEXT));
        QRect bottomLeft(rect.left(), rect.center().y(), rect.width() / 2, rect.height() / 2);
        p.drawText(bottomLeft, Qt::AlignCenter, QString::number(down));
    }
    else {                                      // other wise block
        p.setBrush(QColor(COLOR_BLOCKED));
        p.setPen(Qt::NoPen);
        p.drawPolygon(bottomLeftTriangle);
        p.setBrush(Qt::NoBrush);
    }
}
 
void GridWidget::drawEmptyCell(QPainter &p, const QRect &rect, int value, bool selected, bool inRun) const {
    QColor bg = selected ? QColor(COLOR_SELECTED) : inRun ? QColor(COLOR_RUN_HIGHLIGHT) : QColor(COLOR_CELL_BG);
    p.fillRect(rect, bg);
 
    p.setPen(QPen(QColor(COLOR_CELL_BORDER), 1));
    p.drawRect(rect);
 
    if (value > 0) {
        int fontSize = std::max(8, cellSize / 3);
        QFont font = p.font();
        font.setPointSize(fontSize);
        font.setBold(selected);     // bold if selected cell
        p.setFont(font);
        p.setPen(QColor(selected ? COLOR_SELECTED_TEXT : COLOR_CELL_TEXT));
        p.drawText(rect, Qt::AlignCenter, QString::number(value));
    }
}
 

void GridWidget::mousePressEvent(QMouseEvent *event) {
    if (cellSize == 0) return;
 
    int c = (event->pos().x() - offsetX) / cellSize;
    int r = (event->pos().y() - offsetY) / cellSize;
 
    const Board &board = controller->getBoard();
    if (r < 0 || r >= board.rows() || c < 0 || c >= board.cols()) return;
 
    if (board.getCell(r, c).type != CellType::Empty) return;

    selectedRow = r;
    selectedCol = c;
    update();            // trigger repaint
}
 

void GridWidget::keyPressEvent(QKeyEvent *event) {
    if (selectedRow < 0 || selectedCol < 0) return;
 
    const Board &board = controller->getBoard();
    int rows = board.rows();
    int cols = board.cols();
 
    switch (event->key()) {
        case Qt::Key_1: case Qt::Key_2: case Qt::Key_3:             // if input is 1-9
        case Qt::Key_4: case Qt::Key_5: case Qt::Key_6:
        case Qt::Key_7: case Qt::Key_8: case Qt::Key_9:
            inputDigit(event->key() - Qt::Key_0);
            break;
 
        case Qt::Key_Backspace:                                     // if delete
        case Qt::Key_Delete:
            controller->setCellValue(selectedRow, selectedCol, 0);
            update();
            break;
 
        case Qt::Key_Left:                                          // for baord navigation
            if (selectedCol > 0) { --selectedCol; update(); }
            break;
        case Qt::Key_Right:
            if (selectedCol < cols - 1) { ++selectedCol; update(); }
            break;
        case Qt::Key_Up:
            if (selectedRow > 0) { --selectedRow; update(); }
            break;
        case Qt::Key_Down:
            if (selectedRow < rows - 1) { ++selectedRow; update(); }
            break;
 
        default:
            QWidget::keyPressEvent(event);
    }
}
 
void GridWidget::inputDigit(int digit) {                // set cell value
    if (selectedRow < 0 || selectedCol < 0) return;
    controller->setCellValue(selectedRow, selectedCol, digit);
    update();
}

QSize GridWidget::sizeHint() const {
    return QSize(400, 400);
}