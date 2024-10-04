#ifndef QT_THEME_UTILS_H
#define QT_THEME_UTILS_H

#include <QToolButton>
#include <QMenu>
#include <functional>

namespace QtTheme {

namespace Utils {

bool openUrl(const QString& url);
std::function<void(void)> toOpenUrl(QString url);

void copyText(const QString& text);
std::function<void(void)> toCopyText(QString text);

QToolButton* makeQToolButton(QMenu* menu, QWidget* parent=nullptr) noexcept;

}; // namespace Utils

}; // namespace QtTheme

#endif