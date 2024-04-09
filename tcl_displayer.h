#ifndef TCL_DISPLAYER_H
#define TCL_DISPLAYER_H
#include <tcl.h>
#include <stdbool.h>

typedef enum {
    GRAY,
    WHITE,
    RED,
    GREEN,
} Tcl_color_t;

extern Tcl_Interp * interp;

void tcl_setup();

void tcl_set_tile(int x, int y, Tcl_color_t color);

void tcl_display_fail(const size_t steps, const size_t tries);

void tcl_display_result(const bool is_success, const size_t steps);

#endif
