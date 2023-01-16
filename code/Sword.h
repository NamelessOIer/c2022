#ifndef _SWORD_H
#define _SWORD_H
#include "itemObject.h"

extern ACL_Image sword;

class Sword: public itemObject{
public:
    Sword(Point P, ACL_Image* img = &sword);
    bool effect();
};

#endif
