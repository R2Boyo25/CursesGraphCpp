#include "cgraph.hpp"

namespace cgraph {
    PointGraph::PointGraph(WINDOW* wind, std::vector<point::Point> points) {
        start_color();
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
        float y;

        if (this->getMin(points, "y") < 0) {

            y = this->fit(pnt.y, wy - 1, this->getMax(points, "y"), this->getMin(points, "y"));

        } else {
            y = this->fit(pnt.y, wy - 1, this->getMax(points, "y"), this->getMin(points, "y"));

            // TODO: fix negative numbers for y.

            //y = this->fit(pnt.y - this->getMin(points, "y") + 1, wy - 1, this->getMax(points, "y") - this->getMin(points, "y") + 1, this->getMin(points, "y") - this->getMin(points, "y") + 1);
        }

        float mx = this->getMax(points, "x");
        if (mx < wx) {
            x = pnt.x;
        }
        
        x = x + maxLength + 1;

        if (x > wx) {
            pnt.rem = true;
        }

        if (l) {
            for (int i; i < y; i++) {
                wattron(this->wind, COLOR_PAIR(pnt.color));
                auto e = mvwaddch(this->wind, wy - i - 2 , wx - x, ACS_BLOCK);
                wattroff(this->wind, COLOR_PAIR(pnt.color));
            }
        } else {
            wattron(this->wind, COLOR_PAIR(pnt.color));
            auto e = mvwaddch(this->wind, wy - y, wx - x, ACS_BLOCK);
            wattroff(this->wind, COLOR_PAIR(pnt.color));
        }
    }

    int followingZeros(std::string numstr) {
        int i = 0;
        while (numstr[numstr.size() - (i + 1)] == '0') {
            i++;
        }

        if (numstr[numstr.size() - (i + 1)] == '.') {
            i++;
        }

        return i;
    }

    std::string cleanFloat(std::string num) {
        std::string nnum = num;
        for (int i = followingZeros(num); i != 0; i--) {
            nnum.erase(nnum.size()-1);
        }

        return nnum;
    }

    float median(std::vector<point::Point> v) {
        std::sort(v.begin(), v.end(), [](point::Point a, point::Point b) {
            return a.y > b.y;
        });
        
        if (v.size() % 2 == 0) {
            return (v[v.size()/2 - 1].y + v[v.size()/2].y) / 2;
        } else {
            return v[v.size()/2].y;
        }
    }

    float mean(std::vector<point::Point> v) {
        float sum = 0;

        for (auto& p: v) {
            sum += p.y;
        }

        return sum / v.size();
    }

    void PointGraph::updateMaxLength() {
        int maxlen = 0;
        for (auto& point : points) {
            int l = cleanFloat(std::to_string(point.y)).size();

            if (l > maxlen) {
                maxlen = l;
            }
        }

        maxLength = maxlen;
    }

    void PointGraph::addPoint(float x, float y, int color) {
        this->points.push_back(point::Point(x, y, color));
        this->updateMaxLength();
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

    void PointGraph::drawLabels() {
        int my = getmaxy(this->wind);

        mvwaddstr(this->wind, my - 1, 0, "Median: ");
        waddstr(this->wind, cleanFloat(std::to_string(median(this->points))).c_str());
        waddstr(this->wind, " Mean: ");
        waddstr(this->wind, cleanFloat(std::to_string(mean(this->points))).c_str());
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

        this->drawLabels();

        //mvwaddstr(this->wind, 0, 0, cleanFloat(std::to_string(maxLength)).c_str());

        wrefresh(this->wind);
    }

    std::vector<point::Point> PointGraph::getPoints() {
        return this->points;
    }

    void PointGraph::setStatistics(bool s) {
        this->statistics = s;
    }
}