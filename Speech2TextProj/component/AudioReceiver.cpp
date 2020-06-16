#include "AudioReceiver.h"

//class MainForm;

AudioReceiver::AudioReceiver(QWidget *parent) : QWidget(parent)
{
//    this->form = (MainForm *)parent;
    this->parent = (MainForm *)parent;
//    audioLevel = new AudioLevel();
//    audioRecorder = new QAudioRecorder(this);
    audioRecorder = new QAudioRecorder();

    QStringList audioInputList = audioRecorder->audioInputs();
    QStringList audioCodecsList = audioRecorder->supportedAudioCodecs();

    audioRecorder->setAudioInput("default:");
//    settings.setCodec("audio/pcm");
//    settings.setCodec("alsa:default");
    settings.setSampleRate(16000);
    settings.setBitRate(16);
    settings.setChannelCount(2);
    settings.setQuality(QMultimedia::VeryHighQuality);
    settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
    audioRecorder->setContainerFormat("wav");
    audioRecorder->setEncodingSettings(settings,QVideoEncoderSettings(), "audio/x-wav");
    audioRecorder->setOutputLocation(QUrl::fromLocalFile("/home/smg/swork/Speech2TextProj/res/123.wav"));
    audioRecorder->record();


    probe = new QAudioProbe();
    QObject::connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    probe->setSource(audioRecorder);

    foreach(const QString &device, audioRecorder->audioInputs()) {
        qDebug() << device;
    }

    // scan audio codecs
    foreach (const QString &codecName, audioRecorder->supportedAudioCodecs()) {
        qDebug() << codecName;
    }

    // containers
    foreach (const QString &containerName, audioRecorder->supportedContainers()) {
        qDebug() << containerName;
    }


    // sample rate
    foreach(const int sampleRate, audioRecorder->supportedAudioSampleRates()) {
        qDebug() << QString(sampleRate);
    }

}

AudioReceiver::~AudioReceiver() {
    if(!settings.isNull())
        delete &settings;
    delete audioRecorder;
    delete probe;
}

void AudioReceiver::initObjectEvent() {
//    QObject::connect(audioRecorder, SIGNAL(durationChanged(qint64)),
//                     this, SLOT(updateProgress(qint64)));
//    QObject::connect(audioRecorder, SIGNAL(statusChanged(QMediaRecorder::Status)),
//                     this, SLOT(updateStatus(QMediaRecorder::Status)));
//    QObject::connect(audioRecorder, SIGNAL(stateChanged(QMediaRecorder::State)),
//                     this, SLOT(onStateChanged(QMediaRecorder::State)));
//    QObject::connect(audioRecorder, SIGNAL(error(QMediaRecorder::Error)),
//                     this, SLOT(displayErrorMessage()));
}

void AudioReceiver::startReceiveAudio() {
    audioRecorder->record();
}


void AudioReceiver::stopReceiveAudio() {
    audioRecorder->stop();
}

void AudioReceiver::pauseReceiveAudio() {
    audioRecorder->pause();
}


void AudioReceiver::updateProgress(qint64 duration) {
    if(audioRecorder->error() != QMediaRecorder::NoError || duration < 1000) {
        return;
    }
}

void AudioReceiver::updateStatus(QMediaRecorder::Status status) {
    qDebug() << status;
    QString statusInfo;
    switch(status) {

    case QMediaRecorder::RecordingStatus:
        qDebug() << tr("Receiver mic");
        break;
    case QMediaRecorder::PausedStatus:
        qDebug() << tr("Paused");
        break;
    case QMediaRecorder:: UnloadedStatus:
        break;
    case QMediaRecorder::LoadedStatus:
        qDebug() << tr("Stopped");
        break;
    default:
        break;

    }
}

void AudioReceiver::onStateChanged(QMediaRecorder::State state) {
    qDebug() << state;
}

void AudioReceiver::displayErrorMessage() {
    qDebug() << audioRecorder->errorString();
}


