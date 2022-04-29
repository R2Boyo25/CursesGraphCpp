#include "cgraph.hpp"

namespace cgraph {
    PointGraph::PointGraph(WINDOW* wind, std::vector<point::Point> points) {
        use_default_colors();
        for (int i = 1; i <= 8; i++) {
            init_pair(i, i, i);
        }

        this->wind = wind;
        this->points = points;
        this->wdim = {10, 10};
    }

    float PointGraph::getMax(std::vector<point::Point> points, std::string axis) {
        int curmax = 0;

        for (point::Point& point : points) {
            if (point.y > curmax) {
                if (axis == "x") {
                    curmax = point.x;
                } else {
                    curmax = point.y;
                }
            }
        }

        return curmax;
    }

    float PointGraph::getMin(std::vector<point::Point> points, std::string axis) {
        int curmin = 0;

        for (point::Point& point : points) {
            if (point.y < curmin) {
                if (axis == "x") {
                    curmin = point.x;
                } else {
                    curmin = point.y;
                }
            }
        }

        return curmin;
    }

    float PointGraph::rng(std::vector<point::Point> points, std::string axis) {
        return std::abs(this->getMax(points, axis) - this->getMin(points, axis));
    }

    float PointGraph::fit(float num, float wd, float mx, float mn) {
        if ((mx - mn) == 0) {
            return 0;
        } else {
            return (int)std::round(((num - mn) / (mx - mn)) * wd);
        }
    }

    void PointGraph::drawPoint(point::Point pnt, std::vector<point::Point> points, std::vector<int> wd, bool l) {
        int wx = wd[0];
        int wy = wd[1];

        float x = this->fit(pnt.x, wx, this->getMax(points, "x"), this->getMin(points, "x"));
        float y = this->fit(pnt.y, wy, this->getMax(points, "y"), this->getMin(points, "y"));

        float mx = this->getMax(points, "x");
        if (mx < wx) {
            x = pnt.x;
        }

        if (x > wx) {
            pnt.rem = true;
        }

        if (l) {
            for (int i; i <= y; i++) {
                wattrset(this->wind, COLOR_PAIR(pnt.color));
                auto e = mvwaddch(this->wind, wy - i, wx - x, 'a');
            }
        } else {
            wattrset(this->wind, COLOR_PAIR(pnt.color));
            auto e = mvwaddch(this->wind, wy - y, wx - x, 'A');
        }
    }

    void PointGraph::addPoint(float x, float y, int color) {
        this->points.push_back(point::Point(x, y, color));
    }

    void PointGraph::increment(float amt, bool crop) {
        for (int i; i <= this->points.size(); i++) {
            points[i].x += amt;

            if (crop) {
                if (points[i].x > this->wdim[0]) {
                    this->points.erase(this->points.begin() + i);
                }
            }
        }
    }

    void PointGraph::draw(bool l) {
        werase(this->wind);
        int my = getmaxy(this->wind);
        int mx = getmaxx(this->wind);
        this->wdim = {mx, my};

        std::vector<point::Point> points = this->points;

        for (auto point : points) {
            this->drawPoint(point, points, this->wdim, l);
        }

        wrefresh(this->wind);
    }

    std::vector<point::Point> PointGraph::getPoints() {
        return this->points;
    }
}