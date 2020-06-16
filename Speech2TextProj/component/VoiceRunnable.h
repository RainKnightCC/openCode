#ifndef VOICERUNNABLE_H
#define VOICERUNNABLE_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include <string.h>
#include <unistd.h>

class VoiceRunnable : public QObject
{
    Q_OBJECT
public:
    explicit VoiceRunnable(QObject *parent = nullptr);

public slots:
    void speechText(const char *in);
    void SpeechToText();

signals:
    void signalSpeech();

public slots:
};

#endif // VOICERUNNABLE_H
