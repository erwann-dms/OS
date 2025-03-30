// gui/window.c
#include "gui.h"
#include "../drivers/vesa.h"

void draw_window(window *win) {
    // Dessine le cadre
    for (int x = win->x; x < win->x + win->width; x++) {
        draw_pixel(x, win->y, 0x00FFFFFF);  // Bordure blanche
        draw_pixel(x, win->y + win->height, 0x00FFFFFF);
    }
    // ... (compléter avec le remplissage)
}

void create_window(int x, int y, int w, int h, const char *title) {
    window *win = &windows[window_count++];
    win->x = x; win->y = y;
    win->width = w; win->height = h;
    strcpy(win->title, title);
    draw_window(win);
}