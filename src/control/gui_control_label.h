
//  gui_label.c
//  gui_label
//
//  Created by Andrew Macfarlane on 04/08/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_label_h_
#define gui_label_h_

#include "../base/g_gui.h"
#include "../base/gui_component.h"
typedef struct GLabel
{
	char* text;
	char* localtext;
	bool vertical;
} GLabel;

GuiComponent* gui_control_label_create(Gui* gui, const char* label);

#endif
