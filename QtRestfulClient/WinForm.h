#ifndef WINFORM_H
#define WINFORM_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QtNetwork>

namespace Ui {
class WinForm;
}

class WinForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit WinForm(QWidget *parent = 0);
    ~WinForm();

private:
    Ui::WinForm *ui;
};

#endif // WINFORM_H
