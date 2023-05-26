#include <QApplication>
#include "mainwindow.h"
#include "QtTheme.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    QtTheme::removeTheme("light");
    return app.exec();
}