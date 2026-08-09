// ============================================================================
// Copyright (c) 2026 Brunohudley. All rights reserved.
//
// This code is free software: you can redistribute it and/or modify it 
// under the terms of the MIT License. The above copyright notice must be 
// included in all copies or substantial portions of the software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
// ============================================================================

#include "../include/tui_widgets.h"
#include "../include/tui_buffer.h"
#include "../include/tui_window.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>


void tui_create_window(
    screen_buffer_t* screen_buffer,
    tui_window_t* tui_window
)
{
    if(!tui_window->is_active)
    {
        return;
    }

    for(
        int y_pos = tui_window->min_y_coord;
        y_pos <= tui_window->max_y_coord;
        y_pos++
    )
    {
        for(
            int x_pos = tui_window->min_x_coord;
            x_pos <= tui_window->max_x_coord;
            x_pos++
        )
        {
            if(
                x_pos == tui_window->min_x_coord ||
                x_pos == tui_window->max_x_coord
            )
            {
                set_buffer_cell(
                    screen_buffer,
                    x_pos,
                    y_pos,
                    tui_window->tui_window_fill.outside_fg,
                    tui_window->tui_window_fill.outside_bg,
                    tui_window->vertical_arrow
                );
            }
            else
            {
                set_buffer_cell(
                    screen_buffer,
                    x_pos,
                    y_pos,
                    tui_window->tui_window_fill.inside_fg,
                    tui_window->tui_window_fill.inside_bg,
                    L' '
                );
            }
        }
    }


    for(
        int x_pos = tui_window->min_x_coord + 1;
        x_pos < tui_window->max_x_coord;
        x_pos++
    )
    {
        set_buffer_cell(
            screen_buffer,
            x_pos,
            tui_window->min_y_coord,
            tui_window->tui_window_fill.inside_fg,
            tui_window->tui_window_fill.inside_bg,
            tui_window->horizontal_arrow
        );

        set_buffer_cell(
            screen_buffer,
            x_pos,
            tui_window->max_y_coord,
            tui_window->tui_window_fill.inside_fg,
            tui_window->tui_window_fill.inside_bg,
            tui_window->horizontal_arrow
        );
    }


    if(
        tui_window->container_tittle.title != NULL &&
        tui_window->container_tittle.title[0] != L'\0'
    )
    {
        int start_x =
            tui_window->min_x_coord +
            tui_window->container_tittle.title_padding;

        int title_length =
            (int)wcslen(tui_window->container_tittle.title);

        if(start_x + title_length <= tui_window->max_x_coord)
        {
            set_string_buffer_cell(
                screen_buffer,
                start_x,
                tui_window->min_y_coord,
                tui_window->tui_window_fill.inside_fg,
                tui_window->tui_window_fill.inside_bg,
                tui_window->container_tittle.title
            );
        }
    }


    if(tui_window->has_shadow)
    {
        int shadow_x = tui_window->max_x_coord + 1;

        for(
            int y_pos = tui_window->min_y_coord + 1;
            y_pos <= tui_window->max_y_coord + 1;
            y_pos++
        )
        {
            set_buffer_cell(
                screen_buffer,
                shadow_x,
                y_pos,
                tui_window->window_shadow.fg_color,
                tui_window->window_shadow.bg_color,
                tui_window->window_shadow.ch
            );
        }

        int shadow_y = tui_window->max_y_coord + 1;

        for(
            int x_pos = tui_window->min_x_coord + 1;
            x_pos <= tui_window->max_x_coord;
            x_pos++
        )
        {
            set_buffer_cell(
                screen_buffer,
                x_pos,
                shadow_y,
                tui_window->window_shadow.fg_color,
                tui_window->window_shadow.bg_color,
                tui_window->window_shadow.ch
            );
        }
    }
}


