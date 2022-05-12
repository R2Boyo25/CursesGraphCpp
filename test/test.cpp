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
        for (int e = 0; e < 10; e++) {
            g.addPoint(0, 10 - e, 2);
            g.increment(1);
            g.draw();
        }
        for (int e = 10; e > 0; e--) {
            g.addPoint(0, 10 - e, 3);
            g.increment(1);
            g.draw();
        }
    }

    while (true) {
        erase();
        g.draw();
        refresh();

        usleep(500);
    }

    return 0;
}