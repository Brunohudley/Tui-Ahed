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

#include <stdbool.h>
#include <wchar.h>


typedef struct tui_check_box tui_check_box_t;


void tui_check_list_click(
    tui_check_box_t* tui_check_box,
    int x_mouse,
    int y_mouse,
    wchar_t check_sign,
    bool mouse_click
);
