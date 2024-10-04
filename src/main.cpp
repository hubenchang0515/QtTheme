#include <QApplication>
#include <QStyle>
#include <QScreen>
#include "mainwindow.h"

using namespace QtTheme;

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication app(argc, argv);
    MainWindow window;
    window.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            window.sizeHint(),
            qApp->primaryScreen()->availableGeometry()
        )
    );
    window.show();
    return app.exec();
}