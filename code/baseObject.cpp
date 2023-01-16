#include "baseObject.h"
#include <unordered_set>
using namespace std;

extern unordered_set<baseObject*> ALL;

baseObject:: baseObject(Point P, Vec V, ACL_Image* imgL, ACL_Image* imgR): Position(P), Velocity(V), imgL(imgL), imgR(imgR), img(imgR), imgSiz(0,0) {
    ALL.insert(this);
}

baseObject::~baseObject(){
    ALL.erase(this);
}

Point baseObject::getPosition(){
    return Position;
}

Point baseObject::getVelocity(){
    return Velocity;
}

Point baseObject::getP1() const{
    return Position - imgSiz / 2;
}

Point baseObject::getP2() const{
    return Position + imgSiz / 2;
}

void baseObject::invertX(){
    Velocity.x = -Velocity.x;
    // if(type == 0) Velocity.x *= 0.3;
}
void baseObject::invertY(){
    Velocity.y = -Velocity.y;
    // if(type == 0) Velocity.y *= 0.3;
}

void baseObject::print(){
    if(Velocity.x < -10) img = imgL;
    if(Velocity.x >  10) img = imgR;

    putImageTransparent(img, Position.x - imgSiz.x / 2, Position.y - imgSiz.y / 2, imgSiz.x, imgSiz.y, WHITE);
}

void baseObject::sizUpdate(double t){
    if(dcmp(imgSiz.x - AreaImg.x) < 0){ // 0.5s 生成
        imgSiz += AreaImg * t / 0.5;
    }
}

void baseObject::update(double t){
    calcVelocity(t);
    move(t);
    sizUpdate(t);
}

void baseObject::move(double t){
    if((dcmp(Position.x - imgSiz.x / 2) <= 0 && Velocity.x < 0) || (dcmp(Position.x - (Area.x - imgSiz.x / 2)) >= 0 && Velocity.x > 0)){
        invertX();
    }
    if((dcmp(Position.y - imgSiz.y / 2) <= 0 && Velocity.y < 0) || (dcmp(Position.y - (Area.y - imgSiz.y / 2)) >= 0 && Velocity.y > 0)){
        invertY();
    }
    check(Velocity);
    Position += Velocity * t;
    Position.x = max(Position.x, imgSiz.x / 2);
    Position.y = max(Position.y, imgSiz.y / 2);
    Position.x = min(Position.x, Area.x - imgSiz.x / 2);
    Position.y = min(Position.y, Area.y - imgSiz.y / 2);
}

bool collision(baseObject* A, baseObject* B){
    return intersect(A -> getP1(), A -> getP2(), B -> getP1(), B -> getP2());
}
