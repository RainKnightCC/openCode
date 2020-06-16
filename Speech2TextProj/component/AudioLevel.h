#ifndef AUDIOLEVEL_H
#define AUDIOLEVEL_H

#include <QObject>
#include <QWidget>
#include <QPainter>

class AudioLevel : public QWidget
{
    Q_OBJECT
public:
    explicit AudioLevel(QWidget *parent = nullptr);
    void setLevel(qreal level);

protected:
    void paintEvent(QPaintEvent *event);

private:
    qreal m_level;

signals:

public slots:
};

#endif // AUDIOLEVEL_H
