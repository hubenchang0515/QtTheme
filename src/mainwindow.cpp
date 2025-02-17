#include "mainwindow.h"
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
#include <QTimer>
#include <QStyle>
#include <QScreen>
#include <QUiLoader>
#include <QBuffer>
#include <QFontDatabase>
#include <QSet>

#include <QtTheme/QtTheme.h>

namespace QtTheme
{

MainWindow::MainWindow(QWidget* parent) noexcept:
    QMainWindow{parent},
    menus_{nullptr},
    tools_{nullptr},
    dock_{nullptr},
    status_{nullptr},
    config_{nullptr},
    tabs_{nullptr},
    scroll_{nullptr},
    preview_{nullptr},
    packer_{nullptr},
    placeholder_{new QLabel{"Loading..."}}
{
    #ifndef Q_OS_WASM
        placeholder_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        setCentralWidget(placeholder_);
        QTimer::singleShot(1000, this, &MainWindow::init);
    #else
        init();
    #endif
}

void MainWindow::showStatus(const QString& message, int ms) const noexcept
{
    status_->showMessage(message, ms);
}

void MainWindow::setTheme(const QString& themeName, const QString& baseColor, const QString& primaryColor, const QString& secondaryColor) noexcept
{
    takeCentralWidget();
    setCentralWidget(placeholder_);
    qApp->processEvents();

    setStyleSheet(QtTheme::getThemeStyle(themeName, baseColor, primaryColor, secondaryColor));

    takeCentralWidget();
    setCentralWidget(tabs_);
    showStatus(QString("Set theme: %1 %2 %3 %4").arg(themeName).arg(baseColor).arg(primaryColor).arg(secondaryColor));
}

void MainWindow::exportTheme(const QString& themeName, const QString& baseColor, const QString& primaryColor, const QString& secondaryColor) const noexcept
{
    showStatus(QString("Export theme: %1 %2 %3 %4").arg(themeName).arg(baseColor).arg(primaryColor).arg(secondaryColor));
    packer_->open();
    QString qrc = "";
    QTextStream stream{&qrc, QIODevice::WriteOnly};
    stream << "<RCC>\n";
    stream << "  <qresource prefix=\"/QtTheme/\">\n";

    QString qssFileName = QString("theme/%1/%2/%3/%4.qss").arg(themeName).arg(baseColor).arg(primaryColor).arg(secondaryColor);
    QString qssContent = QtTheme::getThemeStyle(themeName, baseColor, primaryColor, secondaryColor);
    stream << QString("    <file>%1</file>\n").arg(qssFileName);
    packer_->addFile(qssFileName, qssContent.toUtf8());

    QRegularExpression regexp("url\\(\"(:/QtTheme/(icon/.*))\"\\)");
    QRegularExpressionMatchIterator iter = regexp.globalMatch(qssContent);
    QSet<QString> set;
    while (iter.hasNext())
    {
        QRegularExpressionMatch match = iter.next();
        QString resPath = match.captured(1);
        QString iconPath = match.captured(2);
        if (set.contains(resPath)) 
        {
            continue;
        }
        set.insert(resPath);
        QFile icon{resPath};
        icon.open(QFile::ReadOnly);

        packer_->addFile(iconPath, icon.readAll());
        stream << QString("    <file>%1</file>\n").arg(iconPath);
    }

    stream << "  </qresource>\n";
    stream << "</RCC>\n";

    QString qrcFileName = "QtTheme.qrc";
    packer_->addFile(qrcFileName, qrc.toUtf8());
    QFileDialog::saveFileContent(packer_->data(), "QtTheme.zip");
}

void MainWindow::adjustDock() noexcept
{
    dock_->adjustSize();
}

void MainWindow::loadUiFile(const QString& filepath, const QByteArray& data) noexcept
{
    QFileInfo info{filepath};
    QBuffer buffer;
    buffer.setData(data);
    QUiLoader loader;
    QWidget* widget = loader.load(&buffer);
    Utils::setFont(widget, font_);
    tabs_->addTab(widget, info.fileName());
    tabs_->setCurrentWidget(widget);
}


void MainWindow::loadFontFile(const QString& filepath, const QByteArray& data) noexcept
{
    int id = QFontDatabase::addApplicationFontFromData(data);
    if (id >= 0)
    {
        font_ = QFont{QFontDatabase::applicationFontFamilies(id)[0]};
        int n = tabs_->count();
        for (int i = 1; i < n; i++)
        {
            Utils::setFont(tabs_->widget(i), font_);
        }
    }
}

QSize MainWindow::sizeHint() const noexcept
{
    if (preview_)
    {
        QSize size = dock_->sizeHint();
        size.rwidth() += preview_->minimumSizeHint().width() + 32; // 32 弥补滚动条和各个缝隙的宽度
        size.setHeight(size.width() * 9 / 16); 
        return size;
    }
    else
    {
        return QSize{300, 100};
    }

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

        auto exportTheme = menu->addAction(QIcon(":/QtTheme/icon/save/#26c6da.svg"), tr("&Export Theme"));
        exportTheme->setShortcut(QKeySequence::Save);
        connect(exportTheme, &QAction::triggered, config_, &ThemeConfigurator::emitExportTheme);
        tools_->addAction(exportTheme);

        menu->addSeparator();
        tools_->addSeparator();

        auto go = menu->addMenu(QIcon(":/QtTheme/icon/link/#26c6da.svg"), tr("&Go"));
        auto gotoSource = go->addAction(tr("Go to &Source Page"));
        connect(gotoSource, &QAction::triggered, Utils::toOpenUrl("https://github.com/hubenchang0515/QtTheme"));
        auto gotoPreview = go->addAction(tr("Go to &Preview Page"));
        connect(gotoPreview, &QAction::triggered, Utils::toOpenUrl("https://hubenchang0515.github.io/QtTheme"));
        auto gotoDownload = go->addAction(tr("Go to &Download Page"));
        connect(gotoDownload, &QAction::triggered, Utils::toOpenUrl("https://github.com/hubenchang0515/QtTheme/releases"));
        tools_->addWidget(Utils::makeQToolButton(go));

        auto share = menu->addMenu(QIcon(":/QtTheme/icon/share/#26c6da.svg"), tr("&Share"));
        auto copySource = share->addAction(tr("Copy &Source Page Link"));
        connect(copySource, &QAction::triggered, Utils::toCopyText("https://github.com/hubenchang0515/QtTheme"));
        auto copyPreview = share->addAction(tr("Copy &Preview Page Link"));
        connect(copyPreview, &QAction::triggered, Utils::toCopyText("https://hubenchang0515.github.io/QtTheme"));
        auto copyDownload = share->addAction(tr("Copy &Download Page Link"));
        connect(copyDownload, &QAction::triggered, Utils::toCopyText("https://github.com/hubenchang0515/QtTheme/releases"));
        tools_->addWidget(Utils::makeQToolButton(share));

        menu->addSeparator();
        tools_->addSeparator();

        auto quit = menu->addAction(QIcon(":/QtTheme/icon/close/#f44336.svg"), tr("&Quit"));
        quit->setShortcut(QKeySequence::Quit);
        connect(quit, &QAction::triggered, this, &MainWindow::close);
    }

