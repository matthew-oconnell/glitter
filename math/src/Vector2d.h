#pragma once

namespace Glitter {
  namespace Math {
    struct Vec2d {
        float x;
        float y;

        inline void operator*=(float f){
            x *= f;
            y *= f;
        }

        inline void operator/=(float f){
            x /= f;
            y /= f;
        }

        inline Vec2d operator+(Vec2d rhs){
            return Vec2d{this->x + rhs.x, this->y + rhs.y};
        }

        inline Vec2d operator-(Vec2d rhs){
            return Vec2d{this->x - rhs.x, this->y - rhs.y};
        }
    };
    inline std::ostream& operator<<(std::ostream& stream, const Vec2d& obj) {
        stream<<obj.x<<" "; stream<<obj.y;
        return stream;
    }
  }
}