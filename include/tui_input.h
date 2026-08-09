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


typedef struct tui_input_box tui_input_box_t;


void get_input_box_event(
    tui_input_box_t* tui_input_box,
    int x_mouse,
    int y_mouse,
    bool mouse_click
);
