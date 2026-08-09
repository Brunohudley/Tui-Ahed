#include "../include/tui_buffer.h"
#include "../include/tui_utils.h"

#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>


screen_buffer_t* create_screen_buffer(
    int width,
    int height
)
{
    screen_buffer_t* screen_buffer =
        malloc(sizeof(screen_buffer_t));

    if(screen_buffer == NULL)
    {
        return NULL;
    }

    screen_buffer->front_screen_cell = NULL;
    screen_buffer->back_screen_cell = NULL;

    screen_buffer->width = width;
    screen_buffer->height = height;

    screen_buffer->front_screen_cell =
        malloc(
            width *
            height *
            sizeof(screen_cell_t)
        );

    screen_buffer->back_screen_cell =
        malloc(
            width *
            height *
            sizeof(screen_cell_t)
        );


    if(
        screen_buffer->front_screen_cell == NULL ||
        screen_buffer->back_screen_cell == NULL
    )
    {
        free(screen_buffer->front_screen_cell);
        free(screen_buffer->back_screen_cell);
        free(screen_buffer);

        return NULL;
    }


    for(
        int i = 0;
        i < width * height;
        i++
    )
    {
        screen_buffer->front_screen_cell[i] =
            (screen_cell_t){L'\0',0,0};

        screen_buffer->back_screen_cell[i] =
            (screen_cell_t){L' ',7,0};
    }


    return screen_buffer;
}


void destroy_screen_buffer(
    screen_buffer_t* screen_buffer
)
{
    if(screen_buffer == NULL)
    {
        return;
    }

    free(screen_buffer->back_screen_cell);
    free(screen_buffer->front_screen_cell);
    free(screen_buffer);
}


void set_buffer_cell(
    screen_buffer_t* screen_buffer,
    int width,
    int height,
    int fg,
    int bg,
    wchar_t ch
)
{
    if(
        width >= 0 &&
        width < screen_buffer->width &&
        height >= 0 &&
        height < screen_buffer->height
    )
    {
        int index =
            height * screen_buffer->width +
            width;

        screen_buffer->back_screen_cell[index].ch = ch;
        screen_buffer->back_screen_cell[index].fg_color = fg;
        screen_buffer->back_screen_cell[index].bg_color = bg;
    }
}


int resize_screen_buffer(
    screen_buffer_t* screen_buffer,
    int new_width,
    int new_height
)
{
    if(screen_buffer == NULL)
    {
        return -1;
    }

    if(new_width <= 0 || new_height <= 0)
    {
        return -1;
    }


    int old_width = screen_buffer->width;
    int old_height = screen_buffer->height;


    size_t new_array_size =
        new_width *
        new_height *
        sizeof(screen_cell_t);


    screen_cell_t* new_front_buffer =
        malloc(new_array_size);

    screen_cell_t* new_back_buffer =
        malloc(new_array_size);


    if(
        new_front_buffer == NULL ||
        new_back_buffer == NULL
    )
    {
        free(new_front_buffer);
        free(new_back_buffer);

        return -1;
    }


    for(
        int y_pointer = 0;
        y_pointer < new_height;
        y_pointer++
    )
    {
        for(
            int x_pointer = 0;
            x_pointer < new_width;
            x_pointer++
        )
        {
            int new_index =
                y_pointer * new_width +
                x_pointer;


            if(
                x_pointer < old_width &&
                y_pointer < old_height
            )
            {
                int old_index =
                    y_pointer * old_width +
                    x_pointer;


                new_front_buffer[new_index] =
                    screen_buffer->front_screen_cell[old_index];

                new_back_buffer[new_index] =
                    screen_buffer->back_screen_cell[old_index];
            }
            else
            {
                new_front_buffer[new_index] =
                    (screen_cell_t){L'\0',0,0};

                new_back_buffer[new_index] =
                    (screen_cell_t){L' ',7,0};
            }
        }
    }


    free(screen_buffer->front_screen_cell);
    free(screen_buffer->back_screen_cell);


    screen_buffer->front_screen_cell =
        new_front_buffer;

    screen_buffer->back_screen_cell =
        new_back_buffer;


    screen_buffer->width = new_width;
    screen_buffer->height = new_height;


    return 0;
}


