#include <cstddef>
#include <curses.h>
#include "point.hpp"
#include <vector>
#include <string>
#include <cmath>

namespace cgraph {
    class PointGraph {
        public:
            PointGraph(WINDOW* wind, std::vector<point::Point> points = {});
            void addPoint(float x, float y, int color = 0);
            void increment(float amt = 1, bool crop = true);
            void draw(bool l = true);

        private:
            WINDOW* wind;
            std::vector<point::Point> points;
            std::vector<int> wdim;
            float getMax(std::vector<point::Point> points, std::string axis = "y");
            float getMin(std::vector<point::Point> points, std::string axis = "y");
            float rng(std::vector<point::Point> points,    std::string axis = "y");
            float fit(float num, float wd, float mx, float mn);
            void drawPoint(point::Point pnt, std::vector<point::Point> points, std::vector<int> wd, bool l = true);
    };
}