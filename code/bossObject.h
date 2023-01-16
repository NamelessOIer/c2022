#ifndef _BOSSOBJ_H
#define _BOSSOBJ_H

#include "avoidObject.h"

extern ACL_Image dogL, dogR;

class bossObject : public avoidObject{
protected:
    void calcVelocity(double t);
    virtual void sizUpdate(double t);
    virtual void move(double t);
public:
    bossObject(Point P, Vec V, int d, int v = 10, ACL_Image* imgL = &dogL, ACL_Image* imgR = &dogR);
    ~bossObject();
    virtual bool effect();
};

#endif