#include "../include/tui_button.h"
#include "../include/tui_widgets.h"


bool tui_button_click(
    tui_button_t* tui_button,
    int x_mouse,
    int y_mouse,
    bool mouse_click
)
{
    if(
        x_mouse >= tui_button->min_x_coord &&
        x_mouse <= tui_button->max_x_coord &&
        y_mouse >= tui_button->min_y_coord &&
        y_mouse <= tui_button->max_y_coord &&
        mouse_click == true
    )
    {
        return true;
    }

    return false;
}
