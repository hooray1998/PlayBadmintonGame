#include "racket.h"
#define STEP 10
#define GROUNDLINE 600
#define PI  3.1415926
#define BAT_LEN 100
#define PLAYER_HEIGHT 100
Racket::Racket()
{

    swingingUp= false;
    swingingDn= false;
    jumping = false;
    handing = false;
    swingAngle = -60;

}

void Racket::setId(bool id0)
{
    id = id0;
    if(!id)
        playerPos.set(200,GROUNDLINE);
    else
        playerPos.set(1000,GROUNDLINE);
}

void Racket::Move(int key, int y)
{
    if((!id&&key==0)||(id&&key==4))
    {
        if(!id)
        {
            if(playerPos.x<=120) return ;
            playerPos.x -= STEP;
        }
        else
        {
            if(playerPos.x<=600) return ;
            playerPos.x -= STEP;
        }
    }
    else if((!id&&key==2)||(id&&key==6))
    {
        if(!id)
        {
            if(playerPos.x>=580) return ;
            playerPos.x += STEP;
        }
        else
        {
            if(playerPos.x>=1060) return ;
            playerPos.x += STEP;
        }
    }
    else if((!id&&key==1)||(id&&key==5))
    {
        if(jumping) return ;
        jumping = true;
        speedJump = -60;
    }
    else if((!id&&key==3)||(id&&key==7))
    {
        if(swingingUp||swingingDn) return;

        if(y<(GROUNDLINE - PLAYER_HEIGHT - BAT_LEN/3))
            swingingUp = true;
        else
        {
            swingAngle = 0;
            swingingDn = true;
        }
    }
}

void Racket::Jumping()
{
   if(jumping)
   {
       if(playerPos.y>GROUNDLINE)
       {
           playerPos.y = GROUNDLINE;
           jumping = false;
           return ;
       }
        playerPos.y += speedJump*0.1;
        speedJump += 1.8;
   }
}

void Racket::Swinging()
{

    if(swingingUp)
    {
            if(swingAngle>=60)
            {
                swingingUp= false;
                swingAngle = -60;
                return ;
            }

            swingAngle+=6;
            if(!id)
            {
                batPos.x = playerPos.x + BAT_LEN*qSin(swingAngle*PI/180);
            }
            else
                batPos.x = playerPos.x - BAT_LEN*qSin(swingAngle*PI/180);
                batPos.y = playerPos.y -PLAYER_HEIGHT- BAT_LEN*qCos(swingAngle*PI/180);
    }
    else if(swingingDn)
    {

            if(swingAngle>=88)
            {
                swingingDn= false;
                swingAngle = -60;
                return ;
            }

            swingAngle+=8;
            if(!id)
            {
                batPos.x = playerPos.x + BAT_LEN*qSin(swingAngle*PI/180);
            }
            else
                batPos.x = playerPos.x - BAT_LEN*qSin(swingAngle*PI/180);
                batPos.y = playerPos.y -PLAYER_HEIGHT + BAT_LEN*qCos(swingAngle*PI/180);
    }
    else
    {
        swingAngle = -60;
        if(!id)
            batPos.x = playerPos.x + BAT_LEN*qSin(swingAngle*PI/180);
        else
            batPos.x = playerPos.x - BAT_LEN*qSin(swingAngle*PI/180);
            batPos.y = playerPos.y -PLAYER_HEIGHT- BAT_LEN*qCos(swingAngle*PI/180);

    }



}

bool Racket::judge()
{

}

void Racket::Hand()
{
    handing = true;
}
