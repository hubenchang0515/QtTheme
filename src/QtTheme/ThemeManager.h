#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include <QString>
#include <QStringList>

namespace QtTheme
{

class ThemeManager
{
public:
    ~ThemeManager() noexcept;

    static ThemeManager& singleton() noexcept;

    /***********************************
    * @brief Get valid themes
    * @return string list of valid themes
    ************************************/
    QStringList getThemes() const noexcept;

    /***********************************
    * @brief Get valid base colors
    * @param name theme name
    * @return string list of valid base colors
    ************************************/
    QStringList getBaseColors(const QString& name) const noexcept;

    /***********************************
    * @brief Get valid primary colors
    * @param name theme name
    * @param base base color
    * @return string list of valid primary colors
    ************************************/
    QStringList getPrimaryColors(const QString& name, const QString& base) const noexcept;

    /***********************************
    * @brief Get valid secondary colors
    * @param name theme name
    * @param base base color
    * @param primary primary clolor
    * @return string list of valid secondary colors
    ************************************/
    QStringList getSecondaryColors(const QString& name, const QString& base, const QString& primary) const noexcept;

    /***********************************
    * @brief Get theme qss string
    * @param name theme name
    * @param base base color
    * @param primary primary clolor
    * @param secondary secondary color
    * @return qss string
    ************************************/
    QString getThemeStyle(const QString& name, const QString& base, const QString& primary, const QString& secondary) const noexcept;

private:
    ThemeManager() noexcept;
}; // class ThemeManager

}; // namespace QtTheme
#endif // THEME_MANAGER_H