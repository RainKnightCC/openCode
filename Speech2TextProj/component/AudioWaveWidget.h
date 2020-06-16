#ifndef AUDIOWAVEWIDGET_H
#define AUDIOWAVEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>

class AudioWaveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AudioWaveWidget(QWidget *parent = nullptr);  

    void updateLevel(qreal level);
    void clearLevels();

protected:
    void paintEvent(QPaintEvent *event);

private:
    int number = 0;
    QList<qreal> m_levels;

signals:

public slots:
};

#endif // AUDIOWAVEWIDGET_H
