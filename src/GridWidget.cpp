#include "GridWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QSize>

GridWidget::GridWidget(QWidget *parent) : QWidget(parent) {
}

void GridWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::black);

    int rows = 16;
    int cols = 16;
    int cellW = width() / cols;
    int cellH = height() / rows;

    for (int r = 0; r <= rows; ++r) {
        painter.drawLine(0, r * cellH, width(), r * cellH);
    }
    for (int c = 0; c <= cols; ++c) {
        painter.drawLine(c * cellW, 0, c * cellW, height());
    }
}

QSize GridWidget::sizeHint() const {
    return QSize(400, 400);
}