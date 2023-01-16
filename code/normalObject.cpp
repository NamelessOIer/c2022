#include "normalObject.h"
#include "userObject.h"

extern int countRat;

extern userObject *user;

normalObject::normalObject(Point P, Vec V, int v, ACL_Image* imgL, ACL_Image* imgR): baseObject(P, V, imgL, imgR), value(v){
    ++countRat;
}

normalObject::~normalObject(){
    --countRat;
}

void normalObject::sizUpdate(double t){
    if(dcmp(imgSiz.x - 0.7 * AreaImg.x) < 0){
        imgSiz += AreaImg * t / 0.5;
    }
}

bool normalObject::effect(){
    user -> addScore(value);
    return 1;
}

void normalObject::calcVelocity(double t){}
