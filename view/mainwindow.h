#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Model/Model.h"
#include <qcustomplot.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int count = 0;

private slots:
    void on_lineEdit_editingFinished();
    void xAxisRangeChanged(const QCPRange &newRange, const QCPRange &oldRange);

private:
    Ui::MainWindow *ui;
    //Function *model;
    std::vector<Function*> models;


};
#endif // MAINWINDOW_H
