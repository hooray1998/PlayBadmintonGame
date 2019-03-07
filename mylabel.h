#ifndef MYLABEL_H
#define MYLABEL_H

#include <QTimer>
#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <QtDebug>
#include <QMouseEvent>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QtMath>
#include <QFile>
#include <QTextStream>

#include "racket.h"
#include "ball.h"
#include "pos.h"

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget*parent = 0);

    bool usefulKey[20];

    bool judgeHit();
    bool judgeOnFront(bool left_or_right, bool direction);

    void readGrade();
    void writeGrade();
private:
    QPainter painter;
    QTimer *timer;
    QTimer *moveTimer;


    Ball ball;
    Racket lracket;
    Racket rracket;

    bool lhiting,rhiting;

    int grade;
    int oldgrade;
    QFile file;
protected:

public slots:
    void paintEvent(QPaintEvent *);
    void Going();
    void moveFluently();
    void readySwing(int);
    void end(int);//0   1--left  2--right
    void start();
};

#endif // MYLABEL_H