void tui_create_button(
    screen_buffer_t* screen_buffer,
    tui_button_t* tui_button
)
{
    if(tui_button->is_active == false)
    {
        return;
    }

    for(
        int y_pos = tui_button->min_y_coord;
        y_pos <= tui_button->max_y_coord;
        y_pos++
    )
    {
        for(
            int x_pos = tui_button->min_x_coord;
            x_pos <= tui_button->max_x_coord;
            x_pos++
        )
        {
            set_buffer_cell(
                screen_buffer,
                x_pos,
                y_pos,
                tui_button->tui_button_fill.outside_fg,
                tui_button->tui_button_fill.outside_bg,
                L' '
            );
        }
    }


    int button_width =
        (tui_button->max_x_coord - tui_button->min_x_coord) + 1;

    int button_height =
        (tui_button->max_y_coord - tui_button->min_y_coord) + 1;

    int string_offset = (int)wcslen(tui_button->label);

    if(string_offset > button_width)
    {
        return;
    }

    int x_index =
        tui_button->min_x_coord +
        ((button_width - string_offset) / 2);

    int y_index =
        tui_button->min_y_coord +
        (button_height / 2);

    set_string_buffer_cell(
        screen_buffer,
        x_index,
        y_index,
        tui_button->tui_button_fill.inside_fg,
        tui_button->tui_button_fill.inside_bg,
        tui_button->label
    );


    if(tui_button->has_shadow)
    {
        int shadow_x = tui_button->max_x_coord + 1;

        for(
            int y_pos = tui_button->min_y_coord + 1;
            y_pos <= tui_button->max_y_coord + 1;
            y_pos++
        )
        {
            set_buffer_cell(
                screen_buffer,
                shadow_x,
                y_pos,
                tui_button->tui_shadow.fg_color,
                tui_button->tui_shadow.bg_color,
                tui_button->tui_shadow.ch
            );
        }

        int shadow_y = tui_button->max_y_coord + 1;

        for(
            int x_pos = tui_button->min_x_coord + 1;
            x_pos <= tui_button->max_x_coord;
            x_pos++
        )
        {
            set_buffer_cell(
                screen_buffer,
                x_pos,
                shadow_y,
                tui_button->tui_shadow.fg_color,
                tui_button->tui_shadow.bg_color,
                tui_button->tui_shadow.ch
            );
        }
    }
}


void tui_create_check_box(
    screen_buffer_t* screen_buffer,
    tui_check_box_t* tui_check_box
)
{
    if(tui_check_box->is_active == false)
    {
        return;
    }

    wchar_t string_result[128];

    if(tui_check_box->check_box_ch == L'\0')
    {
        tui_check_box->check_box_ch = L' ';
    }

    _snwprintf_s(
        string_result,
        128,
        _TRUNCATE,
        L"(%lc)%ls",
        tui_check_box->check_box_ch,
        tui_check_box->label
    );

    int width =
        (tui_check_box->max_x_coord -
         tui_check_box->min_x_coord) + 1;

    int height =
        (tui_check_box->max_y_coord -
         tui_check_box->min_y_coord) + 1;

    int string_offset = (int)wcslen(string_result);

    if(string_offset > width)
    {
        return;
    }

    int x_index =
        tui_check_box->min_x_coord +
        ((width - string_offset) / 2);

    int y_index =
        tui_check_box->min_y_coord +
        (height / 2);

    set_string_buffer_cell(
        screen_buffer,
        x_index,
        y_index,
        tui_check_box->fg_color,
        tui_check_box->bg_color,
        string_result
    );
}


void tui_create_input_box(
    screen_buffer_t* screen_buffer,
    tui_input_box_t* tui_input_box
)
{
    if(tui_input_box->is_active == false)
    {
        return;
    }

    for(
        int y_pos = tui_input_box->min_y_coord;
        y_pos <= tui_input_box->max_y_coord;
        y_pos++
    )
    {
        for(
            int x_pos = tui_input_box->min_x_coord;
            x_pos <= tui_input_box->max_x_coord;
            x_pos++
        )
        {
            set_buffer_cell(
                screen_buffer,
                x_pos,
                y_pos,
                tui_input_box->tui_input_fill.outside_fg,
                tui_input_box->tui_input_fill.outside_bg,
                L' '
            );
        }
    }


    int input_width =
        (tui_input_box->max_x_coord -
         tui_input_box->min_x_coord) + 1;

    int input_height =
        (tui_input_box->max_y_coord -
         tui_input_box->min_y_coord) + 1;

    int y_index =
        tui_input_box->min_y_coord +
        (input_height / 2);

    int x_start =
        tui_input_box->min_x_coord + 1;


    if(
        tui_input_box->text_length == 0 &&
        tui_input_box->placeholder != NULL
    )
    {
        set_string_buffer_cell(
            screen_buffer,
            x_start,
            y_index,
            tui_input_box->tui_input_fill.inside_fg,
            tui_input_box->tui_input_fill.inside_bg,
            tui_input_box->placeholder
        );
    }
    else if(tui_input_box->text != NULL)
    {
        set_string_buffer_cell(
            screen_buffer,
            x_start,
            y_index,
            tui_input_box->tui_input_fill.inside_fg,
            tui_input_box->tui_input_fill.inside_bg,
            tui_input_box->text
        );
    }
}
