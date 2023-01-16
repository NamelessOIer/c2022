#include "Sword.h"
#include "userObject.h"

extern ACL_Sound swordSound;
extern int swordtime;
extern int defaultswordexisttime;
extern userObject *user;

Sword::Sword(Point P, ACL_Image* img):itemObject(P, img){}

bool Sword::effect(){
    playSound(swordSound, 0);
    user -> setState(1);
    swordtime = defaultswordexisttime;
    startTimer(2, 1000);
    return 1;
}
