#include "AABB_box.h"
#include <cmath>
#include <algorithm>


AABB_box::AABB_box(const float x,const float y,const float z,const float r){
         center.x=x;
         center.y=y;
         center.z=z;
         this->r[0]=r;
         this->r[1]=r;
         this->r[2]=r;
}

AABB_box::AABB_box(const Point center,const float r){
        this->center=center;
        this->r[0]=r;
        this->r[1]=r;
        this->r[2]=r;



}

float AABB_box::getSurface(){

    return r[0]*r[1]*r[2];
}
     
AABB_box& AABB_box::operator=(const AABB_box& src){
        this->center = src.center;
        this->r[0]=src.r[0];
        this->r[1]=src.r[1];
        this->r[2]=src.r[2];

        return *this;
}



bool isOverlap(AABB_box a, AABB_box b){


    if (((std::abs(a.center.x-b.center.x)>(a.r[0]+b.r[0]))
    || (std::abs(a.center.y-b.center.y)>(a.r[1]+b.r[1]))
    || (std::abs(a.center.z-b.center.z)>(a.r[2]+b.r[2])))) return false;

    return true;
}

AABB_box Combine(AABB_box a, AABB_box b){

    //typedef std::pow pow;

    float dist = std::sqrt(pow(a.center.x-b.center.x,2)+
                           pow(a.center.y-b.center.y,2)+
                           pow(a.center.z-b.center.z,2))+
                  std::abs(std::max(a.r[0],b.r[0]));

    AABB_box combined(median(a.center,b.center),dist);

    return combined;
}
