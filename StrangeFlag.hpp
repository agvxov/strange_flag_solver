#ifndef STRAGEFLAG_HPP
#define STRAGEFLAG_HPP
#include <stddef.h>

class StrangeFlag_Displayer;

class StrangeFlag {
public:
    static const int HEIGHT = 5;
    static const int WIDTH  = 3;

    typedef enum {
        UP,
        DOWN,
        RIGHT,
        LEFT,
        DIRECTION_END,
    } direction_t;

    typedef enum {
        BLANK,
        RED,
        GREEN,
        FULL,
        TILE_END,
    } tile_t;

private:
    tile_t map_m[HEIGHT][WIDTH] = {
        {GREEN, GREEN, GREEN},
        {FULL, BLANK, FULL},
        {BLANK, BLANK, FULL},
        {FULL, BLANK, FULL},
        {RED, RED, RED},
    };
    
    void direction_to_cord(const int x, const int y, const direction_t direction, int &new_x, int &new_y);

public:
    StrangeFlag * copy();

    tile_t map(int x, int y);
    bool is_goal();
    void apply_operator(int x, int y, direction_t direction);
    bool is_operation(int x, int y, direction_t direction);
    size_t solve(size_t max, StrangeFlag_Displayer * displayer);
};
#endif
