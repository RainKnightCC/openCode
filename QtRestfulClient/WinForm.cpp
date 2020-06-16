#include "WinForm.h"
#include "ui_WinForm.h"

#define WINDOWS_TITLE "Windows Form"

WinForm::WinForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WinForm)
{
    ui->setupUi(this);
    this->setWindowTitle(WINDOWS_TITLE);
}

WinForm::~WinForm()
{
    delete ui;
}
