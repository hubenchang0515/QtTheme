#ifndef QTTHEME_QTTHEME_H
#define QTTHEME_QTTHEME_H

#include "ThemeManager.h"

namespace QtTheme
{

/***********************************
* @brief get valid themes
* @return string list of valid themes
************************************/
inline QStringList getThemes() noexcept
{
    return ThemeManager::singleton().getThemes();
}

/***********************************
* @brief get valid base colors
* @param name theme name
* @return string list of valid base colors
************************************/
inline QStringList getBaseColors(const QString& name) noexcept
{
    return ThemeManager::singleton().getBaseColors(name);
}

/***********************************
* @brief get valid primary colors
* @param name theme name
* @param base base color
* @return string list of valid primary colors
************************************/
inline QStringList getPrimaryColors(const QString& name, const QString& base) noexcept
{
    return ThemeManager::singleton().getPrimaryColors(name, base);
}

/***********************************
* @brief get valid secondary colors
* @param name theme name
* @param base base color
* @param primary primary clolor
* @return string list of valid secondary colors
************************************/
inline QStringList getSecondaryColors(const QString& name, const QString& base, const QString& primary) noexcept
{
    return ThemeManager::singleton().getSecondaryColors(name, base, primary);
}

/***********************************
* @brief get theme qss string
* @param name theme name
* @param base base color
* @param primary primary clolor
* @param secondary secondary color
* @return qss string
************************************/
inline QString getThemeStyle(const QString& name, const QString& base, const QString& primary, const QString& secondary) noexcept
{
    return ThemeManager::singleton().getThemeStyle(name, base, primary, secondary);
}

}; // namespace QtTheme

#endif // QTTHEME_QTTHEME_H