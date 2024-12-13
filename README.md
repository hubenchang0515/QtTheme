# Qt Theme

Qt theme in pure qss - 纯 qss 的 Qt 主题

[Preview and Export Resource Package Online - 在线预览和导出资源包](https://hubenchang0515.github.io/moe-tools/#/qt-theme)

## Preview - 预览

![dark](./doc/image/dark.png)

![light](./doc/image/light.png)

## Usage - 使用说明

1. Export the resource package from [here](https://hubenchang0515.github.io/moe-tools/#/qt-theme), and add it to your project.

2. Use `QMainWindow::setStyleSheet` to set the global style.
    ```c++
    QFile file(":/QtTheme/QtTheme_Flat_Dark_LightBlue_Indigo.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    ```
3. Use `QWdiget::setProperty` to set the color.
    ```c++
    auto button = new QPushButton(tr("Button"));
    button->setProperty("Color", "Primary");
    ```

| Color        | Explain                                                                    |
| :----------- | :------------------------------------------------------------------------- |
| Primary      | The primary color selected when exporting                                  |
| Secondary    | The secondary color selected when exporting                                |
| Success      | The success color(![GREEN](https://placehold.co/16x16/4caf50/4caf50.png))  |
| Warning      | The warning color(![ORANGE](https://placehold.co/16x16/ff9800/ff9800.png)) |
| Danger        | The error color(![RED](https://placehold.co/16x16/f44336/f44336.png))      |

--- 

1. 在[这里](https://hubenchang0515.github.io/moe-tools/#/qt-theme)导出资源包，然后将其加入你的项目。

2. 使用 `QMainWindow::setStyleSheet` 设置全局样式。
    ```c++
    QFile file(":/QtTheme/QtTheme_Flat_Dark_LightBlue_Indigo.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    ```

3. 使用 `QWdiget::setProperty` 设置颜色。
    ```c++
    auto button = new QPushButton(tr("Button"));
    button->setProperty("Color", "Primary");
    ```

| 颜色          | 说明                                                         |
| :----------- | :---------------------------------------------------------- |
| Primary      | 导出时选择的主要颜色                                             |
| Secondary    | 导出时选择的次要颜色                                             |
| Success      | 成功色(![绿色](https://placehold.co/16x16/4caf50/4caf50.png)) |
| Warning      | 警告色(![橙色](https://placehold.co/16x16/ff9800/ff9800.png)) |
| Danger       | 危险色(![红色](https://placehold.co/16x16/f44336/f44336.png)) |


## Notice - 注意事项

Customized `QWidget` subclasses must override `paintEvent`, otherwise the style will not take effect on this class:  

自定义的 `QWidget` 子类，必须重载 `paintEvent`，否则样式不会再该类上生效:  

> https://doc.qt.io/qt-6/stylesheet-reference.html#qwidget-widget

```cpp
void CustomWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
```


Style will not update itself automatically when the value of a property referenced from the style sheet changes, you must update it manually:  

当样式表引用的属性值发生变化时，样式不会自动更新，必须手动更新:  

> https://wiki.qt.io/Dynamic_Properties_and_Stylesheets

```cpp
// property changes
widget->setProperty("Color", "Secondary");

// update style manually
widget->style()->unpolish(widget);
widget->style()->polish(widget);
```

QComboBox must set the view for the internal style to take effect:  

QComboBox 必须设置 view, 内部的样式才能生效:  

> https://doc.qt.io/qt-6/stylesheet-reference.html#qcombobox-widget

```cpp
comboBox->setView(new QListView);
```