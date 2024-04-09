#include "tcl_displayer.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <tcl.h>
#include <tk.h>

int ree = 0;

Tcl_Interp * interp;

Tcl_color_t grid[5][3];

void tcl_set_tile(int x, int y, Tcl_color_t color) {
    grid[x][y] = color;
}

void tcl_display_fail(const size_t steps, const size_t tries) { ; }

void tcl_display_result(const bool is_success, const size_t steps) {
    if (!is_success) {
        return;
    }
    char * r;
    asprintf(&r, "Found a solution in %d steps.", steps);
    Tcl_SetVar(interp, "message", r, 0); 
    free(r);
}

const char * color_t2str(Tcl_color_t color) {
    const char * lookup_table[] = {
        [GRAY]  = "gray",
        [WHITE] = "white",
        [RED]   = "red",
        [GREEN] = "green",
    };
    return lookup_table[color];
}

int Tcl_cUpdateDisplay(ClientData clientData, Tcl_Interp *interp, int argc, char **argv) {
    char value[] = "colorIH";
    int I_POS = 5;
    int H_POS = 6;
    for (char i = '0'; i < '5'; i++) {
        value[I_POS] = i;
        for (char h = '0'; h < '3'; h++) {
            value[H_POS] = h;
            Tcl_SetVar(interp, value, color_t2str(grid[i - '0'][h - '0']), 0); 
        }
    }
    return TCL_OK;
}

void tcl_run(void) {
    interp = Tcl_CreateInterp();
    if (interp == NULL) {
        fprintf(stderr, "Can't creae Tcl interpreter\n");
        exit(1);
    }
    Tk_Init(interp);
    int result = Tcl_EvalFile(interp, "gui.tcl");
    if (result == TCL_ERROR) {
        fprintf(stderr, "Tcl script execution failed: %s\n", Tcl_GetStringResult(interp));
        exit(1);
    }
    Tcl_CreateCommand(interp, "cUpdateDisplay", Tcl_cUpdateDisplay, (ClientData)NULL, (void (*)())NULL);
    Tk_MainLoop();
}

void tcl_setup() {
    pthread_t tcl_thread;
    pthread_create(&tcl_thread, NULL, tcl_run, NULL);
}
