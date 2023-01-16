#ifndef _GEO_H
#define _GEO_H

#include<bits/stdc++.h>

const double eps = 1e-6;
const double PI = acos(-1.0);

class Point{
    public:
    double x,y;
    
    Point();
    Point(const double &alpha);
    Point(const double &x ,const double &y);
    
};

int dcmp(const double &x);

#define Vec Point

Vec operator +(const Vec &a, const Vec &b);

Vec operator -(const Vec &a,const Vec &b);

void operator +=(Vec &a, const Vec &b);
void operator -=(Vec &a, const Vec &b);

Vec operator *(const Vec &a, const double &b);

Vec operator *(const double &b, const Vec &a);

void operator *=(Vec &a, const double &b);

Vec operator /(const Vec &a, const double &b);

void operator /=(Vec &a, const double &b);

double Cross(const Vec &a, const Vec &b);

double Dot(const Vec &a, const Vec &b);

Vec Rotate(const Vec &a);

double norm(const Vec &a);

Vec Itemize(const Vec &a);

double Angle(const Vec &a);

void check(Vec &a);

bool intersect(const Point &A,const Point &B, const Point &C, const Point &D);

#endif