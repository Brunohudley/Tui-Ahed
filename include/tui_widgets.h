// ============================================================================
// Copyright (c) 2026 Brunohudley. All rights reserved.
//
// This code is free software: you can redistribute it and/or modify it 
// under the terms of the MIT License. The above copyright notice must be 
// included in all copies or substantial portions of the software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
// ============================================================================

#pragma once

#include <wchar.h>
#include <stdbool.h>

#include "tui_window.h"


typedef struct tui_screen_buffer screen_buffer_t;


typedef struct tui_window
{
    tui_container_shadow_t window_shadow;
    tui_container_tittle_t container_tittle;
    tui_window_fill_t tui_window_fill;

    int min_x_coord, min_y_coord;
    int max_x_coord, max_y_coord;

    wchar_t vertical_arrow;
    wchar_t horizontal_arrow;

    bool has_shadow;
    bool is_active;
}tui_window_t;


typedef struct tui_button
{
    tui_container_shadow_t tui_shadow;
    tui_window_fill_t tui_button_fill;

    int min_x_coord, min_y_coord;
    int max_x_coord, max_y_coord;

    wchar_t* label;

    bool (*on_click)(
        struct tui_button* tui_button,
        int x_mouse,
        int y_mouse,
        bool mouse_click
    );

    bool has_shadow;
    bool is_active;
}tui_button_t;


typedef struct tui_check_box
{
    int min_x_coord, min_y_coord;
    int max_x_coord, max_y_coord;

    int fg_color, bg_color;

    wchar_t check_box_ch;
    wchar_t* label;

    void (*on_click)(
        struct tui_check_box* tui_check_box,
        int x_mouse,
        int y_mouse,
        wchar_t check_sign,
        bool mouse_click
    );

    bool is_active;
}tui_check_box_t;


typedef struct tui_input_box
{
    tui_window_fill_t tui_input_fill;

    int min_x_coord, min_y_coord;
    int max_x_coord, max_y_coord;

    wchar_t* text;
    int text_length;
    int max_characters;

    wchar_t* placeholder;
    int placeholder_fg;

    void (*on_click)(
        struct tui_input_box* tui_input_box,
        int x_mouse,
        int y_mouse,
        bool mouse_click
    );

    bool is_focused;
    bool is_active;
}tui_input_box_t;


void tui_create_window(
    screen_buffer_t* screen_buffer,
    tui_window_t* tui_window
);

void tui_create_button(
    screen_buffer_t* screen_buffer,
    tui_button_t* tui_button
);

void tui_create_check_box(
    screen_buffer_t* screen_buffer,
    tui_check_box_t* tui_check_box
);

void tui_create_input_box(
    screen_buffer_t* screen_buffer,
    tui_input_box_t* tui_input_box
);