void tui_render_buffer(
    screen_buffer_t* screen_buffer
)
{
    int changes = 0;


    for(
        int y_pos = 0;
        y_pos < screen_buffer->height;
        y_pos++
    )
    {
        for(
            int x_pos = 0;
            x_pos < screen_buffer->width;
            x_pos++
        )
        {
            int index =
                y_pos * screen_buffer->width +
                x_pos;


            if(
                screen_buffer->back_screen_cell[index].ch !=
                screen_buffer->front_screen_cell[index].ch ||

                screen_buffer->back_screen_cell[index].fg_color !=
                screen_buffer->front_screen_cell[index].fg_color ||

                screen_buffer->back_screen_cell[index].bg_color !=
                screen_buffer->front_screen_cell[index].bg_color
            )
            {
                set_cursor_pos(
                    x_pos,
                    y_pos
                );


                int text_attribute =
                    (screen_buffer->back_screen_cell[index].bg_color << 4) |
                    screen_buffer->back_screen_cell[index].fg_color;


                SetConsoleTextAttribute(
                    GetStdHandle(STD_OUTPUT_HANDLE),
                    text_attribute
                );


                WriteConsoleW(
                    GetStdHandle(STD_OUTPUT_HANDLE),
                    &(screen_buffer->back_screen_cell[index].ch),
                    1,
                    NULL,
                    NULL
                );


                screen_buffer->front_screen_cell[index] =
                    screen_buffer->back_screen_cell[index];

                changes++;
            }
        }
    }


    if(changes > 0)
    {
        fflush(stdout);
    }
}


void fill_screen_buffer(
    screen_buffer_t* screen_buffer,
    int fg,
    int bg,
    wchar_t new_ch
)
{
    for(
        int y_pointer = 0;
        y_pointer < screen_buffer->height;
        y_pointer++
    )
    {
        for(
            int x_pointer = 0;
            x_pointer < screen_buffer->width;
            x_pointer++
        )
        {
            int index =
                y_pointer * screen_buffer->width +
                x_pointer;

            screen_buffer->back_screen_cell[index].ch =
                new_ch;

            screen_buffer->back_screen_cell[index].fg_color =
                fg;

            screen_buffer->back_screen_cell[index].bg_color =
                bg;
        }
    }
}


void copy_screen_buffer(
    screen_buffer_t* source_buffer,
    screen_buffer_t* destine_buffer
)
{
    if(source_buffer == NULL || destine_buffer == NULL)
    {
        return;
    }

    if(
        source_buffer->width != destine_buffer->width ||
        source_buffer->height != destine_buffer->height
    )
    {
        return;
    }


    for(
        int y_pointer = 0;
        y_pointer < source_buffer->height;
        y_pointer++
    )
    {
        for(
            int x_pointer = 0;
            x_pointer < source_buffer->width;
            x_pointer++
        )
        {
            int index =
                y_pointer * source_buffer->width +
                x_pointer;


            destine_buffer->back_screen_cell[index].ch =
                source_buffer->back_screen_cell[index].ch;

            destine_buffer->back_screen_cell[index].fg_color =
                source_buffer->back_screen_cell[index].fg_color;

            destine_buffer->back_screen_cell[index].bg_color =
                source_buffer->back_screen_cell[index].bg_color;
        }
    }
}


void set_string_buffer_cell(
    screen_buffer_t* screen_buffer,
    int width,
    int height,
    int fg,
    int bg,
    wchar_t* str
)
{
    if(
        width < 0 ||
        width >= screen_buffer->width ||
        height < 0 ||
        height >= screen_buffer->height
    )
    {
        return;
    }


    if(str == NULL)
    {
        return;
    }


    for(
        int i = 0;
        str[i] != L'\0';
        i++
    )
    {
        int current_x =
            width + i;


        if(current_x >= screen_buffer->width)
        {
            break;
        }


        int index =
            (height * screen_buffer->width) +
            current_x;


        screen_buffer->back_screen_cell[index].ch =
            str[i];

        screen_buffer->back_screen_cell[index].fg_color =
            fg;

        screen_buffer->back_screen_cell[index].bg_color =
            bg;
    }
}