    {
        auto menu = new QMenu{tr("&File"), this};
        menus_->addMenu(menu);

        auto loadUi = menu->addAction(QIcon(":/QtTheme/icon/arrow_up_circle/#26c6da.svg"), tr("Load &UI File"));
        connect(loadUi, &QAction::triggered, this, &MainWindow::loadUiWidget);
        tools_->addAction(loadUi);

        auto loadFont = menu->addAction(QIcon(":/QtTheme/icon/font/#26c6da.svg"), tr("Load &Font File"));
        connect(loadFont, &QAction::triggered, this, &MainWindow::loadFont);
        tools_->addAction(loadFont);

        tools_->addSeparator();
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

        auto doc = menu->addAction(QIcon(":/QtTheme/icon/book/#26c6da.svg"), tr("&Document"));
        connect(doc, &QAction::triggered, Utils::toOpenUrl("https://github.com/hubenchang0515/QtTheme/tree/master/doc"));
        tools_->addAction(doc);

        auto about = menu->addAction(QIcon(":/QtTheme/icon/help/#26c6da.svg"), tr("&About"));
        connect(about, &QAction::triggered, [this](){QMessageBox::aboutQt(this);});
        tools_->addAction(about);
    }
    
}


void MainWindow::init() noexcept
{
    menus_ = new QMenuBar;
    tools_ = new QToolBar;
    dock_ = new QDockWidget{tr("Theme Config")};
    status_ = new QStatusBar;
    config_ = new ThemeConfigurator;
    tabs_ = new QTabWidget;
    scroll_ = new QScrollArea;
    preview_ = new ThemePreview;
    packer_ = new QtTheme::ZipPacker{this};

    config_->setProperty("Depth", 9);
    dock_->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock_->setWidget(config_);
    status_->setProperty("Color", "Primary");

    scroll_->takeWidget();
    scroll_->setWidget(preview_);
    scroll_->setWidgetResizable(true);

    tabs_->addTab(scroll_, "Preview");
    tabs_->setTabsClosable(true);
    tabs_->tabBar()->setTabButton(0, QTabBar::RightSide, nullptr); // 禁止关闭默认的预览页
    tabs_->tabBar()->setTabButton(0, QTabBar::LeftSide, nullptr);
    connect(tabs_, &QTabWidget::tabCloseRequested, this, &MainWindow::closeUiWidget);

    initActions();

    config_->setTheme("Flat");
    config_->setBaseColor("Dark");
    config_->setPrimaryColor("Blue");
    config_->setSecondaryColor("Pink");

    connect(config_, &ThemeConfigurator::currentThemeChanged, this, &MainWindow::setTheme);
    connect(config_, &ThemeConfigurator::exportThemeClicked, this, &MainWindow::exportTheme);
    connect(dock_, &QDockWidget::topLevelChanged, this, &MainWindow::adjustDock);
    config_->emitCurrentTheme();

    setMenuBar(menus_);
    addToolBar(tools_);
    addDockWidget(Qt::LeftDockWidgetArea, dock_);
    setStatusBar(status_);
    takeCentralWidget();
    setCentralWidget(tabs_);

    #ifndef Q_OS_WASM
        setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                sizeHint(),
                qApp->primaryScreen()->availableGeometry()
            )
        );
    #endif
}

void MainWindow::loadUiWidget() noexcept
{
    QFileDialog::getOpenFileContent("UI File(*.ui *.xml)", [this](const QString& filepath, const QByteArray& data){
        this->loadUiFile(filepath, data);
    });
}

void MainWindow::closeUiWidget(int index) noexcept
{
    tabs_->widget(index)->deleteLater();
}


void MainWindow::loadFont() noexcept
{
    QFileDialog::getOpenFileContent("Font File(*.otf *.ttf *.woff *.woff2)", [this](const QString& filepath, const QByteArray& data){
        this->loadFontFile(filepath, data);
    });
}

}; // namespace QtTheme
