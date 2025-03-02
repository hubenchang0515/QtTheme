# Qt Theme

Qt theme in pure qss - 纯 qss 的 Qt 主题

[Preview and Export Resource Package Online - 在线预览和导出资源包](https://hubenchang0515.github.io/QtTheme/)

![dark](https://github.com/hubenchang0515/QtTheme/raw/master/doc/image/dark.png)

![light](https://github.com/hubenchang0515/QtTheme/raw/master/doc/image/light.png)

## Usage

Install by `pip install QtTheme` then:  

```python
# import resource
import QtTheme.PySide6 as QtTheme
# import QtTheme.PySide2 as QtTheme
# import QtTheme.PyQt6 as QtTheme
# import QtTheme.PyQt5 as QtTheme

# set style sheet of the root widget
mainwindow.setStyleSheet(QtTheme.getThemeStyle('Flat', 'Dark', 'Blue', 'Pink'))

# set color of widgets
button.setProperty("Color", "Primary")
```

---

Alternatively, without installing QtTheme, you can export a single-style qrc resource package through the [online website](https://hubenchang0515.github.io/QtTheme/). Use [RCC](https://doc.qt.io/qt-6/rcc.html) to add it to your project.

```bash
pyside6-rcc -o resource.py QtTheme.qrc
```

```python
# import resource
import resource

# open qss file
qss = QFile(":/QtTheme/theme/Flat/Dark/Blue/Pink.qss")
qss.open(QFile.OpenModeFlag.ReadOnly)

# set style sheet of the root widget
mainwindow.setStyleSheet(qss.readAll().data().decode())

# set color of widgets
button.setProperty("Color", "Primary")
```

### API

Use `QWidget.setProperty` to set color of widget:  

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

To get themes: 
```python
def getThemes(): ...

def getBaseColors(theme:str): ...

def getPrimaryColors(theme:str, base:str): ...

def getSecondaryColors(theme:str, base:str, primary:str): ...

def getThemeStyle(theme:str, base:str, primary:str, secondary:str): ...
```

## Tips

* [Packaging Python Projects](https://packaging.python.org/en/latest/tutorials/packaging-projects/)