qreal AudioReceiver::getPeakValue(const QAudioFormat &format) {
    if(!format.isValid())
        return qreal(0);

    if(format.codec() != "audio/pcm")
        return qreal(0);

    switch(format.sampleType()) {
    case QAudioFormat::Unknown:
        break;
    case QAudioFormat::Float:
        if(format.sampleSize() != 32)
            return qreal(0);
        return qreal(1.00003);
    case QAudioFormat::SignedInt:
        if(format.sampleSize() == 32)
            return qreal(INT_MAX);
        if(format.sampleSize() == 16)
            return qreal(SHRT_MAX);
        if(format.sampleSize() == 8)
            return qreal(CHAR_MAX);
        break;
    case QAudioFormat::UnSignedInt:
        if(format.sampleSize() == 32)
            return qreal(UINT_MAX);
        if(format.sampleSize() == 16)
            return qreal(USHRT_MAX);
        if(format.sampleSize() == 8)
            return qreal(UCHAR_MAX);
        break;
    }
    return qreal(0);

}


QVector<qreal> AudioReceiver::getBufferLevels(const QAudioBuffer &buffer) {
    QVector<qreal> values;

    if(!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian) {
        return values;
    }
    if(buffer.format().codec() != "audio/pcm") {
        return values;
    }

    int channelCount = buffer.format().channelCount();
    values.fill(0, channelCount);
    qreal peak_value = getPeakValue(buffer.format());
    if(qFuzzyCompare(peak_value, qreal(0)))
        return values;

    switch(buffer.format().sampleType()) {
    case QAudioFormat::Unknown:
    case QAudioFormat::UnSignedInt:
        if(buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
        if(buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
        if(buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);

        for(int i=0;i<values.size(); ++i) {
            values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
        }

        break;
    case QAudioFormat::Float:
        if(buffer.format().sampleSize() == 32) {
            values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
            for(int i = 0; i < values.size(); ++i)
                values[i] /= peak_value;
        }
        break;
    case QAudioFormat::SignedInt:
        if(buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
        if(buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
        if(buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
        for(int i=0;i < values.size(); ++i)
            values[i] /= peak_value;
        break;
    }
    return values;

}


void AudioReceiver::processBuffer(const QAudioBuffer &buffer) {
//    qDebug() << "processing:" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    if (audioLevels.count() != buffer.format().channelCount()) {
        qDeleteAll(audioLevels);
        audioLevels.clear();
        for (int i = 0; i < buffer.format().channelCount(); ++i) {
            audioLevel = new AudioLevel(this);
            audioLevels.append(audioLevel);
            QHBoxLayout *layout = this->parent->getlevelsLayout();
            layout->addWidget(audioLevel);
        }
    }

//    if (audioWaveWidgets.count() != buffer.format().channelCount()) {
//        qDeleteAll(audioWaveWidgets);
//        audioWaveWidgets.clear();
//        for (int i = 0; i < buffer.format().channelCount(); ++i) {
//            audioWaveWidget *waveWidget = new audioWaveWidgets(this->parent->getAudioWaveWidget(), i);
//            waveForm->setStyleSheet("QWidget{background:#00BB11;}");
//            audioWaveForms.append(waveForm);
//            QLayout *waveLayout = this->parent->getAudioWaveLayout();
//            waveLayout->addWidget(waveForm);
//        }
//    }


    qreal volume = audioRecorder->volume();
    QVector<qreal> levels = getBufferLevels(buffer);
    audioLevel->setLevel(volume * levels.at(0));
    this->parent->getAudioWidget()->updateLevel(volume *levels.at(0));
}


template <class T>
QVector<qreal> AudioReceiver::getBufferLevels(const T *buffer, int frames, int channels)
{
    QVector<qreal> max_values;
    max_values.fill(0, channels);

    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i * channels + j]));
            if (value > max_values.at(j))
                max_values.replace(j, value);
        }
    }

    return max_values;
}
