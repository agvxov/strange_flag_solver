#include "StrangeFlag.hpp"
#include "StrangeFlag_Displayer.hpp"

#include <stdlib.h>
#include <string.h>

void StrangeFlag::direction_to_cord(const int x, const int y, const direction_t direction, int &new_x, int &new_y) {
    new_x = x;
    new_y = y;
    switch (direction) {
        case UP: {
            --new_x;
        } break;
        case DOWN: {
            ++new_x;
        } break;
        case LEFT: {
            --new_y;
        } break;
        case RIGHT: {
            ++new_y;
        } break;
    }

    if (new_x < 0
    ||  new_y < 0
    ||  new_x >= HEIGHT
    ||  new_y >= WIDTH) {
        throw 1;
    }
}

StrangeFlag::tile_t StrangeFlag::map(int x, int y) {
    if (x >= 0
    &&  y >= 0
    &&  x <  HEIGHT
    &&  y <  WIDTH) {
        return map_m[x][y];
    } else {
        return FULL;
    }
}

bool StrangeFlag::is_goal() {
    tile_t goal[HEIGHT][WIDTH] = {
        {RED, RED, RED},
        {FULL, BLANK, FULL},
        {BLANK, BLANK, FULL},
        {FULL, BLANK, FULL},
        {GREEN, GREEN, GREEN},
    };
    return !memcmp(map_m, goal, sizeof(tile_t) * HEIGHT * WIDTH);
}

StrangeFlag * StrangeFlag::copy() {
    StrangeFlag * r = new StrangeFlag;
    memcpy(r, this, sizeof(tile_t) * HEIGHT * WIDTH);
    return r;
}

void StrangeFlag::apply_operator(int x, int y, direction_t direction) {
    if (not is_operation(x, y, direction)) {
        throw 1;
    }

    int new_x, new_y;
    direction_to_cord(x, y, direction, new_x, new_y);
    tile_t swp = map_m[new_x][new_y];
    map_m[new_x][new_y] = map_m[x][y];
    map_m[x][y] = swp;
}

bool StrangeFlag::is_operation(int x, int y, direction_t direction) {
    if (map_m[x][y] != GREEN
    &&  map_m[x][y] != RED) {
        return false;
    }

    int new_x, new_y;
    try {
        direction_to_cord(x, y, direction, new_x, new_y);
    } catch (...) {
        return false;
    }

    return map_m[new_x][new_y] == BLANK;
}

size_t StrangeFlag::solve(size_t max, StrangeFlag_Displayer * displayer) {
    displayer->display_state(this);
    size_t steps = 1;
    for (size_t tries = 0; !is_goal() && steps <= max; tries++) {
        int x = rand() % HEIGHT;
        int y = rand() % WIDTH;
        int d = rand() % DIRECTION_END;
        try {
            apply_operator(x, y, (direction_t)d);
        } catch (...) {
            displayer->display_fail(steps, tries);
            continue;
        }
        ++steps;
        displayer->display_state(this);
    }

    bool is_success = is_goal();
    displayer->display_result(is_success, steps);
    return (is_success ? steps : 0);
}

