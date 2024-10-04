#ifndef THEME_PREVIEW_H
#define THEME_PREVIEW_H

#include <QWidget>
#include <QLayout>

namespace QtTheme
{

class ThemePreview : public QWidget
{
public:
    ThemePreview(QWidget* parent=nullptr) noexcept;
    ~ThemePreview() noexcept = default;

private:
    QGridLayout*    layout_;
};

}; // namespace QtTheme

#endif // THEME_PREVIEW_H