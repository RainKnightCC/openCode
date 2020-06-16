#ifndef VOICEBUTTON_H
#define VOICEBUTTON_H

#include <unistd.h>

#include <QPushButton>
#include <QBitmap>
#include <QObject>
#include <QDebug>

#include <QtMultimedia/qsound.h>

#include "globalUnility.h"

/* ALSA */
#include "alsa/asoundlib.h"

#include "config.h"

/* CMUSphinx*/
#include "sphinxbase/cmd_ln.h"
#include "sphinxbase/logmath.h"
#include "sphinxbase/fe.h"
#include "sphinxbase/feat.h"

/* PockSphinx */
#include "pocketsphinx/pocketsphinx.h"

/* runnabel thread */
#include "component/VoiceRunnable.h"
#include "component/SpeechThread.h"

using namespace std;

class WorkObject : public QObject {
    Q_OBJECT
public:

public slots:

signals:
    void pushReadySpeech(const char *in);

};


class VoicesLib : public QObject
{
    Q_OBJECT
public:
    explicit VoicesLib();
    ~VoicesLib();

    void Init();
//    void InitSpeechEnv();
    int EkhoInit();
    int loadWavFile(const char *path);
    bool isRecognizeSuccess();

//    VoiceRunnable runnable;
//    SpeechThread sThread;
//    WorkObject wObj;

signals:
    void sendRecognizeText(char *);

private:
    string result;
    ps_decoder_t *ps = NULL;
    cmd_ln_t *config = NULL;
    ngram_model_t *model;
    char const *hyp, *uttid;
    int16 buf[512];
    int rv;
    int32 score;
    FILE *file;

};


class VoiceButton : public QPushButton
{
        Q_OBJECT
public:
    VoiceButton(QWidget *parent = nullptr);
    bool toggleFlag = false;

    VoiceRunnable runnable;
    SpeechThread sThread;
    WorkObject wObj;

    VoicesLib *voiceLib;

    void InitSpeechEnv();

protected:
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mousePressEvent(QMouseEvent *);

private:
};







#endif // VOICEBUTTON_H
