#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QDebug>
#include <QThread>
#include <QObject>

namespace Ui {
class MainForm;
}

class QtRunnable;
class QWorker;

class QtRunnable : public QObject
{
    Q_OBJECT

public:
    QtRunnable(QObject *parent=0);
    ~QtRunnable();

public slots:

signals:
    void sendGetSignalRequest();
    void sendPostSignalRequest();

};

class QWorker : public QObject
{
    Q_OBJECT
public:
   explicit QWorker();
    ~QWorker();

public slots:
    void getRequest();
    void postRequest();
};


class MainForm : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    QThread thread;
    QtRunnable runnable;
    QWorker worker;

public slots:
    void triggerRequestEvent();

private:
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
