#include <QApplication>
#include "MainForm.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    qWarning() << logCommands[enumToInt(LogType::FrontBlue)] << logCommands[enumToInt(LogType::BackRed)] << u8"Engine Start .." << logCommands[0];
    MainForm win;
    win.setWindowTitle(WINDOWS_TITLE);
    win.setFixedWidth(WINDOWS_WIDTH);
    win.setFixedHeight(WINDOWS_HEIGHT);
    win.setWindowFlags(Qt::FramelessWindowHint);
    win.show();



//    qWarning() << logCommands[enumToInt(LogType::FrontBlue)] << logCommands[enumToInt(LogType::BackRed)] << u8"Engine Finish .." << logCommands[0];

    return app.exec();
}
