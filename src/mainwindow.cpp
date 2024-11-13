#include "mainwindow.h"
#include "QtTheme.h"
#include "utils.h"

#include <QApplication>
#include <QFileDialog>
#include <QSizePolicy>
#include <QTextStream>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>
#include <QClipboard>
#include <QKeySequence>
#include <QToolButton>

namespace QtTheme
{

MainWindow::MainWindow(QWidget* parent) noexcept:
    QMainWindow{parent},
    menus_{new QMenuBar},
    tools_{new QToolBar},
    dock_{new QDockWidget{tr("Theme Config")}},
    status_{new QStatusBar},
    config_{new ThemeConfigurator},
    scroll_{new QScrollArea},
    preview_{new ThemePreview},
    packer_{new QtTheme::ZipPacker{this}}
{
    connect(config_, &ThemeConfigurator::currentThemeChanged, this, &MainWindow::setTheme);
    connect(config_, &ThemeConfigurator::exportThemeClicked, this, &MainWindow::exportTheme);
    connect(dock_, &QDockWidget::topLevelChanged, this, &MainWindow::adjustDock);

    setMenuBar(menus_);
    addToolBar(tools_);

    config_->setProperty("Depth", 9);
    dock_->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock_->setWidget(config_);
    addDockWidget(Qt::LeftDockWidgetArea, dock_);

    status_->setProperty("Color", "Primary");
    setStatusBar(status_);

    scroll_->setWidget(preview_);
    scroll_->setWidgetResizable(true);
    setCentralWidget(scroll_);

    initActions();

    config_->setTheme("Flat");
    config_->setBaseColor("Dark");
    config_->setPrimaryColor("Blue");
    config_->setSecondaryColor("Pink");
}

void MainWindow::showStatus(const QString& message, int ms) const noexcept
{
    status_->showMessage(message, ms);
}

void MainWindow::setTheme(const QString& themeName, const QString& baseColor, const QString& primaryColor, const QString& secondaryColor) noexcept
{
    showStatus(QString("Set theme: %1 %2 %3 %4").arg(themeName).arg(baseColor).arg(primaryColor).arg(secondaryColor));
    setStyleSheet(QtTheme::getTheme(themeName, baseColor, primaryColor, secondaryColor));
    qApp->processEvents();
}

void MainWindow::exportTheme(const QString& themeName, const QString& baseColor, const QString& primaryColor, const QString& secondaryColor) const noexcept
{
    showStatus(QString("Export theme: %1 %2 %3 %4").arg(themeName).arg(baseColor).arg(primaryColor).arg(secondaryColor));
    packer_->open();
    QString qrc = "";
    QTextStream stream{&qrc, QIODevice::WriteOnly};
    stream << "<RCC>\n";
    stream << "  <qresource prefix=\"/\">\n";

    QString qssFileName = QString("%1_%2_%3_%4.qss").arg(themeName).arg(baseColor).arg(primaryColor).arg(secondaryColor);
    QString qssContent = QtTheme::getTheme(themeName, baseColor, primaryColor, secondaryColor);
    stream << QString("    <file>%1</file>\n").arg(qssFileName);
    packer_->addFile(qssFileName, qssContent.toUtf8());

    QRegularExpression regexp("url\\(\"(:/(icon/.*))\"\\)");
    QRegularExpressionMatchIterator iter = regexp.globalMatch(qssContent);
    while (iter.hasNext())
    {
        QRegularExpressionMatch match = iter.next();
        QString resPath = match.captured(1);
        QString iconPath = match.captured(2);
        QFile icon{resPath};
        icon.open(QFile::ReadOnly);

        packer_->addFile(iconPath, icon.readAll());
        stream << QString("    <file>%1</file>\n").arg(iconPath);
    }

    stream << "  </qresource>\n";
    stream << "</RCC>\n";
    packer_->addFile("resource.qrc", qrc.toUtf8());
    QFileDialog::saveFileContent(packer_->data(), "theme.zip");
}

void MainWindow::adjustDock() noexcept
{
    dock_->adjustSize();
}

QSize MainWindow::sizeHint() const noexcept
{
    QSize size = dock_->sizeHint();
    size.rwidth() += preview_->minimumSizeHint().width() + 32; // 32 弥补滚动条和各个缝隙的宽度
    size.setHeight(size.width() * 9 / 16); 
    return size;
}

void MainWindow::closeEvent(QCloseEvent* event) noexcept
{
    showStatus(QString("Exit"));

    QMessageBox::StandardButton v = QMessageBox::question(this, tr("Exit"), tr("Do you confirm the exit?"));
    if (v == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::initActions() noexcept
{
    {
        auto menu = new QMenu{tr("&Application"), this};
        menus_->addMenu(menu);

        auto exportTheme = menu->addAction(QIcon(":/icon/save/#26c6da.svg"), tr("&Export Theme"));
        exportTheme->setShortcut(QKeySequence::Save);
        connect(exportTheme, &QAction::triggered, config_, &ThemeConfigurator::emitExportTheme);
        tools_->addAction(exportTheme);

        menu->addSeparator();
        tools_->addSeparator();

        auto go = menu->addMenu(QIcon(":/icon/link/#26c6da.svg"), tr("&Go"));
        auto gotoSource = go->addAction(tr("Go to &Source Page"));
        connect(gotoSource, &QAction::triggered, Utils::toOpenUrl("https://github.com/hubenchang0515/QtTheme"));
        auto gotoPreview = go->addAction(tr("Go to &Preview Page"));
        connect(gotoPreview, &QAction::triggered, Utils::toOpenUrl("https://hubenchang0515.github.io/QtTheme/QtTheme.html"));
        auto gotoDownload = go->addAction(tr("Go to &Download Page"));
        connect(gotoDownload, &QAction::triggered, Utils::toOpenUrl("https://github.com/hubenchang0515/QtTheme/releases"));
        tools_->addWidget(Utils::makeQToolButton(go));

        auto share = menu->addMenu(QIcon(":/icon/share/#26c6da.svg"), tr("&Share"));
        auto copySource = share->addAction(tr("Copy &Source Page Link"));
        connect(copySource, &QAction::triggered, Utils::toCopyText("https://github.com/hubenchang0515/QtTheme"));
        auto copyPreview = share->addAction(tr("Copy &Preview Page Link"));
        connect(copyPreview, &QAction::triggered, Utils::toCopyText("https://hubenchang0515.github.io/QtTheme/QtTheme.html"));
        auto copyDownload = share->addAction(tr("Copy &Download Page Link"));
        connect(copyDownload, &QAction::triggered, Utils::toCopyText("https://github.com/hubenchang0515/QtTheme/releases"));
        tools_->addWidget(Utils::makeQToolButton(share));

        menu->addSeparator();
        tools_->addSeparator();

        auto quit = menu->addAction(QIcon(":/icon/close/#f44336.svg"), tr("&Quit"));
        quit->setShortcut(QKeySequence::Quit);
        connect(quit, &QAction::triggered, this, &MainWindow::close);
    }


    {
        auto menu = new QMenu{tr("&View"), this};
        menus_->addMenu(menu);

        auto toggleThemeConfig = dock_->toggleViewAction();
        toggleThemeConfig->setText(tr("Theme &Config"));
        menu->addAction(toggleThemeConfig);

        auto toggleToolBar = tools_->toggleViewAction();
        toggleToolBar->setText(tr("&Tool Bar"));
        menu->addAction(toggleToolBar);
    }


    {
        auto menu = new QMenu{tr("&Help"), this};
        menus_->addMenu(menu);

        auto doc = menu->addAction(QIcon(":/icon/book/#26c6da.svg"), tr("&Document"));
        connect(doc, &QAction::triggered, Utils::toOpenUrl("https://github.com/hubenchang0515/QtTheme/tree/master/doc"));
        tools_->addAction(doc);

        auto about = menu->addAction(QIcon(":/icon/help/#26c6da.svg"), tr("&About"));
        connect(about, &QAction::triggered, [this](){QMessageBox::aboutQt(this);});
        tools_->addAction(about);
    }
    
}

}; // namespace QtTheme
