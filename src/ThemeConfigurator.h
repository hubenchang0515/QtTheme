#ifndef THEME_CONFIGURATOR_H
#define THEME_CONFIGURATOR_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

namespace QtTheme
{

class ThemeConfigurator : public QWidget
{
    Q_OBJECT
public:
    ThemeConfigurator(QWidget* parent=nullptr) noexcept;
    ~ThemeConfigurator() noexcept = default;

    bool setTheme(const QString& themeName) noexcept;
    bool setBaseColor(const QString color) noexcept;
    bool setPrimaryColor(const QString color) noexcept;
    bool setSecondaryColor(const QString color) noexcept;

    void emitCurrentTheme() const noexcept;
    void emitExportTheme() const noexcept;

signals:
    void currentThemeChanged(const QString& themeName, const QString& baseColor, const QString& primaryColor, const QString& secondaryColor) const;
    void exportThemeClicked(const QString& themeName, const QString& baseColor, const QString& primaryColor, const QString& secondaryColor) const;

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    QGridLayout* layout_;
    QLabel* themeLabel_;
    QComboBox* themeName_;
    QLabel* baseLabel_;
    QComboBox* baseColor_;
    QLabel* primaryLabel_;
    QComboBox* primaryColor_;
    QLabel* secondaryLabel_;
    QComboBox* secondaryColor_;
    QPushButton* exportButton_;

private slots:
    static void setOptions(QComboBox* box, QStringList options) noexcept;

    void themeNameChanged() noexcept;
    void baseColorChanged() noexcept;
    void primaryColorChanged() noexcept;
    void secondaryColorChanged() noexcept;
};

}; //namespace QtTheme


#endif // THEME_CONFIGURATOR_H