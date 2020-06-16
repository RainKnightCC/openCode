#-------------------------------------------------
#
# Project created by QtCreator 2020-06-04T09:12:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtRestfulClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Third-party library
INCLUDEPATH += /usr/local/speechsdk/include/c_api
INCLUDEPATH += /usr/local/speechsdk/include/cxx_api
INCLUDEPATH += /usr/share/opencc/

LIBS += -L/usr/local/speechsdk/lib/x64 -lMicrosoft.CognitiveServices.Speech.core -lMicrosoft.CognitiveServices.Speech.extension.kws -lMicrosoft.CognitiveServices.Speech.extension.codec
LIBS += -L$$PWD/lib/ -lopencc


SOURCES += \
        main.cpp \
        WinForm.cpp

HEADERS += \
        WinForm.h

FORMS += \
        WinForm.ui
