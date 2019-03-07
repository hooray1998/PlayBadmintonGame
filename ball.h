#ifndef BALL_H
#define BALL_H

#include "pos.h"

class Ball
{
public:
    Ball();
    void set(Pos p);
    void readyFly(bool d, float sx, float sy);
    Pos curPos();
    void nextPos();//per 1/10  second
    void start();
    void stop();


    bool flying;//true:  flying and nextPos()
private:
    Pos pos;
    float speedX;//toRight is positive and toLeft is negative;
    float speedY;//toDown is positive and toUp is negative;
    bool direction;//0-right;1-left

    bool nextNet;
    bool nextWall;
};

#endif // BALL_H
