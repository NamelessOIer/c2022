#ifndef _NORMALOBJ_H
#define _NORMALOBJ_H

#include "baseObject.h"

extern ACL_Image jerryL, jerryR;

class normalObject : public baseObject{
protected:
    const int value;
    void calcVelocity(double t);
    virtual void sizUpdate(double t);
public:
    normalObject(Point P, Vec V, int v = 1, ACL_Image* imgL = &jerryL, ACL_Image* imgR = &jerryR);
    ~normalObject();
    virtual bool effect();
};

#endif