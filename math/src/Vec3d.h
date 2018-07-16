#pragma once
#include <iostream>

namespace Glitter {
  namespace Math {
    struct Vec3d {
        float x, y, z;
        inline void operator*=(float f){
            x *= f;
            y *= f;
            z *= f;
        }

        inline void operator/=(float f){
            x /= f;
            y /= f;
            z /= f;
        }

        inline Vec3d operator+(Vec3d rhs){
            return Vec3d{
                this->x+rhs.x,
                this->y+rhs.y,
                this->z+rhs.z};
        }

        inline Vec3d operator-(Vec3d rhs){
            return Vec3d{
                    this->x-rhs.x,
                    this->y-rhs.y,
                    this->z-rhs.z};
        }
    };
    std::ostream& operator<<(std::ostream& stream,const Vec3d& obj) {
        stream<<obj.x<<" ";
        stream<<obj.y<<" ";
        stream<<obj.z;
        return stream;
    }
  }
}

