#include "mainwindow.h"
#include "QtTheme.h"

#include <QFileDialog>
#include <QSizePolicy>

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTimeEdit>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QSlider>
#include <QDial>
#include <QProgressBar>
#include <QLCDNumber>
#include <QRadioButton>
#include <QCheckBox>
#include <QListView>
#include <QSlider>

MainWindow::MainWindow(QWidget* parent) noexcept:
    QMainWindow(parent),
    layout_(new QGridLayout),
    themeLabel_(new QLabel(tr("Theme:"))),
    themeSelector_(new QComboBox),
    exportButton_(new QPushButton(tr("EXPORT")))
{
    {
        auto row = new QHBoxLayout;
        row->addWidget(themeLabel_);
        row->addWidget(themeSelector_);
        row->addWidget(exportButton_);
        layout_->addLayout(row, 0, 0, 1, -1);

        auto themes = QtTheme::getThemeList();
        themeSelector_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        if (!themes.empty())
        {
            setStyleSheet(QtTheme::getTheme(themes[0]));
            themeSelector_->addItems(themes);
            themeSelector_->setView(new QListView);
        }
        connect(themeSelector_, &QComboBox::currentTextChanged, this, &MainWindow::setTheme);

        exportButton_->setProperty("color", "Primary");
        connect(exportButton_, &QPushButton::clicked, this, &MainWindow::exportTheme);
    }
    
    {
        auto label1 = new QLabel(tr("Label"));
        auto label2 = new QLabel(tr("Disabled"));
        label2->setEnabled(false);

        auto label3 = new QLabel(tr("Primary"));
        label3->setProperty("color", "Primary");
        auto label4 = new QLabel(tr("Primary"));
        label4->setProperty("color", "Primary");
        label4->setEnabled(false);

        auto label5 = new QLabel(tr("Secondary"));
        label5->setProperty("color", "Secondary");
        auto label6 = new QLabel(tr("Secondary"));
        label6->setProperty("color", "Secondary");
        label6->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(label1, 0, 0);
        grid->addWidget(label2, 0, 1);
        grid->addWidget(label3, 1, 0);
        grid->addWidget(label4, 1, 1);
        grid->addWidget(label5, 2, 0);
        grid->addWidget(label6, 2, 1);

        auto groupbox = new QGroupBox(tr("QLabel"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 1, 0);
    }

    {
        auto button1 = new QPushButton(tr("Button"));
        auto button2 = new QPushButton(tr("Disabled"));
        button2->setEnabled(false);

        auto button3 = new QPushButton(tr("Primary"));
        button3->setProperty("color", "Primary");
        auto button4 = new QPushButton(tr("Primary"));
        button4->setProperty("color", "Primary");
        button4->setEnabled(false);

        auto button5 = new QPushButton(tr("Secondary"));
        button5->setProperty("color", "Secondary");
        auto button6 = new QPushButton(tr("Secondary"));
        button6->setProperty("color", "Secondary");
        button6->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(button1, 0, 0);
        grid->addWidget(button2, 1, 0);
        grid->addWidget(button3, 0, 1);
        grid->addWidget(button4, 1, 1);
        grid->addWidget(button5, 0, 2);
        grid->addWidget(button6, 1, 2);
        
        auto groupbox = new QGroupBox(tr("QButton"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 1, 1);
    }

    {
        auto line1 = new QLineEdit(tr("Line Edit"));
        auto line2 = new QLineEdit(tr("Read Only"));
        line2->setReadOnly(true);
        auto line3 = new QLineEdit(tr("Disabled"));
        line3->setEnabled(false);

        auto line4 = new QLineEdit(tr("Primary"));
        line4->setProperty("color", "Primary");
        auto line5 = new QLineEdit(tr("Primary"));
        line5->setProperty("color", "Primary");
        line5->setReadOnly(true);
        auto line6 = new QLineEdit(tr("Primary"));
        line6->setProperty("color", "Primary");
        line6->setEnabled(false);

        auto line7 = new QLineEdit(tr("Secondary"));
        line7->setProperty("color", "Secondary");
        auto line8 = new QLineEdit(tr("Secondary"));
        line8->setProperty("color", "Secondary");
        line8->setReadOnly(true);
        auto line9 = new QLineEdit(tr("Secondary"));
        line9->setProperty("color", "Secondary");
        line9->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(line1, 0, 0);
        grid->addWidget(line2, 1, 0);
        grid->addWidget(line3, 2, 0);
        grid->addWidget(line4, 0, 1);
        grid->addWidget(line5, 1, 1);
        grid->addWidget(line6, 2, 1);
        grid->addWidget(line7, 0, 2);
        grid->addWidget(line8, 1, 2);
        grid->addWidget(line9, 2, 2);

        auto groupbox = new QGroupBox(tr("QLineEdit"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 2, 0, 1, 2);
    }

    {
        auto progress1 = new QProgressBar;
        progress1->setValue(66);
        auto progress2 = new QProgressBar;
        progress2->setValue(66);
        progress2->setEnabled(false);

        auto progress3 = new QProgressBar;
        progress3->setProperty("color", "Primary");
        progress3->setValue(66);
        auto progress4 = new QProgressBar;
        progress4->setProperty("color", "Primary");
        progress4->setValue(66);
        progress4->setEnabled(false);

        auto progress5 = new QProgressBar;
        progress5->setProperty("color", "Secondary");
        progress5->setValue(66);
        auto progress6 = new QProgressBar;
        progress6->setProperty("color", "Secondary");
        progress6->setValue(66);
        progress6->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(progress1, 0, 0);
        grid->addWidget(progress2, 0, 1);
        grid->addWidget(progress3, 1, 0);
        grid->addWidget(progress4, 1, 1);
        grid->addWidget(progress5, 2, 0);
        grid->addWidget(progress6, 2, 1);

        auto groupbox = new QGroupBox(tr("QProgressBar"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 3, 0, 1, 2);
    }

    {
        auto radio1 = new QRadioButton(tr("Radio Button"));
        auto radio2 = new QRadioButton(tr("Disabled"));
        radio2->setEnabled(false);

        auto radio3 = new QRadioButton(tr("Primary"));
        radio3->setProperty("color", "Primary");
        auto radio4 = new QRadioButton(tr("Disabled"));
        radio4->setProperty("color", "Primary");
        radio4->setEnabled(false);

        auto radio5 = new QRadioButton(tr("Secondary"));
        radio5->setProperty("color", "Secondary");
        auto radio6 = new QRadioButton(tr("Disabled"));
        radio6->setProperty("color", "Secondary");
        radio6->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(radio1, 0, 0);
        grid->addWidget(radio2, 0, 1);
        grid->addWidget(radio3, 1, 0);
        grid->addWidget(radio4, 1, 1);
        grid->addWidget(radio5, 2, 0);
        grid->addWidget(radio6, 2, 1);

        auto groupbox = new QGroupBox(tr("QRadioButton"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 4, 0);
    }

    {
        auto check1 = new QCheckBox(tr("Check Box"));
        auto check2 = new QCheckBox(tr("Disabled"));
        check2->setEnabled(false);
        auto check3 = new QCheckBox(tr("Primary"));
        check3->setProperty("color", "Primary");
        auto check4 = new QCheckBox(tr("Primary"));
        check4->setProperty("color", "Primary");
        check4->setEnabled(false);
        auto check5 = new QCheckBox(tr("Secondary"));
        check5->setProperty("color", "Secondary");
        auto check6 = new QCheckBox(tr("Secondary"));
        check6->setProperty("color", "Secondary");
        check6->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(check1, 0, 0);
        grid->addWidget(check2, 0, 1);
        grid->addWidget(check3, 1, 0);
        grid->addWidget(check4, 1, 1);
        grid->addWidget(check5, 2, 0);
        grid->addWidget(check6, 2, 1);
        
        auto groupbox = new QGroupBox(tr("QCheckBox"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 5, 0);
    }

    {
        auto slider1 = new QSlider(Qt::Horizontal);
        slider1->setValue(66);
        auto slider2 = new QSlider(Qt::Horizontal);
        slider2->setValue(66);
        slider2->setEnabled(false);

        auto slider3 = new QSlider(Qt::Horizontal);
        slider3->setValue(66);
        slider3->setProperty("color", "Primary");
        auto slider4 = new QSlider(Qt::Horizontal);
        slider4->setValue(66);
        slider4->setProperty("color", "Primary");
        slider4->setEnabled(false);

        auto slider5 = new QSlider(Qt::Horizontal);
        slider5->setValue(66);
        slider5->setProperty("color", "Secondary");
        auto slider6 = new QSlider(Qt::Horizontal);
        slider6->setValue(66);
        slider6->setProperty("color", "Secondary");
        slider6->setEnabled(false);

        auto slider7 = new QSlider(Qt::Vertical);
        slider7->setValue(66);
        auto slider8 = new QSlider(Qt::Vertical);
        slider8->setValue(66);
        slider8->setEnabled(false);

        auto slider9 = new QSlider(Qt::Vertical);
        slider9->setValue(66);
        slider9->setProperty("color", "Primary");
        auto slider10 = new QSlider(Qt::Vertical);
        slider10->setValue(66);
        slider10->setProperty("color", "Primary");
        slider10->setEnabled(false);

        auto slider11 = new QSlider(Qt::Vertical);
        slider11->setValue(66);
        slider11->setProperty("color", "Secondary");
        auto slider12 = new QSlider(Qt::Vertical);
        slider12->setValue(66);
        slider12->setProperty("color", "Secondary");
        slider12->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(slider1, 0, 0);
        grid->addWidget(slider2, 1, 0);
        grid->addWidget(slider3, 2, 0);
        grid->addWidget(slider4, 3, 0);
        grid->addWidget(slider5, 4, 0);
        grid->addWidget(slider6, 5, 0);

        grid->addWidget(slider7, 0, 1, 6, 1);
        grid->addWidget(slider8, 0, 2, 6, 1);
        grid->addWidget(slider9, 0, 3, 6, 1);
        grid->addWidget(slider10, 0, 4, 6, 1);
        grid->addWidget(slider11, 0, 5, 6, 1);
        grid->addWidget(slider12, 0, 6, 6, 1);

        auto groupbox = new QGroupBox(tr("QSlider"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 4, 1, 2, 1);
    }

    auto widget = new QWidget;
    widget->setLayout(layout_);
    setCentralWidget(widget);
}

void MainWindow::setTheme(const QString& theme) noexcept
{
    setStyleSheet(QtTheme::getTheme(theme));
}

void MainWindow::exportTheme() noexcept
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Export Theme Directory"), QDir::homePath());
    QtTheme::exportThemes(path, QStringList{themeSelector_->currentText()});
}