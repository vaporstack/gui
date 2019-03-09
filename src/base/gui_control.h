//
//  gui_control.h
//  sun
//
//  Created by vs on 12/28/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef gui_control_h
#define gui_control_h

#include <stdio.h>

#include "g_gui.h"

int gui_handle_mouse_down(Gui* gui, int x, int y);
int gui_handle_mouse_move(Gui* gui, int x, int y);
int gui_handle_mouse_drag(Gui* gui, int x, int y);
int gui_handle_mouse_up(Gui* gui, int x, int y);

int gui_handle_touch_down(Gui* gui, int x, int y);
int gui_handle_touch_move(Gui* gui, int x, int y);
int gui_handle_touch_drag(Gui* gui, int x, int y);
int gui_handle_touch_up(Gui* gui, int x, int y);

int gui_handle_key(Gui* gui, int, int, int, int);

#endif /* gui_control_h */
