#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <QFileInfo>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QAudioDeviceInfo>

#include <math.h>
#include <iosfwd>
#include <fstream>

#include "globalUnility.h"

#include "component/DigiFlip.h"
#include "component/VoiceButton.h"
#include "component/AudioReceiver.h"
#include "component/AudioWaveWidget.h"

namespace Ui {
class MainForm;
}

namespace little_endian_io
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}

using namespace little_endian_io;
using namespace std;

class AudioReceiver;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

    void initView();
    void initAudioDevice();
    void initAudioObjectEvent();

    void initTimerDevice();

    void saveWAVFile();
    bool fileExists(QString path);

    QHBoxLayout *getlevelsLayout();
    AudioWaveWidget *getAudioWidget();

public slots:
    void doLoadWavFile();

private:
    AudioReceiver *audioReceiver;
//    QAudioEncoderSettings audioSettings;

    QTimer *timer;
    QThread *listenthread;

    QHBoxLayout *hLayout;
    AudioWaveWidget *centerWidget;

private:
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
