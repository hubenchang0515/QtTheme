#include "ThemePreview.h"

#include <QFileDialog>
#include <QSizePolicy>

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTimeEdit>
#include <QDateEdit>
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
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QMessageBox>
#include <QSplitter>

namespace QtTheme
{

ThemePreview::ThemePreview(QWidget* parent) noexcept:
    QWidget{parent},
    layout_{new QGridLayout}
{
    {
        auto label1 = new QLabel(tr("Label"));
        auto label2 = new QLabel(tr("Disabled"));
        label2->setEnabled(false);

        auto label3 = new QLabel(tr("Primary"));
        label3->setProperty("Color", "Primary");
        auto label4 = new QLabel(tr("Primary"));
        label4->setProperty("Color", "Primary");
        label4->setEnabled(false);

        auto label5 = new QLabel(tr("Secondary"));
        label5->setProperty("Color", "Secondary");
        auto label6 = new QLabel(tr("Secondary"));
        label6->setProperty("Color", "Secondary");
        label6->setEnabled(false);

        auto label7 = new QLabel(tr("Success"));
        label7->setProperty("Color", "Success");
        auto label8 = new QLabel(tr("Success"));
        label8->setProperty("Color", "Success");
        label8->setEnabled(false);

        auto label9 = new QLabel(tr("Warning"));
        label9->setProperty("Color", "Warning");
        auto label10 = new QLabel(tr("Warning"));
        label10->setProperty("Color", "Warning");
        label10->setEnabled(false);

        auto label11 = new QLabel(tr("Danger"));
        label11->setProperty("Color", "Danger");
        auto label12 = new QLabel(tr("Danger"));
        label12->setProperty("Color", "Danger");
        label12->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(label1, 0, 0);
        grid->addWidget(label2, 0, 1);
        grid->addWidget(label3, 1, 0);
        grid->addWidget(label4, 1, 1);
        grid->addWidget(label5, 2, 0);
        grid->addWidget(label6, 2, 1);
        grid->addWidget(label7, 3, 0);
        grid->addWidget(label8, 3, 1);
        grid->addWidget(label9, 4, 0);
        grid->addWidget(label10, 4, 1);
        grid->addWidget(label11, 5, 0);
        grid->addWidget(label12, 5, 1);

        auto groupbox = new QGroupBox(tr("QLabel"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 0, 0, 2, 1);
    }

    {
        auto button1 = new QPushButton(tr("Button"));
        auto button2 = new QPushButton(tr("Checkable"));
        button2->setCheckable(true);
        auto button3 = new QPushButton(tr("Disabled"));
        button3->setEnabled(false);

        auto button4 = new QPushButton(tr("Primary"));
        button4->setProperty("Color", "Primary");
        auto button5 = new QPushButton(tr("Checkable"));
        button5->setProperty("Color", "Primary");
        button5->setCheckable(true);
        auto button6 = new QPushButton(tr("Primary"));
        button6->setProperty("Color", "Primary");
        button6->setEnabled(false);

        auto button7 = new QPushButton(tr("Secondary"));
        button7->setProperty("Color", "Secondary");
        auto button8 = new QPushButton(tr("Checkable"));
        button8->setProperty("Color", "Secondary");
        button8->setCheckable(true);
        auto button9 = new QPushButton(tr("Secondary"));
        button9->setProperty("Color", "Secondary");
        button9->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(button1, 0, 0);
        grid->addWidget(button2, 1, 0);
        grid->addWidget(button3, 2, 0);
        grid->addWidget(button4, 0, 1);
        grid->addWidget(button5, 1, 1);
        grid->addWidget(button6, 2, 1);
        grid->addWidget(button7, 0, 2);
        grid->addWidget(button8, 1, 2);
        grid->addWidget(button9, 2, 2);
        
        auto groupbox = new QGroupBox(tr("QButton"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 0, 1);
    }

    {
        auto line1 = new QLineEdit(tr("Line Edit"));
        auto line2 = new QLineEdit(tr("Read Only"));
        line2->setReadOnly(true);
        auto line3 = new QLineEdit(tr("Disabled"));
        line3->setEnabled(false);

        auto line4 = new QLineEdit(tr("Primary"));
        line4->setProperty("Color", "Primary");
        auto line5 = new QLineEdit(tr("Primary"));
        line5->setProperty("Color", "Primary");
        line5->setReadOnly(true);
        auto line6 = new QLineEdit(tr("Primary"));
        line6->setProperty("Color", "Primary");
        line6->setEnabled(false);

        auto line7 = new QLineEdit(tr("Secondary"));
        line7->setProperty("Color", "Secondary");
        auto line8 = new QLineEdit(tr("Secondary"));
        line8->setProperty("Color", "Secondary");
        line8->setReadOnly(true);
        auto line9 = new QLineEdit(tr("Secondary"));
        line9->setProperty("Color", "Secondary");
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

        layout_->addWidget(groupbox, 1, 1, 1, 1);
    }

    {
        auto progress1 = new QProgressBar;
        progress1->setValue(66);
        auto progress2 = new QProgressBar;
        progress2->setValue(66);
        progress2->setEnabled(false);

        auto progress3 = new QProgressBar;
        progress3->setProperty("Color", "Primary");
        progress3->setValue(66);
        auto progress4 = new QProgressBar;
        progress4->setProperty("Color", "Primary");
        progress4->setValue(66);
        progress4->setEnabled(false);

        auto progress5 = new QProgressBar;
        progress5->setProperty("Color", "Secondary");
        progress5->setValue(66);
        auto progress6 = new QProgressBar;
        progress6->setProperty("Color", "Secondary");
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

        layout_->addWidget(groupbox, 2, 0, 1, 2);
    }

    {
        auto radio1 = new QRadioButton(tr("Radio Button"));
        auto radio2 = new QRadioButton(tr("Disabled"));
        radio2->setEnabled(false);

        auto radio3 = new QRadioButton(tr("Primary"));
        radio3->setProperty("Color", "Primary");
        auto radio4 = new QRadioButton(tr("Disabled"));
        radio4->setProperty("Color", "Primary");
        radio4->setEnabled(false);

        auto radio5 = new QRadioButton(tr("Secondary"));
        radio5->setProperty("Color", "Secondary");
        auto radio6 = new QRadioButton(tr("Disabled"));
        radio6->setProperty("Color", "Secondary");
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

        layout_->addWidget(groupbox, 3, 0);
    }

    {
        auto check1 = new QCheckBox(tr("Check Box"));
        auto check2 = new QCheckBox(tr("Disabled"));
        check2->setEnabled(false);
        auto check3 = new QCheckBox(tr("Primary"));
        check3->setProperty("Color", "Primary");
        auto check4 = new QCheckBox(tr("Primary"));
        check4->setProperty("Color", "Primary");
        check4->setEnabled(false);
        auto check5 = new QCheckBox(tr("Secondary"));
        check5->setProperty("Color", "Secondary");
        auto check6 = new QCheckBox(tr("Secondary"));
        check6->setProperty("Color", "Secondary");
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

        layout_->addWidget(groupbox, 4, 0);
    }

    {
        auto slider1 = new QSlider(Qt::Horizontal);
        slider1->setValue(66);
        auto slider2 = new QSlider(Qt::Horizontal);
        slider2->setValue(66);
        slider2->setEnabled(false);

        auto slider3 = new QSlider(Qt::Horizontal);
        slider3->setValue(66);
        slider3->setProperty("Color", "Primary");
        auto slider4 = new QSlider(Qt::Horizontal);
        slider4->setValue(66);
        slider4->setProperty("Color", "Primary");
        slider4->setEnabled(false);

        auto slider5 = new QSlider(Qt::Horizontal);
        slider5->setValue(66);
        slider5->setProperty("Color", "Secondary");
        auto slider6 = new QSlider(Qt::Horizontal);
        slider6->setValue(66);
        slider6->setProperty("Color", "Secondary");
        slider6->setEnabled(false);

        auto slider7 = new QSlider(Qt::Vertical);
        slider7->setValue(66);
        auto slider8 = new QSlider(Qt::Vertical);
        slider8->setValue(66);
        slider8->setEnabled(false);

        auto slider9 = new QSlider(Qt::Vertical);
        slider9->setValue(66);
        slider9->setProperty("Color", "Primary");
        auto slider10 = new QSlider(Qt::Vertical);
        slider10->setValue(66);
        slider10->setProperty("Color", "Primary");
        slider10->setEnabled(false);

        auto slider11 = new QSlider(Qt::Vertical);
        slider11->setValue(66);
        slider11->setProperty("Color", "Secondary");
        auto slider12 = new QSlider(Qt::Vertical);
        slider12->setValue(66);
        slider12->setProperty("Color", "Secondary");
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

        layout_->addWidget(groupbox, 3, 1, 2, 1);
    }

    {
        auto scroll1 = new QScrollBar;
        auto scroll2 = new QScrollBar;
        scroll2->setDisabled(true);

        auto scroll3 = new QScrollBar;
        scroll3->setProperty("Color", "Primary");
        auto scroll4 = new QScrollBar;
        scroll4->setProperty("Color", "Primary");
        scroll4->setDisabled(true);

        auto scroll5 = new QScrollBar;
        scroll5->setProperty("Color", "Secondary");
        auto scroll6 = new QScrollBar;
        scroll6->setProperty("Color", "Secondary");
        scroll6->setDisabled(true);

        auto scroll7 = new QScrollBar(Qt::Horizontal);
        auto scroll8 = new QScrollBar(Qt::Horizontal);
        scroll8->setDisabled(true);

        auto scroll9 = new QScrollBar(Qt::Horizontal);
        scroll9->setProperty("Color", "Primary");
        auto scroll10 = new QScrollBar(Qt::Horizontal);
        scroll10->setProperty("Color", "Primary");
        scroll10->setDisabled(true);

        auto scroll11 = new QScrollBar(Qt::Horizontal);
        scroll11->setProperty("Color", "Secondary");
        auto scroll12 = new QScrollBar(Qt::Horizontal);
        scroll12->setProperty("Color", "Secondary");
        scroll12->setDisabled(true);

        auto grid = new QGridLayout;
        grid->addWidget(scroll1, 0, 0);
        grid->addWidget(scroll2, 0, 1);
        grid->addWidget(scroll3, 0, 2);
        grid->addWidget(scroll4, 0, 3);
        grid->addWidget(scroll5, 0, 4);
        grid->addWidget(scroll6, 0, 5);

        
        grid->addWidget(scroll7, 1, 0, 1, 6);
        grid->addWidget(scroll8, 2, 0, 1, 6);
        grid->addWidget(scroll9, 3, 0, 1, 6);
        grid->addWidget(scroll10, 4, 0, 1, 6);
        grid->addWidget(scroll11, 5, 0, 1, 6);
        grid->addWidget(scroll12, 6, 0, 1, 6);

        auto groupbox = new QGroupBox(tr("QScrollBar"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 5, 0);
    }

    {
        auto edit1 = new QPlainTextEdit(tr("PlainText Edit"));
        auto edit2 = new QPlainTextEdit(tr("Read Only"));
        edit2->setReadOnly(true);
        auto edit3 = new QPlainTextEdit(tr("Disabled"));
        edit3->setEnabled(false);

        auto edit4 = new QPlainTextEdit(tr("Primary"));
        edit4->setProperty("Color", "Primary");
        auto edit5 = new QPlainTextEdit(tr("Primary"));
        edit5->setProperty("Color", "Primary");
        edit5->setReadOnly(true);
        auto edit6 = new QPlainTextEdit(tr("Primary"));
        edit6->setProperty("Color", "Primary");
        edit6->setEnabled(false);

        auto edit7 = new QPlainTextEdit(tr("Secondary"));
        edit7->setProperty("Color", "Secondary");
        auto edit8 = new QPlainTextEdit(tr("Secondary"));
        edit8->setProperty("Color", "Secondary");
        edit8->setReadOnly(true);
        auto edit9 = new QPlainTextEdit(tr("Secondary"));
        edit9->setProperty("Color", "Secondary");
        edit9->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(edit1, 0, 0);
        grid->addWidget(edit2, 0, 1);
        grid->addWidget(edit3, 0, 2);
        grid->addWidget(edit4, 1, 0);
        grid->addWidget(edit5, 1, 1);
        grid->addWidget(edit6, 1, 2);
        grid->addWidget(edit7, 2, 0);
        grid->addWidget(edit8, 2, 1);
        grid->addWidget(edit9, 2, 2);

        auto groupbox = new QGroupBox(tr("QPlainTextEdit"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 5, 1);
    }

    {
        auto button1 = new QPushButton(tr("about"));
        auto button2 = new QPushButton(tr("aboutQt")); 
        auto button3 = new QPushButton(tr("critical")); 
        auto button4 = new QPushButton(tr("information")); 
        auto button5 = new QPushButton(tr("question")); 
        auto button6 = new QPushButton(tr("warning")); 

        connect(button1, &QPushButton::clicked, [this](){QMessageBox::about(this, tr("Title"), tr("Content"));});
        connect(button2, &QPushButton::clicked, [this](){QMessageBox::aboutQt(this);});
        connect(button3, &QPushButton::clicked, [this](){QMessageBox::critical(this, tr("Title"), tr("Content"));});
        connect(button4, &QPushButton::clicked, [this](){QMessageBox::information(this, tr("Title"), tr("Content"));});
        connect(button5, &QPushButton::clicked, [this](){QMessageBox::question(this, tr("Title"), tr("Content"));});
        connect(button6, &QPushButton::clicked, [this](){QMessageBox::warning(this, tr("Title"), tr("Content"));});

        auto grid = new QGridLayout;
        grid->addWidget(button1, 0, 0);
        grid->addWidget(button2, 1, 0);
        grid->addWidget(button3, 2, 0);
        grid->addWidget(button4, 3, 0);
        grid->addWidget(button5, 4, 0);
        grid->addWidget(button6, 5, 0);

        auto groupbox = new QGroupBox(tr("QMessageBox"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 6, 0);
    }

    {
        auto widget1 = new QWidget;
        widget1->setProperty("Color", "Success");
        widget1->setProperty("Depth", 5);
        auto widget2 = new QWidget;
        widget2->setProperty("Color", "Warning");
        widget2->setProperty("Depth", 5);
        auto widget3 = new QWidget;
        widget3->setProperty("Color", "Danger");
        widget3->setProperty("Depth", 5);

        auto spliter = new QSplitter;
        spliter->setProperty("Color", "Primary");
        spliter->addWidget(widget1);
        spliter->addWidget(widget2);
        spliter->addWidget(widget3);
        spliter->handle(1)->setAttribute(Qt::WA_Hover, true);
        spliter->handle(2)->setAttribute(Qt::WA_Hover, true);

        auto row = new QHBoxLayout;
        row->addWidget(spliter);

        auto groupbox = new QGroupBox(tr("QSplitter"));
        groupbox->setLayout(row);

        layout_->addWidget(groupbox, 6, 1);
    }

        {
        auto spin1 = new QSpinBox;
        auto spin2 = new QSpinBox;
        spin2->setReadOnly(true);
        auto spin3 = new QSpinBox;
        spin3->setEnabled(false);

        auto spin4 = new QSpinBox;
        spin4->setProperty("Color", "Primary");
        auto spin5 = new QSpinBox;
        spin5->setProperty("Color", "Primary");
        spin5->setReadOnly(true);
        auto spin6 = new QSpinBox;
        spin6->setProperty("Color", "Primary");
        spin6->setEnabled(false);

        auto spin7 = new QSpinBox;
        spin7->setProperty("Color", "Secondary");
        auto spin8 = new QSpinBox;
        spin8->setProperty("Color", "Secondary");
        spin8->setReadOnly(true);
        auto spin9 = new QSpinBox;
        spin9->setProperty("Color", "Secondary");
        spin9->setEnabled(false);

        auto dspin1 = new QDoubleSpinBox;
        auto dspin2 = new QDoubleSpinBox;
        dspin2->setReadOnly(true);
        auto dspin3 = new QDoubleSpinBox;
        dspin3->setEnabled(false);

        auto dspin4 = new QDoubleSpinBox;
        dspin4->setProperty("Color", "Primary");
        auto dspin5 = new QDoubleSpinBox;
        dspin5->setProperty("Color", "Primary");
        dspin5->setReadOnly(true);
        auto dspin6 = new QDoubleSpinBox;
        dspin6->setProperty("Color", "Primary");
        dspin6->setEnabled(false);

        auto dspin7 = new QDoubleSpinBox;
        dspin7->setProperty("Color", "Secondary");
        auto dspin8 = new QDoubleSpinBox;
        dspin8->setProperty("Color", "Secondary");
        dspin8->setReadOnly(true);
        auto dspin9 = new QDoubleSpinBox;
        dspin9->setProperty("Color", "Secondary");
        dspin9->setEnabled(false);

        auto time1 = new QTimeEdit{QTime::currentTime()};
        auto time2 = new QTimeEdit{QTime::currentTime()};
        time2->setReadOnly(true);
        auto time3 = new QTimeEdit{QTime::currentTime()};
        time3->setEnabled(false);

        auto time4 = new QTimeEdit{QTime::currentTime()};
        time4->setProperty("Color", "Primary");
        auto time5 = new QTimeEdit{QTime::currentTime()};
        time5->setProperty("Color", "Primary");
        time5->setReadOnly(true);
        auto time6 = new QTimeEdit{QTime::currentTime()};
        time6->setProperty("Color", "Primary");
        time6->setEnabled(false);

        auto time7 = new QTimeEdit{QTime::currentTime()};
        time7->setProperty("Color", "Secondary");
        auto time8 = new QTimeEdit{QTime::currentTime()};
        time8->setProperty("Color", "Secondary");
        time8->setReadOnly(true);
        auto time9 = new QTimeEdit{QTime::currentTime()};
        time9->setProperty("Color", "Secondary");
        time9->setEnabled(false);

        auto date1 = new QDateEdit{QDate::currentDate()};
        auto date2 = new QDateEdit{QDate::currentDate()};
        date2->setReadOnly(true);
        auto date3 = new QDateEdit{QDate::currentDate()};
        date3->setEnabled(false);

        auto date4 = new QDateEdit{QDate::currentDate()};
        date4->setProperty("Color", "Primary");
        auto date5 = new QDateEdit{QDate::currentDate()};
        date5->setProperty("Color", "Primary");
        date5->setReadOnly(true);
        auto date6 = new QDateEdit{QDate::currentDate()};
        date6->setProperty("Color", "Primary");
        date6->setEnabled(false);

        auto date7 = new QDateEdit{QDate::currentDate()};
        date7->setProperty("Color", "Secondary");
        auto date8 = new QDateEdit{QDate::currentDate()};
        date8->setProperty("Color", "Secondary");
        date8->setReadOnly(true);
        auto date9 = new QDateEdit{QDate::currentDate()};
        date9->setProperty("Color", "Secondary");
        date9->setEnabled(false);

        auto datetime1 = new QDateTimeEdit{QDateTime::currentDateTime()};
        auto datetime2 = new QDateTimeEdit{QDateTime::currentDateTime()};
        datetime2->setReadOnly(true);
        auto datetime3 = new QDateTimeEdit{QDateTime::currentDateTime()};
        datetime3->setEnabled(false);

        auto datetime4 = new QDateTimeEdit{QDateTime::currentDateTime()};
        datetime4->setProperty("Color", "Primary");
        auto datetime5 = new QDateTimeEdit{QDateTime::currentDateTime()};
        datetime5->setProperty("Color", "Primary");
        datetime5->setReadOnly(true);
        auto datetime6 = new QDateTimeEdit{QDateTime::currentDateTime()};
        datetime6->setProperty("Color", "Primary");
        datetime6->setEnabled(false);

        auto datetime7 = new QDateTimeEdit{QDateTime::currentDateTime()};
        datetime7->setProperty("Color", "Secondary");
        auto datetime8 = new QDateTimeEdit{QDateTime::currentDateTime()};
        datetime8->setProperty("Color", "Secondary");
        datetime8->setReadOnly(true);
        auto datetime9 = new QDateTimeEdit{QDateTime::currentDateTime()};
        datetime9->setProperty("Color", "Secondary");
        datetime9->setEnabled(false);

        auto grid = new QGridLayout;
        grid->addWidget(spin1, 0, 0);
        grid->addWidget(spin2, 1, 0);
        grid->addWidget(spin3, 2, 0);
        grid->addWidget(spin4, 0, 1);
        grid->addWidget(spin5, 1, 1);
        grid->addWidget(spin6, 2, 1);
        grid->addWidget(spin7, 0, 2);
        grid->addWidget(spin8, 1, 2);
        grid->addWidget(spin9, 2, 2);
        
        grid->addWidget(dspin1, 0, 3);
        grid->addWidget(dspin2, 1, 3);
        grid->addWidget(dspin3, 2, 3);
        grid->addWidget(dspin4, 0, 4);
        grid->addWidget(dspin5, 1, 4);
        grid->addWidget(dspin6, 2, 4);
        grid->addWidget(dspin7, 0, 5);
        grid->addWidget(dspin8, 1, 5);
        grid->addWidget(dspin9, 2, 5);

        grid->addWidget(time1, 0, 6);
        grid->addWidget(time2, 1, 6);
        grid->addWidget(time3, 2, 6);
        grid->addWidget(time4, 0, 7);
        grid->addWidget(time5, 1, 7);
        grid->addWidget(time6, 2, 7);
        grid->addWidget(time7, 0, 8);
        grid->addWidget(time8, 1, 8);
        grid->addWidget(time9, 2, 8);

        grid->addWidget(date1, 3, 0);
        grid->addWidget(date2, 4, 0);
        grid->addWidget(date3, 5, 0);
        grid->addWidget(date4, 3, 1);
        grid->addWidget(date5, 4, 1);
        grid->addWidget(date6, 5, 1);
        grid->addWidget(date7, 3, 2);
        grid->addWidget(date8, 4, 2);
        grid->addWidget(date9, 5, 2);

        grid->addWidget(datetime1, 3, 3, 1, 2);
        grid->addWidget(datetime2, 4, 3, 1, 2);
        grid->addWidget(datetime3, 5, 3, 1, 2);
        grid->addWidget(datetime4, 3, 5, 1, 2);
        grid->addWidget(datetime5, 4, 5, 1, 2);
        grid->addWidget(datetime6, 5, 5, 1, 2);
        grid->addWidget(datetime7, 3, 7, 1, 2);
        grid->addWidget(datetime8, 4, 7, 1, 2);
        grid->addWidget(datetime9, 5, 7, 1, 2);

        auto groupbox = new QGroupBox(tr("QSpinbox && QDoubleSpinbox && QTimeEdit && QDateEdit && QDateTimeEdit"));
        groupbox->setLayout(grid);

        layout_->addWidget(groupbox, 7, 0, 1, 2);
    }

    
    this->setLayout(layout_);
}

}; // namespace QtTheme
