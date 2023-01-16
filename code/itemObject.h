#ifndef _itemObjectOBJ_H
#define _itemObjectOBJ_H

#include "baseObject.h"

class itemObject: public baseObject{
protected:
    void calcVelocity(double t);
    virtual void sizUpdate(double t);
public:
    itemObject(Point P, ACL_Image* img);
};

#endif