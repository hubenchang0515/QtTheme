#include "ThemeManager.h"

#include <QFile>
#include <QFileInfo>
#include <QDirIterator>
#include <QSet>
#include <QRegularExpression>

static inline void initResource()
{
    Q_INIT_RESOURCE(QtTheme);
}

namespace QtTheme
{

ThemeManager::ThemeManager() noexcept
{
    initResource();
}

ThemeManager::~ThemeManager() noexcept
{

}

ThemeManager& ThemeManager::singleton() noexcept
{
    static ThemeManager instance;
    return instance;
}

QStringList ThemeManager::getThemes() const noexcept
{
    QStringList themes;
    QDirIterator iter(":/QtTheme/theme");
    while(iter.hasNext())
    {
        QFileInfo info(iter.next());
        themes.append(info.baseName());
    }

    return themes;
}

QStringList ThemeManager::getBaseColors(const QString& name) const noexcept
{
    QStringList colors;
    QDirIterator iter(QString(":/QtTheme/theme/%1").arg(name));
    while(iter.hasNext())
    {
        QFileInfo info(iter.next());
        colors.append(info.baseName());
    }

    return colors;
}

QStringList ThemeManager::getPrimaryColors(const QString& name, const QString& base) const noexcept
{
    QStringList colors;
    QDirIterator iter(QString(":/QtTheme/theme/%1/%2").arg(name).arg(base));
    while(iter.hasNext())
    {
        QFileInfo info(iter.next());
        colors.append(info.baseName());
    }

    return colors;
}

QStringList ThemeManager::getSecondaryColors(const QString& name, const QString& base, const QString& primary) const noexcept
{
    QStringList colors;
    QDirIterator iter(QString(":/QtTheme/theme/%1/%2/%3").arg(name).arg(base).arg(primary));
    while(iter.hasNext())
    {
        QFileInfo info(iter.next());
        colors.append(info.baseName());
    }

    return colors;
}

QString ThemeManager::getTheme(const QString& name, const QString& base, const QString& primary, const QString& secondary) const noexcept
{
    QFile file(QString(":/QtTheme/theme/%1/%2/%3/%4.qss").arg(name).arg(base).arg(primary).arg(secondary));
    file.open(QFile::ReadOnly);
    return file.readAll();
}

};  // namespace QtTheme
