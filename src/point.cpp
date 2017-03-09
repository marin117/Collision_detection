#include "point.h"

Point::Point(){
        this->x=0;
        this->y=0;
        this->z=0;

    }

Point::Point(const float x, const float y, const float z){
        this->x=x;
        this->y=y;
        this->z=z;

}

Point operator-(const Point& lhs, const Point& rhs){

    return Point(lhs.x-rhs.x,lhs.y-rhs.y,lhs.z-rhs.z);

}


Point median(Point a, Point b){
    Point center;

    center.x=(a.x+b.x)/2;
    center.y=(a.y+b.y)/2;
    center.z=(a.y+b.y)/2;

    return center;
}
