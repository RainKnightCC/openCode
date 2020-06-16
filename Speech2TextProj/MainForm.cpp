#include "MainForm.h"
#include "ui_MainForm.h"

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    initView();
    initTimerDevice();
    initAudioDevice();
    initAudioObjectEvent();

//    saveWAVFile();
}

MainForm::~MainForm()
{
    delete audioReceiver;
    delete timer;
//    delete &audioSettings;
    delete ui;
}

void MainForm::initView() {
    this->setStyleSheet("background: #000000;");
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout = new QHBoxLayout();
    centerWidget = new AudioWaveWidget();
    QWidget *bottomWidget = new QWidget();
    VoiceButton *voiceBtn = new VoiceButton();

    centerWidget->setFixedWidth(CENTER_WIDGET_WIDTH - CENTER_WIDGET_OFFSET);
    centerWidget->setFixedHeight(CENTER_WIDGET_HEIGHT);
    centerWidget->setStyleSheet("background: #000000;");

    bottomWidget->setFixedWidth(BOTTOM_WIDGET_WIDTH - BOTTOM_WIDGET_OFFSET);
    bottomWidget->setFixedHeight(BOTTOM_WIDGET_HEIGHT);
    bottomWidget->setStyleSheet("background: #000000;");

    hLayout->setAlignment(bottomWidget, Qt::AlignCenter);
    hLayout->addWidget(voiceBtn);
    bottomWidget->setLayout(hLayout);

    DigiFlip *time = new DigiFlip(this->centralWidget());
    time->resize(320, 120);

    vLayout->addWidget(time);
    vLayout->addWidget(centerWidget);
    vLayout->addWidget(bottomWidget);

    this->centralWidget()->setLayout(vLayout);
}

void MainForm::initAudioDevice() {
//    QAudioFormat m_format;
//    m_format.setSampleRate(16000);
//        m_format.setChannelCount(1);
//        m_format.setSampleSize(16);
////        m_format.setSampleType(QAudioFormat::SignedInt);
////        m_format.setByteOrder(QAudioFormat::LittleEndian);
//        m_format.setCodec("audio/pcm");

//    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());

//    if (!info.isFormatSupported(m_format)) {
//        qWarning() << "Default format not supported - trying to use nearest";
////        m_format = info.nearestFormat(m_format);
//    }

    audioReceiver = new AudioReceiver(this);
//    this->layout()->addWidget(audioReceiver);

//    audioReceiver->audioRecorder->setAudioInput("default:");
////    audioSettings.setCodec("audio/x-wav");
//    audioSettings.setCodec("audio/pcm");
//    audioSettings.setSampleRate(16000);
//    audioSettings.setBitRate(16);
//    audioSettings.setChannelCount(1);
//    audioSettings.setQuality(QMultimedia::HighQuality);
//    audioSettings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
//    audioReceiver->audioRecorder->setEncodingSettings(audioSettings);
//    audioReceiver->audioRecorder->setContainerFormat("wav");
//    audioReceiver->audioRecorder->record();
}

void MainForm::initTimerDevice() {
    timer = new QTimer(0);
    listenthread = new QThread(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(doLoadWavFile()));
    // Make sure the timer gets started from m_thread.
    QObject::connect(listenthread, SIGNAL(started()), timer, SLOT(start()));
//    QObject::connect(voiceLib, SIGNAL(sendRecognizeText(char*)), listenthread,SLOT(setPushToSpeechText(char*)));

    timer->setInterval(INTERVAL_TIME);
    timer->moveToThread(listenthread);
    listenthread->start();
}

QHBoxLayout *MainForm::getlevelsLayout() {
    return this->hLayout;
}

AudioWaveWidget *MainForm::getAudioWidget() {
    return this->centerWidget;
}

bool MainForm::fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {

        // remove
//        QFile file(path);
//        file.remove();
        return true;
    } else {
        return false;
    }
}

void MainForm::saveWAVFile() {

//    QString fileNamePath = "/home/smg/swork/Speech2TextProj/res/123.wav";
//    if (!fileNamePath.isEmpty()) {
//        if (audioReceiver->audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileNamePath))) {
//            qDebug() << "Save output wav file";
//        }else{
//            this->saveWAVFile();
//        }
//    }

    ofstream f("example.wav", ios::binary );

    // Write the file headers
    f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    write_word( f,     16, 4 );  // no extension data
    write_word( f,      1, 2 );  // PCM - integer samples
    write_word( f,      1, 2 );  // two channels (stereo file)
    write_word( f,  16000, 4 );  // samples per second (Hz)
    write_word( f, 32000, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word( f,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word( f,     16, 2 );  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    size_t data_chunk_pos = f.tellp();
    f << "data----";  // (chunk size to be filled in later)

    // Write the audio samples
    // (We'll generate a single C4 note with a sine wave, fading from left to right)
    constexpr double two_pi = 6.283185307179586476925286766559;
    constexpr double max_amplitude = 32760;  // "volume"

    double hz        = 16000;    // samples per second
    double frequency = 261.626;  // middle C
    double seconds   = 4;      // time

    int N = hz * seconds;  // total number of samples
    for (int n = 0; n < N; n++) {
        double amplitude = (double)n / N * max_amplitude;
        double value     = sin( (two_pi * n * frequency) / hz );
        write_word( f, (int)((max_amplitude - amplitude) * value), 2 );
    }

    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = f.tellp();

    // Fix the data chunk header to contain the data size
    f.seekp( data_chunk_pos + 4 );
    write_word( f, file_length - data_chunk_pos + 8 );

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    f.seekp( 0 + 4 );
    write_word( f, file_length - 8, 4 );

    audioReceiver->stopReceiveAudio();
}

void MainForm::doLoadWavFile() {
    qWarning() << logCommands[enumToInt(LogType::FrontBlue)] << u8"Load wav file .." << logCommands[0];

    this->saveWAVFile();

    if(fileExists("/home/smg/swork/Speech2TextProj/res/123.wav")) {
        VoicesLib *voiceLib = new VoicesLib();
        voiceLib->Init();
        QFile file("/home/smg/swork/Speech2TextProj/res/123.wav");
        file.remove();

    }else{
        return;
    }
//    audioReceiver->startReceiveAudio();

//    audioReceiver->audioRecorder->stop();
}

void MainForm::initAudioObjectEvent() {
    QObject::connect(audioReceiver->audioRecorder, SIGNAL(durationChanged(qint64)),
                     audioReceiver, SLOT(updateProgress(qint64)));
    QObject::connect(audioReceiver->audioRecorder, SIGNAL(statusChanged(QMediaRecorder::Status)),
                     audioReceiver, SLOT(updateStatus(QMediaRecorder::Status)));
    QObject::connect(audioReceiver->audioRecorder, SIGNAL(stateChanged(QMediaRecorder::State)),
                     audioReceiver, SLOT(onStateChanged(QMediaRecorder::State)));
    QObject::connect(audioReceiver->audioRecorder, SIGNAL(error(QMediaRecorder::Error)),
                     audioReceiver, SLOT(displayErrorMessage()));
}
