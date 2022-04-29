#include "../src/cgraph.hpp"
#include <curses.h>

int main() {
    initscr();
    curs_set(0);

    cgraph::PointGraph g = cgraph::PointGraph(stdscr);

    for (float i; i < 201; i++) {
        g.addPoint(0, i, 3);
        g.addPoint(0, i/2, 1);

        g.increment();
        g.draw();
    }

    g.addPoint(1, 5, 1);
    g.addPoint(2, 2, 2);
    //g.increment();
    g.draw();

    refresh();

    getch();

    endwin();

    return 0;
}