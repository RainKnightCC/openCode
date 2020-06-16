#include "VoiceButton.h"

VoiceButton::VoiceButton(QWidget *parent)
{
    QPixmap pixmap("://res/init.png");
    resize(pixmap.size());
    setMask(QBitmap(pixmap.mask()));
    setMinimumHeight(TOGGLE_BUTTON_HEIGHT);
    setMinimumWidth(TOGGLE_BUTTON_WIDTH);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setStyleSheet("QPushButton{border-image: url(://res/init.png);height: 190px;width: 150px;}");

    voiceLib = new VoicesLib();
    InitSpeechEnv();
    voiceLib->Init();

}


void VoiceButton::enterEvent(QEvent *) {
    setStyleSheet("QPushButton{border-image: url(://res/click.png);}");
}


void VoiceButton::leaveEvent(QEvent *) {
    setStyleSheet("QPushButton{border-image: url(://res/init.png);}");
}

void VoiceButton::mousePressEvent(QMouseEvent *) {
    if(toggleFlag == false) {
        toggleFlag = true;
        QSound::play("://res/alert.wav");
        usleep(500);
        QSound::play("://res/girl_output.wav");
        sThread.start();
        qWarning() << logCommands[enumToInt(LogType::FrontBlue)] << u8"Engine Start .." << logCommands[0];
    }else{
        toggleFlag = false;
        QSound::play("://res/alert.wav");
        usleep(500);
        QSound::play("://res/girl_sleep.wav");
        sThread.start();
        qWarning() << logCommands[enumToInt(LogType::FrontBlue)] << u8"Engine Finish .." << logCommands[0];
    }

}

VoicesLib::VoicesLib() {

}


VoicesLib::~VoicesLib() {
    cmd_ln_free_r(config);
}

void VoicesLib::Init() {
    if(EkhoInit()) {
        loadWavFile("/home/smg/swork/Speech2TextProj/res/123.wav");
        if(isRecognizeSuccess()) {
            QSound::play("://res/alert.wav");
            usleep(500);
            QSound::play("://res/girl_output.wav");
//            sleep(5);
//            sThread.start();
//            wObj.pushReadySpeech("Test");
        }
    }
}

//void VoicesLib::InitSpeechEnv() {
void VoiceButton::InitSpeechEnv() {

    wObj.moveToThread(&sThread);
    QObject::connect(&wObj, SIGNAL(pushReadySpeech(const char*)), &runnable, SLOT(speechText(const char*)));
    QObject::connect(voiceLib, SIGNAL(sendRecognizeText(char*)), &sThread,SLOT(setPushToSpeechText(char*)));
}


int VoicesLib::EkhoInit() {
    /** initialization config **/
    config = cmd_ln_init(NULL, ps_args(), TRUE, "-hmm", MODEL_ENGLISG_DIR"/en-us/en-us", "-lm", MODEL_ENGLISG_DIR"/custom-en-us/en-us.lm.bin", "-dict", MODEL_ENGLISG_DIR"/custom-en-us/en-us.dict", NULL);
    if (config == NULL) {
        fprintf(stderr, "Failed to create config object, see log for details\n");
        return -1;
    }

    ps = ps_init(config);
    if (ps == NULL) {
        fprintf(stderr, "Failed to create recognizer, see log for details\n");
        return -1;
    }
}

int VoicesLib::loadWavFile(const char *path) {
    result = "";
    file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Unable to open input file goforward.raw\n");
        return -1;
    }

    rv = ps_start_utt(ps);
    while (!feof(file)) {
        size_t nsamp;
        nsamp = fread(buf, 2, 512, file);
        rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
    }

    rv = ps_end_utt(ps);
    hyp = ps_get_hyp(ps, &score);
    printf("score: %d\n", &score);
    if(hyp != NULL) {
        string str(hyp);
        result = str;
        printf("Recognized: %s\n", result);
        qWarning() << logCommands[enumToInt(LogType::FrontBlue)] << u8"Recognized result .." << QString::fromStdString(result) << logCommands[0];
    }
    fclose(file);
    ps_free(ps);
}


bool VoicesLib::isRecognizeSuccess() {
    char *loc_call = nullptr;
    char *loc_name = nullptr;
    char source[80] = {'\0'};
    strcpy(source , result.data());
    if(result != "") {
        loc_call = strstr(source, KEY_WORD_1);
        loc_name = strstr(source ,KEY_WORD_2);

        if((loc_call == NULL) && (loc_name == NULL)) {
            printf("can't find contain sub string \r\n");
            return false;
        } else {
            printf("find in location : %d \r\n", loc_call - source);
            printf("find in location : %d \r\n", loc_name - source);
            emit sendRecognizeText(loc_call);
            return true;
        }
    }else{
        return false;
    }
}
