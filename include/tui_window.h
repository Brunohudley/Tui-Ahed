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

typedef struct tui_window_fill
{
    int inside_fg, inside_bg;
    int outside_fg, outside_bg;
}tui_window_fill_t;


typedef struct tui_container_shadow
{
    int fg_color, bg_color;
    wchar_t ch;
}tui_container_shadow_t;


typedef struct tui_container_tittle
{
    int title_padding;
    wchar_t* title;
}tui_container_tittle_t;
