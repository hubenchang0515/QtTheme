#!/usr/bin/env python3

import sys
from PySide6.QtCore import Qt, QUrl, QFile
from PySide6.QtWidgets import (
    QApplication,
    QGridLayout,
    QDialog,
    QLabel,
    QLineEdit,
    QPushButton,
    QProgressBar,
)
from PySide6.QtNetwork import QNetworkAccessManager, QNetworkRequest, QNetworkReply
import QtTheme.PySide6 as QtTheme


class Window(QDialog):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.__url = QLineEdit()
        self.__url.setPlaceholderText("URL")

        self.__btn = QPushButton("Download")
        self.__btn.setProperty("Color", "Primary")

        self.__progress = QProgressBar()
        self.__progress.setProperty("Color", "Secondary")

        self.__manager = QNetworkAccessManager(self)

        layout = QGridLayout()
        layout.addWidget(self.__url, 0, 0)
        layout.addWidget(self.__btn, 0, 1)
        layout.addWidget(self.__progress, 1, 0, 1, 2)

        self.__label = QLabel("Progress")
        self.__label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        label_layout = QGridLayout()
        label_layout.addWidget(self.__label)
        label_layout.setContentsMargins(0, 0, 0, 0)
        self.__progress.setLayout(label_layout)

        self.setLayout(layout)
        self.setStyleSheet(QtTheme.getThemeStyle("Flat", "Dark", "Blue", "Pink"))

        self.__btn.clicked.connect(self.download)

    def setProgressColor(self, color: str):
        self.__progress.setProperty("Color", color)
        self.__progress.style().unpolish(self.__progress)
        self.__progress.style().polish(self.__progress)

    def sizeHint(self):
        size = super().sizeHint()
        size.setWidth(480)
        return size

    def download(self):
        url = QUrl(self.__url.text())
        request = QNetworkRequest(url)
        request.setTransferTimeout(30000)
        self.__file = None
        self.__reply = self.__manager.get(request)
        self.__reply.readyRead.connect(self.readyRead)
        self.__reply.downloadProgress.connect(self.downloadProgress)
        self.__reply.finished.connect(self.finish)
        self.__url.setEnabled(False)
        self.__progress.setRange(0, 0)
        self.setProgressColor("Secondary")
        self.__label.setText("Connect")

    def readyRead(self):
        if self.__file is None:
            disposition: str = self.__reply.header(
                QNetworkRequest.KnownHeaders.ContentDispositionHeader
            )

            if disposition is not None and disposition.startswith(
                "attachment; filename="
            ):
                filename = disposition[len("attachment; filename=") :]
            else:
                filename = "unknown.download"
            self.__file = QFile(filename)
            self.__file.open(QFile.OpenModeFlag.WriteOnly)

        data = self.__reply.readAll()
        self.__file.write(data)

    def finish(self):
        if self.__file is not None:
            self.__file.flush()
            self.__file.close()
            self.__file = None
        self.__url.setEnabled(True)
        self.__progress.setRange(0, 100)
        self.__progress.setValue(100)

        if self.__reply.error() == QNetworkReply.NetworkError.NoError:
            self.setProgressColor("Success")
            self.__label.setText("Finish")
        else:
            self.setProgressColor("Danger")
            self.__label.setText("Failed")

    def downloadProgress(self, done, total):
        if total == 0:
            return
        self.__progress.setRange(0, total)
        self.__progress.setValue(done)
        self.__label.setText(f"{done}/{total}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = Window()
    window.show()
    sys.exit(app.exec())
