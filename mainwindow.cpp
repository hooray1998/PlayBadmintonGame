#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Badminton");
    resize(1200,700);
    initStyle();

    QObject::connect(this,SIGNAL(press(int)),ui->label,SLOT(readySwing(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initStyle()
{
    //加载样式表
    QFile file(":/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_S)
    {
        ui->label->usefulKey[0] = true;
    }
    else if(event->key()==Qt::Key_E)
    {
        ui->label->usefulKey[1] = true;
    }
    else if(event->key()==Qt::Key_F)
    {
        ui->label->usefulKey[2] = true;
    }
    else if(event->key()==Qt::Key_D)
    {
        emit press(0);
    }
    else if(event->key()==Qt::Key_J||event->key()==Qt::Key_Left||event->key()==Qt::Key_1)
    {
        ui->label->usefulKey[4] = true;
    }
    else if(event->key()==Qt::Key_I||event->key()==Qt::Key_Up||event->key()==Qt::Key_5)
    {
        ui->label->usefulKey[5] = true;
    }
    else if(event->key()==Qt::Key_L||event->key()==Qt::Key_Right||event->key()==Qt::Key_3)
    {
        ui->label->usefulKey[6] = true;
    }
    else if(event->key()==Qt::Key_K||event->key()==Qt::Key_Down||event->key()==Qt::Key_2)
    {
        emit press(1);
    }
    else if(event->key()==Qt::Key_Space)
    {
        emit press(6);
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_S)
    {
        ui->label->usefulKey[0] = false;
    }
    else if(event->key()==Qt::Key_E)
    {
        ui->label->usefulKey[1] = false;
    }
    else if(event->key()==Qt::Key_F)
    {
        ui->label->usefulKey[2] = false;
    }
    else if(event->key()==Qt::Key_D)
    {
        ui->label->usefulKey[3] = false;
    }
    else if(event->key()==Qt::Key_J||event->key()==Qt::Key_Left||event->key()==Qt::Key_1)
    {
        ui->label->usefulKey[4] = false;
    }
    else if(event->key()==Qt::Key_I||event->key()==Qt::Key_Up||event->key()==Qt::Key_5)
    {
        ui->label->usefulKey[5] = false;
    }
    else if(event->key()==Qt::Key_L||event->key()==Qt::Key_Right||event->key()==Qt::Key_3)
    {
        ui->label->usefulKey[6] = false;
    }
    else if(event->key()==Qt::Key_K||event->key()==Qt::Key_Down||event->key()==Qt::Key_2)
    {
        ui->label->usefulKey[7] = false;
    }
    else if(event->key()==Qt::Key_Enter)
    {
    }
}
