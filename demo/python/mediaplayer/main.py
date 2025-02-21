#!/usr/bin/env python3

import sys
from PySide6.QtCore import Qt, QUrl, QSize, QDir, Signal
from PySide6.QtGui import QPainter, QPixmap
from PySide6.QtWidgets import (
    QApplication,
    QGridLayout,
    QVBoxLayout,
    QWidget,
    QLabel,
    QPushButton,
    QSlider,
    QGraphicsView,
    QGraphicsScene,
    QSpacerItem,
    QSizePolicy,
    QStyleOption,
    QStyle,
    QFileDialog,
    QProxyStyle,
)
from PySide6.QtMultimedia import QMediaPlayer, QAudioOutput
from PySide6.QtMultimediaWidgets import QGraphicsVideoItem
import QtTheme.PySide6 as QtTheme


class SliderStyle(QProxyStyle):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def styleHint(self, hint, /, option=..., widget=..., returnData=...):
        if hint == QStyle.StyleHint.SH_Slider_AbsoluteSetButtons:
            return Qt.MouseButton.LeftButton.value
        return super().styleHint(hint, option, widget, returnData)


class Control(QWidget):
    playClicked = Signal()
    pauseClicked = Signal()
    videoChanged = Signal(str)
    positionChanged = Signal(int)

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.__playing = False

        openIcon = QPixmap()
        playIcon = QPixmap()
        backwardIcon = QPixmap()
        forwardIcon = QPixmap()

        openIcon.loadFromData(
            b'<svg viewBox="0 0 16 16" fill="none" xmlns="http://www.w3.org/2000/svg"><g id="SVGRepo_bgCarrier" stroke-width="0"></g><g id="SVGRepo_tracerCarrier" stroke-linecap="round" stroke-linejoin="round"></g><g id="SVGRepo_iconCarrier"> <path d="M7 0H2V16H14V7H7V0Z" fill="#ffffff"></path> <path d="M9 0V5H14L9 0Z" fill="#ffffff"></path> </g></svg>'
        )
        playIcon.loadFromData(
            b'<svg viewBox="0 0 16 16" fill="none" xmlns="http://www.w3.org/2000/svg"><g id="SVGRepo_bgCarrier" stroke-width="0"></g><g id="SVGRepo_tracerCarrier" stroke-linecap="round" stroke-linejoin="round"></g><g id="SVGRepo_iconCarrier"> <path d="M1 14H3L9 8L3 2H1V14Z" fill="#ffffff"></path> <path d="M15 2H13V14H15V2Z" fill="#ffffff"></path> <path d="M9 2H11V14H9V2Z" fill="#ffffff"></path> </g></svg>'
        )
        backwardIcon.loadFromData(
            b'<svg viewBox="0 0 16 16" fill="none" xmlns="http://www.w3.org/2000/svg"><g id="SVGRepo_bgCarrier" stroke-width="0"></g><g id="SVGRepo_tracerCarrier" stroke-linecap="round" stroke-linejoin="round"></g><g id="SVGRepo_iconCarrier"> <path d="M8.70714 13.2929L3.41424 8.00001L8.70714 2.70712L7.29292 1.29291L0.585815 8.00001L7.29292 14.7071L8.70714 13.2929Z" fill="#ffffff"></path> <path d="M15.2071 13.2929L9.91424 8.00001L15.2071 2.70712L13.7929 1.29291L7.08582 8.00001L13.7929 14.7071L15.2071 13.2929Z" fill="#ffffff"></path> </g></svg>'
        )
        forwardIcon.loadFromData(
            b'<svg viewBox="0 0 16 16" fill="none" xmlns="http://www.w3.org/2000/svg"><g id="SVGRepo_bgCarrier" stroke-width="0"></g><g id="SVGRepo_tracerCarrier" stroke-linecap="round" stroke-linejoin="round"></g><g id="SVGRepo_iconCarrier"> <path d="M7.29286 13.2929L12.5858 8.00001L7.29286 2.70712L8.70708 1.29291L15.4142 8.00001L8.70707 14.7071L7.29286 13.2929Z" fill="#ffffff"></path> <path d="M0.792862 13.2929L6.08576 8.00001L0.792862 2.70712L2.20708 1.29291L8.91418 8.00001L2.20707 14.7071L0.792862 13.2929Z" fill="#ffffff"></path> </g></svg>'
        )

        self.__progress = QSlider(Qt.Orientation.Horizontal)
        self.__time = QLabel("00:00/00:00")
        self.__open = QPushButton(openIcon, "")
        self.__backward = QPushButton(backwardIcon, "")
        self.__play = QPushButton(playIcon, "")
        self.__forward = QPushButton(forwardIcon, "")

        self.__progress.setRange(0, 0)
        self.__progress.setStyle(SliderStyle(self.__progress.style()))

        self.__layout = QGridLayout()
        self.__layout.addWidget(self.__progress, 0, 0, 1, -1)
        self.__layout.addWidget(self.__open, 1, 0)
        self.__layout.addItem(
            QSpacerItem(
                0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Preferred
            ),
            1,
            1,
        )
        self.__layout.addWidget(self.__backward, 1, 2)
        self.__layout.addWidget(self.__play, 1, 3)
        self.__layout.addWidget(self.__forward, 1, 4)
        self.__layout.addItem(
            QSpacerItem(
                0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Preferred
            ),
            1,
            5,
        )
        self.__layout.addWidget(self.__time, 1, 6)

        self.setLayout(self.__layout)

        self.__open.clicked.connect(self.open)
        self.__play.clicked.connect(self.togglePlaying)
        self.__progress.valueChanged.connect(self.movePosition)
        self.__backward.clicked.connect(self.backward)
        self.__forward.clicked.connect(self.forward)

        self.__time.setProperty("Color", "Secondary")
        self.__progress.setProperty("Color", "Secondary")
        self.__play.setProperty("Color", "Primary")
        self.setStyleSheet("Control{background:rgba(255,255,255,0.2);}")

    def timeFormat(self, ms: int):
        minutes = int(ms / 1000 / 60)
        seconds = int(ms / 1000 - minutes * 60)
        return "%02d:%02d" % (minutes, seconds)

    def paintEvent(self, _):
        opt = QStyleOption()
        opt.initFrom(self)
        p = QPainter(self)
        self.style().drawPrimitive(QStyle.PE_Widget, opt, p, self)

    def open(self):
        file = QFileDialog.getOpenFileName(self)
        if file[0] != "":
            self.videoChanged.emit(file[0])
            self.playClicked.emit()

    def setPlaying(self, play: bool):
        self.__playing = play

    def togglePlaying(self):
        if self.__playing:
            self.pauseClicked.emit()
        else:
            self.playClicked.emit()

    def setPosition(self, ms: int):
        restore = self.__progress.blockSignals(True)
        self.__progress.setValue(ms)
        self.__progress.blockSignals(restore)
        self.__time.setText(
            f"{self.timeFormat(self.__progress.value())}/{self.timeFormat(self.__progress.maximum())}"
        )

    def setDuration(self, ms: int):
        restore = self.__progress.blockSignals(True)
        self.__progress.setRange(0, ms)
        self.__progress.blockSignals(restore)

    def movePosition(self, ms: int):
        self.positionChanged.emit(ms)

    def backward(self):
        if self.__progress.value() > 10000:
            self.movePosition(self.__progress.value() - 10000)
        else:
            self.movePosition(0)

    def forward(self):
        if self.__progress.maximum() > self.__progress.value() + 10000:
            self.movePosition(self.__progress.value() + 10000)
        else:
            self.movePosition(self.__progress.maximum())


