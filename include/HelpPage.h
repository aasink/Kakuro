#pragma once
#include <QWidget>

class QPushButton;
class QVBoxLayout;

class HelpPage : public QWidget {
    Q_OBJECT

public:
    explicit HelpPage(QWidget *parent = nullptr);

signals:
    void backClicked();

private:
    QWidget *makeCard(const QString &title, const QString &body);
    QWidget *makeRuleRow(const QString &number, const QString &text);
    QWidget *makeSectionLabel(const QString &text);
    QWidget *makeDivider();
};