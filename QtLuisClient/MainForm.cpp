#include "MainForm.h"
#include "ui_MainForm.h"

/*
 * (1) 請描述 hash, heap, merge sort, quick sort 的關聯
    (2) 解釋 STL vector 跟 list 的差別
    (3) 承上，解釋為何 list 沒有 random access iterator？
    (4) 聽過 traits 嗎？ (STL)
    (5) 什麼狀況下用過 Boost，用 Boost 的原因？
    (6) 請解釋 GOT/PLT stub
    (7) 請解釋何謂 relocation
    (8) GOT hijacking 是個很嚴重的安全性問題，如何保護 GOT。(為何 loader 不能在 load phase 全部 relocate 完後把 GOT 設為唯讀？)
    (9) 聽過 CI (continuous integration) 嗎？
    (10) 簡述你某次遇過 debug 的經驗
    (11) 請簡述你聽過的 design pattern，跟其行為
    (12) 解釋 Adaptor pattern
 *
 */

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    this->setWindowTitle("LUIS NLP");
    qDebug()<<"Main thread : "<<QThread::currentThreadId();

    worker.moveToThread(&thread);
    QObject::connect(&runnable, SIGNAL(sendGetSignalRequest()), &worker, SLOT(getRequest()));
    thread.start();
    triggerRequestEvent();
}

MainForm::~MainForm()
{
    thread.deleteLater();
    delete &runnable;
    delete &worker;
    delete ui;
}

void MainForm::triggerRequestEvent() {
    emit runnable.sendGetSignalRequest();
}

QtRunnable::QtRunnable(QObject *parent) : QObject(parent) {

}

QtRunnable::~QtRunnable() {

}

QWorker::QWorker() {

}

QWorker::~QWorker() {

}

void QWorker::getRequest() {
    qDebug() << "[Request GET] Thread id : " << QThread::currentThreadId();
}

void QWorker::postRequest(){
    qDebug() << "[Request POST] Thread id : " << QThread::currentThreadId();
}