class Window(QGraphicsView):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.__scene = QGraphicsScene()
        self.__video = QGraphicsVideoItem()
        self.__scene.addItem(self.__video)
        self.setScene(self.__scene)

        self.__control = Control()
        self.__layout = QVBoxLayout()
        self.__layout.addSpacerItem(
            QSpacerItem(
                0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding
            )
        )
        self.__layout.addWidget(self.__control)
        self.setLayout(self.__layout)

        self.__audioOutput = QAudioOutput(self)
        self.__player = QMediaPlayer(self)
        self.__player.setAudioOutput(self.__audioOutput)
        self.__player.setVideoOutput(self.__video)

        self.__player.playingChanged.connect(self.__control.setPlaying)
        self.__player.durationChanged.connect(self.__control.setDuration)
        self.__player.positionChanged.connect(self.__control.setPosition)

        self.__control.videoChanged.connect(self.__player.setSource)
        self.__control.playClicked.connect(self.__player.play)
        self.__control.pauseClicked.connect(self.__player.pause)
        self.__control.positionChanged.connect(self.__player.setPosition)

        self.__control.sizePolicy().setRetainSizeWhenHidden(True)
        self.setMouseTracking(True)

        self.setStyleSheet(QtTheme.getThemeStyle("Flat", "Dark", "Purple", "Yellow"))

    def sizeHint(self):
        return QSize(1280, 720)

    def resizeEvent(self, event):
        super().resizeEvent(event)
        self.__video.setSize(event.size())
        self.__scene.setSceneRect(0, 0, event.size().width(), event.size().height())
        self.__control.show()

    def mouseMoveEvent(self, event):
        if self.__player.isPlaying() and not self.__control.geometry().contains(
            event.position().toPoint()
        ):
            self.__control.hide()
        else:
            self.__control.show()

        return super().mouseMoveEvent(event)

    def play(self, src: str):
        url = QUrl(QDir.fromNativeSeparators(src))
        self.__player.setSource(url)
        self.__player.play()


if __name__ == "__main__":
    print(sys.argv)
    app = QApplication(sys.argv)
    window = Window()
    window.show()
    app.exec()
