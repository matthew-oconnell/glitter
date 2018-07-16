#pragma once

namespace Glitter {
  namespace Math {
    struct Vector3d {
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

        inline Vector3d operator+(Vector3d rhs){
            return Vector3d{
                this->x+rhs.x,
                this->y+rhs.y,
                this->z+rhs.z};
        }

        inline Vector3d operator-(Vector3d rhs){
            return Vector3d{
                    this->x-rhs.x,
                    this->y-rhs.y,
                    this->z-rhs.z};
        }
    };
  }
}

