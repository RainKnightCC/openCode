#ifndef SPEECHTHREAD_H
#define SPEECHTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "globalUnility.h"

/* Ekho */
#include "ekho.h"

using namespace ekho;

class SpeechThread : public QThread
{
    Q_OBJECT
public:
    SpeechThread();
    bool isRun;

public slots:
    void setPushToSpeechText(char *output);

public:
    void run();

private:
    char  *input;
};

#endif // SPEECHTHREAD_H
