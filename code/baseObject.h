#ifndef _BASEOBJ_H
#define _BASEOBJ_H

#include "acllib.h"
#include "Geometry.h"

extern Point Area;
extern Point AreaImg;

class baseObject{
protected:
    Point Position;
    Vec Velocity;
	ACL_Image *imgL;
	ACL_Image *imgR;
    ACL_Image *img;
    Point imgSiz;
    virtual void calcVelocity(double t)=0;
    virtual void sizUpdate(double t);
    virtual void invertX();
    virtual void invertY();
    virtual void move(double t);

public:

    baseObject(Point P, Vec V, ACL_Image* imgL, ACL_Image* imgR);
    virtual ~baseObject();
    virtual bool effect()=0;

    Point getPosition();

    Point getVelocity();

    Point getP1() const;

    Point getP2() const;

    void print();

    void update(double t);

};

bool collision(baseObject* A, baseObject* B);

#endif