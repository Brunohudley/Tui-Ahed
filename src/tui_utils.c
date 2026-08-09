// ============================================================================
// Copyright (c) 2026 Brunohudley. All rights reserved.
//
// This code is free software: you can redistribute it and/or modify it 
// under the terms of the MIT License. The above copyright notice must be 
// included in all copies or substantial portions of the software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
// ============================================================================

#include <windows.h>
#include <stdlib.h>
#include <wchar.h>

#include "../include/tui_utils.h"


void clear_screen()
{
    HANDLE handle_stdout =
        GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD mode = 0;

    GetConsoleMode(handle_stdout,&mode);

    SetConsoleMode(
        handle_stdout,
        mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING
    );

    DWORD written = 0;

    PCWSTR sequence = L"\x1b[2J\x1b[3J";

    WriteConsoleW(
        handle_stdout,
        sequence,
        (DWORD)wcslen(sequence),
        &written,
        NULL
    );
}


void set_cursor_pos(int x_pos, int y_pos)
{
    HANDLE handle_stdout =
        GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos = {
        (SHORT)x_pos,
        (SHORT)y_pos
    };

    SetConsoleCursorPosition(
        handle_stdout,
        pos
    );
}


void tui_get_mouse_state(
    int* x_pos,
    int* y_pos,
    bool* mouse_click
)
{
    HANDLE stdin_handle =
        GetStdHandle(STD_INPUT_HANDLE);

    if(stdin_handle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    *mouse_click = false;

    DWORD prev_mode;

    GetConsoleMode(
        stdin_handle,
        &prev_mode
    );

    SetConsoleMode(
        stdin_handle,
        prev_mode |
        ENABLE_MOUSE_INPUT |
        ENABLE_EXTENDED_FLAGS
    );

    INPUT_RECORD input_record;

    DWORD event_read;

    ReadConsoleInput(
        stdin_handle,
        &input_record,
        1,
        &event_read
    );

    if(input_record.EventType == MOUSE_EVENT)
    {
        MOUSE_EVENT_RECORD mouse_event =
            input_record.Event.MouseEvent;

        *x_pos =
            mouse_event.dwMousePosition.X;

        *y_pos =
            mouse_event.dwMousePosition.Y;

        if(
            mouse_event.dwButtonState &
            FROM_LEFT_1ST_BUTTON_PRESSED
        )
        {
            *mouse_click = true;
        }
    }

    SetConsoleMode(
        stdin_handle,
        prev_mode
    );
}


void tui_set_raw_mode(DWORD* console_mode)
{
    HANDLE stdin_handle =
        GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;

    if(
        !GetConsoleMode(
            stdin_handle,
            &mode
        )
    )
    {
        return;
    }

    *console_mode = mode;

    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_EXTENDED_FLAGS;

    SetConsoleMode(
        stdin_handle,
        mode
    );
}


void tui_unset_raw_mode(DWORD console_mode)
{
    HANDLE stdin_handle =
        GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(
        stdin_handle,
        console_mode
    );
}


wchar_t tui_get_input()
{
    HANDLE stdin_handle =
        GetStdHandle(STD_INPUT_HANDLE);

    INPUT_RECORD ir;

    DWORD read;

    while(1)
    {
        ReadConsoleInputW(
            stdin_handle,
            &ir,
            1,
            &read
        );

        if(
            ir.EventType == KEY_EVENT &&
            ir.Event.KeyEvent.bKeyDown
        )
        {
            WORD vk =
                ir.Event.KeyEvent.wVirtualKeyCode;

            if(
                ir.Event.KeyEvent.uChar.UnicodeChar != 0
            )
            {
                return ir.Event.KeyEvent.uChar.UnicodeChar;
            }

            return (wchar_t)vk;
        }
    }
}
