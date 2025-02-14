#! /usr/bin/bash
set -e
TOOL_DIR=$(dirname $(readlink -f $0))

# qtbase5-dev-tools
QT_SELECT=qt5 rcc -g python -o "${TOOL_DIR}/../src/python/QtTheme/PySide2/resource.py" "${TOOL_DIR}/../src/resource/QtTheme.qrc" --compress-algo zlib

# qt6-base-dev-tools
pyside6-rcc -o "${TOOL_DIR}/../src/python/QtTheme/PySide6/resource.py" "${TOOL_DIR}/../src/resource/QtTheme.qrc" --compress-algo zlib

# pyqt5-dev-tools
pyrcc5 -o "${TOOL_DIR}/../src/python/QtTheme/PyQt5/resource.py" "${TOOL_DIR}/../src/resource/QtTheme.qrc"

sed 's/PySide6/PyQt6/g' "${TOOL_DIR}/../src/python/QtTheme/PySide6/resource.py" > "${TOOL_DIR}/../src/python/QtTheme/PyQt6/resource.py"