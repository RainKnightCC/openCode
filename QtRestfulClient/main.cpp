#include "WinForm.h"
#include <QApplication>
#include <QDebug>
#include <QTextCodec>

#include <iostream>
#include <speechapi_cxx.h>

#include <locale.h>
#include <iconv.h>
#include <opencc/opencc.h>

#define APP_ID "87015e56-e0bf-4414-87a3-10133b92d90f"  //"4a1d6439-791f-4229-afd2-3d331a944287" //"813befe2-85d5-4739-bb4b-cda8b15b6d65"
#define LOCATION "eastus" //"westus"
#define _KEY1 "d725cba9795148739328aef7577d3a90"
#define _KEY2 "c9cdc7dce719459a949f375aa24aa082"
#define PRIMARY_KEY "f858e158bcaa4ef1813d8883e81bbfae"
#define SECONDARY_KEY "d3327806011b45dabd332432cadf0dc9"
#define ENDPOINT_URL "https://luisqservice.cognitiveservices.azure.com/"
#define REQUEST_URL "https://luisqservice.cognitiveservices.azure.com/luis/prediction/v3.0/apps/4a1d6439-791f-4229-afd2-3d331a944287/slots/production/predict?subscription-key=f858e158bcaa4ef1813d8883e81bbfae&verbose=true&show-all-intents=true&log=true&query=YOUR_QUERY_HERE"
#define PRICING "S0"

#define YOURSUBSCRIPTION_KEY1 "ad9c840cf43340b08b292455978d3a38"
#define YOURSUBSCRIPTION_KEY2 "c0c95eb21cc24c159a21b38a402058af"
#define YOURSERVICEREGION "eastus"
//"eastasia"

#define CODEPAGE_GB2312      936
#define CODEPAGE_BIG5           950
#define CODEPAGE_UTF8       65001


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Intent;

//https://luisqservice.cognitiveservices.azure.com/luis/prediction/v3.0/apps/4a1d6439-791f-4229-afd2-3d331a944287/slots/production/predict?subscription-key=f858e158bcaa4ef1813d8883e81bbfae&verbose=true&show-all-intents=true&log=true&query=YOUR_QUERY_HERE
//https://westus.api.cognitive.microsoft.com/luis/v3.0-preview/apps/4a1d6439-791f-4229-afd2-3d331a944287/versions/0.1/predict?query=home


//QString TSTransform(const QString pSrc) {

//    locale def;
//    cout<<def.name()<<endl;
//    locale current = cout.getloc();
//    cout<<current.name()<<endl;


////    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
//    QTextCodec *gbk = QTextCodec::codecForName("gbk");
//    QTextCodec::setCodecForLocale(gbk);

////    char *p=pSrc.toLocal8Bit().data();

////    QString strUnicode= utf8->toUnicode(pSrc.toLocal8Bit().data());

////    strUnicode=gbk->toUnicode(p);
////    //2. unicode -> utf-8
////    QByteArray utf8_bytes=utf8->fromUnicode(strUnicode);
////    p = utf8_bytes.data();


//    QString strUnicode= gbk->toUnicode(pSrc.toLocal8Bit().data());
////    QByteArray ByteUtf8= utf8->fromUnicode(strUnicode);

////    char *utf8code = ByteUtf8.data();
////    printf("@@@ Utf8  strGb2312toUtf8:%s\n",utf8code);

//    QTextCodec *codec = QTextCodec::codecForName("Big5");
//    QByteArray b_array = codec->fromUnicode(strUnicode);

//    unsigned char command_chinese[4];
//    memcpy(command_chinese,b_array,4);
//    for(int i = 0 ; i< sizeof(b_array); i++) {
//        int tmp = (int)command_chinese[i];
//        qDebug()<<tmp;
//    }

//}


////
//wchar_t* ToWideChar(const char* pStr, int nCodePage)
//{
////    int nStrLen = MultiByteToWideChar(nCodePage, 0, pStr, -1, NULL, 0);
////    wchar_t* pWStr = new wchar_t[nStrLen + 1];
////    memset(pWStr, 0, nStrLen + 1);
////    MultiByteToWideChar(nCodePage, 0, pStr, -1, pWStr, nStrLen);
////    return pWStr;
//}

////
//char* ToMultiByte(const wchar_t* pWStr, int nCodePage)
//{
////    int nStrLen = WideCharToMultiByte(nCodePage, 0, pWStr, -1, NULL, 0, NULL, NULL);
////    char* pStr = new char[nStrLen + 1];
////    memset(pStr, 0, nStrLen + 1);
////    WideCharToMultiByte(nCodePage, 0, pWStr, -1, pStr, nStrLen, NULL, NULL);
////    return pStr;
//}

//char* CPTransform(const char* pStrSrc, int nCPSrc, int nCPTar)
//{
//    wchar_t* pWStr = ToWideChar(pStrSrc, nCPSrc);
//    char* pStr = ToMultiByte(pWStr, nCPTar);
//    delete [] pWStr;
//    return pStr;
//}


string UnicodeToUTF8(const wstring &wstr)
{
    string ret;
    try {
        wstring_convert< codecvt_utf8<wchar_t> > wcv;
        ret = wcv.to_bytes(wstr);
    } catch (const exception & e) {
        cerr << e.what() << endl;
    }
    return ret;
}

wstring UTF8ToUnicode(const string & str)
{
    wstring ret;
    try {
        wstring_convert< codecvt_utf8<wchar_t> > wcv;
        ret = wcv.from_bytes(str);
    } catch (const exception & e) {
        cerr << e.what() << endl;
    }
    return ret;
}

