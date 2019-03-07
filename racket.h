#ifndef RACKET_H
#define RACKET_H

#include "pos.h"
#include <QtMath>
#include <QtDebug>


class Racket
{
public:
    Racket();

    void setId(bool id0);
    void Move(int key, int y);
    void Jumping();//strat jump
    void Swinging();//
    bool judge();//


    void Hand();

    Pos playerPos;
    Pos batPos;

    //swing module
    float swingAngle;//-60--60
    bool swingingUp;
    bool swingingDn;

private:
    bool id;
    bool handing;//1-- ball is in hand; 0 -- ball is flying.
    bool jumping;



    //jump module
    float speedJump;


};

#endif // RACKET_H
