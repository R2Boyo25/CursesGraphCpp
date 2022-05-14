#include "../src/cgraph.hpp"
#include <curses.h>
#include <signal.h>
#include <unistd.h>

void catchSigInt(int signum) {
    endwin();

    exit(signum);
}

int main() {
    initscr();
    curs_set(0);
    signal(SIGINT, catchSigInt);

    cgraph::PointGraph g = cgraph::PointGraph(stdscr);

    for (int i = 0; i < 15; i++) {
        for (int e = 0; e < 11; e++) {
            g.addPoint(0, 11 - e, 1);
            if (10 - e - 5 > 0 ) {
                g.addPoint(0, 10 - e - 5, 3);
            }
            g.increment(1);
            g.draw();
        }
        for (int e = 11; e > 0; e--) {
            g.addPoint(0, 12 - e, 2);
            if (11 - e - 5 > 0 ) {
                g.addPoint(0, 11 - e - 5, 3);
            }
            g.increment(1);
            g.draw();
        }
    }

    //g.addPoint(5, -5, 5);

    while (true) {
        erase();
        g.draw();
        refresh();

        usleep(500);
    }

    return 0;
}