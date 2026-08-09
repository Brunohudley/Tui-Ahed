#include "../include/tui_input.h"
#include "../include/tui_widgets.h"
#include "../include/tui_utils.h"

#include <windows.h>
#include <stdlib.h>


void get_input_box_event(
    tui_input_box_t* tui_input_box,
    int x_mouse,
    int y_mouse,
    bool mouse_click
)
{
    if(
        mouse_click == true &&
        x_mouse >= tui_input_box->min_x_coord &&
        x_mouse <= tui_input_box->max_x_coord &&
        y_mouse >= tui_input_box->min_y_coord &&
        y_mouse <= tui_input_box->max_y_coord
    )
    {
        tui_input_box->is_focused = true;
    }
    else if(mouse_click)
    {
        tui_input_box->is_focused = false;
    }


    if(tui_input_box->is_focused)
    {
        wchar_t temp_ch = tui_get_input();

        if(temp_ch == 0)
        {
            return;
        }


        if(
            temp_ch == 8 ||
            temp_ch == VK_BACK
        )
        {
            if(tui_input_box->text_length > 0)
            {
                tui_input_box->text_length--;

                tui_input_box->text[
                    tui_input_box->text_length
                ] = L'\0';
            }

            return;
        }


        if(
            tui_input_box->text_length + 1 >=
            tui_input_box->max_characters
        )
        {
            tui_input_box->max_characters *= 2;

            wchar_t* temp_string =
                (wchar_t*)realloc(
                    tui_input_box->text,
                    tui_input_box->max_characters *
                    sizeof(wchar_t)
                );

            if(temp_string == NULL)
            {
                return;
            }

            tui_input_box->text = temp_string;
        }


        tui_input_box->text[
            tui_input_box->text_length
        ] = temp_ch;

        tui_input_box->text_length++;

        tui_input_box->text[
            tui_input_box->text_length
        ] = L'\0';
    }
}
