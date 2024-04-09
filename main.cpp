#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "StrangeFlag.hpp"
#include "StrangeFlag_Displayer.hpp"
extern "C" {
    #include "tcl_displayer.h"
}

class StrangeFlag_Printer : public StrangeFlag_Displayer {
    const char * tile2str(StrangeFlag::tile_t t) {
        switch (t) {
            case StrangeFlag::BLANK:
                return " ";
            case StrangeFlag::RED:
                return "\033[31mR\033[0m";
            case StrangeFlag::GREEN:
                return "\033[32mG\033[0m";
            case StrangeFlag::FULL:
                return "#";
        }
        return "";
    }
public:
    void display_state(StrangeFlag * f) {
        for (int i = 0; i < f->HEIGHT; i++) {
            for (int h = 0; h < f->WIDTH; h++) {
                printf("[%s]", tile2str(f->map(i, h)));
            }
            puts("");
        }
        puts("");
    }

    void display_fail(const size_t steps, const size_t tries) {
        printf("\033[36m[Invalid attempt (%ld|%ld)]\033[0m\n\n", steps, tries);
    }

    void display_result(const bool is_success, const size_t steps) {
        if (is_success) {
            printf("\033[32mSolved in %ld steps.\033[0m\n", steps);
        } else {
            printf("\033[31mMission failed, we'll get em next time.\033[0m\n");
        }
    }
};

class StrangeFlag_tk : public StrangeFlag_Displayer {
public:
    StrangeFlag_tk() {
        tcl_setup();
    }

    void display_state(StrangeFlag * f) {
        for (int i = 0; i < f->HEIGHT; i++) {
            for (int h = 0; h < f->WIDTH; h++) {
                Tcl_color_t color;
                switch(f->map(i, h)) {
                    case StrangeFlag::FULL:
                        color = GRAY;
                        break;
                    case StrangeFlag::BLANK:
                        color = WHITE;
                        break;
                    case StrangeFlag::RED:
                        color = RED;
                        break;
                    case StrangeFlag::GREEN:
                        color = GREEN;
                        break;
                }
                tcl_set_tile(i, h, color);
            }
        }
    }

    void display_fail(const size_t steps, const size_t tries) {
        tcl_display_fail(steps, tries);
    }

    void display_result(const bool is_success, const size_t steps) {
        tcl_display_result(is_success, steps);
    }
};

void setup() {
}

#define CONSOLE 1
#define TK 2
#define DISPLAY TK

signed main() {
    setup();
    srand(time(NULL));

    const size_t max_tries =
        //1'000'000
        //100'000
        //10'000
        //7'000
        3'000
    ;
    
  #if DISPLAY == CONSOLE
    StrangeFlag_Printer printer;
    StrangeFlag_Displayer &displayer = printer;
  #elif DISPLAY == TK
    StrangeFlag_tk tk;
    StrangeFlag_Displayer &displayer = tk;
  #endif

    while (true) {
        StrangeFlag f;
        size_t steps = f.solve(max_tries, &displayer);
        if (steps) {
            break;
        }
    }

    while (true) { ; }
}
