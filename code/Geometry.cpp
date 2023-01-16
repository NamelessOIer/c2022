#include "Geometry.h"

Point::Point(void) : x(0), y(0){}
Point::Point(const double &alpha) : x(cos(alpha)), y(sin(alpha)) {}
Point::Point(const double &x ,const double &y) : x(x), y(y) {}

int dcmp(const double &x){
    if(fabs(x) <= eps) return 0;
    return x > 0 ? 1 : -1;
}

#define Vec Point

Vec operator +(const Vec &a, const Vec &b){
    return Vec(a.x + b.x, a.y + b.y);
}

Vec operator -(const Vec &a,const Vec &b) {
    return Vec(a.x - b.x, a.y - b.y);
}

void operator +=(Vec &a, const Vec &b){
    a.x += b.x, a.y += b.y;
}

void operator -=(Vec &a, const Vec &b){
    a.x -= b.x, a.y -= b.y;
}

Vec operator *(const Vec &a, const double &b){
    return Vec(a.x * b, a.y * b);
}

Vec operator *(const double &b, const Vec &a){
    return Vec(a.x * b, a.y * b);
}

void operator *=(Vec &a, const double &b){
    a.x *= b, a.y *= b;
}

Vec operator /(const Vec &a, const double &b){
    return Vec(a.x / b, a.y / b);
}

void operator /=(Vec &a, const double &b){
    a.x /= b, a.y /= b;
}

double Cross(const Vec &a, const Vec &b){
    return a.x * b.y - a.y * b.x;
}

double Dot(const Vec &a, const Vec &b){
    return a.x * b.x + a.y * b.y;
}

Vec Rotate(const Vec &a){
    return Vec(-a.y, a.x);
}

double norm(const Vec &a){
    return sqrt(a.x * a.x + a.y * a.y);
}

Vec Itemize(const Vec &a){
    if(dcmp(norm(a)) == 0) return Point(0, 0);
    return a / norm(a);
}

double Angle(const Vec &a){
    return atan2(a.y, a.x);
}

void check(Vec &a){
    if(dcmp(a.x) == 0) a.x = 0;
    if(dcmp(a.y) == 0) a.y = 0;
}

bool intersect(const Point &A,const Point &B, const Point &C, const Point &D){
    if(B.x <= C.x || A.x >= D.x) return 0;
    if(B.y <= C.y || A.y >= D.y) return 0;
    return 1;
}
