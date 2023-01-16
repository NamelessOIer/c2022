#include "userObject.h"
#include "bossObject.h"
#include "Game.h"
#include "acllib.h"

using namespace std;

extern ACL_Sound dieSound;
extern ACL_Sound moneySound;
// extern int INF;
extern unordered_set<bossObject*> DOG;

userObject::userObject(Point P, Vec V, ACL_Image* imgL, ACL_Image* imgR): baseObject(P, V, imgL, imgR), Force0(0, 0), Target(-1, -1), score(0), life(5), state(0){}

bool userObject::effect(){
    return 0;
}

Vec userObject::getAcceleration(double dt){
    // cerr << "Target = (" << Target.x << "," << Target.y << ")" << endl; 
    // cerr << "Position = (" << Position.x << "," << Position.y << ")" << endl; 
    Point Force;
    if(Target.x < 0 || Target.y < 0){
        Force = Point(0, 0);
    }
    else{
        Target.x = max(Target.x, AreaImg.x / 2);
        Target.y = max(Target.y, AreaImg.y / 2);
        Target.x = min(Target.x, Area.x - AreaImg.x / 2);
        Target.y = min(Target.y, Area.y - AreaImg.y / 2);
        Force = (Target - Position);
        if(norm(Force) < 400){
            Force = Itemize(Force) * 400;
        }
        Force.x /= min(Area.x, Area.y);
        Force.y /= min(Area.x, Area.y);
        check(Force);
        double a = norm(Force);
        Force = Itemize(Force) * min(0.5, norm(Force)) * min(Area.x, Area.y);
        // Force = Itemize(Force) * a * 500;
    }
    Force += Force0;
    // cerr << "Force0:(" << Force0.x << "," << Force0.y << ") " << endl;
    // Acceleration = Force - Itemize(Velocity) * min(norm(Velocity) / dt, Af);
    return Force - Itemize(Velocity) * min(norm(Velocity) / dt, Af);
    // cerr << "Acceleration = (" << Acceleration.x << "," << Acceleration.y << ")" << endl;
}

void userObject::calcVelocity(double t){
    Velocity += getAcceleration(t) * t; 
    // cerr << "Velocity = (" << Velocity.x << "," << Velocity.y << ")" << endl;
    // cerr << "Position = (" << Position.x << "," << Position.y << ")" << endl;
}

void userObject::invertX(){
    Velocity.x = -0.3 * Velocity.x;
}
void userObject::invertY(){
    Velocity.y = -0.3 * Velocity.y;
}

void userObject::addScore(int v){
	playSound(moneySound, 0);
    score += v;
}

int userObject::getScore(){
    return score;
}

bool userObject::die(){
	playSound(dieSound, 0);
    int tim = 10;
    int mx = 0;
    while(tim--){
        Point np = randPoint();
        double mi = INF;
        for(auto &x:DOG){
            mi = min(mi, norm(np - x -> getPosition()));
        }
        if(mi > mx){
            Position = np;
            mx = mi;
        }
        if(mx > 1000) break;
    }
    Velocity = 0;
    imgSiz = Point(0, 0);
    return --life == 0;
}

int userObject::getLife(){
    return life;
}

void userObject::addLife(){
    ++life;
}

void userObject::setState(int s){
    state = s;
    if(s){
        imgL = &tomSwordL;
        imgR = &tomSwordR;
    }
    else{
        imgL = &tomL;
        imgR = &tomR;
    }
}

int userObject::getState(){
    return state;
}

void userObject::setTarget(const Point &T){
    Target = T;
}

void userObject::onUP(){
    if(dcmp(Force0.y - (-0.45 * min(Area.x, Area.y))) != 0){
        Force0.y = -0.45 * min(Area.x, Area.y);
    }
}

void userObject::offUP(){
    if(dcmp(Force0.y - (-0.45 * min(Area.x, Area.y))) == 0){
        Force0.y = 0;
    }
}

void userObject::onDOWN(){
    if(dcmp(Force0.y - (0.45 * min(Area.x, Area.y))) != 0){
        Force0.y = 0.45 * min(Area.x, Area.y);
    }
}

void userObject::offDOWN(){
    if(dcmp(Force0.y - (0.45 * min(Area.x, Area.y))) == 0){
        Force0.y = 0;
    }
}

void userObject::onLEFT(){
    if(dcmp(Force0.x - (-0.45 * min(Area.x, Area.y))) != 0){
        Force0.x = -0.45 * min(Area.x, Area.y);
    }
}

void userObject::offLEFT(){
    if(dcmp(Force0.x - (-0.45 * min(Area.x, Area.y))) == 0){
        Force0.x = 0;
    }
}

void userObject::onRIGHT(){
    if(dcmp(Force0.x - (0.45 * min(Area.x, Area.y))) != 0){
        Force0.x = 0.45 * min(Area.x, Area.y);
    }
}

void userObject::offRIGHT(){
    if(dcmp(Force0.x - (0.45 * min(Area.x, Area.y))) == 0){
        Force0.x = 0;
    }
}
