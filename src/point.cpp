#include "point.hpp"

namespace point {
    Point::Point(float x , float y, int color) {
        this->x     = x;
        this->y     = y;
        this->color = color;
    }

    int Point::operator > (Point o) {
        return this->y > o.y;
    }
}