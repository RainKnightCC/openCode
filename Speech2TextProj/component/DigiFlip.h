#ifndef DIGIFLIP_H
#define DIGIFLIP_H

#include <QMainWindow>
#include <QObject>
#include <QBasicTimer>
#include <QTime>
#include <QAction>
#include <QKeyEvent>

#include "Digits.h"

//class DigiFlip : public QMainWindow
class DigiFlip : public QWidget
{
    Q_OBJECT
public:
    DigiFlip(QWidget *parent = nullptr);

    void updateTime();
    void switchTransition(int delta);

protected:
    void resizeEvent(QResizeEvent*);
    void timerEvent(QTimerEvent*);
    void keyPressEvent(QKeyEvent *event);

private:
    QBasicTimer m_ticker;
    Digits *m_hour;
    Digits *m_minute;
    Digits *m_sec;

signals:

public slots:

private slots:
    void chooseSlide();
    void chooseFlip();
    void chooseRotate();

};

#endif // DIGIFLIP_H
