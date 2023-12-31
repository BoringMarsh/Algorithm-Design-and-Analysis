# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'checkedboard.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.

import sys
import PyQt5
from functools import partial
from PyQt5 import QtCore, QtGui, QtWidgets

buttonStyle = "QPushButton{\n" \
              "background-color: white;\n" \
              "border-radius: 10px;\n" \
              "border: 2px black;\n" \
              "border-style: outset;\n" \
              "}\n" \
              "QPushButton:hover{\n" \
              "background-color: green;\n" \
              "}\n" \
              "QPushButton:pressed{\n" \
              "background-color: white;\n" \
              "border-radius: 10px;\n" \
              "border: 2px black;\n" \
              "border-style: outset;\n" \
              "}"

buttonClickedStyle = "QPushButton{\n" \
                     "background-color: black;\n" \
                     "border-radius: 10px;\n" \
                     "border: 2px black;\n" \
                     "border-style: outset;\n" \
                     "}"


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(787, 576)
        self.pushButton_1 = QtWidgets.QPushButton(Form)
        self.pushButton_1.setGeometry(QtCore.QRect(280, 30, 31, 31))
        self.pushButton_1.setStyleSheet(buttonStyle)
        self.pushButton_1.setText("1")
        self.pushButton_1.setObjectName("pushButton_1")
        self.pushButton_2 = QtWidgets.QPushButton(Form)
        self.pushButton_2.setGeometry(QtCore.QRect(240, 70, 31, 31))
        self.pushButton_2.setStyleSheet(buttonStyle)
        self.pushButton_2.setText("2")
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_3 = QtWidgets.QPushButton(Form)
        self.pushButton_3.setGeometry(QtCore.QRect(320, 70, 31, 31))
        self.pushButton_3.setStyleSheet(buttonStyle)
        self.pushButton_3.setText("3")
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_4 = QtWidgets.QPushButton(Form)
        self.pushButton_4.setGeometry(QtCore.QRect(360, 110, 31, 31))
        self.pushButton_4.setStyleSheet(buttonStyle)
        self.pushButton_4.setText("6")
        self.pushButton_4.setObjectName("pushButton_4")
        self.pushButton_5 = QtWidgets.QPushButton(Form)
        self.pushButton_5.setGeometry(QtCore.QRect(240, 150, 31, 31))
        self.pushButton_5.setStyleSheet(buttonStyle)
        self.pushButton_5.setText("8")
        self.pushButton_5.setObjectName("pushButton_5")
        self.pushButton_6 = QtWidgets.QPushButton(Form)
        self.pushButton_6.setGeometry(QtCore.QRect(200, 190, 31, 31))
        self.pushButton_6.setStyleSheet(buttonStyle)
        self.pushButton_6.setText("12")
        self.pushButton_6.setObjectName("pushButton_6")
        self.pushButton_7 = QtWidgets.QPushButton(Form)
        self.pushButton_7.setGeometry(QtCore.QRect(360, 190, 31, 31))
        self.pushButton_7.setStyleSheet(buttonStyle)
        self.pushButton_7.setText("14")
        self.pushButton_7.setObjectName("pushButton_7")
        self.pushButton_8 = QtWidgets.QPushButton(Form)
        self.pushButton_8.setGeometry(QtCore.QRect(430, 190, 31, 31))
        self.pushButton_8.setStyleSheet(buttonStyle)
        self.pushButton_8.setText("15")
        self.pushButton_8.setObjectName("pushButton_8")
        self.pushButton_9 = QtWidgets.QPushButton(Form)
        self.pushButton_9.setGeometry(QtCore.QRect(280, 190, 31, 31))
        self.pushButton_9.setStyleSheet(buttonStyle)
        self.pushButton_9.setText("13")
        self.pushButton_9.setObjectName("pushButton_9")
        self.pushButton_10 = QtWidgets.QPushButton(Form)
        self.pushButton_10.setGeometry(QtCore.QRect(320, 150, 31, 31))
        self.pushButton_10.setStyleSheet(buttonStyle)
        self.pushButton_10.setText("9")
        self.pushButton_10.setObjectName("pushButton_10")
        self.pushButton_11 = QtWidgets.QPushButton(Form)
        self.pushButton_11.setGeometry(QtCore.QRect(160, 150, 31, 31))
        self.pushButton_11.setStyleSheet(buttonStyle)
        self.pushButton_11.setText("7")
        self.pushButton_11.setObjectName("pushButton_11")
        self.pushButton_12 = QtWidgets.QPushButton(Form)
        self.pushButton_12.setGeometry(QtCore.QRect(200, 110, 31, 31))
        self.pushButton_12.setStyleSheet(buttonStyle)
        self.pushButton_12.setText("4")
        self.pushButton_12.setObjectName("pushButton_12")
        self.pushButton_13 = QtWidgets.QPushButton(Form)
        self.pushButton_13.setGeometry(QtCore.QRect(280, 110, 31, 31))
        self.pushButton_13.setStyleSheet(buttonStyle)
        self.pushButton_13.setText("5")
        self.pushButton_13.setObjectName("pushButton_13")
        self.pushButton_14 = QtWidgets.QPushButton(Form)
        self.pushButton_14.setGeometry(QtCore.QRect(120, 190, 31, 31))
        self.pushButton_14.setStyleSheet(buttonStyle)
        self.pushButton_14.setText("11")
        self.pushButton_14.setObjectName("pushButton_14")
        self.pushButton_15 = QtWidgets.QPushButton(Form)
        self.pushButton_15.setGeometry(QtCore.QRect(400, 150, 31, 31))
        self.pushButton_15.setStyleSheet(buttonStyle)
        self.pushButton_15.setText("10")
        self.pushButton_15.setObjectName("pushButton_15")

        self.pushButton_1.clicked.connect(partial(push_button, 1))
        self.pushButton_2.clicked.connect(partial(push_button, 2))
        self.pushButton_3.clicked.connect(partial(push_button, 3))
        self.pushButton_4.clicked.connect(partial(push_button, 4))
        self.pushButton_5.clicked.connect(partial(push_button, 5))
        self.pushButton_6.clicked.connect(partial(push_button, 6))
        self.pushButton_7.clicked.connect(partial(push_button, 7))
        self.pushButton_8.clicked.connect(partial(push_button, 8))
        self.pushButton_9.clicked.connect(partial(push_button, 9))
        self.pushButton_10.clicked.connect(partial(push_button, 10))
        self.pushButton_11.clicked.connect(partial(push_button, 11))
        self.pushButton_12.clicked.connect(partial(push_button, 12))
        self.pushButton_13.clicked.connect(partial(push_button, 13))
        self.pushButton_14.clicked.connect(partial(push_button, 14))
        self.pushButton_15.clicked.connect(partial(push_button, 15))

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))


def push_button(button_num):
    if button_pressed[button_num - 1]:
        mainWindow.findChild(QtWidgets.QPushButton, f"pushButton_{button_num}").setStyleSheet(buttonStyle)
        button_pressed[button_num - 1] = False
    else:
        mainWindow.findChild(QtWidgets.QPushButton, f"pushButton_{button_num}").setStyleSheet(buttonClickedStyle)
        button_pressed[button_num - 1] = True


if __name__ == '__main__':
    app = PyQt5.QtWidgets.QApplication(sys.argv)
    initializer = Ui_Form()
    mainWindow = QtWidgets.QWidget()
    initializer.setupUi(mainWindow)
    initializer.retranslateUi(mainWindow)

    button_pressed = []
    for i in range(15):
        button_pressed.append(False)

    mainWindow.show()
    sys.exit(app.exec_())