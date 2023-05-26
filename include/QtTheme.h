#ifndef QTTHEME_QTTHEME_H
#define QTTHEME_QTTHEME_H

#include "ThemeManager.h"

namespace QtTheme
{

inline QStringList getThemeList() noexcept
{
    return ThemeManager::singleton().getThemeList();
}

inline QString getTheme(const QString& name) noexcept
{
    return ThemeManager::singleton().getTheme(name);
}

inline void addTheme(const QString& name, const QString& path) noexcept
{
    ThemeManager::singleton().addTheme(name, path);
}

inline void removeTheme(const QString& name) noexcept
{
    ThemeManager::singleton().removeTheme(name);
}

inline void exportThemes(const QString& path, const QStringList& themes) noexcept
{
    ThemeManager::singleton().exportThemes(path, themes);
}

}; // namespace QtTheme

#endif // QTTHEME_QTTHEME_H