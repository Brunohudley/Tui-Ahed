// ============================================================================
// Copyright (c) 2026 Brunohudley. All rights reserved.
//
// This code is free software: you can redistribute it and/or modify it 
// under the terms of the MIT License. The above copyright notice must be 
// included in all copies or substantial portions of the software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
// ============================================================================

#include "../include/tui_check_list.h"
#include "../include/tui_widgets.h"


void tui_check_list_click(
    tui_check_box_t* tui_check_box,
    int x_mouse,
    int y_mouse,
    wchar_t check_sign,
    bool mouse_click
)
{
    if(
        x_mouse >= tui_check_box->min_x_coord &&
        x_mouse <= tui_check_box->max_x_coord &&
        y_mouse >= tui_check_box->min_y_coord &&
        y_mouse <= tui_check_box->max_y_coord &&
        mouse_click == true
    )
    {
        tui_check_box->check_box_ch = check_sign;
    }
}
