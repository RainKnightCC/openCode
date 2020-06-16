#ifndef GLOBALUNILITY_H
#define GLOBALUNILITY_H

#define WINDOWS_TITLE "Speech Engine"
#define WINDOWS_WIDTH 640
#define WINDOWS_HEIGHT 640

#define BOTTOM_WIDGET_HEIGHT 200
#define BOTTOM_WIDGET_WIDTH 640
#define BOTTOM_WIDGET_OFFSET 15

#define CENTER_WIDGET_HEIGHT 150
#define CENTER_WIDGET_WIDTH 640
#define CENTER_WIDGET_OFFSET 15

#define TOGGLE_BUTTON_HEIGHT 190
#define TOGGLE_BUTTON_WIDTH 150

#define DIFFERENCE_THREAD_PADDING_TIME 4

#define MODEL_ENGLISG_DIR "/home/smg/Downloads/PocketSphinx/sample/1" // english
#define MODEL_CHINESE_DIR "/home/smg/Downloads/PocketSphinx/sample/2" // chinese

//#define KEY_WORD_1 "HEY"
//#define KEY_WORD_2 "SEMI"
#define KEY_WORD_1 "HELLO"
#define KEY_WORD_2 "EVERYBODY"

#define EKHO_VOICE_SPEEP 90

#define INTERVAL_TIME 4000

#define TEST_QUESTION_SPEECH_TEXT "您好大家好，今天天氣不錯, 讓我為您服務 請問有什麼可以幫您"
#define TEST_WARRING_UNDERSTAND_TEXT "我不明白您的意思"
#define TEST_VOICE "wadechen_voice.wav"

enum class LogType {
    Reset = 0,

    Bold,
    Unbold,

    FrontBlack,
    FrontRed,
    FrontGreen,
    FrontYellow,
    FrontBlue,
    FrontPurple,
    FrontCyan,
    FrontWhite,
    BackBlack,
    BackRed,
    BackGreen,
    BackYellow,
    BackBlue,
    BackPurple,
    BackCyan,
    BackWhite,

    TypeCount
};

static const char * logCommands[] = {
    "\033[0m",
    "\033[1m",
    "\033[2m",
    "\033[30m",
    "\033[31m",
    "\033[32m",
    "\033[33m",
    "\033[34m",
    "\033[35m",
    "\033[36m",
    "\033[37m",
    "\033[40m",
    "\033[41m",
    "\033[42m",
    "\033[43m",
    "\033[44m",
    "\033[45m",
    "\033[46m",
    "\033[47m",
};

template <typename EnumType, typename IntType = int>
int enumToInt(EnumType enumValue)
{
    static_assert (std::is_enum<EnumType>::value, "EnumType must be enum");

    return static_cast<IntType>(enumValue);
}

#endif // GLOBALUNILITY_H
