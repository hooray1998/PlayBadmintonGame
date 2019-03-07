#include "mylabel.h"

#define BAT_LEN 100
#define PLAYER_HEIGHT 100
#define ENERGY  90

myLabel::myLabel(QWidget *parent) :
    QLabel(parent)
{


    grade = 0;
    readGrade();

    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(Going()));
    timer->start(10);

    //For move fluently.
    for(int i=0;i<20;i++)
       usefulKey[i] = false;

    moveTimer = new QTimer();
    QObject::connect(moveTimer,SIGNAL(timeout()),this,SLOT(moveFluently()));
    moveTimer->start(20);

    lracket.setId(0);
    rracket.setId(1);


    //lracket.Hand();



    //underground
}



void myLabel::paintEvent(QPaintEvent *)
{
        painter.begin(this);          //进行重绘;

        //all  Points
        QPoint lcenter, rcenter;
        QPoint lheart,  rheart;
        QPoint ltop,    rtop;
        QPoint lbtm,    rbtm;

        QPoint p1[4],p2[4];
        QPoint q1[4],q2[4];


        lcenter.setX(lracket.batPos.x);
        lcenter.setY(lracket.batPos.y);
        lheart.setX(lracket.playerPos.x);
        lheart.setY(lracket.playerPos.y-PLAYER_HEIGHT);
        ltop = lcenter-(lheart - lcenter)/3;
        lbtm = lcenter+(lheart - lcenter)/3;

        rcenter.setX(rracket.batPos.x);
        rcenter.setY(rracket.batPos.y);
        rheart.setX(rracket.playerPos.x);
        rheart.setY(rracket.playerPos.y-PLAYER_HEIGHT);
        rtop = rcenter-(rheart - rcenter)/3;
        rbtm = rcenter+(rheart - rcenter)/3;


        //////////////////draw Circle

        //special Points
        p1[0] = ltop;
        p1[2] = (ltop+lcenter)/2;
        p1[1] = (p1[2]+ltop)/2;
        p1[3] = (p1[2]+lcenter)/2;
        p2[0] = lbtm;
        p2[2] = (lbtm+lcenter)/2;
        p2[1] = (p2[2]+lbtm)/2;
        p2[3] = (p2[2]+lcenter)/2;

        q1[0] = rtop; q1[2] = (rtop+rcenter)/2;
        q1[1] = (q1[2]+rtop)/2;
        q1[3] = (q1[2]+rcenter)/2;
        q2[0] = rbtm;
        q2[2] = (rbtm+rcenter)/2;
        q2[1] = (q2[2]+rbtm)/2;
        q2[3] = (q2[2]+rcenter)/2;


        int s[5] = {8,17,20,23,24};

        for(int i=0;i<4;i++)
        {
            painter.setPen(QPen(Qt::gray, s[i], Qt::SolidLine, Qt::RoundCap));    //设置画笔;
            painter.drawPoint(p1[i]);
            painter.drawPoint(p2[i]);
            painter.drawPoint(q1[i]);
            painter.drawPoint(q2[i]);
        }
        painter.setPen(QPen(Qt::gray, s[4], Qt::SolidLine, Qt::RoundCap));    //设置画笔;
        painter.drawPoint(lcenter);
        painter.drawPoint(rcenter);

        //draw net
        painter.setPen(QPen(Qt::gray, 5, Qt::SolidLine, Qt::RoundCap));    //设置画笔;
        painter.drawLine(0, 550, 1200, 550);

        //shu
        painter.drawLine(570,400,570,570);
        painter.drawLine(630,480,630,680);

        //heng
        painter.drawLine(570,400,630,480);
        painter.drawLine(570,500,630,585);


        //xian -heng   dashLine
        painter.setPen(QPen(Qt::gray, 3, Qt::DashLine, Qt::RoundCap));    //设置画笔;
        painter.drawLine(570,425,630,506);
        painter.drawLine(570,450,630,532);
        painter.drawLine(570,475,630,558);
        //xian -shu    dashLine
        painter.drawLine(582,416,582,517);
        painter.drawLine(594,432,594,534);
        painter.drawLine(606,448,606,551);
        painter.drawLine(618,464,618,568);


        //draw ball
        painter.setPen(QPen(Qt::gray, 20, Qt::SolidLine, Qt::RoundCap));    //设置画笔;
        painter.drawPoint(ball.curPos().x,ball.curPos().y);


        //racket  Line
        painter.setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap));    //设置画笔;
        painter.drawLine(lracket.playerPos.x,lracket.playerPos.y-PLAYER_HEIGHT,lracket.batPos.x,lracket.batPos.y);
        painter.drawLine(rracket.playerPos.x,rracket.playerPos.y-PLAYER_HEIGHT,rracket.batPos.x,rracket.batPos.y);


        //draw shadow
        painter.setPen(QPen(Qt::gray, 5, Qt::SolidLine, Qt::RoundCap));    //设置画笔;
        painter.drawEllipse(lracket.playerPos.x-80,lracket.playerPos.y,80,40);
        painter.drawEllipse(rracket.playerPos.x,rracket.playerPos.y,80,40);

        //record grade
        painter.setFont(QFont(NULL,20));
        painter.drawText(QRect(400,0,400,30), Qt::AlignCenter, QString("history:\t%1").arg(oldgrade));
        painter.setFont(QFont(NULL,30));
        painter.drawText(QRect(400,30,400,50), Qt::AlignCenter, QString("grade:\t%1").arg(grade));

        painter.end();  //重绘结束;

}

void myLabel::Going()
{
    ball.nextPos();
    lracket.Swinging();
    lracket.Jumping();
    rracket.Swinging();
    rracket.Jumping();
    judgeHit();
    update();
}


