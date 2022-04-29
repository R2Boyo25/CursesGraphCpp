#include "../src/cgraph.hpp"
#include <curses.h>

int main() {
    initscr();
    curs_set(0);

    cgraph::PointGraph g = cgraph::PointGraph(stdscr);

    
    /*for (float i; i < 201; i++) {
        g.addPoint(1, i, 3);
        g.addPoint(1, i/2, 1);

        g.increment();
        g.draw();
    }*/

    for (int i = 0; i < 15; i++) {
        for (int e = 0; e < 10; e++) {
            g.addPoint(0, 10 - e, 2);
            g.increment();
            g.draw();
        }
        for (int e = 10; e > 0; e--) {
            g.addPoint(0, 10 - e, 3);
            g.increment();
            g.draw();
        }
    }

    refresh();

    getch();

    endwin();

    return 0;
}