#! /usr/bin/bash
set -e
TOOL_DIR=$(dirname $(readlink -f $0))

# qtbase5-dev-tools
/usr/lib/qt5/bin/rcc -g python -o "${TOOL_DIR}/../src/python/QtTheme/PySide2/theme.py" "${TOOL_DIR}/../src/resource/theme.qrc"
/usr/lib/qt5/bin/rcc -g python -o "${TOOL_DIR}/../src/python/QtTheme/PySide2/icon.py" "${TOOL_DIR}/../src/resource/icon.qrc"

# qt6-base-dev-tools
/usr/lib/qt6/libexec/rcc -g python -o "${TOOL_DIR}/../src/python/QtTheme/PySide6/theme.py" "${TOOL_DIR}/../src/resource/theme.qrc"
/usr/lib/qt6/libexec/rcc -g python -o "${TOOL_DIR}/../src/python/QtTheme/PySide6/icon.py" "${TOOL_DIR}/../src/resource/icon.qrc"

# pyqt5-dev-tools
pyrcc5 -o "${TOOL_DIR}/../src/python/QtTheme/PyQt5/theme.py" "${TOOL_DIR}/../src/resource/theme.qrc"
pyrcc5 -o "${TOOL_DIR}/../src/python/QtTheme/PyQt5/icon.py" "${TOOL_DIR}/../src/resource/icon.qrc"

sed 's/PySide6/PyQt6/g' "${TOOL_DIR}/../src/python/QtTheme/PySide6/theme.py" > "${TOOL_DIR}/../src/python/QtTheme/PyQt6/theme.py"
sed 's/PySide6/PyQt6/g' "${TOOL_DIR}/../src/python/QtTheme/PySide6/icon.py" > "${TOOL_DIR}/../src/python/QtTheme/PyQt6/icon.py"