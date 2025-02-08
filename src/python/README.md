# Qt Theme

Qt theme in pure qss - 纯 qss 的 Qt 主题

[Preview and Export Resource Package Online - 在线预览和导出资源包](https://hubenchang0515.github.io/QtTheme/)

![dark](https://github.com/hubenchang0515/QtTheme/raw/master/doc/image/dark.png)

![light](https://github.com/hubenchang0515/QtTheme/raw/master/doc/image/light.png)

## Usage

### PySide6

```python
# import resource
import QtTheme.PySide6

# open qss file
qss = QFile(":/QtTheme/theme/Flat/Dark/Blue/Pink.qss")
qss.Open(QFile.OpenModeFlag.ReadOnly)

# set style sheet of the root widget
mainwindow.setStyleSheet(qss.readAll().data().decode())

# set color of widgets
button.setProperty("Color", "Primary")
```



### PyQt5

```python
# import resource
import QtTheme.PyQt5

# open qss file
qss = QFile(":/QtTheme/theme/Flat/Dark/Blue/Pink.qss")
qss.Open(QFile.OpenModeFlag.ReadOnly)

# set style sheet to the root widgets
mainwindow.setStyleSheet(qss.readAll().data().decode())

# set color of widgets
button.setProperty("Color", "Primary")
```

### API

Only one API:  

```python
QWidget.setProperty("Color", "XXX")
```

| Color        | Explain                                                                    |
| :----------- | :------------------------------------------------------------------------- |
| Primary      | The primary color selected when exporting                                  |
| Secondary    | The secondary color selected when exporting                                |
| Success      | The success color(![GREEN](https://placehold.co/16x16/4caf50/4caf50.png))  |
| Warning      | The warning color(![ORANGE](https://placehold.co/16x16/ff9800/ff9800.png)) |
| Danger       | The error color(![RED](https://placehold.co/16x16/f44336/f44336.png))      |


