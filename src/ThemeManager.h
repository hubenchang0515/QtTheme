#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

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
    * @brief 获取主题名称列表
    * @return 主题名称列表
    ************************************/
    QStringList getThemes() const noexcept;

    /***********************************
    * @brief 获取主题的基础色列表（通常为Dark、Light）
    * @param name 主题名称
    * @return 基础色列表
    ************************************/
    QStringList getBaseColors(const QString& name) const noexcept;

    /***********************************
    * @brief 获取主题的主配色列表
    * @param name 主题名称
    * @param base 基础色
    * @return 主配色列表
    ************************************/
    QStringList getPrimaryColors(const QString& name, const QString& base) const noexcept;

    /***********************************
    * @brief 获取主题的次配色列表
    * @param name 主题名称
    * @param base 基础色
    * @param primary 主配色
    * @return 次配色列表
    ************************************/
    QStringList getSecondaryColors(const QString& name, const QString& base, const QString& primary) const noexcept;

    /***********************************
    * @brief 获取主题配置
    * @param name 主题名称
    * @param base 基础色
    * @param primary 主配色
    * @param secondary 次配色
    * @return 主题的 QSS 配置，不存在时为空字符串
    ************************************/
    QString getTheme(const QString& name, const QString& base, const QString& primary, const QString& secondary) const noexcept;

private:
    ThemeManager() noexcept;
}; // class ThemeManager

}; // namespace QtTheme
#endif // THEME_MANAGER_H