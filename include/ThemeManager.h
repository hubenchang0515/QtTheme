#ifndef CUSTOM_WIDGETS_THEME_MANAGER_H
#define CUSTOM_WIDGETS_THEME_MANAGER_H

#include <QString>
#include <QStringList>
#include <QMap>

namespace QtTheme
{

class ThemeManager
{
public:
    ~ThemeManager() noexcept;

    static ThemeManager& singleton() noexcept;

    /***********************************
    * @brief 获取主题列表
    * @return 主题列表
    ************************************/
    QStringList getThemeList() const noexcept;

    /***********************************
    * @brief 获取主题列表
    * @param name 主题名称
    * @return 主题的QSS配置，不存在时为空字符串
    ************************************/
    QString getTheme(const QString& name) const noexcept;

    /***********************************
    * @brief 添加主题
    * @param name 主题名称
    * @param filepath qss文件路径
    * @note name存在时会覆盖
    ************************************/
    void addTheme(const QString& name, const QString& filepath) noexcept;

    /***********************************
    * @brief 添加主题
    * @param name 主题名称
    * @note name 不存在时不会出错
    ************************************/
    void removeTheme(const QString& name) noexcept;

    /***********************************
    * @brief 到处主题
    * @param path 导出路径
    * @param themes 主题名称列表
    * @note 到处不存在的主题会得到空文件
    ************************************/
    void exportThemes(const QString& path, const QStringList& themes) noexcept;

private:
    QMap<QString, QString> themes_; // MAP[name] => filepath

    ThemeManager() noexcept;
}; // class ThemeManager

}; // namespace QtTheme
#endif // CUSTOM_WIDGETS_THEME_MANAGER_H