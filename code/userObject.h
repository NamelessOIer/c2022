#ifndef _USEROBJ_H
#define _USEROBJ_H

#include "baseObject.h"

extern ACL_Image tomL, tomR;
extern ACL_Image tomSwordL, tomSwordR;
const double Af = 50; //阻力系数

class userObject : public baseObject{ // user
private:
    Point Target;
    Vec Force0;

    int score;
    int life;
    int state; // 0: 正常, 1: 剑

    Vec getAcceleration(double dt);
    void calcVelocity(double t);
    virtual bool effect();
    void invertX();
    void invertY();

public:
    userObject(Point P, Vec V, ACL_Image* imgL = &tomL, ACL_Image* imgR = &tomR);

    void addScore(int v);
    int getScore();

    bool die();
    void addLife();
    int getLife();

    void setState(int s);
    int getState();

    void setTarget(const Point &T);

    void onUP();
    void offUP();
    void onDOWN();
    void offDOWN();
    void onLEFT();
    void offLEFT();
    void onRIGHT();
    void offRIGHT();

};

#endif