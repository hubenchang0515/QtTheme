#include <QApplication>
#include <QStyle>
#include <QScreen>
#include "mainwindow.h"

using namespace QtTheme;

int main(int argc, char* argv[])
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

#if QT_VERSION >=  QT_VERSION_CHECK(5, 14, 0)
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif

    QApplication app(argc, argv);
    MainWindow window;

    #ifndef Q_OS_WASM
        window.setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                window.sizeHint(),
                qApp->primaryScreen()->availableGeometry()
            )
        );
    #endif

    window.show();
    return app.exec();
}