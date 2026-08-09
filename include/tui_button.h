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


typedef struct tui_button tui_button_t;


bool tui_button_click(
    tui_button_t* tui_button,
    int x_mouse,
    int y_mouse,
    bool mouse_click
);
