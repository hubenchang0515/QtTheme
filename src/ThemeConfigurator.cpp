#include "ThemeConfigurator.h"

#include <QSpacerItem>
#include <QListView>
#include <QPainter>

#include "QtTheme.h"

namespace QtTheme
{

ThemeConfigurator::ThemeConfigurator(QWidget* parent) noexcept:
    QWidget{parent},
    layout_{new QGridLayout},
    themeLabel_{new QLabel{tr("Theme")}},
    themeName_{new QComboBox},
    baseLabel_{new QLabel{tr("Base Color")}},
    baseColor_{new QComboBox},
    primaryLabel_{new QLabel{tr("Primary Color")}},
    primaryColor_{new QComboBox},
    secondaryLabel_{new QLabel{tr("Secondary Color")}},
    secondaryColor_{new QComboBox},
    exportButton_{new QPushButton{tr("EXPORT")}}
{
    primaryLabel_->setProperty("Color", "Primary");
    primaryColor_->setProperty("Color", "Primary");

    secondaryLabel_->setProperty("Color", "Secondary");
    secondaryColor_->setProperty("Color", "Secondary");

    exportButton_->setProperty("Color", "Success");

    layout_->addWidget(themeLabel_, 0, 0);
    layout_->addWidget(themeName_, 0, 1);
    layout_->addWidget(baseLabel_, 1, 0);
    layout_->addWidget(baseColor_, 1, 1);
    layout_->addWidget(primaryLabel_, 2, 0);
    layout_->addWidget(primaryColor_, 2, 1);
    layout_->addWidget(secondaryLabel_, 3, 0);
    layout_->addWidget(secondaryColor_, 3, 1);
    layout_->addWidget(exportButton_, 4, 0, 1, 2);
    layout_->addItem(new QSpacerItem{0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding}, 5, 0);
    setLayout(layout_);

    themeName_->setView(new QListView);
    baseColor_->setView(new QListView);
    primaryColor_->setView(new QListView);
    secondaryColor_->setView(new QListView);

    setOptions(themeName_, QtTheme::getThemes());
    setOptions(baseColor_, QtTheme::getBaseColors(themeName_->currentText()));
    setOptions(primaryColor_, QtTheme::getPrimaryColors(themeName_->currentText(), baseColor_->currentText()));
    setOptions(secondaryColor_, QtTheme::getSecondaryColors(themeName_->currentText(), baseColor_->currentText(), primaryColor_->currentText()));

    connect(themeName_, &QComboBox::currentTextChanged, this, &ThemeConfigurator::themeNameChanged);
    connect(baseColor_, &QComboBox::currentTextChanged, this, &ThemeConfigurator::baseColorChanged);
    connect(primaryColor_, &QComboBox::currentTextChanged, this, &ThemeConfigurator::primaryColorChanged);
    connect(secondaryColor_, &QComboBox::currentTextChanged, this, &ThemeConfigurator::secondaryColorChanged);
    connect(exportButton_, &QPushButton::clicked, this, &ThemeConfigurator::emitExportTheme);
}

bool ThemeConfigurator::setTheme(const QString& themeName) noexcept
{
    int index = themeName_->findText(themeName);
    if (index < 0)
        return false;

    themeName_->setCurrentIndex(index);
    emitCurrentTheme();
    return true;
}

bool ThemeConfigurator::setBaseColor(const QString color) noexcept
{
    int index = baseColor_->findText(color);
    if (index < 0)
        return false;

    baseColor_->setCurrentIndex(index);
    emitCurrentTheme();
    return true;
}

bool ThemeConfigurator::setPrimaryColor(const QString color) noexcept
{
    int index = primaryColor_->findText(color);
    if (index < 0)
        return false;

    primaryColor_->setCurrentIndex(index);
    emitCurrentTheme();
    return true;
}

bool ThemeConfigurator::setSecondaryColor(const QString color) noexcept
{
    int index = secondaryColor_->findText(color);
    if (index < 0)
        return false;

    secondaryColor_->setCurrentIndex(index);
    emitCurrentTheme();
    return true;
}


void ThemeConfigurator::emitExportTheme() const noexcept
{
    emit exportThemeClicked(themeName_->currentText(), baseColor_->currentText(), primaryColor_->currentText(), secondaryColor_->currentText());
}

void ThemeConfigurator::emitCurrentTheme() const noexcept
{
    emit currentThemeChanged(themeName_->currentText(), baseColor_->currentText(), primaryColor_->currentText(), secondaryColor_->currentText());
}

void ThemeConfigurator::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ThemeConfigurator::setOptions(QComboBox* box, QStringList options) noexcept
{
    QString prev = box->currentText();
    box->blockSignals(true);
    box->clear();
    options.sort();
    box->addItems(options);
    box->blockSignals(false);
    int index = box->findText(prev);
    if (index >= 0)
    {
        box->setCurrentIndex(index);
    }
}

void ThemeConfigurator::themeNameChanged() noexcept
{
    setOptions(baseColor_, QtTheme::getBaseColors(themeName_->currentText()));
    emitCurrentTheme();
}

void ThemeConfigurator::baseColorChanged() noexcept
{
    setOptions(primaryColor_, QtTheme::getPrimaryColors(themeName_->currentText(), baseColor_->currentText()));
    emitCurrentTheme();
}

void ThemeConfigurator::primaryColorChanged() noexcept
{
    setOptions(secondaryColor_, QtTheme::getSecondaryColors(themeName_->currentText(), baseColor_->currentText(), primaryColor_->currentText()));
    emitCurrentTheme();
}

void ThemeConfigurator::secondaryColorChanged() noexcept
{
    emitCurrentTheme();
}

}; // namespace QtTheme
