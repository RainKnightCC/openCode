#include "SpeechThread.h"

SpeechThread::SpeechThread()
{
    this->isRun = false;
}


void SpeechThread::run() {

    sleep(DIFFERENCE_THREAD_PADDING_TIME);

    Ekho ekho("Mandarin");
    ekho.setVoice("pinyin");
    ekho.setSpeed(EKHO_VOICE_SPEEP);
    ekho.setEnglishVoice("voice_cmu_us_slt_arctic");
    ekho.blockSpeak(TEST_QUESTION_SPEECH_TEXT);
}

void SpeechThread::setPushToSpeechText(char *output) {
    input = output;
    qWarning() << logCommands[enumToInt(LogType::FrontGreen)]  << QString::fromStdString(output) << logCommands[0];
}
