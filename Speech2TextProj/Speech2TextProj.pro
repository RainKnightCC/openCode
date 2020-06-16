#-------------------------------------------------
#
# Project created by QtCreator 2020-05-11T09:21:42
#
#-------------------------------------------------

QT       += core gui multimedia
#CONFIG += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Speech2TextProj
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

INCLUDEPATH += /usr/include/espeak/
INCLUDEPATH += /home/smg/swork/Speech2TextProj/sonic
INCLUDEPATH += /home/smg/swork/Speech2TextProj/utfcpp/source

INCLUDEPATH += /usr/local/include/pocketsphinx/
INCLUDEPATH += /usr/local/include/sphinxbase/

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

PRE_TARGETDEPS += $$PWD/./libekho.a
PRE_TARGETDEPS += $$PWD/./libmusicxml2.a

LIBS += -L$$PWD/./ -lekho
LIBS += -L$$PWD/./ -lmusicxml2

LIBS += -lpthread -lsndfile -lpulse-simple -lpulse -lespeak -lpocketsphinx -lsphinxbase -lsphinxad

SOURCES += \
        main.cpp \
        MainForm.cpp \
        sonic/sonic.c \
        sonic/wave.c \
        component/Digits.cpp \
        component/DigiFlip.cpp \
        component/VoiceButton.cpp \
        component/VoiceRunnable.cpp \
        component/SpeechThread.cpp \
        component/AudioWaveWidget.cpp \
        component/AudioReceiver.cpp \
        component/AudioLevel.cpp

HEADERS += \
        MainForm.h \
        config.h \
        utfcpp/source/utf8/checked.h \
        utfcpp/source/utf8/core.h \
        utfcpp/source/utf8/unchecked.h \
        utfcpp/source/utf8.h \
        sonic/sonic.h \
        sonic/wave.h \
        globalUnility.h \
        component/Digits.h \
        component/DigiFlip.h \
        component/VoiceButton.h \
        component/VoiceRunnable.h \
        component/SpeechThread.h \
        component/AudioWaveWidget.h \
        component/AudioReceiver.h \
        component/AudioLevel.h

FORMS += \
        MainForm.ui

RESOURCES += \
    res.qrc
