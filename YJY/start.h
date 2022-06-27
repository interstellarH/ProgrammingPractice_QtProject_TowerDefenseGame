#ifndef START_H
#define START_H

#include <QWidget>
#include <QMainWindow>
#include <QPaintEvent>
#include <QWidget>
#include <QWindow>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class start;
}
QT_END_NAMESPACE

class start: public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();

    void paintEvent(QPaintEvent*);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::start *ui;

};

#endif // START_H
