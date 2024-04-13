#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    int values[10] = {10, 11, 16, 12, 25, 20, 14, 7, 19, 13};
    const int vertStep = 10;
    const int horStep = 40;
    const int sX = 50;
    const int sY = 30 * vertStep;

    QPainter painter(this);

    painter.setPen(QColor(30, 30, 30));
    painter.drawLine(sX, sY, sX, sY - (30 * vertStep + 50));
    painter.drawLine(sX, sY, sX + horStep * 10, sY);

    painter.setPen(QColor(70, 100, 220));
    painter.drawLine(sX, sY - 10 * vertStep, sX + horStep * 10, sY - 10 * vertStep);
    painter.drawLine(sX, sY - 20 * vertStep, sX + horStep * 10, sY - 20 * vertStep);
    painter.drawLine(sX, sY - 30 * vertStep, sX + horStep * 10, sY - 30 * vertStep);

    QPoint valuesPoints[10];
    for (int i = 0; i < 10; ++i) {
        valuesPoints[i] = QPoint(sX - i * horStep + 15, sY - values[i] * vertStep);
    }


}

