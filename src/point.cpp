#include "point.hpp"
#include <string>

namespace point {
    Point::Point(float x , float y, int color) {
        this->x     = x;
        this->y     = y;
        this->color = color;
    }

    int Point::operator > (Point o) {
        return this->y > o.y;
    }

    int Point::operator < (Point o) {
        return this->y < o.y;
    }

    std::string Point::toString() {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
    }
}