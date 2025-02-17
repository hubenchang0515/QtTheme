#ifndef QTTHEME_QTTHEME_H
#define QTTHEME_QTTHEME_H

#include "ThemeManager.h"

namespace QtTheme
{

inline QStringList getThemes() noexcept
{
    return ThemeManager::singleton().getThemes();
}

inline QStringList getBaseColors(const QString& name) noexcept
{
    return ThemeManager::singleton().getBaseColors(name);
}

inline QStringList getPrimaryColors(const QString& name, const QString& base) noexcept
{
    return ThemeManager::singleton().getPrimaryColors(name, base);
}

inline QStringList getSecondaryColors(const QString& name, const QString& base, const QString& primary) noexcept
{
    return ThemeManager::singleton().getSecondaryColors(name, base, primary);
}

inline QString getTheme(const QString& name, const QString& base, const QString& primary, const QString& secondary) noexcept
{
    return ThemeManager::singleton().getTheme(name, base, primary, secondary);
}

}; // namespace QtTheme

#endif // QTTHEME_QTTHEME_H