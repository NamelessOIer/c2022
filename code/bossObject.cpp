#include "bossObject.h"
#include "userObject.h"
#include "Game.h"
#include <unordered_set>

extern int countDog;
extern ACL_Sound dogSound;
extern std::unordered_set<bossObject*> DOG;

extern userObject *user;
extern Game *game;

bossObject::bossObject(Point P, Vec V, int d, int v, ACL_Image* imgL, ACL_Image* imgR): avoidObject(P, V, d, v, imgL, imgR){
    ++countDog;
    DOG.insert(this);
    playSound(dogSound, 0);
}

bossObject::~bossObject(){
    --countDog;
    DOG.erase(this);
}

bool bossObject::effect(){
    if(user -> getState() == 0){
        if(user -> die()){
            game -> GameOver();
        }
        return 0;
    }
    else{
        return normalObject::effect();
    }
}

void bossObject::sizUpdate(double t){
    if(dcmp(imgSiz.x - 1.2 * AreaImg.x) < 0){
        imgSiz += AreaImg * t / 0.5;
    }
}

void bossObject::move(double t){
    baseObject::move(t);
}

void bossObject::calcVelocity(double t){
    // cerr << norm(Velocity) << endl;
    if(norm(user -> getPosition() - Position) > Limit){
        return normalObject::calcVelocity(t);
    }
    if(user -> getState() == 1){
        avoidObject::calcVelocity(t);
        // cerr << "Position:(" << Position.x << "," << Position.y << ")" << endl;
        // cerr << "Velocity0:(" << Velocity.x << "," << Velocity.y << ")" << endl;
        if(norm(Position - imgSiz) < 50 && Velocity.x <= 0 && Velocity.y <= 0){
            if(fabs(Velocity.x) < fabs(Velocity.y)){
                Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(1, 0));
            }
            else{
                Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(0, 1));
            }
        }
        else if(norm(Position - Point(Area.x - imgSiz.x, imgSiz.y)) < 50 && Velocity.x >= 0 && Velocity.y <= 0){
            if(fabs(Velocity.x) < fabs(Velocity.y)){
                Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(-1, 0));
            }
            else{
                Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(0, 1));
            }
        }
        else if(norm(Position - (Area - imgSiz)) < 50 && Velocity.x >= 0 && Velocity.y >= 0){
            if(fabs(Velocity.x) < fabs(Velocity.y)){
                Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(-1, 0));
            }
            else{
                Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(0, -1));
            }
        }
        else if(norm(Position - Point(imgSiz.x, Area.y - imgSiz.y)) < 50 && Velocity.x <= 0 && Velocity.y >= 0){
            if(fabs(Velocity.x) < fabs(Velocity.y)){
                Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(1, 0));
            }
            else{
                Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(0, -1));
            }
        }
        else if(Position.x - imgSiz.x < 50 && Velocity.x <= 0){
            Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(0.3, Velocity.y < 0 ? -1 : 1));
        }
        else if(Area.x - imgSiz.x - Position.x < 50 && Velocity.x >= 0){
            Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(-0.3, Velocity.y < 0 ? -1 : 1));
        }
        else if(Position.y - imgSiz.y < 50 && Velocity.y <= 0){
            Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(Velocity.x < 0 ? -1 : 1, 0.3));
        }
        else if(Area.y - imgSiz.y - Position.y < 50 && Velocity.y >= 0){
            Velocity = norm(Velocity) * Itemize(Itemize(Velocity) + Point(Velocity.x < 0 ? -1 : 1, -0.3));
        }
        // cerr << "Velocity1:(" << Velocity.x << "," << Velocity.y << ")" << endl;
    }
    else{
        double alpha = sqrt(1 - norm(user -> getPosition() - Position) / Limit);
        Velocity = norm(Velocity) * Itemize((alpha * Itemize(user -> getPosition() - Position) + (1 - alpha) * Itemize(Velocity)));
    }
}
