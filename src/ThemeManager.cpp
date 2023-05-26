#include "ThemeManager.h"

#include <QFile>
#include <QFileInfo>
#include <QDirIterator>
#include <QSet>
#include <QRegularExpression>

static inline void initResource()
{
    Q_INIT_RESOURCE(theme);
    Q_INIT_RESOURCE(icon);
}

namespace QtTheme
{

ThemeManager::ThemeManager() noexcept
{
    initResource();
    QDirIterator iter(":/theme");
    while(iter.hasNext())
    {
        QFileInfo info(iter.next());
        addTheme(info.baseName(), info.filePath());
    }
}

ThemeManager::~ThemeManager() noexcept
{

}

ThemeManager& ThemeManager::singleton() noexcept
{
    static ThemeManager instance;
    return instance;
}

QStringList ThemeManager::getThemeList() const noexcept
{
    return themes_.keys();
}

QString ThemeManager::getTheme(const QString& name) const noexcept
{
    if (!themes_.contains(name))
        return "";
 
    QFile file(themes_[name]);
    file.open(QFile::ReadOnly);
    return file.readAll();
}

void ThemeManager::addTheme(const QString& name, const QString& filepath) noexcept
{
    themes_[name] = filepath;
}

void ThemeManager::removeTheme(const QString& name) noexcept
{
    themes_.remove(name);
}

void ThemeManager::exportThemes(const QString& path, const QStringList& themes) noexcept
{
    QDir dir{path};
    QDir exportDir{dir.absoluteFilePath("QtTheme-Export")};
    QDir themeDir{exportDir.absoluteFilePath("theme")};
    QDir iconDir{exportDir.absoluteFilePath("icon")};

    if (exportDir.exists()) exportDir.removeRecursively();
    exportDir.mkpath(".");
    themeDir.mkpath(".");
    iconDir.mkpath(".");

    QRegularExpression regexp("url\\(\"(:/icon/(.*))\"\\)");
    QSet<QString> icons;
    for (auto theme : themes)
    {
        QFile file(themeDir.absoluteFilePath(QString("%1.qss").arg(theme)));
        file.open(QFile::WriteOnly|QFile::Truncate);
        QString qss = getTheme(theme);
        file.write(qss.toUtf8());

        QRegularExpressionMatchIterator iter = regexp.globalMatch(qss);
        while (iter.hasNext())
        {
            QRegularExpressionMatch match = iter.next();
            QFile input{match.captured(1)};
            QFile output{iconDir.absoluteFilePath(match.captured(2))};

            input.open(QFile::ReadOnly);
            output.open(QFile::WriteOnly|QFile::Truncate);
            output.write(input.readAll());

            icons.insert(match.captured(2));
        }
    }

    QFile qrcFile{exportDir.absoluteFilePath("resource.qrc")};
    qrcFile.open(QFile::WriteOnly|QFile::Truncate);
    qrcFile.write("<RCC>\n");
    qrcFile.write("  <qresource prefix=\"/\">\n");
    for (auto theme : themes)
    {
        qrcFile.write(QString("    <file>theme/%1.qss</file>\n").arg(theme).toUtf8());
    }
    for (auto& icon : icons)
    {
        qrcFile.write(QString("    <file>icon/%1</file>\n").arg(icon).toUtf8());
    }
    qrcFile.write("  </qresource>\n");
    qrcFile.write("</RCC>\n");
}

};  // namespace QtTheme
