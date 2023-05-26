#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=nullptr) noexcept;
    ~MainWindow() noexcept = default;

    void setTheme(const QString& theme) noexcept;
    void exportTheme() noexcept;

private:
    QGridLayout*    layout_;
    QLabel*         themeLabel_;
    QComboBox*      themeSelector_;
    QPushButton*    exportButton_;
};

#endif