# Tui-Ahed
A minimalist TUI modeled after the classic MS-DOS aesthetic. Built with simple components, it grants developers complete control and a high degree of customization.

## Features

- Screen buffers
- Windows
- Buttons
- Check boxes
- Input boxes
- Mouse input
- Unicode / `wchar_t` support
- Custom callbacks

## Project Structure

```text
tui/
├── include/
│   ├── tui.h
│   └── ...
├── src/
│   ├── tui.c
│   └── ...
└── examples/
    └── test.c
```

## Basic Usage

Create a screen buffer:

```c
screen_buffer_t* screen_buffer =
    create_screen_buffer(80, 30);
```

Draw widgets into it:

```c
tui_create_window(
    screen_buffer,
    &window
);

tui_create_button(
    screen_buffer,
    &button
);
```

Then render:

```c
tui_render_buffer(screen_buffer);
```

A typical loop:

```c
while(1)
{
    fill_screen_buffer(
        screen_buffer,
        0,
        1,
        L' '
    );

    tui_create_window(screen_buffer, &window);
    tui_create_button(screen_buffer, &button);
    tui_create_check_box(screen_buffer, &check_box);
    tui_create_input_box(screen_buffer, &input_box);

    tui_render_buffer(screen_buffer);

    /* handle events */
}
```

---

# Widgets

## Window

```c
tui_container_tittle_t title =
{
    2,
    L"Settings"
};

tui_window_fill_t fill =
{
    15, 1,
    7, 1
};

tui_container_shadow_t shadow =
{
    0, 0,
    L'#'
};

tui_window_t window = {0};

window.min_x_coord = 5;
window.min_y_coord = 3;

window.max_x_coord = 45;
window.max_y_coord = 25;

window.vertical_arrow = L'|';
window.horizontal_arrow = L'-';

window.window_shadow = shadow;
window.container_tittle = title;
window.tui_window_fill = fill;

window.has_shadow = true;
window.is_active = true;
```

Draw:

```c
tui_create_window(
    screen_buffer,
    &window
);
```

The title is drawn **inside the top border**:

```text
+-- Settings ----------------+
|                            |
|                            |
+----------------------------+
```

---

## Button

```c
tui_button_t button = {0};

button.min_x_coord = 10;
button.min_y_coord = 18;

button.max_x_coord = 25;
button.max_y_coord = 21;

button.label = L"Quit";

button.tui_shadow = shadow;
button.tui_button_fill = fill;

button.has_shadow = true;
button.is_active = true;
```

Draw:

```c
tui_create_button(
    screen_buffer,
    &button
);
```

---

## Check Box

```c
tui_check_box_t check_box = {0};

check_box.min_x_coord = 10;
check_box.min_y_coord = 8;

check_box.max_x_coord = 35;
check_box.max_y_coord = 10;

check_box.fg_color = 15;
check_box.bg_color = 1;

check_box.check_box_ch = L' ';
check_box.label = L"Enable feature";

check_box.is_active = true;
```

Draw:

```c
tui_create_check_box(
    screen_buffer,
    &check_box
);
```

---

## Input Box

```c
tui_input_box_t input_box = {0};

input_box.min_x_coord = 10;
input_box.min_y_coord = 12;

input_box.max_x_coord = 35;
input_box.max_y_coord = 15;

input_box.tui_input_fill = fill;

input_box.max_characters = 64;

input_box.text =
    malloc(
        input_box.max_characters *
        sizeof(wchar_t)
    );

input_box.text[0] = L'\0';
input_box.text_length = 0;

input_box.placeholder =
    L"Type something...";

input_box.placeholder_fg = 8;

input_box.is_focused = false;
input_box.is_active = true;
```

Draw:

```c
tui_create_input_box(
    screen_buffer,
    &input_box
);
```

---

# Callbacks

Buttons can use callbacks:

```c
bool on_click(
    tui_button_t* button,
    int x_mouse,
    int y_mouse,
    bool mouse_click
)
{
    if(mouse_click)
    {
        return true;
    }

    return false;
}
```

Assign:

```c
button.on_click = on_click;
```

---

# Mouse

```c
int mouse_x;
int mouse_y;
bool mouse_click;

tui_get_mouse_state(
    &mouse_x,
    &mouse_y,
    &mouse_click
);
```

---

# Console Setup

Before starting:

```c
DWORD console_mode = 0;

tui_set_raw_mode(
    &console_mode
);
```

Before exiting:

```c
tui_unset_raw_mode(
    console_mode
);
```

---

# Memory

Destroy buffers when finished:

```c
destroy_screen_buffer(
    screen_buffer
);
```

Input text allocated with `malloc()` must also be freed:

```c
free(input_box.text);
```

---

# API

### Buffer

```c
create_screen_buffer()
destroy_screen_buffer()
set_buffer_cell()
set_string_buffer_cell()
fill_screen_buffer()
tui_render_buffer()
```

### Widgets

```c
tui_create_window()
tui_create_button()
tui_create_check_box()
tui_create_input_box()
```

### Input

```c
tui_get_mouse_state()
get_input_box_event()
```

---

# Design

TUI gives the application direct control over its widgets.

You create and configure the structs yourself:

```c
tui_window_t window = {0};
tui_button_t button = {0};
```

Then draw them into a screen buffer.

There is no global widget manager.

This keeps the API simple and flexible.
