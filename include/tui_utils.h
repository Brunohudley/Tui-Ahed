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
#include <wchar.h>


void clear_screen();

void set_cursor_pos(
    int x_pos,
    int y_pos
);

void tui_get_mouse_state(
    int* x_pos,
    int* y_pos,
    bool* mouse_click
);

void tui_set_raw_mode(
    DWORD* console_mode
);

void tui_unset_raw_mode(
    DWORD console_mode
);

wchar_t tui_get_input();
