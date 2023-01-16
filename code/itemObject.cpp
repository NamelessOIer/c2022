#include "itemObject.h"

itemObject::itemObject(Point P, ACL_Image* img):baseObject(P, Point(0, 0), img, img){}

void itemObject::sizUpdate(double t){
    if(dcmp(imgSiz.x - 0.7 * AreaImg.x) < 0){
        imgSiz += AreaImg * t / 0.5;
    }
}

void itemObject::calcVelocity(double t){}