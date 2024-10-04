#include "utils.h"

#include <QApplication>
#include <QDesktopServices>
#include <QClipboard>
#include <QString>
#include <QUrl>

namespace QtTheme
{

namespace Utils
{

bool openUrl(const QString& url)
{
    return QDesktopServices::openUrl(QUrl(url));
}

std::function<void(void)> toOpenUrl(QString url)
{
    return [url](){
        openUrl(url);
    };
}

void copyText(const QString& text)
{
    qApp->clipboard()->setText(text);
}

std::function<void(void)> toCopyText(QString text)
{
    return [text](){
        copyText(text);
    };
}

QToolButton* makeQToolButton(QMenu* menu, QWidget* parent) noexcept
{
    auto tool = new QToolButton{parent};
    tool->setMenu(menu);
    tool->setPopupMode(QToolButton::InstantPopup);
    tool->setToolButtonStyle(Qt::ToolButtonIconOnly);
    tool->setIcon(menu->icon());
    return tool;
}

}; // namespace Utils

}; // namespace QtTheme