void myLabel::moveFluently()
{
    for(int i=0;i<20;i++)
    {
        if(usefulKey[i])
        {
            lracket.Move(i, ball.curPos().y);
            rracket.Move(i, ball.curPos().y);
        }
    }
}

//Swing  for ready
void myLabel::readySwing(int i)
{
    if(i==0)
        lracket.Move(3, ball.curPos().y);
    else if(i==1)
        rracket.Move(7, ball.curPos().y);
    else if(i==6)
    {
        if(ball.flying) return ;
        start();
    }
}

bool myLabel::judgeHit()
{

    QPoint Bll(ball.curPos().x,ball.curPos().y);
    QPoint BatL(lracket.batPos.x,lracket.batPos.y);
    QPoint BatR(rracket.batPos.x,rracket.batPos.y);

    //27*27 = 729
    bool nearL  = ((Bll-BatL).x()*(Bll-BatL).x() + (Bll-BatL).y()*(Bll-BatL).y() )<2000? true:false;
    bool nearR  = ((Bll-BatR).x()*(Bll-BatR).x() + (Bll-BatR).y()*(Bll-BatR).y() )<2000? true:false;
    //bool frontL = (Bll.)



    if(!nearL)
    {
        lhiting = false;
    }

    if(!nearR)
    {
        rhiting = false;
    }

    if(lracket.swingingUp&&nearL&&!lhiting)
    {
        bool dir = (lracket.swingAngle>=0);
        if(!judgeOnFront(0,!dir)) return false;
        float newSpeedX = qCos(lracket.swingAngle*3.1415926/180)*ENERGY;
        float newSpeedY = qSin(lracket.swingAngle*3.1415926/180)*ENERGY;

        lhiting = true;
        rhiting = false;

        ball.start();
        ball.readyFly(0,newSpeedX,newSpeedY);

    }
    else if(lracket.swingingDn&&nearL&&!lhiting)
    {
        if(!judgeOnFront(0,true)) return false;
        float newSpeedX = qCos(lracket.swingAngle*3.1415926/180)*ENERGY;
        float newSpeedY = -qSin(lracket.swingAngle*3.1415926/180)*ENERGY-20;

        lhiting = true;
        rhiting = false;

        ball.start();
        ball.readyFly(0,newSpeedX,newSpeedY);
    }
    else if(rracket.swingingUp&&nearR&&!rhiting)
    {
        bool dir = (lracket.swingAngle>=0);
        if(!judgeOnFront(1,dir)) return false;
        float newSpeedX = -qCos(lracket.swingAngle*3.1415926/180)*ENERGY;
        float newSpeedY = qSin(lracket.swingAngle*3.1415926/180)*ENERGY;

        lhiting = false;
        rhiting = true;

        ball.start();
        ball.readyFly(0,newSpeedX,newSpeedY);
    }
    else if(rracket.swingingDn&&nearR&&!rhiting)
    {
        if(!judgeOnFront(1,false)) return false;
        float newSpeedX = -qCos(lracket.swingAngle*3.1415926/180)*ENERGY;
        float newSpeedY = -qSin(lracket.swingAngle*3.1415926/180)*ENERGY-20;

        lhiting = false;
        rhiting = true;

        ball.start();
        ball.readyFly(0,newSpeedX,newSpeedY);
    }
    else
    {
        return false;
    }

    grade++;
    return true;

}

void myLabel::end(int num)
{
}

void myLabel::start()
{

    lhiting = false;
    rhiting = false;

    writeGrade();
    readGrade();
    grade = 0;

    ball.set(Pos(150,250));
    ball.start();
    ball.readyFly(0,0,-70);
}


//judge front or back
bool myLabel::judgeOnFront(bool left_or_right, bool direction)
{
        //all  Points
        Pos lctr(lracket.batPos), rctr(rracket.batPos);
        Pos lhrt,  rhrt;
        Pos curBall(ball.curPos());

        if(!left_or_right)
        {
            lhrt.set(lracket.playerPos.x,lracket.playerPos.y-PLAYER_HEIGHT);
            float kl = (lctr.y-lhrt.y) / (lctr.x-lhrt.x) ;
            float bl = lctr.y - kl*lctr.x;

            float flag = kl*curBall.x + bl - curBall.y;
            if(direction)//na
            {
                if(flag>0)
                    return true;
                else
                    return false;
            }
            else//pie
            {
                if(flag<0)
                    return true;
                else
                    return false;
            }
        }
        else
        {
            rhrt.set(rracket.playerPos.x,rracket.playerPos.y-PLAYER_HEIGHT);
            float kr = (rctr.y-rhrt.y) / (rctr.x-rhrt.x) ;
            float br = rctr.y - kr*rctr.x;

            float flag = kr*curBall.x + br - curBall.y;
            if(direction)//na
            {
                if(flag<0)
                    return true;
                else
                    return false;
            }
            else//pie
            {
                if(flag>0)
                    return true;
                else
                    return false;
            }
        }

}

void myLabel::readGrade()
{
    QFile *file = new QFile("old.grade");
    bool ok =file->open(QIODevice::ReadOnly|QIODevice::Text);

    if(ok)
    {
        QTextStream in(file);
        in>>oldgrade;
        file->close();
        delete file;
    }
}
void myLabel::writeGrade()
{
    if(grade>oldgrade)
    {
        QFile *file = new QFile("old.grade");
        bool ok = file->open(QIODevice::WriteOnly|QIODevice::Text);

        if(ok)
        {
            QTextStream out(file);
            out<<grade;
            file->close();
            delete file;
        }

    }
}
