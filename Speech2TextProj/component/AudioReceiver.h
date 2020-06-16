#ifndef AUDIORECEIVER_H
#define AUDIORECEIVER_H

#include <QObject>
#include <QWidget>
#include <QMediaRecorder>
#include <QAudioBuffer>
#include <QAudioRecorder>
#include <QAudioProbe>
#include <QDateTime>
#include <QHBoxLayout>

#include "MainForm.h"
#include "component/AudioWaveWidget.h"
#include "component/AudioLevel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AudioReceiver;
}
class QAudioBuffer;
class QAudioRecorder;
class QAudioProbe;
class MainForm;
QT_END_NAMESPACE

class AudioReceiver : public QWidget
{
    Q_OBJECT
public:
    AudioReceiver(QWidget *parent = nullptr);
    ~AudioReceiver();

    qreal getPeakValue(const QAudioFormat &format);
    QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

    template <class T>
    QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);

    QAudioRecorder *audioRecorder;
    QAudioProbe *probe;
    QAudioEncoderSettings settings;

    void initObjectEvent();

    void startReceiveAudio();
    void stopReceiveAudio();
    void pauseReceiveAudio();

public:
    AudioLevel *audioLevel;
    MainForm *parent;

private:
    Ui::AudioReceiver *ui;

     QList<AudioLevel *> audioLevels;
     QList<AudioWaveWidget *> audioWaveWidgets;

signals:

public slots:
    void processBuffer(const QAudioBuffer &buffer);

    void updateProgress(qint64 duration);
    void updateStatus(QMediaRecorder::Status status);
    void onStateChanged(QMediaRecorder::State state);
    void displayErrorMessage();
};

#endif // AUDIORECEIVER_H
