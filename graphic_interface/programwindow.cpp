#include <QApplication>
#include <QMainWindow>
#include "programwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Main Window");
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
