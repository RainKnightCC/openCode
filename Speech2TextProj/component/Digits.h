#ifndef DIGITS_H
#define DIGITS_H

#include <QObject>
#include <QWidget>
#include <QTimeLine>
#include <QPainter>

class Digits : public QWidget
{
public:
    Digits(QWidget *parent);

    void setTransition(int tr);
    int transition() const;
    void setNumber(int n);
    void flipTo(int n);
    void preparePixmap();

    void drawFrame(QPainter *p, const QRect &rect);
    QPixmap drawDigits(int n, const QRect &rect);

    void resizeEvent(QResizeEvent*);
    void paintStatic();
    void paintSlide();
    void paintFlip();
    void paintRotate();

    void paintEvent(QPaintEvent *event);

    enum {
        Slide,
        Flip,
        Rotate
    };

private:
    int m_number;//number to set to digits
    int m_transition;//transition mode(change effect)
    QPixmap m_pixmap;//current time pixmap
    QPixmap m_lastPixmap;//next state time pixmap
    QTimeLine m_animator;

};

#endif // DIGITS_H
