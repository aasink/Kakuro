#pragma once
#include <QWidget>

class GridWidget : public QWidget {
    Q_OBJECT

public:
    explicit GridWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;
};