#include "ball.h"
#include <QtDebug>
Ball::Ball()
{
    flying = false;
    set(Pos(150,250));
    nextNet = false;
    nextWall = false;
}

void Ball::set(Pos p)
{
    pos = p;
}
void Ball::readyFly(bool d, float sx, float sy)
{
    direction = d;
    speedX = sx;
    speedY = sy;
}

Pos Ball::curPos()
{
    return pos;
}

void Ball::nextPos()//1/100 once
{
    //56px per 1 meter
    //if speed = 1m/s.  move 0.01m/n = 56px/n
    if(!flying) return ;
    pos.x += speedX*0.1;
    pos.y += speedY*0.1;
    //g = 9.8 m/s^2  ~ 10m/s^2
    //g -= 10m/s  /s == 0.1m/s  /n  --
    speedY += 1; //v = v0 + gt;

    if(!nextWall&&(pos.x<=30||pos.x>=1170))
    {
        speedX = -speedX/3;
        speedY = speedY/3;
        nextWall = true;
    }
    else if(pos.x>20&&pos.x<1150)
    {
        nextWall = false;
    }

    if(pos.y>=600)
    {
       set(Pos(150,250));
       stop();
    }

    if(!nextNet&&(pos.x>=595&&pos.x<=605&&pos.y>440))
    {
        speedX = -speedX/4;
        speedY /= 4;
        nextNet = true;
    }
    else if(pos.x<595||pos.x>605||pos.y<440)
    {
        nextNet = false;
    }

}

void Ball::start()
{
    flying = true;
}

void Ball::stop()
{
    flying = false;
}

