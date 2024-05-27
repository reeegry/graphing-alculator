#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    models.reserve(3);

    //connect(ui->widget->xAxis, SIGNAL(rangeChanged(const QCPRange &, const QCPRange &)), this, SLOT(xAxisRangeChanged(const QCPRange &, const QCPRange &)));
    //connect( ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange,QCPRange)), this, SLOT(xAxisRangeChanged(QCPRange,QCPRange)) );
    ui->setupUi(this);

    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->widget->xAxis->setRange(-10, 10);
    ui->widget->yAxis->setRange(-10, 10);
    //connect(ui->widget->xAxis, SIGNAL(rangeChanged(const QCPRange &, const QCPRange &)), this, SLOT(xAxisRangeChanged(const QCPRange &, const QCPRange &)));
    connect( ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange,QCPRange)), this, SLOT(xAxisRangeChanged(QCPRange,QCPRange)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_editingFinished()
{
    std::string funcStr = ui->lineEdit->text().toStdString();

    if (!count) {
        count++;
    }

    //Function *func = new Function(funcStr);
    models[0] = new Function(funcStr);
//    qDebug() << funcStr << '\n';
}

// void MainWindow::initConnections(){
//     connect( ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange,QCPRange)), this, SLOT(xAxisRangeChanged(QCPRange,QCPRange)) );
// }

// (r - l) / x = 10

void MainWindow::xAxisRangeChanged(const QCPRange &newRange, const QCPRange &oldRange)
{
    Q_UNUSED(oldRange); // Используем это, чтобы избежать предупреждения о неиспользуемой переменной
    if (!count) {
        return;
    }


    models[0]->setStep(((newRange.upper - newRange.lower) / 1000));
    models[0]->getPoints(models[0]->getOriginalFunction(), newRange.lower, newRange.upper);

    if (!ui->widget->graphCount()) {
            ui->widget->addGraph();
    }

    ui->widget->graph(0)->setData(*models[0]->getX(), *models[0]->getY());

}
