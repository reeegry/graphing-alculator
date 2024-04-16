#include "mainwindow.h"
#include "gridwidget.h"

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QGraphicsView>
#include <QTextEdit>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPaintDevice>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QGraphicsScene scene;
    QGraphicsView view(&scene);

    GridWidget* grid = new GridWidget();
    scene.addItem(grid);

    w.setCentralWidget(&view);

    w.show();
    return a.exec();
}


