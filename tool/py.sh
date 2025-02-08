#! /usr/bin/bash
set -e
TOOL_DIR=$(dirname $(readlink -f $0))

pyrcc5 -o "${TOOL_DIR}/../src/python/QtTheme/PyQt5/theme.py" "${TOOL_DIR}/../src/resource/theme.qrc"
pyrcc5 -o "${TOOL_DIR}/../src/python/QtTheme/PyQt5/icon.py" "${TOOL_DIR}/../src/resource/icon.qrc"

/usr/lib/qt6/libexec/rcc -g python -o "${TOOL_DIR}/../src/python/QtTheme/PySide6/theme.py" "${TOOL_DIR}/../src/resource/theme.qrc"
/usr/lib/qt6/libexec/rcc -g python -o "${TOOL_DIR}/../src/python/QtTheme/PySide6/icon.py" "${TOOL_DIR}/../src/resource/icon.qrc"