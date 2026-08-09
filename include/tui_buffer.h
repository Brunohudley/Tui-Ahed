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

#include <windows.h>
#include <stdbool.h>
#include <stdint.h>
#include <wchar.h>

typedef struct
{
    wchar_t ch;
    uint8_t fg_color;
    uint8_t bg_color;
}screen_cell_t;


typedef struct tui_screen_buffer
{
    int width;
    int height;

    screen_cell_t *front_screen_cell;
    screen_cell_t *back_screen_cell;
}screen_buffer_t;


screen_buffer_t* create_screen_buffer(int width, int height);

void destroy_screen_buffer(screen_buffer_t* screen_buffer);

void set_buffer_cell(
    screen_buffer_t* screen_buffer,
    int width,
    int height,
    int fg,
    int bg,
    wchar_t ch
);

void set_string_buffer_cell(
    screen_buffer_t* screen_buffer,
    int width,
    int height,
    int fg,
    int bg,
    wchar_t* str
);

int resize_screen_buffer(
    screen_buffer_t* screen_buffer,
    int new_width,
    int new_height
);

void fill_screen_buffer(
    screen_buffer_t* screen_buffer,
    int fg,
    int bg,
    wchar_t new_ch
);

void copy_screen_buffer(
    screen_buffer_t* source_buffer,
    screen_buffer_t* destine_buffer
);

void tui_render_buffer(screen_buffer_t* screen_buffer);
