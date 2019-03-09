
//  gui_checkbox.c
//  gui_checkbox
//
//  Created by Andrew Macfarlane on 23/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_checkbox_h_
#define gui_checkbox_h_

#include "../base/gui_component.h"
//#include <stdbool.h>

GuiComponent* gui_checkbox_create(const char* label, bool* data);

#endif
