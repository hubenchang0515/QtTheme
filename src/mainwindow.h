#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QScrollArea>
#include <QEvent>
#include <QCloseEvent>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>

#include "ThemeConfigurator.h"
#include "ThemePreview.h"
#include "ZipPacker.h"

namespace QtTheme
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=nullptr) noexcept;
    ~MainWindow() noexcept = default;

    void showStatus(const QString& message, int ms=2000) const noexcept;
    void setTheme(const QString& themeName, const QString& baseColor, const QString& primaryColor, const QString& secondaryColor) noexcept;
    void exportTheme(const QString& themeName, const QString& baseColor, const QString& primaryColor, const QString& secondaryColor) const noexcept;
    void adjustDock() noexcept;

    virtual QSize sizeHint() const noexcept override;

protected:
    virtual void closeEvent(QCloseEvent* event) noexcept override;

private:
    QMenuBar* menus_;
    QToolBar* tools_;
    QDockWidget* dock_;
    QStatusBar* status_;
    ThemeConfigurator* config_;
    QScrollArea* scroll_;
    ThemePreview* preview_;
    QtTheme::ZipPacker* packer_;

    void initActions() noexcept;
};

}; // namespace QtTheme

#endif