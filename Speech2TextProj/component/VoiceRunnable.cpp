#include "VoiceRunnable.h"

VoiceRunnable::VoiceRunnable(QObject *parent) : QObject(parent)
{

}

void VoiceRunnable::speechText(const char *in) {

    qDebug() << "I'm working in thread:" << QThread::currentThreadId();
//    sleep(3);

//    Ekho ekho("Mandarin");
//    ekho.setVoice("pinyin");
//    ekho.setSpeed(EKHO_VOICE_SPEEP);
//    ekho.setEnglishVoice("voice_cmu_us_slt_arctic");
//    ekho.blockSpeak(TEST_SPEECH_TEXT);
//    ekho.stop();
}

void VoiceRunnable::SpeechToText() {

}