string UnicodeToANSI(const wstring & wstr)
{
    string ret;
    mbstate_t state = {};
    const wchar_t *src = wstr.data();
    size_t len = wcsrtombs(nullptr, &src, 0, &state);
    if (static_cast<size_t>(-1) != len) {
        unique_ptr< char [] > buff(new char[len + 1]);
        len = wcsrtombs(buff.get(), &src, len, &state);
        if (static_cast<size_t>(-1) != len) {
            ret.assign(buff.get(), len);
        }
    }
    return ret;
}

wstring ANSIToUnicode(const string & str)
{
    wstring ret;
    mbstate_t state = {};
    const char *src = str.data();
    size_t len = mbsrtowcs(nullptr, &src, 0, &state);
    if (static_cast<size_t>(-1) != len) {
        unique_ptr< wchar_t [] > buff(new wchar_t[len + 1]);
        len = mbsrtowcs(buff.get(), &src, len, &state);
        if (static_cast<size_t>(-1) != len) {
            ret.assign(buff.get(), len);
        }
    }
    return ret;
}

//void utf8ToBIG5(char *strUtf8) {
void UTF8ToBIG5(QString strUtf8) {
    printf("~~~~ utf8  str is:%s\n", strUtf8);
    QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
    QTextCodec* big5Codec = QTextCodec::codecForName("big5");

    QString strUnicode= utf8Codec->toUnicode(strUtf8.toLocal8Bit().data());
    QByteArray ByteBIG5= big5Codec->fromUnicode(strUnicode);

//    strUtf8 = ByteBIG5.data();
//    printf("~~~~~ Big5	strUtf8toBig5:%s\n", strUtf8);
}



/**
 * Intent Recognize
 */
void recognizeIntent() {
    auto config = SpeechConfig::FromSubscription("2dbf3bb5efdc4bcd874024194270f873" /*"1819e7e1dae548ec84414e1c46bd8ade"*/, LOCATION);

    config->SetSpeechRecognitionLanguage("zh-cn");

    // create an intent recognizer using microphone as audio input.
    auto recognizer = IntentRecognizer::FromConfig(config);
    // create a language inderstanding model using the app id, and adds specific intents from your model
    auto model = LanguageUnderstandingModel::FromAppId(APP_ID);
    recognizer->AddIntent(model, "HomeAutomation.TurnOn");
    recognizer->AddIntent(model, "HomeAutomation.TurnOff");

    qDebug() << "Say something...\n";

    auto result = recognizer->RecognizeOnceAsync().get();

    // check result
    if(result->Reason == ResultReason::RecognizedIntent) {
        cout << "RECOGNIZED: Text= " << result->Text << endl;
        cout << "Intent Id: " << result->IntentId << endl;
        cout << "Intent Service JSON: " << result->Properties.GetProperty(PropertyId::LanguageUnderstandingServiceResponse_JsonResult) << endl;
    } else if (result->Reason == ResultReason::RecognizedSpeech) {
        cout << "RECOGNIZED: Text= " << result->Text << "(intent could not be recognized)" << endl;
    } else if (result ->Reason == ResultReason::NoMatch) {
        cout << "NOMATCH: Speech could not be recognized." << endl;
    } else if (result->Reason == ResultReason::Canceled) {
        auto cancellation = CancellationDetails::FromResult(result);
        cout << "CANCELED: Reason= " << (int)cancellation->Reason << endl;

        if(cancellation->Reason == CancellationReason::Error) {
            cout << "CANCELED: ErrorCode= " << (int)cancellation->ErrorCode << endl;
            cout << "CANCELED: ErrorDetails= " << cancellation->ErrorDetails << endl;
            cout << "CANCELED: Did you update the subscription info?" << endl;
        }
    }

    opencc_t ot = opencc_open(OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD);

    char buffer[512] = {'\0'};
    opencc_convert_utf8_to_buffer(ot, result->Text.c_str(), result->Text.size(), buffer);
    cout << "result is " << buffer << endl;
    opencc_close(ot);

}

/**
 * Speech Recognize
 */
void recognizeSpeech() {
    auto config = SpeechConfig::FromSubscription(YOURSUBSCRIPTION_KEY1, YOURSERVICEREGION);
    config->SetSpeechRecognitionLanguage("zh-TW");
    // create a speech recognizer
    auto recognizer = SpeechRecognizer::FromConfig(config);
    qDebug() << "Say something ... \n";

    auto result = recognizer->RecognizeOnceAsync().get();

    // check result
    if(result->Reason == ResultReason::RecognizedSpeech) {
        cout << "We recognized : " << result->Text << endl;
    } else if (result->Reason == ResultReason::NoMatch) {
        cout << "NOMATCH: Speech could not be recognized." << endl;
    } else if (result->Reason == ResultReason::Canceled) {
        auto cancellation = CancellationDetails::FromResult(result);
        cout << "CANCELED: Reason= " << (int)cancellation->Reason << endl;

        if(cancellation->Reason == CancellationReason::Error) {
            cout << "CANCELED: ErrorCode= " << (int)cancellation->ErrorCode << endl;
            cout << "CANCELED: ErrorDetails= " << cancellation->ErrorDetails << endl;
            cout << "CANCELED: Did you update the subscription info?" << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    WinForm w;
//    w.show();


//    setlocale(LC_ALL, "");
//    setlocale(LC_ALL, "zh-TW");
//    recognizeSpeech();

    recognizeIntent();
    cout << "Please press a key to continue.\n";
    cin.get();

//    return a.exec();
    return 0;
}
