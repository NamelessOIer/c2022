#ifndef _AVOIDOBJ_H
#define _AVOIDOBJ_H

#include "normalObject.h"

extern ACL_Image duckL, duckR;

class avoidObject : public normalObject{
protected:
    const int Limit;
    void calcVelocity(double t);
    virtual void move(double t);
public:
    avoidObject(Point P, Vec V, int d, int v = 5, ACL_Image* imgL = &duckL, ACL_Image* imgR = &duckR);
};

#endif