#include "avoidObject.h"
#include "userObject.h"

using namespace std;

extern userObject *user;

avoidObject::avoidObject(Point P, Vec V, int d, int v, ACL_Image* imgL, ACL_Image* imgR): normalObject(P, V, v, imgL, imgR), Limit(d){}

void avoidObject::move(double t){
    if((dcmp(Position.x - imgSiz.x / 2 + 200) <= 0 && Velocity.x < 0) || (dcmp(Position.x - (Area.x - imgSiz.x / 2) - 200) >= 0 && Velocity.x > 0)){
        invertX();
    }
    if((dcmp(Position.y - imgSiz.y / 2 + 200) <= 0 && Velocity.y < 0) || (dcmp(Position.y - (Area.y - imgSiz.y / 2) - 200) >= 0 && Velocity.y > 0)){
        invertY();
    }
    check(Velocity);
    Position += Velocity * t;
    Position.x = max(Position.x, imgSiz.x / 2 - 200);
    Position.y = max(Position.y, imgSiz.y / 2 - 200);
    Position.x = min(Position.x, Area.x - imgSiz.x / 2 + 200);
    Position.y = min(Position.y, Area.y - imgSiz.y / 2 + 200);
}

void avoidObject::calcVelocity(double t){
    if(norm(user -> getPosition() - Position) < Limit){
        double alpha = sqrt(1 - norm(user -> getPosition() - Position) / Limit);
        Velocity = norm(Velocity) * Itemize((alpha * Itemize(Position - user -> getPosition()) + (1 - alpha) * Itemize(Velocity)));
    }
}
