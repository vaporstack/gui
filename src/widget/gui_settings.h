
//  gui_settings.c
//  gui_settings
//
//  Created by Andrew Macfarlane on 29/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef gui_settings_h_
#define gui_settings_h_

#include "../base/gui_component.h"

enum
{
	GUI_SETTINGS_TYPE_NONE,
	GUI_SETTINGS_TYPE_LONG,
	GUI_SETTINGS_TYPE_FLOAT,
	GUI_SETTINGS_TYPE_STRING
};

typedef struct GSettings
{
	int foo;
} GSettings;

GuiComponent* gui_settings_create(void* gui);
void	  gui_settings_destroy(GuiComponent* cmp);

#endif
