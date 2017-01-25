#ifndef _point_h_
#define _point_h_


class Point {

public:
    float x,y,z;    

    Point();

    Point(const float x, const float y, const float z);


};

Point median(Point a, Point b);


#endif