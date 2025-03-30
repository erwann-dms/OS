// gui/gui.h
#pragma once

typedef struct {
    int x, y, width, height;
    char title[32];
} window;

window windows[10];
int window_count = 0;