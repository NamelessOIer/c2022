#include "Heart.h"
#include "userObject.h"

extern ACL_Sound heartSound;
extern userObject *user;

Heart::Heart(Point P, ACL_Image* img):itemObject(P, img){}

bool Heart::effect(){
    if(user -> getLife() < 10){
        playSound(heartSound, 0);
        user -> addLife();
        return 1;
    }
    else return 0;
}
