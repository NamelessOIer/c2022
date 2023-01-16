#ifndef _HEART_H
#define _HEART_H

#include "itemObject.h"

extern ACL_Image heart;

class Heart: public itemObject{
public:
    Heart(Point P, ACL_Image* img = &heart);
    bool effect();
};

#endif