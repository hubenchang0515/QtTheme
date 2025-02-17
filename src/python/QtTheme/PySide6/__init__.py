from . import resource

from PySide6.QtCore import QDir, QFile

def getThemes():
    dir = QDir(":/QtTheme/theme")
    themes = [x.baseName() for x in dir.entryInfoList()]
    return themes

def getBaseColors(theme:str):
    dir = QDir(f":/QtTheme/theme/{theme}")
    colors = [x.baseName() for x in dir.entryInfoList()]
    return colors

def getPrimaryColors(theme:str, base:str):
    dir = QDir(f":/QtTheme/theme/{theme}/{base}")
    colors = [x.baseName() for x in dir.entryInfoList()]
    return colors

def getSecondaryColors(theme:str, base:str, primary:str):
    dir = QDir(f":/QtTheme/theme/{theme}/{base}/{primary}")
    colors = [x.baseName() for x in dir.entryInfoList()]
    return colors

def getThemeStyle(theme:str, base:str, primary:str, secondary:str):
    file = QFile(f":/QtTheme/theme/{theme}/{base}/{primary}/{secondary}.qss")
    file.open(QFile.OpenModeFlag.ReadOnly)
    return file.readAll().data().decode()