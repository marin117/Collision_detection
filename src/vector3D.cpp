#include "vector3D.h"


Vector3D::Vector3D(float x, float y, float z){

    this->vec.reserve(3);
    this->setX(x);
    this->setY(y);
    this->setZ(z);

}

Vector3D::Vector3D (Point point){
    this->vec.reserve(3);
    this->setX(point.x);
    this->setY(point.y);
    this->setZ(point.z);

}


Vector3D Vector3D:: operator* (float const& scalar){

    return Vector3D(this->x()*scalar,this->y()*scalar,this->z()*scalar);
}

Vector3D Vector3D:: operator- (Vector3D& rhs ){

    return Vector3D(this->x()-rhs.x(),this->y()-rhs.y(),this->z()-rhs.z());
}

Vector3D Vector3D::normal(){
    float mag = std::sqrt(std::pow(this->x(),2) + std::pow(this->y(),2) + std::pow(this->z(),2));

    return Vector3D(this->x()/mag,this->y()/mag,this->z()/mag);

}
